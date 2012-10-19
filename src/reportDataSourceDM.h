//---------------------------------------------------------------------------

#ifndef reportDataSourceDMH
#define reportDataSourceDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBTable.hpp>


#include "dataSourceDM.h"
#include <IBQuery.hpp>
#include <DBTables.hpp>


//---------------------------------------------------------------------------
class TdmReportDataSource : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqRepCompetitorDetail;
    TIBQuery *ibqRepCategoryDetail;
    TIBQuery *ibqRepUncategoryListDetail;
    TIBQuery *ibqRepUncategoryFV;
    TIBQuery *ibqRepExtendedFV;
    TIBQuery *ibqRepRequestClubListDetail;
    TIBQuery *ibqRepCategoryFinalCompetitorDetail;
    TIBQuery *ibqSummaryReport;
    void __fastcall ibqRepCategoryDetailAfterScroll(TDataSet *DataSet);
    void __fastcall ibqRepCategoryFinalCompetitorDetailAfterScroll(
          TDataSet *DataSet);
    void __fastcall CategoryDetailAfterScroll(
          TDataSet *DataSet);
private:	// User declarations
    //������� ���������� ���������� �� ���� ����������
    int getCompetitorsAmount(int competitionId);
    // �������� ������ �� ����������, ������ ������� ���������
    TIBQuery* getSummaryReportData(int competitionId, bool female);
    //������� ������ � �������, ��� ������ � Excel
    void fillSummaryReportArray(int orderNum, int competitorInCategoryAmnt,
                                TIBQuery* dsCompetitorsDetail,
                                Variant & categoryArray); 
public:		// User declarations
    //������� ����, ��� �������� ������ �������� 
    bool finalReport;
    __fastcall TdmReportDataSource(TComponent* Owner);
    //���������� ���������, ������� ����� ���������� ��� ������� ������������
    void setCategoriesToPrintByCompetition(int compId);
    //������� ��������� ��������� � ������ 
    void setCategoriesFromList(TList *categories);
    //���������� ���������, ������� ����� �������� 
    void setCategoryToPrintById(int prCat);
    //���������� ������ �� ��������� ������ ���������������� ���������� ��� ������������
    void setUncategoryListQueryByCompetitionId(int competitionId);
    //���������� ������ �� ��������� ������ ������ �� ������� ����������� � ������������� 
    void TdmReportDataSource::setRequestClubListByCompetitionId(int competitionId);

    //-- ������� �������� ��������� �� ������� ����
    void summaryProtocolExport(int competitionId);  
};
//---------------------------------------------------------------------------
extern PACKAGE TdmReportDataSource *dmReportDataSource;
//---------------------------------------------------------------------------
#endif
