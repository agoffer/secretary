//---------------------------------------------------------------------------

#include <vcl.h>
#include <strutils.hpp>
#pragma hdrstop

#include "resultEnterEditU.h"
#include "competitorDM.h"

#include "currentStateDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmResultEnterEdit *frmResultEnterEdit;
//---------------------------------------------------------------------------
__fastcall TfrmResultEnterEdit::TfrmResultEnterEdit(TComponent* Owner)
    : TForm(Owner)
{
}

void TfrmResultEnterEdit::changeCompetitorSearchTableState(void){

    //��������� ������ ������ �������
    dmCompetitorDAO->setFilterCondition_1(lbledtCompetitorSurname->Text);
    //��������� ������ ������ �� �������� �����
    dmCompetitorDAO->setFilterCondition_2(lbledtCompetitorClub->Text);
    dmCompetitorDAO->filterByField(dmCurrentState->getCompetition().getId(),
                                   ctfSurname, ctfClub_Name);

    //������� ������ ������� � �������
//    dmCurrentState->getClub().makeCurrent(); �� �����, ���� ��� 
    //������� �������� ��������� 
    changeCompetitor(); 

}

//---------------------------------------------------------------------------
void __fastcall TfrmResultEnterEdit::lbledtCompetitorSurnameChange(TObject *Sender)
{
    resetCallback();
    //-- ���������� ���� ����������, ������������� � ������� ������
    dbgrdCompetitorList->DataSource = NULL;
    //��������� ������ ������ �������
    changeCompetitorSearchTableState();
    dbgrdCompetitorList->DataSource = dmCompetitorDAO->dsCompetitorExtended;
    setCallback();
    //�������� ���������
    showResult();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultEnterEdit::FormShow(TObject *Sender)
{
    //-- ���������������� �����
    InitFields();
    changeCompetitor();
    showResult();
    setCallback();
}
//---------------------------------------------------------------------------



void TfrmResultEnterEdit::InitFields(void){
    //�������� ���� ��������
    lbledtCompetitorSurname->Clear();
    lbledtCompetitorClub->Clear();
}


void TfrmResultEnterEdit::changeCompetitor(void){
    //������� ������ ���������
    currentCompetitor = TCompetitor::getExtendedTableCurrent();
    //��������� ���������� ��� ���������
    currentCompetitor.loadResult();
}


void competitorResultRecordMoveAction(void){
    //����� ������ ��������
    if(frmResultEnterEdit->Active){
        //������� �������� ���������
        frmResultEnterEdit->changeCompetitor();
        //���������� ���������
        frmResultEnterEdit->lblNewShootResult->Visible = false;
        frmResultEnterEdit->showResult();
        }

}


void __fastcall TfrmResultEnterEdit::mskedtCompetitorShootScoreChange(
      TObject *Sender)
{
    //���������� ����� ��������� ��������
    lblNewShootResult->Visible = true;
}

void __fastcall TfrmResultEnterEdit::mskedtCompetitorCrossTimeChange(TObject *Sender)
{
    //���������� ����� ��������� ��������
    lblNewCrossResult->Visible = true;
}
//---------------------------------------------------------------------------



void TfrmResultEnterEdit::showResult(void){
    //���������� ��������� �������� �� �����, ��� ���������� ���������
    mskedtCompetitorShootScore->Text = IntToStr(currentCompetitor.result.getShootScore());
    lblNewShootResult->Visible = false;
    //���������� ��������� ������ �� �����, ��� ���������� ���������
    mskedtCompetitorCrossTime->Text = currentCompetitor.result.getCrossTime();
    lblNewCrossResult->Visible = false;
}

void TfrmResultEnterEdit::storeResult(void){
    //-- ������������� ��������� ��� ���������
    AnsiString shootRes = frmResultEnterEdit->mskedtCompetitorShootScore->Text.Trim();
    if(shootRes=="") shootRes = "-1"; 
    currentCompetitor.result.setShootScore(StrToInt(shootRes));
    AnsiString crossTime = AnsiReplaceStr(frmResultEnterEdit->mskedtCompetitorCrossTime->Text,
                                            " ", "0");
    currentCompetitor.result.setCrossTime(crossTime);
    currentCompetitor.storeResult();
    lblNewShootResult->Visible = false;
    lblNewCrossResult->Visible = false;    
}


//---------------------------------------------------------------------------

void __fastcall TfrmResultEnterEdit::bbtnAddResultClick(TObject *Sender)
{
    //��������� ���������
    storeResult();
    //�������� ������� ����������
    changeCompetitorSearchTableState();
    lbledtCompetitorSurname->SetFocus();
}
//---------------------------------------------------------------------------


void TfrmResultEnterEdit::setCallback(void){
    TCompetitor::setRecordMoveCallback(competitorResultRecordMoveAction);
}


void TfrmResultEnterEdit::resetCallback(void){
    TCompetitor::setRecordMoveCallback(NULL);
}

