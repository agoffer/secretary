//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "requestDM.h"
#include "dataSourceDM.h"
#include "personCtrl.h"
#include "clubCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmRequestDAO *dmRequestDAO;
//---------------------------------------------------------------------------
__fastcall TdmRequestDAO::TdmRequestDAO(TComponent* Owner)
    : TDataModule(Owner)
{

}
//---------------------------------------------------------------------------


void TdmRequestDAO::initRequestTable(void){
    if(ibqRequestAll->Active){
        ibqRequestAll->Close();
        }
    ibqRequestAll->SQL->Clear();
    ibqRequestAll->SQL->Add("select * from Request");
}

void TdmRequestDAO::deleteById(int requestId){
    String deleteQuery = "delete from Request where id = :id";
    ibqRequest->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    ibqRequest->SQL->Add(deleteQuery);
    ibqRequest->ParamByName("id")->AsInteger = requestId;        
    //выполнить запрос
    ibqRequest->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Запомнить в базе
        dmDataSource->ibtrSecretaryDB->Commit();
        }

}



void TdmRequestDAO::store(TRequest &obj){
AnsiString updateQuery =
"update Request set competitionId = :competitionId,\
 clubId = :clubId, personId = :personId, comments = :comments\
 where id = :id";
AnsiString insertQuery =
"insert into Request(competitionId, clubId, personId, comments)\
 values(:competitionId, :clubId, :personId, :comments)";
AnsiString searchIdQuery =
"select id from Request where competitionId=:competitionId and clubId=:clubId and \
 personId=:personId and comments=:comments";
    //Создать запрос для сохранения объекта в базе данных
    ibqRequest->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    if(obj.getId() > 0){
        //Обновить
    //выполнить запрос
    ibqRequest->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Запомнить в базе
        dmDataSource->ibtrSecretaryDB->Commit();
        }

        ibqRequest->ParamByName("id")->AsInteger = obj.getId();
        }
    else{
        //Добавить
        ibqRequest->SQL->Add(insertQuery);
        }
    ibqRequest->ParamByName("competitionId")->AsInteger = obj.getCompetitionId();
    ibqRequest->ParamByName("clubId")->AsInteger = obj.getClubId();
    ibqRequest->ParamByName("personId")->AsInteger = obj.getPersonId();
    ibqRequest->ParamByName("comments")->AsString = obj.getComments();
    //выполнить запрос
    ibqRequest->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Запомнить в базе
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //Если была добавлена новая запись, узнать ее идентификатор
    if(!obj.getId()){
        //Получить из таблицы последнюю добавленную запись
        ibqRequest->SQL->Clear();
        ibqRequest->SQL->Add(searchIdQuery);                
        ibqRequest->ParamByName("competitionId")->AsInteger = obj.getCompetitionId();
        ibqRequest->ParamByName("clubId")->AsInteger = obj.getClubId();
        ibqRequest->ParamByName("personId")->AsInteger = obj.getPersonId();
        ibqRequest->ParamByName("comments")->AsString = obj.getComments();
        ibqRequest->Open();
        obj.setId(ibqRequest->FieldByName("id")->AsInteger);
        ibqRequest->Close();
        }
}


TRequest TdmRequestDAO::getCurrent(void){
//Возвращаемый объект
TRequest result;
    result.setId(0);    //изначально запись не получена
    //Если таблица открыта, получить текущий объект
    if(ibqRequestAll->State != dsInactive){
        result.setId(ibqRequestAll->FieldByName("id")->AsInteger);
        result.setCompetitionId(ibqRequestAll->FieldByName("competitionId")->AsInteger);
        result.setClubId(ibqRequestAll->FieldByName("clubId")->AsInteger);
        result.setPersonId(ibqRequestAll->FieldByName("personId")->AsInteger);
        result.setComments(ibqRequestAll->FieldByName("comments")->AsString);
        }
    //Вернуть результат
    return result;
}

void TdmRequestDAO::makeCurrent(TRequest obj){
int res;
    if(ibqRequestAll->Active){
        //Если передан не пустой объект
        if(obj.getId() > 0){
            ibqRequestAll->Locate("id", obj.getId(), TLocateOptions());
            }
        }
}




TList * TdmRequestDAO::getByCompetitionId(int competitionId){
AnsiString selectQuery =
"select id, clubId, personId,comments\
 from Request where competitionId=:competitionId";
    //Создать запрос для получения объектов из базы
    ibqRequest->SQL->Clear();
    ibqRequest->SQL->Add(selectQuery);
    //Указать соревнование
    ibqRequest->ParamByName("competitionId")->AsInteger; 
    //Получить записи из базы данных
    ibqRequest->Open();

        //Создаем объекты по количеству полученных из базы данных
        TList* resultList = new TList();
        resultList->Clear(); 
        ibqRequest->First();
        for(int i = 0; i < ibqRequest->RecordCount; i++){
            TRequest * result = new TRequest(); 
            result->setId(ibqRequest->FieldByName("id")->AsInteger);
            result->setClubId(ibqRequest->FieldByName("clubId")->AsInteger);
            result->setPersonId(ibqRequest->FieldByName("personId")->AsInteger);
            result->setComments(ibqRequest->FieldByName("comments")->AsString);
            result->setCompetitionId(competitionId);
            //Добавить в список
            resultList->Add(result); 
            //Перейдем к следующей записи
            ibqRequest->Next();
            }
        //Закроем множество
        ibqRequest->Close();
        //вернем результирующее множество
        return resultList;

}




TList * TdmRequestDAO::getExtendedByCompetitionId(int competitionId){
AnsiString selectQuery =
"select \
       Club.id, \
       Club.name, \
       Club.shortName, \
       Club.country, \
       Club.city, \
       Club.comments, \
       Club.personId, \
       Person.id, \
       Person.surname, \
       Person.name, \
       Person.patronymic, \
       Person.dob, \
       Person.phone, \
       Person.additions, \
       Request.id, \
       Request.comments \
       from Request, Club, Person where \
       Person.id = Request.PersonId and Club.id = Request.clubId \
       and Request.competitionId = :competitionId";
    //Создать запрос для получения объектов из базы
    ibqRequest->SQL->Clear();
    ibqRequest->SQL->Add(selectQuery);
    //Указать соревнование
    ibqRequest->ParamByName("competitionId")->AsInteger = competitionId;
    //Получить записи из базы данных
    ibqRequest->Open();


        //Создаем объекты по количеству полученных из базы данных
        TList* resultList = new TList();
        resultList->Clear();
        ibqRequest->First();
        for(int i = 0; i < ibqRequest->RecordCount; i++){
            //Создать расширенные поля
            TPerson person;
            TClub club;


            person.setId(ibqRequest->FieldByName("id1")->AsInteger);
            person.setSurname(ibqRequest->FieldByName("surname")->AsString);
            person.setName(ibqRequest->FieldByName("name1")->AsString);
            person.setPatronymic(ibqRequest->FieldByName("patronymic")->AsString);
            person.setDob(ibqRequest->FieldByName("dob")->AsDateTime);
            person.setPhone(ibqRequest->FieldByName("phone")->AsString);
            person.setAdditions(ibqRequest->FieldByName("additions")->AsString);

            club.setId(ibqRequest->FieldByName("id")->AsInteger);
            club.setName(ibqRequest->FieldByName("name")->AsString);
            club.setShortName(ibqRequest->FieldByName("shortName")->AsString);
            club.setCountry(ibqRequest->FieldByName("country")->AsString);
            club.setCity(ibqRequest->FieldByName("city")->AsString);
            club.setComments(ibqRequest->FieldByName("comments")->AsString);

            TRequest * result = new TRequest();
            //Заполнить структуру
            result->setId(ibqRequest->FieldByName("id2")->AsInteger);
            result->setClubId(ibqRequest->FieldByName("id")->AsInteger);
            result->setPersonId(ibqRequest->FieldByName("id1")->AsInteger);
            result->setComments(ibqRequest->FieldByName("comments1")->AsString);
            result->setCompetitionId(competitionId);
            //Установим дополнительные поля
            result->extend(person, club);
            //Добавить в список
            resultList->Add(result);
            //Перейдем к следующей записи
            ibqRequest->Next();
            }
        //Закрыть множество
        ibqRequest->Close(); 
        //вернем результирующее множество
        return resultList;
}



//---------------------------------------------------------------------------

