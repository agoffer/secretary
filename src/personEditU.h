//---------------------------------------------------------------------------

#ifndef personEditUH
#define personEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmPersonEdit : public TForm
{
__published:	// IDE-managed Components
    TLabeledEdit *lbledtSurname;
    TLabeledEdit *lbledtName;
    TLabeledEdit *lbledtPatronymic;
    TLabeledEdit *lbledtPhone;
    TDateTimePicker *dtpDOB;
    TLabel *lblDOB;
    TMemo *memAdditions;
    TLabel *lblAdditions;
    TBitBtn *bbtnUpdatePerson;
    TBitBtn *bbtnCancelPerson;
    TCheckBox *chboxFemale;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    //-- Установить начальные значения полей, при добавлении
    void initFields(void); 
public:		// User declarations
    __fastcall TfrmPersonEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPersonEdit *frmPersonEdit;
//---------------------------------------------------------------------------
#endif
