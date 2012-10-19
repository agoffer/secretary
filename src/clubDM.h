//---------------------------------------------------------------------------

#ifndef clubDMH
#define clubDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>
#include <IBTable.hpp>

#include "dataSourceDM.h"
#include "clubCtrl.h"
#include "utils.h"
//---------------------------------------------------------------------------

//--поля таблицы (фильтрация, сортировка)
enum ClubTableField{ctfNoField, ctfName, ctfCountry, ctfCity};


class TdmClubDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqClub;
    TDataSource *dsClubTable;
    TDataSource *dsClubQuery;
    TIBQuery *ibqClubAll;
    void __fastcall ibqClubAllAfterScroll(TDataSet *DataSet);
private:	// User declarations
    //-- Определить начальный запрос для получения всех данных из таблицы
    void initClubTable(void);

    //-- Определяем строковое представление поля
    AnsiString getFieldName(ClubTableField field);

    //-- Состояние отсортированных полей
    SortState sortedFieldState;
    //-- дополнительное условие выборки
    AnsiString filterCondition;
    //-- Поле, по которому выполняется фильтрование
    ClubTableField filteredField;
    //-- Поле, по которому проводится сортировка
    ClubTableField sortedField;


    //-- сформировать таблицу с определенными условиями
    //@param sortField имя поля, по которому проводится сортировки
    //@param filter дополнительное условие выборки
    //@param asc направление сортировки
    void selectFromClubTable(AnsiString sortField, AnsiString filter, bool asc);


public:		// User declarations
    __fastcall TdmClubDAO(TComponent* Owner);


    //-- Вернуть текущю запись для таблицы
    TClub getCurrent(void);
    //-- Сделать запись текущей в таблице
    void makeCurrent(TClub obj);




    //--Сохранить объект в базе данных
    //@param obj объект который требуется сохранить
    void store(TClub &obj);

    //-- Сортировка таблицы по полям
    void sortByField(ClubTableField field);

    //-- Установка строки для фильтрации
    //@param condition строка по которой выполняется фильтрация записей
    void setFilterCondition(AnsiString condition){
        filterCondition = condition;
        }
    //-- Фильтр, по наличию строки в записи
    void filterByField(ClubTableField field);

    //-- Устновить функцию обратного вызова
    void setScrollCallback(CallbackFunction cbf);
};


//---------------------------------------------------------------------------
extern PACKAGE TdmClubDAO *dmClubDAO;
//---------------------------------------------------------------------------
#endif
