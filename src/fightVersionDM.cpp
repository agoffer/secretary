//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fightVersionDM.h"
#include "dataSourceDM.h"
#include "fightVersionCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmFightVersionDAO *dmFightVersionDAO;
//---------------------------------------------------------------------------
__fastcall TdmFightVersionDAO::TdmFightVersionDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------


void TdmFightVersionDAO::initFightVersionTable(){
    if(ibqFightVersionAll->Active){
        ibqFightVersionAll->Close(); 
        }
    ibqFightVersionAll->SQL->Clear();
    ibqFightVersionAll->SQL->Add("select * from FightVersion"); 
}


void TdmFightVersionDAO::store(TFightVersion &obj){
AnsiString updateQuery =
"update FightVersion set code = :code, description = :description, comments = :comments\
 where id = :id";
AnsiString insertQuery =
"insert into FightVersion(code, description, comments) values(:code, :description, :comments)";
AnsiString searchIdQuery =
"select id from FightVersion where code=:code and description=:description and \
 comments=:comments";
    //Создать запрос для сохранения объекта в базе данных
    ibqFightVersion->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction(); 
        }
    if(obj.getId() > 0){
        //Обновить
        ibqFightVersion->SQL->Add(updateQuery);
        ibqFightVersion->ParamByName("id")->AsInteger = obj.getId();
    }
    else{
        //Добавить
        ibqFightVersion->SQL->Add(insertQuery);
    }
    ibqFightVersion->ParamByName("code")->AsString = obj.getCode();
    ibqFightVersion->ParamByName("description")->AsString = obj.getDescription();
    ibqFightVersion->ParamByName("comments")->AsString = obj.getComments();
    //выполнить запрос
    ibqFightVersion->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Запомнить в базе
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //Если была добавлена новая запись, узнать ее идентификатор
    if(!obj.getId()){
        //Получить из таблицы последнюю добавленную запись
        ibqFightVersion->SQL->Clear();
        ibqFightVersion->SQL->Add(searchIdQuery);                
        ibqFightVersion->ParamByName("code")->AsString = obj.getCode();
        ibqFightVersion->ParamByName("description")->AsString = obj.getDescription();
        ibqFightVersion->ParamByName("comments")->AsString = obj.getComments();
        ibqFightVersion->Open();
        obj.setId(ibqFightVersion->FieldByName("id")->AsInteger);
        ibqFightVersion->Close();
        }
}

TList*  TdmFightVersionDAO::getAll(void){
AnsiString selectQuery =
"select id, code, description, comments from FightVersion";
    //Создать запрос для получения объектов из базы
    ibqFightVersion->SQL->Clear();
    ibqFightVersion->SQL->Add(selectQuery);
    //Получить записи из базы данных
    ibqFightVersion->Open();

        //Создаем объекты по количеству полученных из базы данных
        TList* resultList = new TList();
        resultList->Clear(); 
        ibqFightVersion->First();
        for(int i = 0; i < ibqFightVersion->RecordCount; i++){
            TFightVersion * result = new TFightVersion(); 
            result->setId(ibqFightVersion->FieldByName("id")->AsInteger);
            result->setCode(ibqFightVersion->FieldByName("code")->AsString);
            result->setDescription(ibqFightVersion->FieldByName("description")->AsString);
            result->setComments(ibqFightVersion->FieldByName("comments")->AsString);
            //Добавить в список
            resultList->Add(result);
            //Перейдем к следующей записи
            ibqFightVersion->Next();
            }
        //Закрыть множестов
        ibqFightVersion->Close(); 
        //вернем результирующее множество
        return resultList;
}


void TdmFightVersionDAO::getById(int id, TFightVersion &obj){
AnsiString selectQuery =
"select code, description, comments\
 from FightVersion where id = :id";
    //Создать запрос для получения объектов из базы
    ibqFightVersion->SQL->Clear();
    ibqFightVersion->SQL->Add(selectQuery);
    ibqFightVersion->ParamByName("id")->AsInteger = id;
    //Получить записи из базы данных
    ibqFightVersion->Open();
    if(ibqFightVersion->RecordCount){
        obj.setId(id);
        obj.setCode(ibqFightVersion->FieldByName("code")->AsString);
        obj.setDescription(ibqFightVersion->FieldByName("description")->AsString);
        obj.setComments(ibqFightVersion->FieldByName("comments")->AsString);
        }
    //Записи не получены, вернуть null
    else{
        //Обнулить объект
        setmem(&obj, sizeof(obj), 0);
        }
    ibqFightVersion->Close(); 
}

