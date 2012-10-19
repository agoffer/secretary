//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "competitionRankEditU.h"
#include "competitionRankCtrl.h"
#include "competitionRankDM.h"
#include "dataSourceDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCompetitionRankEdit *frmCompetitionRankEdit;
//---------------------------------------------------------------------------
__fastcall TfrmCompetitionRankEdit::TfrmCompetitionRankEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionRankEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    // ���������� ��� ���������� ������
    TIBTransaction *transaction = dmCompetitionRankDAO->ibtCompetitionRank->Transaction;
    if (transaction->Active) {
        // ��������� ��������� ������������ � ����
        transaction->Commit();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionRankEdit::dbgCompetitionRankKeyUp(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == VK_DELETE) {
        if(MessageDlg("�� ������������� ������� ������� ��������� ������� ������������?",
            mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo){
            //���, �� �������
            return;
        }
        // ������� ������� ������ � �������
        dbgCompetitionRank->DataSource->DataSet->Delete();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionRankEdit::FormShow(TObject *Sender)
{
    // ������� ������� � ������� � �������� ������������
    dmCompetitionRankDAO->ibtCompetitionRank->Open();
    // ������� ������� � �������������� ����� �� ������
    dmCompetitionRankDAO->ibtScoreRanking->Open();

}
//---------------------------------------------------------------------------



void __fastcall TfrmCompetitionRankEdit::dbgrScoreRankingKeyUp(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == VK_DELETE) {
        if(MessageDlg("�� ������������� ������� ������� ��������� ����� � ����?",
            mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo){
            //���, �� �������
            return;
        }
        // ������� ������� ������ � �������
        dbgrScoreRanking->DataSource->DataSet->Delete();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionRankEdit::bbtnUpdateCompetitionRankClick(
      TObject *Sender)
{
    if (dbgCompetitionRank->DataSource->State == dsInsert ||
        dbgCompetitionRank->DataSource->State == dsEdit) {
            dbgCompetitionRank->DataSource->DataSet->Post();
        }
    if (dbgrScoreRanking->DataSource->State == dsInsert ||
        dbgrScoreRanking->DataSource->State == dsEdit) {
            dbgrScoreRanking->DataSource->DataSet->Post();
        }
}
//---------------------------------------------------------------------------

