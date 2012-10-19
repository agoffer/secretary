//---------------------------------------------------------------------------

#ifndef categoryReportUH
#define categoryReportUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>

#include <map.h>

#include "categoryCtrl.h"
//---------------------------------------------------------------------------
class TfrmCategoryReport : public TForm
{
__published:	// IDE-managed Components
    TQuickRep *qrCategory;
    TQRSubDetail *qrdbsdCompetitor;
    TQRBand *qrhbTableHeader;
    TQRDBText *qrdbtSurname;
    TQRDBText *qrdbtName;
    TQRDBText *qrdbtPatronymic;
    TQRMemo *qrmCategorySNP;
    TQRMemo *qrmCategorySkill;
    TQRMemo *qrmCategorySortion;
    TQRMemo *qrmCategoryResult;
    TQRMemo *qrmCategoryClub;
    TQRMemo *qrmCategoryShoot;
    TQRMemo *qrmCategoryCross;
    TQRMemo *qrmCategoryPos;
    TQRMemo *qrmCategoryCompAge;
    TQRMemo *qrmCategoryCompWeight;
    TQRDBText *qrdbtSortion;
    TQRDBText *qrdbtSkill;
    TQRDBText *qrdbtClub;
    TQRDBText *qrdbtShoot;
    TQRDBText *qrdbtCross;
    TQRDBText *qrdbtPos;
    TQRDBText *qrdbtAge;
    TQRDBText *qrdbtWeight;
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
    void __fastcall qrdbtFemalePrint(TObject *sender, AnsiString &Value);
    void __fastcall qrdbtCategoryStartWeightPrint(TObject *sender,
          AnsiString &Value);
    void __fastcall qrdbtCategoryEndWeightPrint(TObject *sender,
          AnsiString &Value);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmCategoryReport(TComponent* Owner);

    //-- Просмотр и печать протоколов 
    void PreviewProtocols(TList *categories);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCategoryReport *frmCategoryReport;
//---------------------------------------------------------------------------
#endif
