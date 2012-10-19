//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "personDM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//Функция обратного вызова - скроллинг по таблице
CallbackFunction PersonScrollCallback;

TdmPersonDAO *dmPersonDAO;
//---------------------------------------------------------------------------
__fastcall TdmPersonDAO::TdmPersonDAO(TComponent* Owner)
    : TDataModule(Owner)
{
    //Сбросить состояние сортировки по полям
    sortedFieldState = ssUnsort;
    sortedField = ptfNoField;
    //Сбросить фильтруемое поле
    filteredField = ptfNoField;
    //Условие выборки
    filterCondition  = "";

}
//---------------------------------------------------------------------------


void TdmPersonDAO::initPersonTable(TIBQuery *ibq){
    if(ibq->Active){
        ibq->Close();
        }
    ibq->SQL->Clear();
    ibq->SQL->Add("select * from Person ");
}

void TdmPersonDAO::selectFromPersonTable(TIBQuery *ibq, AnsiString sortField, AnsiString filter, bool asc){
    //Если есть выбранная запись, запомним ее позицию
    TPerson current = getCurrent(ibq);
    //Формируем обычный запрос
    initPersonTable(ibq);
    //Добавим условия выборки и сортировки
    if(filter.Trim()!="")
        ibq->SQL->Add("where " + filter);
    if(sortField.Trim()!=""){
        ibq->SQL->Add("order by " + sortField);
        ibq->SQL->Add(asc?"asc" : "desc");
        } else{
         ibq->SQL->Add("order by surname asc");
        }
    //Выполнить выборку с установленными условиями
    ibq->Open();
    //Пройтись по всем записям
    ibq->Last();
    ibq->First();
    //Вернем указатель на ранее выбранную запись
    if(current.getId()!=0)
        makeCurrent(current, ibq);
}

AnsiString TdmPersonDAO::getFieldName(PersonTableField field){
    switch(field){
        case ptfSurname : return "surname";
        case ptfName : return "name";
        case ptfPatronymic : return "patronymic";
        case ptfPhone : return "phone";
        //Не определно поле
        default: return "";
        }
}


void TdmPersonDAO::filterByField(PersonTableField field){
    //Получим строковое представление поля
    AnsiString asField = getFieldName(field);
    if(asField.Trim()=="") return;  //поле не определено
    //Формируем строку с условием
    AnsiString condition = asField + " like '%" + filterCondition + "%'";
    //Определим дополнительные условия сортировки
    asField = getFieldName(sortedField);
    //Выполнить выборку с установленным условием
    selectFromPersonTable(ibqPersonAll, asField, condition, sortedFieldState != ssDescending);
    //Сбросить условие фильтрации
    filterCondition = "";
    //Запомним, по какому поля выполнялась фильтрация
    filteredField = field;
}

void TdmPersonDAO::refreshSlaveTable(String filter) {
    //Получим строковое представление поля (оно задается выборкой из основной таблицы)
    AnsiString asField = getFieldName(filteredField);
    //Формируем строку с условием
    AnsiString condition = asField + " like '%" + filter + "%'";
    //Определим дополнительные условия сортировки
    asField = getFieldName(sortedField);
    //Выполнить выборку с установленным условием
    selectFromPersonTable(ibqPersonSlaveTable, asField, condition, sortedFieldState != ssDescending);
}




void TdmPersonDAO::sortByField(PersonTableField field){
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
    selectFromPersonTable(ibqPersonAll, asField, condition, sortedFieldState != ssDescending);
    //Сбросить фильтр
    filterCondition="";
    //Запомним поле, по которому выполнялась сортировка
    sortedField = field;
}




void TdmPersonDAO::store(TPerson &obj){
AnsiString updateQuery =
"update Person set surname = :surname, name = :name, patronymic = :patronymic,\
 dob = :dob, female = :female, phone = :phone, additions = :additions\
 where id = :id";
AnsiString insertQuery =
"insert into Person(surname, name, patronymic, dob, female, phone, additions)\
 values(:surname, :name, :patronymic,:dob, :female, :phone, :additions)";
AnsiString searchIdQuery =
"select id from Person where surname=:surname and name=:name and \
 patronymic=:patronymic and dob=:dob and female=:female and phone=:phone and \
 additions=:additions";
    //Создать запрос для сохранения объекта в базе данных
    ibqPerson->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    if(obj.getId() > 0){
        //Обновить
        ibqPerson->SQL->Add(updateQuery);
        ibqPerson->ParamByName("id")->AsInteger = obj.getId();
        }
    else{
        //Добавить
        ibqPerson->SQL->Add(insertQuery);
        }
    ibqPerson->ParamByName("surname")->AsString = obj.getSurname();
    ibqPerson->ParamByName("name")->AsString = obj.getName();
    ibqPerson->ParamByName("patronymic")->AsString = obj.getPatronymic();
    ibqPerson->ParamByName("dob")->AsDateTime = obj.getDob();
    ibqPerson->ParamByName("female")->AsString = ((obj.getFemale())?'T':'F');
    ibqPerson->ParamByName("phone")->AsString = obj.getPhone();
    ibqPerson->ParamByName("additions")->AsString = obj.getAdditions();
    //выполнить запрос
    ibqPerson->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Сохранить в базе
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //Если была добавлена новая запись, узнать ее идентификатор
    if(!obj.getId()){
        //Получить из таблицы последнюю добавленную запись
        ibqPerson->SQL->Clear();
        ibqPerson->SQL->Add(searchIdQuery);
        ibqPerson->ParamByName("surname")->AsString = obj.getSurname();
        ibqPerson->ParamByName("name")->AsString = obj.getName();
        ibqPerson->ParamByName("patronymic")->AsString = obj.getPatronymic();
        ibqPerson->ParamByName("dob")->AsDateTime = obj.getDob();
        ibqPerson->ParamByName("female")->AsString = ((obj.getFemale())?'T':'F');
        ibqPerson->ParamByName("phone")->AsString = obj.getPhone();
        ibqPerson->ParamByName("additions")->AsString = obj.getAdditions();
        ibqPerson->Open();
        obj.setId(ibqPerson->FieldByName("id")->AsInteger);
        ibqPerson->Close();
        }
}

TPerson TdmPersonDAO::getCurrent(){
    return getCurrent(ibqPersonAll);
}

TPerson TdmPersonDAO::getCurrentSlave(){
    return getCurrent(ibqPersonSlaveTable);
}


TPerson TdmPersonDAO::getCurrent(TIBQuery *ibq){
//Возвращаемый объект
TPerson result;
    result.setId(0);    //изначально запись не получена
    //Если таблица открыта, получить текущий объект
    if(ibq->State != dsInactive){
        result.setId(ibq->FieldByName("id")->AsInteger);
        result.setSurname(ibq->FieldByName("surname")->AsString);
        result.setName(ibq->FieldByName("name")->AsString);
        result.setPatronymic(ibq->FieldByName("patronymic")->AsString);
        result.setDob(ibq->FieldByName("dob")->AsDateTime);
        result.setFemale(ibq->FieldByName("female")->AsString =='T'?true:false);
        result.setPhone(ibq->FieldByName("phone")->AsString);
        result.setAdditions(ibq->FieldByName("additions")->AsString);
        }
    //Вернуть результат
    return result;
}

bool TdmPersonDAO::deleteCurrent(void){
AnsiString deleteQuery = "delete from Person where id = :personid";
    //Если таблица открыта, получить текущий объект
    if(ibqPersonAll->State != dsInactive){
      //Создать запрос для сохранения объекта в базе данных
        ibqPerson->SQL->Clear();
        ibqPerson->SQL->Add(deleteQuery);
        ibqPerson->ParamByName("personid")->AsString = ibqPersonAll->FieldByName("id")->AsInteger;
        //выполнить запрос
        ibqPerson->ExecSQL();
        return true;
        }
    else{
      return false;
      }
}


bool TdmPersonDAO::likeAs(TPerson &obj){
bool find = false;//результат поиска
AnsiString searchQuery =
"select id from Person where surname = :surname and \
                             name = :name and \
                             patronymic = :patronymic";

    //Создать запрос для сохранения объекта в базе данных
    ibqPerson->SQL->Clear();
    ibqPerson->SQL->Add(searchQuery);
    ibqPerson->ParamByName("surname")->AsString = obj.getSurname();
    ibqPerson->ParamByName("name")->AsString = obj.getName();
    ibqPerson->ParamByName("patronymic")->AsString = obj.getPatronymic();
    //выполнить запрос
    ibqPerson->Open();
    //Если была получена запись, обновить идентификатор и вернуть истину
    if(ibqPerson->RecordCount){
        obj.setId(ibqPersonAll->FieldByName("id")->AsInteger);
        find = true;
        }
    //Закроем
    ibqPerson->Close();
    //Персона не найдена
    return find;
}

void TdmPersonDAO::makeCurrent(TPerson obj){
    makeCurrent(obj, ibqPersonAll);
}

void TdmPersonDAO::makeCurrent(TPerson obj, TIBQuery *ibq){
    //Если передан не пустой объект
    if(ibq->Active){
        if(obj.getId() > 0){
            ibq->Locate("id", obj.getId(), TLocateOptions());
            }
        }
}


void TdmPersonDAO::setScrollCallback(CallbackFunction cbf){
    PersonScrollCallback = cbf;
}



void __fastcall TdmPersonDAO::ibqPersonAllAfterScroll(TDataSet *DataSet)
{
    //Если определена функция обратного вызова, вызываем ее
    if(PersonScrollCallback){
        PersonScrollCallback();
        }

}
//---------------------------------------------------------------------------

/**
 * Подменить данные из одной таблицы, данными из другой.
 * @param from данные которые меням
 * @param to данные которыми меняем
 */
void TdmPersonDAO::changePersonalData(TIBQuery *from, TIBQuery *to) {
    int fromId = from->FieldByName("id")->AsInteger;
    int toId = to->FieldByName("id")->AsInteger;
    //Сделаем заменту в таблице CLUB
    replacePersonInCertainTable("CLUB", "personId", fromId, toId);
    //Сделаем замену в таблице COMPETITIOR
    replacePersonInCertainTable("COMPETITOR", "personId", fromId, toId);
    //Сделаем замену в таблице REQUEST
    replacePersonInCertainTable("REQUEST", "personId", fromId, toId);
    //Удалить того, которого заменили
    deleteCurrent();
    // завершить транзакцию
        if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}
//---------------------------------------------------------------------------

/**
 * Замена персональных данных в заданной таблице.
 * @param tableName таблица, в которой делается замена
 * @param fieldName поле, по которому делается замена
 * @param personIdFrom идентификатор персоны, которую будем заменять
 * @param personIdTo идентификатор перосны, на которую будем заменять
 */
void TdmPersonDAO::replacePersonInCertainTable(AnsiString tableName, AnsiString fieldName, int personIdFrom, int personIdTo) {
    // Сформировать запрос, для замены значения персональных данных
    AnsiString updateQuery = "update " + tableName + " set " + fieldName + " = " + personIdFrom + " where "
                            + fieldName + " = " + personIdTo;
    //Создать запрос для сохранения объекта в базе данных
    ibqPerson->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    ibqPerson->SQL->Add(updateQuery);
    //выполнить запрос
    ibqPerson->ExecSQL();
}
//---------------------------------------------------------------------------







