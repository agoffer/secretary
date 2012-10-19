//---------------------------------------------------------------------------

#ifndef resultEnterEditUH
#define resultEnterEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <DBCtrls.hpp>

#include "competitorCtrl.h"

//---------------------------------------------------------------------------
class TfrmResultEnterEdit : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grboxCompetitorSearch;
    TDBGrid *dbgrdCompetitorList;
    TGroupBox *grboxCompetitorInfo;
    TGroupBox *grboxSearchCondition;
    TLabeledEdit *lbledtCompetitorSurname;
    TLabeledEdit *lbledtCompetitorClub;
    TLabel *lblCompetitorSurname;
    TLabel *lblCompetitorClub;
    TLabel *blbCompetitorAge;
    TLabel *lblCompetitorWeight;
    TGroupBox *grboxResultEnter;
    TMaskEdit *mskedtCompetitorShootScore;
    TLabel *lblCompetitorShootScore;
    TBitBtn *bbtnAddResult;
    TBitBtn *bbtnClose;
    TDBText *dbtxtCompetitorName;
    TDBText *dbtxtCompetitorPatronymic;
    TDBText *dbtxtCompetitorClub;
    TDBText *dbtxtCompetitorSurname;
    TLabel *lblCompetitorName;
    TLabel *lblCompetitorPatronymic;
    TDBText *dbtxtCompetitorAge;
    TDBText *dbtxtCompetitorWeight;
    TLabel *lblNewShootResult;
    TLabel *lblCompetitorCrossTime;
    TMaskEdit *mskedtCompetitorCrossTime;
    TLabel *lblNewCrossResult;
    void __fastcall lbledtCompetitorSurnameChange(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall mskedtCompetitorShootScoreChange(TObject *Sender);
    void __fastcall bbtnAddResultClick(TObject *Sender);
    void __fastcall mskedtCompetitorCrossTimeChange(TObject *Sender);
private:	// User declarations
    void InitFields(void);
    void changeCompetitorSearchTableState(void);
    void resetCallback(void);
    void setCallback(void);


public:		// User declarations
    __fastcall TfrmResultEnterEdit(TComponent* Owner);
    //Отобразить, сохранить результат
    void showResult(void);
    void storeResult(void);
    //поменять текущего участника 
    void changeCompetitor(void);         
    TCompetitor currentCompetitor;    
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmResultEnterEdit *frmResultEnterEdit;

void competitorResultRecordMoveAction(void); 
//---------------------------------------------------------------------------
#endif
