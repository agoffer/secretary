//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "clubEditU.h"
#include "personDM.h"
#include "personEditU.h"
#include "clubCtrl.h"
#include "currentStateDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmClubEdit *frmClubEdit;
//---------------------------------------------------------------------------
__fastcall TfrmClubEdit::TfrmClubEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmClubEdit::btnAddPersonClick(TObject *Sender)
{
    //��������� �������� ��������
    dmCurrentState->setPerson(TPerson::getCurrent());  
    //�������� �������� � ���� ������
    frmPersonEdit->ShowModal();
    //����������� ������� � ��������
    lbledtPersonQuickSearchChange(Sender);
    //������� �������� �������� ����������
    dmCurrentState->getPerson().makeCurrent();
}
//---------------------------------------------------------------------------
void __fastcall TfrmClubEdit::dbgrdPersonListTitleClick(TColumn *Column)
{
    //���������� ������� �������
    dmPersonDAO->setFilterCondition(lbledtPersonQuickSearch->Text);
   //������������� �������, �� ���������� �������
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
}
//---------------------------------------------------------------------------


void __fastcall TfrmClubEdit::lbledtPersonQuickSearchChange(TObject *Sender)
{
    //��������� ������ ������ �������
    dmPersonDAO->setFilterCondition(lbledtPersonQuickSearch->Text);
    dmPersonDAO->filterByField(ptfSurname);
}
//---------------------------------------------------------------------------
void __fastcall TfrmClubEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //��������� ������, ���� ������ ������� � �����
   //������������ ��������� ������?
    if(ModalResult == mrOk){
        //������� �������������/������������ �������
        //������� ����������� ������
        TClub *newObj = new TClub(lbledtClubName->Text, lbledtClubShortName->Text,
                                    lbledtClubCity->Text,
                                    lbledtClubCountry->Text,
                                    dmCurrentState->getPerson().getId(),
                                    memClubAdditions->Text);
        //��������� �� ������
        AnsiString errmess;
        //��������� ��������� ������
        if(newObj->valid(errmess)){
            //��������� � ����
            newObj->store();
            dmCurrentState->setClub(*newObj); 
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


void TfrmClubEdit::initFields(void){
    //�������� ����
    lbledtClubName->Clear();
    lbledtClubCity->Clear();
    lbledtClubCountry->Clear();
    memClubAdditions->Clear();
    lbledtPersonQuickSearch->Clear(); 



}
void __fastcall TfrmClubEdit::FormShow(TObject *Sender)
{
    //���������������� ���� ���������� ����������
    initFields();     
}
//---------------------------------------------------------------------------

