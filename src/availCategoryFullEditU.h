//---------------------------------------------------------------------------

#ifndef availCategoryFullEditUH
#define availCategoryFullEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfrmAvailCategoryFullEdit : public TForm
{
__published:	// IDE-managed Components
  TGroupBox *grboxAvailCategory;
  TLabel *lblSearchAge;
  TLabel *lblSearchWeight;
  TDBGrid *dbgrAvailCategories;
  TMaskEdit *mskedtEndAge;
  TMaskEdit *mskedtEndWeight;
  TMaskEdit *mskedtStartAge;
  TMaskEdit *mskedtStartWeight;
  TGroupBox *grboxAddNewAvailCategory;
  TGroupBox *grboxWeightRange;
  TLabel *lblStartWeight;
  TLabel *lblEndWeight;
  TMaskEdit *medtStartWeight;
  TMaskEdit *medtEndWeight;
  TGroupBox *grboxAgeRange;
  TLabel *lblStartAge;
  TLabel *lblEndAge;
  TMaskEdit *medtStartAge;
  TMaskEdit *medtEndAge;
  TBitBtn *bbtnAddNew;
  TGroupBox *grboxComments;
  TMemo *memComments;
  TBitBtn *bbtnDeleteAvailCategory;
  TBitBtn *bbtnClose;
  TCheckBox *chboxMaleFemale;
private:	// User declarations
public:		// User declarations
  __fastcall TfrmAvailCategoryFullEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAvailCategoryFullEdit *frmAvailCategoryFullEdit;
//---------------------------------------------------------------------------
#endif
