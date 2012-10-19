//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "personEditU.h"
#include "personCtrl.h"
#include "currentStateDM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPersonEdit *frmPersonEdit;
//---------------------------------------------------------------------------
__fastcall TfrmPersonEdit::TfrmPersonEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPersonEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //������� ��������� ������, ��� ��������� �����
   //������������ ��������� ������?
    if(ModalResult == mrOk){
        //������� ����������� ������
        TPerson *newObj = new TPerson(lbledtSurname->Text,
                                        lbledtName->Text,
                                        lbledtPatronymic->Text,
                                        dtpDOB->Date,
                                        lbledtPhone->Text,
                                        chboxFemale->Checked,
                                        memAdditions->Text);
        //��������� �� ������
        AnsiString errmess;
        //��������� ��������� ������
        if(newObj->valid(errmess)){
            //��������� � ����
            newObj->store();
            //���������� �������� ���������
            dmCurrentState->setPerson(*newObj);
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


void TfrmPersonEdit::initFields(void){
    //�������� ��� ����
    lbledtSurname->Clear();
    lbledtName->Clear();
    lbledtPatronymic->Clear();
    lbledtPhone->Clear();
    memAdditions->Clear();
    chboxFemale->Checked = false; 
    dtpDOB->Date = Now();
}
void __fastcall TfrmPersonEdit::FormShow(TObject *Sender)
{
    //���������������� ���� ���������� ����������
    initFields(); //�������� ����, ��� ���������� ������     
}
//---------------------------------------------------------------------------


