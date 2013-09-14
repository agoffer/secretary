//---------------------------------------------------------------------------

#ifndef resultDMH
#define resultDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>

#include "resultCtrl.h"
#include "utils.h"
#include "map.h"
//---------------------------------------------------------------------------
class TdmResultDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqResult;
    TIBQuery *ibqCompetitorToCategoryResultTable;
    TDataSource *dsCompetitorToCategoryResult;
    void __fastcall ibqCompetitorToCategoryResultTableAfterScroll(
          TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
    __fastcall TdmResultDAO(TComponent* Owner);

    //-- Прочитать результат из базы данных
    void getResults(int competitorId, int categoryId, TResult &result);

    //-- Сохранить результат в базе данных
    void setResults(int competitorId, int cateogryId, TResult result);

    //-- Сформировать таблицу с результатами участников, заданной категории 
    TList* setCompetitorCategoryResultTable(int categoryId);

    //-- Устновить функцию обратного вызова
    void setScrollCallback(CallbackFunction cbf);

    //-- Получить из таблицы с результатами участника в категории
    //-- id текущего участника
    int getCurrentCompetitorIdFromTable(void);

    //-- Сделать текущей запись для участника с заданным идентификатором
    void setCurrentCompetitorByIdFromTable(int competitorId);

    //-- Получить шкалу балов для соревнования
    // disciplineId : 1 рукопашный бой, 0 стрельба
    void getScoreRanking(map<int, int> &scoreRank, int competitionRank, int disciplineId);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmResultDAO *dmResultDAO;
//---------------------------------------------------------------------------
#endif
