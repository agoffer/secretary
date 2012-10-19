//---------------------------------------------------------------------------

#ifndef requestClubReportUH
#define requestClubReportUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>

#include "reportDataSourceDM.h"

//---------------------------------------------------------------------------
class TfrmRequestClubReport : public TForm
{
__published:	// IDE-managed Components
    TQuickRep *qrRequestClubList;
    TQRBand *qrbRequestClub;
    TQRDBText *qrdbtSurname;
    TQRDBText *qrdbtClubName;
    TQRBand *qrbRequestClubListHeader;
    TQRLabel *qrlSNPHeader;
    TQRLabel *qrlClubNameHeader;
    TQRLabel *qrlExtendedHeader;
    TQRLabel *qrlStaticHeader;
    TQRLabel *qrlCompetitionRank;
    TQRLabel *qrlCompetitionDate;
    TQRDBText *qrdbtPhone;
    void __fastcall qrdbtSurnamePrint(TObject *sender, AnsiString &Value);
    void __fastcall qrRequestClubListBeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
    void __fastcall qrdbtClubNamePrint(TObject *sender, AnsiString &Value);
private:	// User declarations
    //—четчик участников
    int counter;
public:		// User declarations
    __fastcall TfrmRequestClubReport(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRequestClubReport *frmRequestClubReport;
//---------------------------------------------------------------------------
#endif
