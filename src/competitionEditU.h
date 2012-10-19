//---------------------------------------------------------------------------

#ifndef competitionEditUH
#define competitionEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <DBCtrls.hpp>


#include "competitionRankCtrl.h"
//---------------------------------------------------------------------------
class TfrmCompetitionEdit : public TForm
{
__published:	// IDE-managed Components
    TDateTimePicker *dtpBeginCompetitionDate;
    TDateTimePicker *dtpEndCompetitionDate;
    TLabel *lblBeginCompetitionDate;
    TLabel *lblEndCompetitionDate;
    TMemo *memCompetitionComments;
    TLabel *lblCompetitionComments;
    TLabel *lblCompetitionRank;
    TBitBtn *bbtnUpdateCompetition;
    TBitBtn *bbtnCancelCompetition;
    TComboBox *cmboxCompetitionRank;
    // void __fastcall bbtnAddCompetitionRankClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    //-- ������� � ���������� ��������� �������� �����
    void InitFields(void); 
    //-- ������� ������ �������� ������������
    void createCompetitionRankList(void);
    //-- ���������� ������ �������� ������������
    void destroyCompetitionRankList(void); 
    //-- ������ �������� ������������
    TList * competitionRankList; 

public:		// User declarations
    __fastcall TfrmCompetitionEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCompetitionEdit *frmCompetitionEdit;
//---------------------------------------------------------------------------
#endif
