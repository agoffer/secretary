//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "competitionRankDM.h"
#include "dataSourceDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmCompetitionRankDAO *dmCompetitionRankDAO;
//---------------------------------------------------------------------------
__fastcall TdmCompetitionRankDAO::TdmCompetitionRankDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}

/**
TODO: Проверить, что это используется
*/
void TdmCompetitionRankDAO::store(TCompetitionRank &obj){
AnsiString updateQuery =
"update CompetitionRank set description = :description, comments = :comments\
 where id = :id";
AnsiString insertQuery =
"insert into CompetitionRank(description, comments) values(:description, :comments)";
AnsiString searchIdQuery =
"select id from CompetitionRank where description=:description and comments=:comments";
    //Создать запрос для сохранения объекта в базе данных
    ibqCompetitionRank->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    if(obj.getId() > 0){
        //Обновить
        ibqCompetitionRank->SQL->Add(updateQuery);
        ibqCompetitionRank->ParamByName("id")->AsInteger = obj.getId();
    }
    else{
        //Добавить
        ibqCompetitionRank->SQL->Add(insertQuery);
    }
    ibqCompetitionRank->ParamByName("description")->AsString = obj.getDescription();
    ibqCompetitionRank->ParamByName("comments")->AsString = obj.getComments();
    //выполнить запрос
    ibqCompetitionRank->ExecSQL();
    //Выполнить сохранение данных
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //Если была добавлена новая запись, узнать ее идентификатор
    if(!obj.getId()){
        //Получить из таблицы последнюю добавленную запись
        ibqCompetitionRank->SQL->Clear();
        ibqCompetitionRank->SQL->Add(searchIdQuery);
        ibqCompetitionRank->ParamByName("description")->AsString = obj.getDescription();
        ibqCompetitionRank->ParamByName("comments")->AsString = obj.getComments();
        ibqCompetitionRank->Open();
        obj.setId(ibqCompetitionRank->FieldByName("id")->AsInteger);
        ibqCompetitionRank->Close();
        }
}

/**
TODO: Проверить, что это используется
*/
TList*  TdmCompetitionRankDAO::getAll(void){
AnsiString selectQuery =
"select id, description, comments from CompetitionRank";
    //Создать запрос для получения объектов из базы
    ibqCompetitionRank->SQL->Clear();
    ibqCompetitionRank->SQL->Add(selectQuery);
    //Получить записи из базы данных
    ibqCompetitionRank->Open();

    //Создаем объекты по количеству полученных из базы данных
    TList* resultList = new TList();
    resultList->Clear();
    ibqCompetitionRank->First();
    for(int i = 0; i < ibqCompetitionRank->RecordCount; i++){
        TCompetitionRank * result = new TCompetitionRank();
        result->setId(ibqCompetitionRank->FieldByName("id")->AsInteger);
        result->setDescription(ibqCompetitionRank->FieldByName("description")->AsString);
        result->setComments(ibqCompetitionRank->FieldByName("comments")->AsString);
        //Добавить запись в список
        resultList->Add(result);
        //Перейдем к следующей записи
        ibqCompetitionRank->Next();
        }
    //Закроем множество
    ibqCompetitionRank->Close();
    //вернем результирующее множество
    return resultList;
}


void TdmCompetitionRankDAO::getById(int id, TCompetitionRank &obj){
AnsiString selectQuery =
"select description, comments\
 from CompetitionRank where id = :id";
    //Создать запрос для получения объектов из базы
    ibqCompetitionRank->SQL->Clear();
    ibqCompetitionRank->SQL->Add(selectQuery);
    ibqCompetitionRank->ParamByName("id")->AsInteger = id;
    //Получить записи из базы данных
    ibqCompetitionRank->Open();
    if(ibqCompetitionRank->RecordCount){
        obj.setId(id);
        obj.setDescription(ibqCompetitionRank->FieldByName("description")->AsString);
        obj.setComments(ibqCompetitionRank->FieldByName("comments")->AsString);
        }
    //Записи не получены, вернуть null
    else{
        //Обнулить объект
        setmem(&obj, sizeof(obj), 0);
        }
    ibqCompetitionRank->Close();
}


//---------------------------------------------------------------------------


/**
 * Перед вставкой записи в таблицу уровней соревонований, убрать
 обязательность поля идентификатора. Идентификатор выставляется триггером.
*/
void __fastcall TdmCompetitionRankDAO::ibtCompetitionRankBeforeInsert(
      TDataSet *DataSet)
{
    // Перед вставкой, убираем обязательность идентификатора. Его заполняет триггер
    DataSet->FieldByName("ID")->Required = false;
}
//---------------------------------------------------------------------------

void __fastcall TdmCompetitionRankDAO::ibtCompetitionRankPostError(
      TDataSet *DataSet, EDatabaseError *E, TDataAction &Action)
{
    //Отобразить сообщение об ошибке
    if (DataSet->FieldByName("DESCRIPTION")->Text.IsEmpty()) {
        E->Message = "Уровень соревнований должен быть указан!";
    }
}
//---------------------------------------------------------------------------




void __fastcall TdmCompetitionRankDAO::ibtScoreRankingBeforeInsert(
      TDataSet *DataSet)
{
    // Перед вставкой данных, убираем обязательность с поля индентификатора уровня соревнований
    DataSet->FieldByName("COMPETITIONRANKID")->Required = false;
}
//---------------------------------------------------------------------------

void __fastcall TdmCompetitionRankDAO::ibtScoreRankingAfterInsert(
      TDataSet *DataSet)
{
    // После того, как запись добавлена, проставляем индетинфикатор уровня соревнований
    DataSet->FieldByName("COMPETITIONRANKID")->AssignValue(ibtCompetitionRank->FieldByName("ID")->AsInteger);
}
//---------------------------------------------------------------------------

void __fastcall TdmCompetitionRankDAO::ibtScoreRankingBeforePost(
      TDataSet *DataSet)
{
    //Если втавляемая запись не содержит данных, отменить вставку
    if(DataSet->FieldByName("RANK")->AsInteger == NULL || DataSet->FieldByName("SCORE")->AsInteger == NULL) {
        DataSet->Cancel();
        DataSet->Edit();
    }
}
//---------------------------------------------------------------------------

void __fastcall TdmCompetitionRankDAO::ibtCompetitionRankAfterPost(
      TDataSet *DataSet)
{
    // Когда запись вставлена, сразу же закрыть транзакци. Переоткрыть таблицу и выбрать посл. запись
    if(ibtCompetitionRank->Transaction->Active) {
        ibtCompetitionRank->Transaction->Commit();
        ibtCompetitionRank->Open();
        ibtScoreRanking->Open();
        ibtCompetitionRank->Last();

    }
}
//---------------------------------------------------------------------------

