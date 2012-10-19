//---------------------------------------------------------------------------

#ifndef fightVersionEditUH
#define fightVersionEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmFightVersionEdit : public TForm
{
__published:	// IDE-managed Components
    TLabeledEdit *lbledtCode;
    TLabeledEdit *lbledtDescription;
    TMemo *memComments;
    TLabel *lblComments;
    TBitBtn *bbtnUpdateFightVersion;
    TBitBtn *bbtnCancelFightVersion;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    void InitFields(void);
public:		// User declarations
    __fastcall TfrmFightVersionEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmFightVersionEdit *frmFightVersionEdit;
//---------------------------------------------------------------------------
#endif
