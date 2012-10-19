//---------------------------------------------------------------------------

#ifndef availCategoryEditUH
#define availCategoryEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmAvailCategoryEdit : public TForm
{
__published:	// IDE-managed Components
    TRadioGroup *rdgrpGender;
    TGroupBox *grboxWeightRange;
    TLabel *lblStartWeight;
    TMaskEdit *medtStartWeight;
    TLabel *lblEndWeight;
    TMaskEdit *medtEndWeight;
    TGroupBox *grboxAgeRange;
    TLabel *lblStartAge;
    TMaskEdit *medtStartAge;
    TLabel *lblEndAge;
    TMaskEdit *medtEndAge;
    TBitBtn *bbtnUpdate;
    TBitBtn *bbtnCancel;
    TGroupBox *grboxComments;
    TMemo *memComments;
        void __fastcall medtStartWeightExit(TObject *Sender);
        void __fastcall medtEndWeightExit(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    //-- Очистка полей
    void initFields(void); 
public:		// User declarations
    __fastcall TfrmAvailCategoryEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAvailCategoryEdit *frmAvailCategoryEdit;


 
//---------------------------------------------------------------------------
#endif
