//---------------------------------------------------------------------------

#ifndef competitorDMH
#define competitorDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>

#include "competitorCtrl.h"
#include "utils.h"


//--поля таблицы (фильтрация, сортировка)
enum CompetitorTableField{ctfSurname, ctfClub_Name};

//---------------------------------------------------------------------------
class TdmCompetitorDAO : public TDataModule
{
__published:	// IDE-managed Components
    TDataSource *dsCompetitorExtended;
    TIBQuery *ibqCompetitorExtendedTable;
    TIBQuery *ibqCompetitorAll;
    TIBQuery *ibqCompetitor;
    TDataSource *dsCompetitorTable;
    TDataSource *dsCompetitor;
    TIBQuery *ibqCompetitorToFightVersion;
    void __fastcall ibqCompetitorExtendedTableAfterScroll(
          TDataSet *DataSet);
private:	// User declarations
    //-- Определить начальный запрос для получения всех данных из таблицы
    void initCompetitorTable(void);
    void initExtendedCompetitorTable(void);

    //-- Определяем строковое представление поля
    AnsiString getFieldName(CompetitorTableField field);

    //-- дополнительное условие выборки
    AnsiString filterCondition_1;
    //-- Поле, по которому выполняется фильтрование
    CompetitorTableField filteredField_1;
    //-- дополнительное условие выборки
    AnsiString filterCondition_2;
    //-- Поле, по которому выполняется фильтрование
    CompetitorTableField filteredField_2;

    //-- сформировать таблицу с определенными условиями
    //@param sortField имя поля, по которому проводится сортировки
    //@param filter дополнительное условие выборки
    //@param asc направление сортировки
    void selectFromCompetitorTable(AnsiString filter);

public:		// User declarations
    __fastcall TdmCompetitorDAO(TComponent* Owner);

    //-- Вернуть текущю запись для таблицы
    TCompetitor getCurrent(void);
    //-- Сделать запись текущей в таблице
    void makeCurrent(TCompetitor obj);

    //-- Вернуть текущю запись для расширенной таблицы
    TCompetitor getExtendedTableCurrent(void);
    //-- Сделать запись текущей в таблице
    void makeExtendedTableCurrent(TCompetitor obj);

    //-- Вернуть всех участников, для текущей заявки
    TList * getByRequestId(int requestId);

    //-- Вернуть всех участников, для заданных соревнований 
    TList * getByCompetitionId(int competitionId);

    //-- Получить участника - задан идентификатор
    void getById(int id, TCompetitor &obj);

    //Открыть таблицу участников для заданной заявки 
    void formTableByRequestId(int requestId);

    //-- Вернуть всех участников (в расширенной форме) для текущих соревнований
    TList * getExtendedByCompetitionId(int competitionId);

    //-- Вернуть расширенный список участников не попавших в категории соревнований 
    TList * getExtendedUncategoryByCompetitionId(int competitionId, bool female);

    //-- Вернуть всех Участников (в расширенной форме), для текущей заявки
    TList * getExtendedByRequestId(int requestId);

    //-- Вернуть всех Участников (в расширенной форме), для заданной категории 
    TList * getExtendedByCategoryId(int categoryId);


    //--Сохранить объект в базе данных
    //@param obj объект который требуется сохранить
    void store(TCompetitor &obj);

    //--Удалить объект из базе данных
    //@param obj объект который требуется удалить 
    void erase(TCompetitor &obj);

    //--Устнаовить для участника боевые версии
    //@param id идентификатор участника
    //@param ids список боевых версий
    void setFightVersion(int id, int * ids, int count);

    //-- Удалить боевые версии для участника
    //@param id - идентификатор участника  
    void eraseFightVersion(int id);

    //-- Получить список боевых версий, для участника 
    //@param id идентификатор участника
    //@param count число версий, в которых участвует участник 
    TList* getFightVersion(int id);

    //-- Получить список нераспределенных боевых версий, для участника 
    //@param id идентификатор участника
    //@param count число версий, которые не распределены
    TList* getUncategoryFightVersion(int id);

    //-- Получить список добавленных боевых версий, для участника
    //@param id идентификатор участника
    //@param count число версий, которые добавлены
    TList* getExtendedFightVersion(int id);

    //-- Установка строки для фильтрации
    //@param condition строка по которой выполняется фильтрация записей
    void setFilterCondition_1(AnsiString condition){
        filterCondition_1 = condition;
        }
    //-- Фильтр, по наличию строки в записи
    void filterByField(int competitionId, CompetitorTableField field_1, CompetitorTableField field_2);

    //-- Установка строки для фильтрации
    //@param condition строка по которой выполняется фильтрация записей
    void setFilterCondition_2(AnsiString condition){
        filterCondition_2 = condition;
        }
    //-- Фильтр, по наличию строки в записи
    void filterByField_1(CompetitorTableField field);

    //-- Устновить функцию обратного вызова
    void setScrollCallback(CallbackFunction cbf);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmCompetitorDAO *dmCompetitorDAO;
//---------------------------------------------------------------------------
#endif
