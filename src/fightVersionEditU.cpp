//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fightVersionEditU.h"
#include "fightVersionCtrl.h"
#include "currentStateDM.h"
#include "dataSourceDM.h" 
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmFightVersionEdit *frmFightVersionEdit;
//---------------------------------------------------------------------------
__fastcall TfrmFightVersionEdit::TfrmFightVersionEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmFightVersionEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   //������������ ��������� ������?
    if(ModalResult == mrOk){
        //������� ����������� ������
        TFightVersion *newObj = new TFightVersion(lbledtCode->Text, lbledtDescription->Text,
                                    memComments->Text);
        //��������� �� ������
        AnsiString errmess;
        //��������� ��������� ������
        if(newObj->valid(errmess)){
            //��������� � ����
            newObj->store();
            //��������� � ������
            dmCurrentState->addFightVersionToList(*newObj);
            //��������� ������� ������ ������
            dmCurrentState->setFightVersion(*newObj);             
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
void __fastcall TfrmFightVersionEdit::FormShow(TObject *Sender)
{
    //���������� ��������� �������� ����� (��� ����������) 
    InitFields();    
}
//---------------------------------------------------------------------------


void TfrmFightVersionEdit::InitFields(void){
    //�������� ���� �����
    lbledtCode->Clear();
    lbledtDescription->Clear();
    memComments->Clear();
}
