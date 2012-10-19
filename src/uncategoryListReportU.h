//---------------------------------------------------------------------------

#ifndef uncategoryListReportUH
#define uncategoryListReportUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmUncategoryListReport : public TForm
{
__published:	// IDE-managed Components
    TQuickRep *qrUncategoryList;
    TQRBand *qrbCompetitor;
    TQRDBText *qrdbtSurname;
    TQRDBText *qrdbtClubName;
    TQRLabel *qrlUncategoryFV;
    TQRLabel *qrlExtendedFV;
    TQRBand *qrbUncategoryListHeader;
    TQRLabel *qrlSNPHeader;
    TQRLabel *qrlClubNameHeader;
    TQRLabel *qrlUncategoryHeader;
    TQRLabel *qrlExtendedHeader;
    TQRLabel *qrlStaticHeader;
    TQRLabel *qrlCompetitionRank;
    TQRLabel *qrlCompetitionDate;
    void __fastcall qrdbtSurnamePrint(TObject *sender, AnsiString &Value);
    void __fastcall qrUncategoryListBeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
private:	// User declarations
    //Счетчик участников 
    int counter;
    //-- Список боевых версий, которые небыли распределены
    AnsiString getUncategoryList(int competitorId);
    //-- Список боевых версий, которыми была расширена заявка участника
    AnsiString getExtendedList(int competitorId);
public:		// User declarations
    __fastcall TfrmUncategoryListReport(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUncategoryListReport *frmUncategoryListReport;
//---------------------------------------------------------------------------
#endif
