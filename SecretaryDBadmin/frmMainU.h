//---------------------------------------------------------------------------

#ifndef frmMainUH
#define frmMainUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grboxLeftDBPane;
    TGroupBox *grboxRightDBPane;
    TStaticText *sttxtLeftDBFileName;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TStaticText *StaticText2;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
