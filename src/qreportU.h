//---------------------------------------------------------------------------

#ifndef qreportUH
#define qreportUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmQreport : public TForm
{
__published:	// IDE-managed Components
    TQuickRep *qrCategory;
    TQRBand *DetailBand1;
    TQRSubDetail *QRSubDetail1;
    TQRDBText *QRDBText1;
    TQRDBText *QRDBText2;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmQreport(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmQreport *frmQreport;
//---------------------------------------------------------------------------
#endif
