//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "availCategoryDM.h"
#include "dataSourceDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmAvailCategoryDAO *dmAvailCategoryDAO;
//---------------------------------------------------------------------------
__fastcall TdmAvailCategoryDAO::TdmAvailCategoryDAO(TComponent* Owner)
        : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------


void TdmAvailCategoryDAO::initAvailCategoryTable(){
    if(ibqAvailCategoryAll->Active){
        ibqAvailCategoryAll->Close(); 
        }
    ibqAvailCategoryAll->SQL->Clear();
    ibqAvailCategoryAll->SQL->Add("select * from AvailableCategory");
}

void TdmAvailCategoryDAO::setCategoryTable(int startAge, int endAge,
                                                double startWeight,
                                                double endWeight, bool female){
    initAvailCategoryTable();
    ibqAvailCategoryAll->SQL->Add(" where ");
    if(!female){
        ibqAvailCategoryAll->SQL->Add(" female='F'");
        }
    else{
        ibqAvailCategoryAll->SQL->Add(" female='T'");
        }
    //Проверим доступные величины и построим условие выборки
    if(startAge > 0){
        ibqAvailCategoryAll->SQL->Add(" and startage >= " + IntToStr(startAge));
        }
    if(endAge > 0){
        ibqAvailCategoryAll->SQL->Add(" and endage <= " + IntToStr(endAge));
        }
    if(startWeight > 0){
        ibqAvailCategoryAll->SQL->Add(" and startweight >= " + FloatToStr(startWeight));
        }
    if(endWeight > 0){
        ibqAvailCategoryAll->SQL->Add(" and endweight <= " + FloatToStr(endWeight));
        }

    ibqAvailCategoryAll->SQL->Add(" order by startage, startweight");
    ibqAvailCategoryAll->Open();
}


void TdmAvailCategoryDAO::store(TAvailCategory &obj){
AnsiString updateQuery =
"update AvailableCategory set startAge = :startAge, endAge = :endAge, \
 startWeight, endWeight, female = :female, comments = :comments \
 where id = :id";
AnsiString insertQuery =
"insert into AvailableCategory(startAge, endAge, startWeight, \
 endWeight, female, comments) \
 values(:startAge, :endAge, :startWeight, :endWeight, :female, :comments)";
AnsiString searchIdQuery =
"select id from AvailableCategory where startAge=:startAge and \
 endAge=:endAge and startWeight=:startWeight and endWeight=:endWeight and \
 female=:female and comments=:comments";
    //Создать запрос для сохранения объекта в базе данных
    ibqAvailCategory->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    if(obj.getId() > 0){
        //Обновить
        ibqAvailCategory->SQL->Add(updateQuery);
        ibqAvailCategory->ParamByName("id")->AsInteger = obj.getId();
    }
    else{
        //Добавить
        ibqAvailCategory->SQL->Add(insertQuery);
    }
    ibqAvailCategory->ParamByName("startAge")->AsInteger = obj.getStartAge();
    ibqAvailCategory->ParamByName("endAge")->AsInteger = obj.getEndAge();
    ibqAvailCategory->ParamByName("startWeight")->AsFloat = obj.getStartWeight();
    ibqAvailCategory->ParamByName("endWeight")->AsFloat = obj.getEndWeight();
    ibqAvailCategory->ParamByName("female")->AsString = ((obj.getFemale())?'T':'F');
    ibqAvailCategory->ParamByName("comments")->AsString = obj.getComments();
    //выполнить запрос

    ibqAvailCategory->ExecSQL();

    if(dmDataSource->ibtrSecretaryDB->Active){
        //Выполнить сохранение данных
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //Если была добавлена новая запись, узнать ее идентификатор
    if(!obj.getId()){
        //Получить из таблицы последнюю добавленную запись
        ibqAvailCategory->SQL->Clear();
        ibqAvailCategory->SQL->Add(searchIdQuery); 
        ibqAvailCategory->ParamByName("startAge")->AsInteger = obj.getStartAge();
        ibqAvailCategory->ParamByName("endAge")->AsInteger = obj.getEndAge();
        ibqAvailCategory->ParamByName("startWeight")->AsFloat = obj.getStartWeight();
        ibqAvailCategory->ParamByName("endWeight")->AsFloat = obj.getEndWeight();
        ibqAvailCategory->ParamByName("female")->AsString = ((obj.getFemale())?'T':'F');
        ibqAvailCategory->ParamByName("comments")->AsString = obj.getComments();
        ibqAvailCategory->Open();
        obj.setId(ibqAvailCategory->FieldByName("id")->AsInteger);
        ibqAvailCategory->Close();
        }
}

TList*  TdmAvailCategoryDAO::getAll(void){
AnsiString selectQuery =
"select id, startAge, endAge, startWeight, endWeight, female, comments \
 from AvailableCategory";
    //Создать запрос для получения объектов из базы
    ibqAvailCategory->SQL->Clear();
    ibqAvailCategory->SQL->Add(selectQuery);
    //Получить записи из базы данных
    ibqAvailCategory->Open();

    //Создаем объекты по количеству полученных из базы данных
    TList* resultList = new TList();
    resultList->Clear();
    ibqAvailCategory->First();
     for(int i = 0; i < ibqAvailCategory->RecordCount; i++){
        TAvailCategory *result = new TAvailCategory();
        result->setId(ibqAvailCategory->FieldByName("id")->AsInteger);
        result->setStartAge(ibqAvailCategory->FieldByName("startAge")->AsInteger);
        result->setEndAge(ibqAvailCategory->FieldByName("endAge")->AsInteger);
        result->setStartWeight(ibqAvailCategory->FieldByName("startWeight")->AsFloat);
        result->setEndWeight(ibqAvailCategory->FieldByName("endWeight")->AsFloat);
        result->setFemale(ibqAvailCategory->FieldByName("female")->AsString =='T'?true:false);
        result->setComments(ibqAvailCategory->FieldByName("comments")->AsString);
        //Добавим в список
        resultList->Add(result);
        //Перейдем к следующей записи
        ibqAvailCategory->Next();
        }
     //вернем результирующее множество
     ibqAvailCategory->Close();
     return resultList;
}


void TdmAvailCategoryDAO::getById(int id, TAvailCategory &obj){
AnsiString selectQuery =
"select id, startAge, endAge, startWeight, endWeight, female, comments \
 from AvailableCategory where id = :id";
    //Создать запрос для получения объектов из базы
    ibqAvailCategory->SQL->Clear();
    ibqAvailCategory->SQL->Add(selectQuery);
    ibqAvailCategory->ParamByName("id")->AsInteger = id;
    //Получить записи из базы данных
    ibqAvailCategory->Open();
    if(ibqAvailCategory->RecordCount){
        obj.setId(ibqAvailCategory->FieldByName("id")->AsInteger);
        obj.setStartAge(ibqAvailCategory->FieldByName("startAge")->AsInteger);
        obj.setEndAge(ibqAvailCategory->FieldByName("endAge")->AsInteger);
        obj.setStartWeight(ibqAvailCategory->FieldByName("startWeight")->AsFloat);
        obj.setEndWeight(ibqAvailCategory->FieldByName("endWeight")->AsFloat);
        obj.setFemale(ibqAvailCategory->FieldByName("female")->AsString =='T'?true:false);
        obj.setComments(ibqAvailCategory->FieldByName("comments")->AsString);
        }
    //Записи не получены, вернуть null
    else{
        //Обнулить объект
        setmem(&obj, sizeof(obj), 0);
        }
    //Закрыть множество
    ibqAvailCategory->Close();
}

int TdmAvailCategoryDAO::getAvailCategoryId(double weight, int age, bool female){
//Результат запроса
int result = 0;
    //Запрос для определенного участника
AnsiString selectQuery =
"select id from AvailableCategory avcat where avcat.startWeight < :weight and \
 avcat.endWeight >= :weight and avcat.startAge <= :age and avcat.endAge >= :age and \
 avcat.female = :female";
    ibqAvailCategory->SQL->Clear();
    ibqAvailCategory->SQL->Add(selectQuery);
    //Определить параметры запроса
    ibqAvailCategory->ParamByName("weight")->AsFloat = weight;
    ibqAvailCategory->ParamByName("age")->AsInteger = age;
    ibqAvailCategory->ParamByName("female")->AsString = female?'T':'F';
    //Выполнить запрос
    ibqAvailCategory->Open();
    ibqAvailCategory->First();
    if(ibqAvailCategory->RecordCount){
        //Была получена категория
        result = ibqAvailCategory->FieldByName("id")->AsInteger;
        }
    //Закрыть множество
    ibqAvailCategory->Close();
    //Вернуть результат
    return result;
}

TAvailCategory TdmAvailCategoryDAO::getCurrent(void){
//Возвращаемый объект
TAvailCategory result;
    result.setId(0);    //изначально запись не получена
    //Если таблица открыта, получить текущий объект
    if(ibqAvailCategoryAll->State != dsInactive){
        result.setId(ibqAvailCategoryAll->FieldByName("id")->AsInteger);
        result.setStartAge (ibqAvailCategoryAll->FieldByName("startage")->AsInteger);
        result.setEndAge(ibqAvailCategoryAll->FieldByName("endage")->AsInteger);
        result.setStartWeight(ibqAvailCategoryAll->FieldByName("startweight")->AsFloat);
        result.setEndWeight(ibqAvailCategoryAll->FieldByName("endweight")->AsFloat);
        result.setFemale(ibqAvailCategoryAll->FieldByName("female")->AsString =='T'?true:false);
        result.setComments(ibqAvailCategoryAll->FieldByName("comments")->AsString);
        }
    //Вернуть результат
    return result;
}


void TdmAvailCategoryDAO::makeCurrent(TAvailCategory obj){
    //Если передан не пустой объект
    if(ibqAvailCategoryAll->Active){
        if(obj.getId() > 0){
            ibqAvailCategoryAll->Locate("id", obj.getId(), TLocateOptions());
            }
        }
}

void TdmAvailCategoryDAO::remove(TAvailCategory obj){
String deleteQuery = "delete from AvailableCategory ac where ac.id=:id";
    //Если передан не пустой объект
    if(obj.getId() > 0){
      ibqAvailCategory->SQL->Clear();
      ibqAvailCategory->SQL->Add(deleteQuery);
      //Определить параметры запроса
      ibqAvailCategory->ParamByName("id")->AsInteger = obj.getId();
      ibqAvailCategory->ExecSQL();
      //Закрыть множество
      ibqAvailCategory->Close();
      }
}


