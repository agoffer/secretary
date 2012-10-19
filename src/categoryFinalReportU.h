//---------------------------------------------------------------------------

#ifndef categoryFinalReportUH
#define categoryFinalReportUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TfrmCategoryFinalReport : public TForm
{
__published:	// IDE-managed Components
    TQuickRep *qrCategory;
    TQRSubDetail *qrdbsdCompetitor;
    TQRDBText *qrdbtSurname;
    TQRDBText *qrdbtName;
    TQRDBText *qrdbtPatronymic;
    TQRDBText *qrdbtSortion;
    TQRDBText *qrdbtShootRank;
    TQRDBText *qrdbtComments;
    TQRBand *qrhbTableHeader;
    TQRMemo *qrmCategorySNP;
    TQRMemo *qrmCategorySortion;
    TQRMemo *qrmShootResult;
    TQRMemo *qrmShootRank;
    TQRMemo *qrmShootScore;
    TQRMemo *qrmComments;
    TQRBand *qrbCategoryFooter;
    TQRMemo *qrmCategoryFooter;
    TQRBand *qrbCategoryTitle;
    TQRLabel *qrlCategoryOrgTitle;
    TQRDBText *qrdbtCategoryCompRank;
    TQRLabel *qrlCategoryProtTitle;
    TQRLabel *qrlCategoryDate;
    TQRDBText *qrdbtCategoryEndDate;
    TQRDBText *qrdbtCategoryCompBegDate;
    TQRLabel *qrlCategoryDateDefis;
    TQRLabel *qrlCategoryAge;
    TQRLabel *qrlCategoryWeight;
    TQRDBText *qrdbCategoryStartAge;
    TQRDBText *qrdbtCategoryEndAge;
    TQRDBText *qrdbtCategoryStartWeight;
    TQRDBText *qrdbtCategoryEndWeight;
    TQRLabel *qrlCategoryFightVersion;
    TQRDBText *qrdbtCategoryFightVersion;
    TQRLabel *qrlCategoryAgeDefis;
    TQRLabel *qrlCategoryWeightDefis;
    TQRDBText *qrdbtFemale;
    TQRMemo *qrmFightWOKResult;
    TQRMemo *qrmFightWOKRank;
    TQRMemo *qrmFightWOKScore;
    TQRMemo *qrmFightWKResult;
    TQRMemo *qrmFightWKRank;
    TQRMemo *qrmFightWKScore;
    TQRMemo *qrmCommonResult;
    TQRMemo *qrmCommonScore;
    TQRMemo *qrmCommonRank;
    TQRDBText *qrdbtFightWOKRank;
    TQRDBText *qrdbtFightWKRank;
    TQRDBText *qrdbtFightWKScore;
    TQRDBText *qrdbtCommonScore;
    TQRDBText *qrdbtCommonRank;
    TQRDBText *qrdbtFightWOKScore;
    TQRDBText *qrdbtShootScore;
    void __fastcall qrdbtScorePrint(TObject *sender,
          AnsiString &Value);
    void __fastcall qrdbtCommonScorePrint(TObject *sender,
          AnsiString &Value);
    void __fastcall qrdbtFemalePrint(TObject *sender, AnsiString &Value);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmCategoryFinalReport(TComponent* Owner);
    void  PreviewFinalProtocols(TList *categories);     
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCategoryFinalReport *frmCategoryFinalReport;
//---------------------------------------------------------------------------
#endif
