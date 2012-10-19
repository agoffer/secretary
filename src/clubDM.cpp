//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "clubDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//Функция обратного вызова - скроллинг по таблице 
CallbackFunction ClubScrollCallback;

TdmClubDAO *dmClubDAO;
//---------------------------------------------------------------------------
__fastcall TdmClubDAO::TdmClubDAO(TComponent* Owner)
    : TDataModule(Owner)
{
    //Сбросить состояние сортировки по полям 
    sortedFieldState = ssUnsort;
    sortedField = ctfNoField;
    //Сбросить фильтруемое поле
    filteredField = ctfNoField;
    //Условие выборки
    filterCondition  = "";
}
//---------------------------------------------------------------------------


void TdmClubDAO::initClubTable(void){
    if(ibqClubAll->Active){
        ibqClubAll->Close();     
        }
    ibqClubAll->SQL->Clear();
    ibqClubAll->SQL->Add("select * from Club");
}

void TdmClubDAO::selectFromClubTable(AnsiString sortField, AnsiString filter, bool asc){
    //Если есть, запомним текущую запись
    TClub current = getCurrent();

    //Формируем обычный запрос
    initClubTable();
    //Добавим условия выборки и сортировки
    if(filter.Trim()!="")
        ibqClubAll->SQL->Add("where " + filter);
    if(sortField.Trim()!=""){
        ibqClubAll->SQL->Add("order by " + sortField);
        ibqClubAll->SQL->Add(asc?"asc" : "desc");
        }
    //Выполнить выборку с установленными условиями
    ibqClubAll->Open();
    //Пройтись по всем записям
    ibqClubAll->Last();
    ibqClubAll->First();

    //Вернуть текущую запись
    makeCurrent(current);
}


AnsiString TdmClubDAO::getFieldName(ClubTableField field){
    switch(field){
        case ctfName : return "name";
        case ctfCountry : return "country";
        case ctfCity : return "city";
        //Не определно поле
        default: return "";
        }
}


void TdmClubDAO::filterByField(ClubTableField field){
    //Получим строковое представление поля
    AnsiString asField = getFieldName(field);
    if(asField.Trim()=="") return;  //поле не определено
    //Формируем строку с условием
    AnsiString condition = asField + " like '%" + filterCondition + "%'";
    //Определим дополнительные условия сортировки
    asField = getFieldName(sortedField);
    //Выполнить выборку с установленным условием
    selectFromClubTable(asField, condition, sortedFieldState != ssDescending);
    //Сбросить условие фильтрации
    filterCondition = "";
    //Запомним, по какому поля выполнялась фильтрация
    filteredField = field; 
}



void TdmClubDAO::sortByField(ClubTableField field){
AnsiString condition;
AnsiString asField;
    //Установим, если нужно условие фильтра выборки
    if(filterCondition.Trim()!=""){
        //Выборка с фильтрацией по заданному полю
        asField = getFieldName(filteredField);
        if(asField.Trim()!=""){
            condition = asField + " like '%" + filterCondition + "%'";
            }
        }
    //Поле, по которому будем выполнять сортировку
    //Если это не предыдущее сортируемое поле, сбросим направление сортировки
    if(field != sortedField){
        sortedFieldState = ssUnsort;
        }
    asField = getFieldName(field);
    //Определим состояние выборки
    if(sortedFieldState == ssUnsort){
        //Сортировать по возрастанию
        sortedFieldState = ssAscending;
        }
    else{
        //Сортировать по возрастанию или убыванию, в зависимости от тек. состояния
        if(sortedFieldState == ssAscending)
            sortedFieldState = ssDescending;
        else
            sortedFieldState = ssAscending;
        }
    //Сделать нужную выборку
    selectFromClubTable(asField, condition, sortedFieldState != ssDescending);
    //Сбросить фильтр
    filterCondition="";
    //Запомним поле, по которому выполнялась сортировка
    sortedField = field;
}




void TdmClubDAO::store(TClub &obj){
AnsiString updateQuery =
"update Club set name = :name, shortname = :shortname, country = :country,\
 city = :city, personId = :personId, comments = :comments\
 where id = :id";
AnsiString insertQuery =
"insert into Club(name, shortname, country, city, personId, comments)\
 values(:name, :shortname, :country, :city, :personId, :comments)";
AnsiString searchIdQuery =
"select id from Club where name=:name and shortname=:shortname and \
 country=:country and city=:city and personId=:personId and \
  comments=:comments";

    //Создать запрос для сохранения объекта в базе данных
    ibqClub->SQL->Clear();
    if(obj.getId() > 0){
        //Обновить
        ibqClub->SQL->Add(updateQuery);
        ibqClub->ParamByName("id")->AsInteger = obj.getId();
        }
    else{
        //Добавить
        ibqClub->SQL->Add(insertQuery);
        }
    ibqClub->ParamByName("name")->AsString = obj.getName();
    ibqClub->ParamByName("shortname")->AsString = obj.getShortName();
    ibqClub->ParamByName("country")->AsString = obj.getCountry();
    ibqClub->ParamByName("city")->AsString = obj.getCity();
    ibqClub->ParamByName("personId")->AsInteger = obj.getPersonId();
    ibqClub->ParamByName("comments")->AsString = obj.getComments();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //выполнить запрос
    ibqClub->ExecSQL();
    //Сохраним данные в базе
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //Если была добавлена новая запись, узнать ее идентификатор
    if(!obj.getId()){
        //Получить из таблицы последнюю добавленную запись
        ibqClub->SQL->Clear();
        ibqClub->SQL->Add(searchIdQuery);                
        ibqClub->ParamByName("name")->AsString = obj.getName();
        ibqClub->ParamByName("shortname")->AsString = obj.getShortName();
        ibqClub->ParamByName("country")->AsString = obj.getCountry();
        ibqClub->ParamByName("city")->AsString = obj.getCity();
        ibqClub->ParamByName("personId")->AsInteger = obj.getPersonId();
        ibqClub->ParamByName("comments")->AsString = obj.getComments();
        ibqClub->Open();
        obj.setId(ibqClub->FieldByName("id")->AsInteger);
        ibqClub->Close();        
        }
}


TClub TdmClubDAO::getCurrent(void){
//Возвращаемый объект
TClub result;
    result.setId(0);    //изначально запись не получена
    //Если таблица открыта, получить текущий объект
    if(ibqClubAll->State != dsInactive){
        result.setId(ibqClubAll->FieldByName("id")->AsInteger);
        result.setName(ibqClubAll->FieldByName("name")->AsString);
        result.setShortName(ibqClubAll->FieldByName("shortname")->AsString);        
        result.setCountry(ibqClubAll->FieldByName("country")->AsString);
        result.setCity(ibqClubAll->FieldByName("city")->AsString);
        result.setPersonId(ibqClubAll->FieldByName("personId")->AsInteger);
        result.setComments(ibqClubAll->FieldByName("comments")->AsString);
        }
    //Вернуть результат
    return result;
}

void TdmClubDAO::makeCurrent(TClub obj){
int res;
    if(ibqClubAll->Active){
        //Если передан не пустой объект
        if(obj.getId() > 0){
            ibqClubAll->Locate("id", obj.getId(), TLocateOptions());
            }
        }
}


void TdmClubDAO::setScrollCallback(CallbackFunction cbf){
    ClubScrollCallback = cbf;
}




void __fastcall TdmClubDAO::ibqClubAllAfterScroll(TDataSet *DataSet)
{
    //Если определена функция обратного вызова, вызываем ее
    if(ClubScrollCallback){
        ClubScrollCallback();
        }
}




//---------------------------------------------------------------------------

