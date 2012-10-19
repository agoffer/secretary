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
    // Транзакция для изменяемых данных
    TIBTransaction *transaction = dmCompetitionRankDAO->ibtCompetitionRank->Transaction;
    if (transaction->Active) {
        // Сохранить изменения пользователя в базе
        transaction->Commit();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionRankEdit::dbgCompetitionRankKeyUp(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == VK_DELETE) {
        if(MessageDlg("Вы действительно желаете удалить выбранный уровень соревнований?",
            mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo){
            //Нет, не удалять
            return;
        }
        // Удаляем текущую запись в таблице
        dbgCompetitionRank->DataSource->DataSet->Delete();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionRankEdit::FormShow(TObject *Sender)
{
    // Открыть таблицу с данными о статусах соревнований
    dmCompetitionRankDAO->ibtCompetitionRank->Open();
    // Открыть таблицу с распределением балов по местам
    dmCompetitionRankDAO->ibtScoreRanking->Open();

}
//---------------------------------------------------------------------------



void __fastcall TfrmCompetitionRankEdit::dbgrScoreRankingKeyUp(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == VK_DELETE) {
        if(MessageDlg("Вы действительно желаете удалить выбранное место и балы?",
            mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo){
            //Нет, не удалять
            return;
        }
        // Удаляем текущую запись в таблице
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

