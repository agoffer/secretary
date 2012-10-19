//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "skillEditU.h"
#include "skillCtrl.h"
#include "currentStateDM.h"
#include "dataSourceDM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSkillEdit *frmSkillEdit;
//---------------------------------------------------------------------------
__fastcall TfrmSkillEdit::TfrmSkillEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSkillEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   //������������ ��������� ������?
    if(ModalResult == mrOk){
        //������� ����������� ������
        TSkill *newObj = new TSkill(lbledtShortDescription->Text,
                                    lbledtFullDescription->Text,
                                    memComments->Text,
                                    StrToInt(medtWeight->Text.Trim()));
        //��������� �� ������
        AnsiString errmess;
        //��������� ��������� ������
        if(newObj->valid(errmess)){
            //��������� � ����
            newObj->store();
            //��������� � ������
            dmCurrentState->addSkillToList(*newObj);            
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
void __fastcall TfrmSkillEdit::FormShow(TObject *Sender)
{
    //���������� ��������� �������� ����� (��� ����������) 
    InitFields();    
}
//---------------------------------------------------------------------------


void TfrmSkillEdit::InitFields(void){
    //�������� ���� �����
    lbledtFullDescription->Clear();
    lbledtShortDescription->Clear();
    memComments->Clear();
    medtWeight->Clear();
}




