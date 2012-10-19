//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "requestEditU.h"
#include "requestDM.h"
#include "requestCtrl.h"
#include "clubDM.h"
#include "personDM.h"
#include "clubEditU.h"
#include "clubCtrl.h"
#include "personEditU.h"
#include "currentStateDM.h"
#include "mainFormU.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmRequestEdit *frmRequestEdit;

//---------------------------------------------------------------------------
__fastcall TfrmRequestEdit::TfrmRequestEdit(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::dbgrdClubListTitleClick(TColumn *Column)
{
    resetCallback();
    //������������� ������� �� ���������� �������
    //��������� �������������� ������� ����������
    dmPersonDAO->setFilterCondition(lbledtClubQuickSearch->Text);
    switch(Column->Index){
        //��������� �� ����� �����
        case 0 :
            dmClubDAO->sortByField(ctfName);
            break;
        //����������� �� �������� ������
        case 1 :
            dmClubDAO->sortByField(ctfCity);
            break;
        //����������� �� ������
        case 2 :
            dmClubDAO->sortByField(ctfCountry);
            break;
        }
    //���������� ������� ������
    dmCurrentState->getClub().makeCurrent();
    setCallback();
}

void TfrmRequestEdit::changePersonSearchTableState(void){
    //��������� ������ ������ �������
    dmPersonDAO->setFilterCondition(lbledtPersonQuickSearch->Text);
    dmPersonDAO->filterByField(ptfSurname);
    //������� ������ ������� � �������
    dmCurrentState->getPerson().makeCurrent();
}

void TfrmRequestEdit::changeClubSearchTableState(void){
    //��������� ������ ������ �������
    dmClubDAO->setFilterCondition(lbledtClubQuickSearch->Text);
    dmClubDAO->filterByField(ctfName);
    //������� ������ ������� � �������
    dmCurrentState->getClub().makeCurrent();
}

//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::btnAddClubClick(TObject *Sender)
{
    resetCallback();
    //�������� ���� �������� ������
    dmCurrentState->setClub(TClub::getCurrent());
    dmCurrentState->setPerson(TPerson::getCurrent());
//    dbgrdPersonList->DataSource = NULL;
//    dbgrdClubList->DataSource = NULL;
    QuickSearchClear();
    //�������� ����� ���� � ���� ������
    frmClubEdit->ShowModal();
    changeClubSearchTableState();
    changePersonSearchTableState();
//    dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;
//    dbgrdClubList->DataSource = dmClubDAO->dsClubTable;
    setCallback();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::btnAddPersonClick(TObject *Sender)
{

    resetCallback();
    //������� ���� �������� ������
    dmCurrentState->setClub(TClub::getCurrent());
    dmCurrentState->setPerson(TPerson::getCurrent());
//    dbgrdPersonList->DataSource = NULL;
//    dbgrdClubList->DataSource = NULL;
    QuickSearchClear();
    //�������� ������� � ���� ������
    frmPersonEdit->ShowModal();
    changePersonSearchTableState();
    changeClubSearchTableState();
//    dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;
//    dbgrdClubList->DataSource = dmClubDAO->dsClubTable;
    setCallback();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::dbgrdPersonListTitleClick(TColumn *Column)
{
    resetCallback();
    //������������� �������, �� ���������� �������
    //��������� �������������� ������� ����������
    dmPersonDAO->setFilterCondition(lbledtPersonQuickSearch->Text);
    switch(Column->Index){
        //��������� �� �������
        case 0 :
            dmPersonDAO->sortByField(ptfSurname);
            break;
        //����������� �� �����
        case 1 :
            dmPersonDAO->sortByField(ptfName);
            break;
        //����������� �� ��������
        case 2 :
            dmPersonDAO->sortByField(ptfPatronymic);
            break;
        //����������� �� ������ ��������
        case 3 :
            dmPersonDAO->sortByField(ptfPhone);

        }
    //������� ������ ������� � �������
    dmCurrentState->getPerson().makeCurrent();
    setCallback();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::lbledtPersonQuickSearchChange(
      TObject *Sender)
{
    dbgrdPersonList->DataSource = NULL;
    //��������� ������ ������ �������
    changePersonSearchTableState();
    dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::FormShow(TObject *Sender)
{
    //���������� ��������� �������� (��� ����������)
    initFields();
    //���������� ������� ��������� ������ ��� ��������� �� ��������
    setCallback();
}
//---------------------------------------------------------------------------


void TfrmRequestEdit::initFields(void){
    //�������� ����������� ����
    QuickSearchClear();
    //��������� ������� � ��������� ����������
//    dbgrdClubList->DataSource = dmClubDAO->dsClubTable;
//    dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;

}
//---------------------------------------------------------------------------

void TfrmRequestEdit::QuickSearchClear(void){
    lbledtPersonQuickSearch->Clear();
    lbledtClubQuickSearch->Clear();
}


void __fastcall TfrmRequestEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //������� ������� ��������� ������
    resetCallback();
    //�������� ������� �� �������� ����������
//    dbgrdClubList->DataSource = NULL;
//    dbgrdPersonList->DataSource = NULL;
    //��������� ������, ���� ������ ������� � �����
   //������������ ��������� ������?
    if(ModalResult == mrOk){
        //������� ����������� ������
        TRequest *newObj = new TRequest(dmCurrentState->getCompetition().getId(),
                                        dmCurrentState->getClub().getId(),
                                        dmCurrentState->getPerson().getId(),
                                        memRequestComments->Text
                                        );

        //��������� �� ������
        AnsiString errmess;
        //��������� ��������� ������
        if(newObj->valid(errmess)){
            //��������� � ����
            newObj->store();
            newObj->extend(dmCurrentState->getPerson(), dmCurrentState->getClub());
            //�������� ������ � ������
            dmCurrentState->addRequestToList(*newObj);
            dmCurrentState->setRequest(*newObj);
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

void TfrmRequestEdit::setCallback(void){
    TClub::setRecordMoveCallback(clubRecordMoveAction);
    TPerson::setRecordMoveCallback(personRecordMoveAction);
    //��������� ������� � ��������� ����������
    dbgrdClubList->DataSource = dmClubDAO->dsClubTable;
    dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;
}

void TfrmRequestEdit::resetCallback(void){

    TClub::setRecordMoveCallback(NULL);
    TPerson::setRecordMoveCallback(NULL);

    //�������� ������� � ��������� ����������
    dbgrdClubList->DataSource = NULL;
    dbgrdPersonList->DataSource = NULL;
}
//---------------------------------------------------------------------------


void __fastcall TfrmRequestEdit::lbledtClubQuickSearchChange(
      TObject *Sender)
{
    dbgrdClubList->DataSource = NULL;
    //��������� ������ ������ �������
    changeClubSearchTableState();
    dbgrdClubList->DataSource = dmClubDAO->dsClubTable;
}
//---------------------------------------------------------------------------

void clubRecordMoveAction(void){
    //����� ������ ��������
    if(frmRequestEdit->Active){
        //���� ������������� ��������� ������� �� ������ ����
        if(TClub::getCurrent().getId() != dmCurrentState->getClub().getId()){
            //��������� ������� �� ��������� �������
            TPerson::setRecordMoveCallback(NULL);
            frmRequestEdit->dbgrdPersonList->DataSource = NULL;
            //������� �������, � ������������ � ��������� ������
            TPerson::makeCurrent(TClub::getCurrent().getPersonId());
            //������� �� �������
            dmCurrentState->setPerson(TPerson::getCurrent());
            //������� ����
            dmCurrentState->setClub(TClub::getCurrent());
            //������� ��������� ������� ������� � ���������
            TPerson::setRecordMoveCallback(personRecordMoveAction);
            frmRequestEdit->dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;
            }
        }
}

void personRecordMoveAction(void){
    //����� ������ ��������
    if(frmRequestEdit->Active){
        //��������, ���� ��������� ������������� ����� �������������
        if(dmCurrentState->getPerson().getId() != TPerson::getCurrent().getId()){
            //������� �������, � ������������ � ��������� ������
            dmCurrentState->setPerson(TPerson::getCurrent());
            }
        }
}


