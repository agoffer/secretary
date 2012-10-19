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
    //¬ернуть количество участников во всех категори€х
    int getCompetitorsAmount(int competitionId);
    // ѕолучить данные по участникам, только мужские категории
    TIBQuery* getSummaryReportData(int competitionId, bool female);
    //—оздать массив с данными, дл€ вывода в Excel
    void fillSummaryReportArray(int orderNum, int competitorInCategoryAmnt,
                                TIBQuery* dsCompetitorsDetail,
                                Variant & categoryArray); 
public:		// User declarations
    //ѕризнак того, что печатаем второй протокол 
    bool finalReport;
    __fastcall TdmReportDataSource(TComponent* Owner);
    //”становить категории, которые будут печататьс€ дл€ текущих соревнований
    void setCategoriesToPrintByCompetition(int compId);
    //¬ыбрать категории указанные в списке 
    void setCategoriesFromList(TList *categories);
    //”становить категорию, которую будем печатать 
    void setCategoryToPrintById(int prCat);
    //”становить запрос на получение списка нераспределенных участников дл€ соревновани€
    void setUncategoryListQueryByCompetitionId(int competitionId);
    //”становить запрос на получение списка клубов по за€вкам участвующих в соревновани€х 
    void TdmReportDataSource::setRequestClubListByCompetitionId(int competitionId);

    //-- ≈кспорт сводного протокола во внешний файл
    void summaryProtocolExport(int competitionId);  
};
//---------------------------------------------------------------------------
extern PACKAGE TdmReportDataSource *dmReportDataSource;
//---------------------------------------------------------------------------
#endif
