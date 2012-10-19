//---------------------------------------------------------------------------

#ifndef personDMH
#define personDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>

#include "dataSourceDM.h"
#include "personCtrl.h"

#include "utils.h"
//---------------------------------------------------------------------------

//--поля таблицы (фильтрация, сортировка) 
enum PersonTableField{ptfNoField, ptfSurname, ptfName, ptfPatronymic, ptfPhone}; 


class TdmPersonDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqPersonAll;
    TIBQuery *ibqPerson;
    TDataSource *dsPersonTable;
    TDataSource *dsPersonQuery;
    TDataSource *dsPersonSlaveTable;
    TIBQuery *ibqPersonSlaveTable;
    void __fastcall ibqPersonAllAfterScroll(TDataSet *DataSet);
private:	// User declarations
    //-- Определить начальный запрос для получения всех данных из таблицы
    void initPersonTable(TIBQuery *ibq);
    //-- Определяем строковое представление поля
    AnsiString getFieldName(PersonTableField field);




    //-- сформировать таблицу с определенными условиями
    //@param sortField имя поля, по которому проводится сортировки
    //@param filter дополнительное условие выборки
    //@param asc направление сортировки
    void selectFromPersonTable(TIBQuery *ibq, AnsiString sortField, AnsiString filter, bool asc);

    //-- Вернуть текущю запись для таблицы
    TPerson getCurrent(TIBQuery *ibq);

    //-- Сделать запись текущей в таблице
    void makeCurrent(TPerson obj, TIBQuery *ibq);

    // -- Подмена персональных данных в заданной таблице.
    void replacePersonInCertainTable(AnsiString tableName, AnsiString fieldName, int personIdFrom, int personIdTo);


    //-- Состояние отсортированных полей
    SortState sortedFieldState;
    //-- дополнительное условие выборки
    AnsiString filterCondition;
    //-- Поле, по которому выполняется фильтрование
    PersonTableField filteredField;
    //-- Поле, по которому проводится сортировка
    PersonTableField sortedField;

public:		// User declarations
    __fastcall TdmPersonDAO(TComponent* Owner);

    //-- Сохранение объекта в базе данных
    //@param obj объект, который сохраняется в базе данных
    void store(TPerson &obj);

    //-- Удалить текущую запись из таблицы
    bool deleteCurrent(void);

    //-- Вернуть текущю запись для таблицы
    TPerson getCurrent();

    //-- Вернуть текущую запись из подчиненной таблицы
    TPerson getCurrentSlave();

    //-- Сделать запись текущей в таблице
    void makeCurrent(TPerson obj);

    //-- Проверить, есть ли такая персона в базе (проверяем по фамилии имени и отчеству)
    bool likeAs(TPerson &obj);

    //-- Сортировка таблицы по полям
    void sortByField(PersonTableField field);

    // -- Обновить данные подчиненной таблицы,
    void refreshSlaveTable(AnsiString filter);

    //-- Установка строки для фильтрации
    //@param condition строка по которой выполняется фильтрация записей
    void setFilterCondition(AnsiString condition){
        filterCondition = condition;
        }
    //-- Фильтр, по наличию строки в записи
    void filterByField(PersonTableField field);

    //-- Устновить функцию обратного вызова
    void setScrollCallback(CallbackFunction cbf);

    //-- Замена персональных данных значением из таблицы from значения в таблице to
    void changePersonalData(TIBQuery *from, TIBQuery *to);

};
//---------------------------------------------------------------------------
extern PACKAGE TdmPersonDAO *dmPersonDAO;
//---------------------------------------------------------------------------
#endif
