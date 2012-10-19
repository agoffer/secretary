//---------------------------------------------------------------------------

#ifndef skillEditUH
#define skillEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfrmSkillEdit : public TForm
{
__published:	// IDE-managed Components
    TLabeledEdit *lbledtShortDescription;
    TLabeledEdit *lbledtFullDescription;
    TMaskEdit *medtWeight;
    TLabel *lblWeight;
    TMemo *memComments;
    TLabel *lblComments;
    TBitBtn *bbtnUpdateSkill;
    TBitBtn *bbtnCancelSkill;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    //-- Инициализация полей
    void InitFields(void); 
public:		// User declarations
    __fastcall TfrmSkillEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSkillEdit *frmSkillEdit;
//---------------------------------------------------------------------------
#endif
