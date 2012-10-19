//---------------------------------------------------------------------------

#ifndef categoryTreeReportUH
#define categoryTreeReportUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmCategoryTreeReport : public TForm
{
__published:	// IDE-managed Components
    TQuickRep *qrTreeCategory;
    TQRBand *qrbCategoryFooter;
    TQRMemo *qrmCategoryFooter;
    TQRBand *qrbCategoryTitle;
    TQRLabel *qrlCategoryOrgTitle;
    TQRDBText *qrdbtCategoryCompRank;
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
    TQRBand *qrbCategoryTree;
    TQRImage *qrimCategoryTree_16;
    TQRImage *qrimAdditionTreeCategory_16;
    TQRLabel *qrlPairsOrder;
    TQRImage *qrimCategoryTree_32;
    TQRLabel *qrlSNF_1;
    TQRLabel *qrlSkill_1;
    TQRLabel *qrlClub_1;
    TQRLabel *qrlSNF_17;
    TQRLabel *qrlSkill_17;
    TQRLabel *qrlClub_17;
    TQRLabel *qrlSNF_9;
    TQRLabel *qrlSkill_9;
    TQRLabel *qrlSNF_19;
    TQRLabel *qrlSkill_19;
    TQRLabel *qrlClub_19;
    TQRLabel *qrlSNF_5;
    TQRLabel *qrlSkill_5;
    TQRLabel *qrlClub_5;
    TQRLabel *qrlSNF_21;
    TQRLabel *qrlSkill_21;
    TQRLabel *qrlClub_21;
    TQRLabel *qrlSNF_11;
    TQRLabel *qrlSkill_11;
    TQRLabel *qrlClub_11;
    TQRLabel *qrlSNF_23;
    TQRLabel *qrlSkill_23;
    TQRLabel *qrlClub_23;
    TQRLabel *qrlSNF_3;
    TQRLabel *qrlSkill_3;
    TQRLabel *qrlClub_3;
    TQRLabel *qrlSNF_25;
    TQRLabel *qrlSkill_25;
    TQRLabel *qrlClub_25;
    TQRLabel *qrlClub_13;
    TQRLabel *qrlSNF_27;
    TQRLabel *qrlSkill_13;
    TQRLabel *qrlSkill_27;
    TQRLabel *qrlClub_27;
    TQRLabel *qrlSNF_7;
    TQRLabel *qrlSkill_7;
    TQRLabel *qrlClub_7;
    TQRLabel *qrlSNF_29;
    TQRLabel *qrlSkill_29;
    TQRLabel *qrlClub_29;
    TQRLabel *qrlSNF_15;
    TQRLabel *qrlSkill_15;
    TQRLabel *qrlClub_15;
    TQRLabel *qrlSNF_31;
    TQRLabel *qrlSkill_31;
    TQRLabel *qrlClub_31;
    TQRLabel *qrlSNF_13;
    TQRLabel *qrlClub_9;
    TQRLabel *qrlSNF_2;
    TQRLabel *qrlSkill_2;
    TQRLabel *qrlClub_2;
    TQRLabel *qrlSNF_18;
    TQRLabel *qrlSkill_18;
    TQRLabel *qrlClub_18;
    TQRLabel *qrlSNF_10;
    TQRLabel *qrlSkill_10;
    TQRLabel *qrlClub_10;
    TQRLabel *qrlSNF_20;
    TQRLabel *qrlSkill_20;
    TQRLabel *qrlClub_20;
    TQRLabel *qrlSkill_6;
    TQRLabel *qrlSNF_6;
    TQRLabel *qrlClub_6;
    TQRLabel *qrlSNF_22;
    TQRLabel *qrlSkill_22;
    TQRLabel *qrlClub_22;
    TQRLabel *qrlSNF_12;
    TQRLabel *qrlSkill_12;
    TQRLabel *qrlClub_12;
    TQRLabel *qrlSNF_24;
    TQRLabel *qrlSkill_24;
    TQRLabel *qrlClub_24;
    TQRLabel *qrlSNF_4;
    TQRLabel *qrlSkill_4;
    TQRLabel *qrlClub_4;
    TQRLabel *qrlSNF_26;
    TQRLabel *qrlSkill_26;
    TQRLabel *qrlClub_26;
    TQRLabel *qrlSNF_14;
    TQRLabel *qrlSkill_14;
    TQRLabel *qrlClub_14;
    TQRLabel *qrlSNF_28;
    TQRLabel *qrlSkill_28;
    TQRLabel *qrlClub_28;
    TQRLabel *qrlSNF_8;
    TQRLabel *qrlSkill_8;
    TQRLabel *qrlClub_8;
    TQRLabel *qrlSNF_30;
    TQRLabel *qrlSkill_30;
    TQRLabel *qrlClub_30;
    TQRLabel *qrlSNF_16;
    TQRLabel *qrlClub_16;
    TQRLabel *qrlSkill_16;
    TQRLabel *qrlSNF_32;
    TQRLabel *qrlSkill_32;
    TQRLabel *qrlClub_32;
    TQRImage *qrimAdditionTreeCategory_32;
    void __fastcall qrdbtFemalePrint(TObject *sender, AnsiString &Value);
    void __fastcall qrbCategoryTreeBeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
    void __fastcall qrdbtCategoryStartWeightPrint(TObject *sender,
          AnsiString &Value);
    void __fastcall qrdbtCategoryEndWeightPrint(TObject *sender,
          AnsiString &Value);
private:	// User declarations
    //--Карнитка с деревом участников
    Graphics::TBitmap * treeview; 
public:		// User declarations
    __fastcall TfrmCategoryTreeReport(TComponent* Owner);
    //-- Просмотр и печать деревьев 
    void PreviewFightTrees(TList *categories);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCategoryTreeReport *frmCategoryTreeReport;
//---------------------------------------------------------------------------
#endif
