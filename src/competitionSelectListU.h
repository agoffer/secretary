//---------------------------------------------------------------------------

#ifndef competitionSelectListUH
#define competitionSelectListUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>



#include "competitionDM.h"
//---------------------------------------------------------------------------
class TfrmCompetitionSelectList : public TForm
{
__published:	// IDE-managed Components
    TDBGrid *dbgrdCompetitionList;
    TDateTimePicker *dtpBeginDate;
    TDateTimePicker *dtpEndDate;
    TBitBtn *bbtnSelect;
    TBitBtn *bbtnCancel;
    TLabel *lblBeginDate;
    TLabel *lblEndDate;
    TBitBtn *bbtnDeleteCompetition;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall dtpDateChange(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall bbtnDeleteCompetitionClick(TObject *Sender);
private:	// User declarations

public:		// User declarations
    __fastcall TfrmCompetitionSelectList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCompetitionSelectList *frmCompetitionSelectList;
//---------------------------------------------------------------------------
#endif
