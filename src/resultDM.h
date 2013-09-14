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

    //-- ��������� ��������� �� ���� ������
    void getResults(int competitorId, int categoryId, TResult &result);

    //-- ��������� ��������� � ���� ������
    void setResults(int competitorId, int cateogryId, TResult result);

    //-- ������������ ������� � ������������ ����������, �������� ��������� 
    TList* setCompetitorCategoryResultTable(int categoryId);

    //-- ��������� ������� ��������� ������
    void setScrollCallback(CallbackFunction cbf);

    //-- �������� �� ������� � ������������ ��������� � ���������
    //-- id �������� ���������
    int getCurrentCompetitorIdFromTable(void);

    //-- ������� ������� ������ ��� ��������� � �������� ���������������
    void setCurrentCompetitorByIdFromTable(int competitorId);

    //-- �������� ����� ����� ��� ������������
    // disciplineId : 1 ���������� ���, 0 ��������
    void getScoreRanking(map<int, int> &scoreRank, int competitionRank, int disciplineId);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmResultDAO *dmResultDAO;
//---------------------------------------------------------------------------
#endif
