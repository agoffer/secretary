//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "currentStateDM.h"
#include "competitionEditU.h"
#include "competitionRankEditU.h"
#include "competitionRankDM.h"
#include "competitionDM.h"
#include "dataSourceDM.h"




//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCompetitionEdit *frmCompetitionEdit;
//---------------------------------------------------------------------------
__fastcall TfrmCompetitionEdit::TfrmCompetitionEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

/* TODO: ������ ���� ����������. �������������� ������� ������������
����������� ����� ������������ � ������� ����. 
void __fastcall TfrmCompetitionEdit::bbtnAddCompetitionRankClick(
      TObject *Sender)
{
    frmCompetitionRankEdit->ShowModal();
    //���� �������� ������, �������� ������
    if(frmCompetitionRankEdit->ModalResult == mrOk){
        //���������� ������ �������� ������������
        destroyCompetitionRankList();
        //������� ������ ������������ ������
        createCompetitionRankList();
        //���������� ����������� ������, ��� �������
        cmboxCompetitionRank->Text =
            frmCompetitionRankEdit->lbledtCompetitionRankDescription->Text;
            cmboxCompetitionRank->ItemIndex =cmboxCompetitionRank->Items->Count - 1;
        }
}
*/
//---------------------------------------------------------------------------

void TfrmCompetitionEdit::createCompetitionRankList(void){
    //�������� ������ ������� ������������ �� ���� ������
    competitionRankList = TCompetitionRank::getAll();
    //������������ ������
    cmboxCompetitionRank->Items->Clear();
    for(int i=0; i < competitionRankList->Count; i++){
        cmboxCompetitionRank->Items->Add(((TCompetitionRank*)competitionRankList->Items[i])->getDescription());
        }
    if(cmboxCompetitionRank->Items->Count){
        //������� ������ �������� �� ���������
        cmboxCompetitionRank->Text = cmboxCompetitionRank->Items->Strings[0];
        cmboxCompetitionRank->ItemIndex = 0;
        } 
}
//---------------------------------------------------------------------------


void __fastcall TfrmCompetitionEdit::FormShow(TObject *Sender)
{
    //���������� ��������� �������� ����� (��� ����������) 
    InitFields();
}
//---------------------------------------------------------------------------

void TfrmCompetitionEdit::InitFields(void){
    //������� ������ �������� ������������
    createCompetitionRankList();
    //���������� ������� ����, � ����� ������
    dtpBeginCompetitionDate->Date = Now();
    dtpEndCompetitionDate->Date = Now();
    //�������� ���������� ���� �����������
    memCompetitionComments->Clear();
}
//---------------------------------------------------------------------------

void TfrmCompetitionEdit::destroyCompetitionRankList(void){
    //������� ��������
    cmboxCompetitionRank->Items->Clear();
    //������ ������
     destroyList(competitionRankList, etCOMPETITIONRANK);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionEdit::FormHide(TObject *Sender)
{
    //������� ������ �������� ������������
    destroyCompetitionRankList();
}
//---------------------------------------------------------------------------


void __fastcall TfrmCompetitionEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   //������������ ��������� ������?
    if(ModalResult == mrOk){
        //������� ������ ���������� ������������
        int competitionRankId = 0;
        if(competitionRankList){
            competitionRankId =
                ((TCompetitionRank*)competitionRankList->Items[cmboxCompetitionRank->ItemIndex])->getId();
            }

        //������� ����������� ������
        TCompetition *newObj = new TCompetition(dtpBeginCompetitionDate->Date,
                                                    dtpEndCompetitionDate->Date,
                                                    competitionRankId,
                                                    memCompetitionComments->Text);
        //��������� �� ������
        AnsiString errmess;
        //��������� ��������� ������
        if(newObj->valid(errmess)){
            //��������� � ����
            newObj->store();
            newObj->extend(*(TCompetitionRank*)competitionRankList->Items[cmboxCompetitionRank->ItemIndex]);             
            //���������� ������������
            dmCurrentState->setCompetition(*newObj);
            }
        //������ ����� �� �����, ����������
        else{
            //���������� ��������� �� ������
            MessageDlg(errmess,
                   mtError, TMsgDlgButtons() << mbOK, 0);

            //��������� �������� ����
            Action = caNone;
            }
        //������� ������   
        delete newObj;
        }
}
//---------------------------------------------------------------------------


