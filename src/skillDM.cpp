//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dataSourceDM.h"
#include "skillDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmSkillDAO *dmSkillDAO;
//---------------------------------------------------------------------------
__fastcall TdmSkillDAO::TdmSkillDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------

void TdmSkillDAO::initSkillTable(){
    if(ibqSkillAll->Active){
        ibqSkillAll->Close(); 
        }
    ibqSkillAll->SQL->Clear();
    ibqSkillAll->SQL->Add("select * from Skill");
}

void TdmSkillDAO::store(TSkill &obj){
AnsiString updateQuery =
"update Skill set shortDescription = :shortDescription,\
 fullDescription = :fullDescription, comments = :comments\
 weight = :weight\
 where id = :id";
AnsiString insertQuery =
"insert into Skill(shortDescription, fullDescription, comments, weight) \
 values(:shortDescription, :fullDescription, :comments, :weight)";
AnsiString searchIdQuery =
"select id from Skill where shortDescription=:shortDescription and \
 fullDescription=:fullDescription and comments=:comments and \
 weight=:weight";
    //Создать запрос для сохранения объекта в базе данных
    ibqSkill->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction(); 
        }
    if(obj.getId() > 0){
        //Обновить
        ibqSkill->SQL->Add(updateQuery);
        ibqSkill->ParamByName("id")->AsInteger = obj.getId();
    }
    else{
        //Добавить
        ibqSkill->SQL->Add(insertQuery);
    }
    ibqSkill->ParamByName("shortDescription")->AsString = obj.getShortDescription();
    ibqSkill->ParamByName("fullDescription")->AsString = obj.getFullDescription();
    ibqSkill->ParamByName("comments")->AsString = obj.getComments();
    ibqSkill->ParamByName("weight")->AsInteger = obj.getWeight();
    //выполнить запрос
    ibqSkill->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Запоминть в базе
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //Если была добавлена новая запись, узнать ее идентификатор
    if(!obj.getId()){
        //Получить из таблицы последнюю добавленную запись
        ibqSkill->SQL->Clear();
        ibqSkill->SQL->Add(searchIdQuery);                
        ibqSkill->ParamByName("shortDescription")->AsString = obj.getShortDescription();
        ibqSkill->ParamByName("fullDescription")->AsString = obj.getFullDescription();
        ibqSkill->ParamByName("comments")->AsString = obj.getComments();
        ibqSkill->ParamByName("weight")->AsInteger = obj.getWeight();
        ibqSkill->Open();
        obj.setId(ibqSkill->FieldByName("id")->AsInteger);
        ibqSkill->Close();        
        }
}

TList*  TdmSkillDAO::getAll(void){
AnsiString selectQuery =
"select id, shortDescription, fullDescription, comments, weight from Skill";
    //Создать запрос для получения объектов из базы
    ibqSkill->SQL->Clear();
    ibqSkill->SQL->Add(selectQuery);
    //Получить записи из базы данных
    ibqSkill->Open();


        //Создаем объекты по количеству полученных из базы данных
        TList* resultList = new TList();
        resultList->Clear(); 
        ibqSkill->First();
        for(int i = 0; i < ibqSkill->RecordCount; i++){
            TSkill * result = new TSkill(); 
            result->setId(ibqSkill->FieldByName("id")->AsInteger);
            result->setShortDescription(ibqSkill->FieldByName("shortDescription")->AsString);
            result->setFullDescription(ibqSkill->FieldByName("fullDescription")->AsString);
            result->setComments(ibqSkill->FieldByName("comments")->AsString);
            result->setWeight(ibqSkill->FieldByName("weight")->AsInteger);

            //Добавить в список
            resultList->Add(result);
            //Перейдем к следующей записи
            ibqSkill->Next();
            }
        //Закроем множество
        ibqSkill->Close();
        //вернем результирующее множество
        return resultList;
}


void TdmSkillDAO::getById(int id, TSkill &obj){
AnsiString selectQuery =
"select shortDescription, fullDescription, comments, weight\
 from Skill where id = :id";
    //Создать запрос для получения объектов из базы
    ibqSkill->SQL->Clear();
    ibqSkill->SQL->Add(selectQuery);    
    ibqSkill->ParamByName("id")->AsInteger = id;
    //Получить записи из базы данных
    ibqSkill->Open();
    if(ibqSkill->RecordCount){
        obj.setId(id);
        obj.setShortDescription(ibqSkill->FieldByName("shortDescription")->AsString);
        obj.setFullDescription(ibqSkill->FieldByName("fullDescription")->AsString);
        obj.setComments(ibqSkill->FieldByName("comments")->AsString);
        obj.setWeight(ibqSkill->FieldByName("weight")->AsInteger);
        }
    //Записи не получены, вернуть null
    else{
        //Обнулить объект
        setmem(&obj, sizeof(obj), 0);
        }
    ibqSkill->Close(); 
}
