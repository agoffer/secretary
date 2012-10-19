//---------------------------------------------------------------------------

#ifndef competitionRankEditUH
#define competitionRankEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmCompetitionRankEdit : public TForm
{
__published:	// IDE-managed Components
    TBitBtn *bbtnUpdateCompetitionRank;
    TLabel *lblHint;
    TGroupBox *grboxCompetitionRank;
    TDBGrid *dbgCompetitionRank;
    TGroupBox *grboxRankScoring;
    TDBGrid *dbgrScoreRanking;
    TLabel *lblHintDetail;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall dbgCompetitionRankKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall dbgrScoreRankingKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall bbtnUpdateCompetitionRankClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmCompetitionRankEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCompetitionRankEdit *frmCompetitionRankEdit;
//---------------------------------------------------------------------------
#endif
