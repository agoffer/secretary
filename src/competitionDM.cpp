//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "competitionDM.h"
#include "dataSourceDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmCompetitionDAO *dmCompetitionDAO;
//---------------------------------------------------------------------------
__fastcall TdmCompetitionDAO::TdmCompetitionDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------

void TdmCompetitionDAO::initCompetitionTable(void){
    //Если таблица открыта, закрыть ее предварительно
    if(ibqCompetitionAll->Active){
        ibqCompetitionAll->Close();
        }
    ibqCompetitionAll->SQL->Clear();
    ibqCompetitionAll->SQL->Add("select * from Competition order by begindate desc");
}


void TdmCompetitionDAO::store(TCompetition &obj){
AnsiString updateQuery =
"update Competition set beginDate = :beginDate, endDate = :endDate,\
 competitionRankId = :competitionRankId, comments = :comments\
 where id = :id";
AnsiString insertQuery =
"insert into Competition(beginDate, endDate, competitionRankId, comments)\
 values(:beginDate, :endDate, :competitionRankId,:comments)";

AnsiString searchIdQuery = "select id from Competition where \
  beginDate=:beginDate and endDate=:endDate and competitionRankId=:competitionRankId \
  and comments=:comments";
    //Создать запрос ля сохранения объекта в базе данных
    ibqCompetition->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    if(obj.getId() > 0){
        //Обновить
        ibqCompetition->SQL->Add(updateQuery);
        ibqCompetition->ParamByName("id")->AsInteger = obj.getId();
    }
    else{
        //Добавить
        ibqCompetition->SQL->Add(insertQuery);
    }
    ibqCompetition->ParamByName("beginDate")->AsDate = obj.getBeginDate();
    ibqCompetition->ParamByName("endDate")->AsDate = obj.getEndDate();
    ibqCompetition->ParamByName("competitionRankId")->AsInteger = obj.getCompetitionRankId();
    ibqCompetition->ParamByName("comments")->AsString = obj.getComments();
    //выполнить запрос
    ibqCompetition->ExecSQL();
    //Выполнить сохранение данных
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //Если была добавлена новая запись, узнать ее идентификатор
    if(!obj.getId()){
        ibqCompetition->SQL->Clear();
        ibqCompetition->SQL->Add(searchIdQuery);
        //Получить из таблицы последнюю добавленную запись
        ibqCompetition->ParamByName("beginDate")->AsDate = obj.getBeginDate();
        ibqCompetition->ParamByName("endDate")->AsDate = obj.getEndDate();
        ibqCompetition->ParamByName("competitionRankId")->AsInteger = obj.getCompetitionRankId();
        ibqCompetition->ParamByName("comments")->AsString = obj.getComments();
        ibqCompetition->Open();
        obj.setId(ibqCompetition->FieldByName("id")->AsInteger);
        ibqCompetition->Close();
        }
}

TList * TdmCompetitionDAO::getAll(void){
AnsiString selectQuery =
"select id, beginDate, endDate, competitionRankId,comments\
 from Competition order by beginDate desc";
    //Создать запрос для получения объектов из базы
    ibqCompetition->SQL->Clear();
    ibqCompetition->SQL->Add(selectQuery);
    //Получить записи из базы данных
    ibqCompetition->Open();
    //Создаем объекты по количеству полученных из базы данных
    TList* resultList = new TList();
    resultList->Clear();
    ibqCompetition->First();
    for(int i = 0; i < ibqCompetition->RecordCount; i++){
        //Создать новую сущность "соревнования"
        TCompetition *result = new TCompetition();
        result->setId(ibqCompetition->FieldByName("id")->AsInteger);
        result->setBeginDate(ibqCompetition->FieldByName("beginDate")->AsDateTime);
        result->setEndDate(ibqCompetition->FieldByName("endDate")->AsDateTime);
        result->setComments(ibqCompetition->FieldByName("comments")->AsString);
        //Поместить ее в список
        resultList->Add(result);
        //Перейдем к следующей записи
        ibqCompetition->Next();
        }
    //Закрываем множество после работы
    ibqCompetition->Close();
    //вернем результирующее множество
    return resultList;
}

void TdmCompetitionDAO::getById(int id, TCompetition &obj){
AnsiString selectQuery =
"select beginDate, endDate, competitionRankId,comments\
 from Competition where id = :id";
    //Создать запрос для получения объектов из базы
    ibqCompetition->SQL->Clear();
    ibqCompetition->SQL->Add(selectQuery);
    ibqCompetition->ParamByName("id")->AsInteger = id;
    //Получить записи из базы данных
    ibqCompetition->Open();
    if(ibqCompetition->RecordCount){
        obj.setId(id);
        obj.setBeginDate(ibqCompetition->FieldByName("beginDate")->AsDateTime);
        obj.setEndDate(ibqCompetition->FieldByName("endDate")->AsDateTime);
        obj.setComments(ibqCompetition->FieldByName("comments")->AsString);
        }
    //Записи не получены, вернуть null
    else{
        //Обнулить объект
        setmem(&obj, sizeof(obj), 0);
        }
    //Закрываем множество
    ibqCompetition->Close();
}


void TdmCompetitionDAO::getMinMaxBeginDate(TDateTime &minBeginDate, TDateTime &maxBeginDate){
//Запрос на получение дат
AnsiString selectQuery = "select max(beginDate), min(beginDate) from competition";
    //Добавим запрос
    ibqCompetition->SQL->Clear();
    ibqCompetition->SQL->Add(selectQuery);
    //Выполнить запрос
    ibqCompetition->Open();

    minBeginDate = ibqCompetition->FieldByName("min")->AsDateTime;
    maxBeginDate = ibqCompetition->FieldByName("max")->AsDateTime;

    //Закрываем множество
    ibqCompetition->Close();
}


void TdmCompetitionDAO::selectRangeExtendedCompetitions(TDateTime begin, TDateTime end){
//Запрос на получение соревнований
AnsiString selectQuery=
"select  Competition.id CID, Competition.beginDate, Competition.endDate,\
 Competition.comments CCOMMENTS, Competition.CompetitionRankId, CompetitionRank.description, \
 CompetitionRank.id CRID, CompetitionRank.comments CRCOMMENTS \
 from Competition, CompetitionRank \
 where CompetitionRank.id = Competition.competitionRankId \
 and Competition.beginDate >= :beginDate and Competition.beginDate <= :endDate order by beginDate desc";

    //Закрыть запрос на получение таблицы
    if(ibqExtendedCompetitionAll->Active)
        ibqExtendedCompetitionAll->Close();

    ibqExtendedCompetitionAll->SQL->Clear();
    ibqExtendedCompetitionAll->SQL->Add(selectQuery);

    //Установить диапазон дат
    ibqExtendedCompetitionAll->ParamByName("beginDate")->AsDateTime = begin;
    ibqExtendedCompetitionAll->ParamByName("endDate")->AsDateTime = end;

    ibqExtendedCompetitionAll->Open();
}


TCompetition TdmCompetitionDAO::getExtendedCurrent(void){
//Возвращаемый объект
TCompetition result;
    result.setId(0);    //изначально запись не получена
    //Если таблица открыта, получить текущий объект
    if(ibqExtendedCompetitionAll->State != dsInactive){
        result.setId(ibqExtendedCompetitionAll->FieldByName("CID")->AsInteger);
        result.setBeginDate(ibqExtendedCompetitionAll->FieldByName("beginDate")->AsDateTime);
        result.setEndDate(ibqExtendedCompetitionAll->FieldByName("endDate")->AsDateTime);
        result.setCompetitionRankId(ibqExtendedCompetitionAll->FieldByName("competitionRankId")->AsInteger);
        result.setComments(ibqExtendedCompetitionAll->FieldByName("CCOMMENTS")->AsString);
        TCompetitionRank crresult;
        crresult.setId(ibqExtendedCompetitionAll->FieldByName("CRID")->AsInteger);
        crresult.setDescription(ibqExtendedCompetitionAll->FieldByName("description")->AsString);
        crresult.setComments(ibqExtendedCompetitionAll->FieldByName("CRCOMMENTS")->AsString);
        //Расширить
        result.extend(crresult);
        }
    //Вернуть результат
    return result;
}

/**
 * Удаляем текущую, выбранную запись.
 */
void TdmCompetitionDAO::removeCurrent() {
    //Если таблица открыта, получить текущий объект
    if(ibqExtendedCompetitionAll->State != dsInactive){
        remove(ibqExtendedCompetitionAll->FieldByName("CID")->AsInteger);
    }
}

void TdmCompetitionDAO::remove(int id) {
 AnsiString deleteQuery = "delete from COMPETITION where ID=:id";
    //Создать запрос для удаления объекта из БД
    ibqCompetition->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active) {
        dmDataSource->ibtrSecretaryDB->StartTransaction();
    }
    ibqCompetition->SQL->Add(deleteQuery);
    ibqCompetition->ParamByName("id")->AsInteger = id;
     //выполнить запрос
    ibqCompetition->ExecSQL();
    //Выполнить сохранение данных
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
    }
}
