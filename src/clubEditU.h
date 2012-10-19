//---------------------------------------------------------------------------

#ifndef clubEditUH
#define clubEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmClubEdit : public TForm
{
__published:	// IDE-managed Components
    TLabeledEdit *lbledtClubName;
    TLabeledEdit *lbledtClubCountry;
    TLabeledEdit *lbledtClubCity;
    TMemo *memClubAdditions;
    TLabel *lblClubAdditions;
    TGroupBox *grboxRepresentative;
    TDBGrid *dbgrdPersonList;
    TLabeledEdit *lbledtPersonQuickSearch;
    TButton *btnAddPerson;
    TBitBtn *bbtnUpdateClub;
    TBitBtn *bbtnCancelClub;
    TLabeledEdit *lbledtClubShortName;
    void __fastcall btnAddPersonClick(TObject *Sender);
    void __fastcall dbgrdPersonListTitleClick(TColumn *Column);
    void __fastcall lbledtPersonQuickSearchChange(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    //--Установить начальные значения полей
    void initFields(void);
public:		// User declarations
    __fastcall TfrmClubEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClubEdit *frmClubEdit;
//---------------------------------------------------------------------------
#endif
