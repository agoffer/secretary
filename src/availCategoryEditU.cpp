//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "utils.h"

#include "availCategoryEditU.h"
#include "availCategoryCtrl.h"
#include "currentStateDM.h"
#include "dataSourceDM.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAvailCategoryEdit *frmAvailCategoryEdit;






//---------------------------------------------------------------------------
__fastcall TfrmAvailCategoryEdit::TfrmAvailCategoryEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAvailCategoryEdit::medtStartWeightExit(TObject *Sender)
{
        medtStartWeight->Text = FormatFloatValueText(medtStartWeight->Text);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAvailCategoryEdit::medtEndWeightExit(TObject *Sender)
{
        medtEndWeight->Text = FormatFloatValueText(medtEndWeight->Text);
}
//---------------------------------------------------------------------------


void __fastcall TfrmAvailCategoryEdit::FormShow(TObject *Sender)
{
    //������������� ����� ���������� ����������
    initFields();     
}
//---------------------------------------------------------------------------

void TfrmAvailCategoryEdit::initFields(void){
    //������� ���� ��������
    medtStartAge->Clear();
    medtEndAge->Clear();
    //�������� ���� ����
    medtStartWeight->Clear();
    medtEndWeight->Clear();
    //���������� ��� ��������� �� ��������� (�������)
    rdgrpGender->ItemIndex = 0;
    //������ �����������
    memComments->Clear();
}

void __fastcall TfrmAvailCategoryEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   //������� ��������� ������, ��� ��������� �����
   //������������ ��������� ������?
    if(ModalResult == mrOk){
        //������� ����������� ������
        TAvailCategory *newObj = new TAvailCategory(StrToInt(medtStartAge->Text.Trim()),
                                                    StrToInt(medtEndAge->Text.Trim()),
                                                    StrToFloat(medtStartWeight->Text),
                                                    StrToFloat(medtEndWeight->Text),
                                                    rdgrpGender->ItemIndex?true:false,
                                                    memComments->Text);
        //��������� �� ������
        AnsiString errmess;
        //��������� ��������� ������
        if(newObj->valid(errmess)){
            //��������� � ����
            newObj->store();
            //��������� ��������� ��������� � ������
            dmCurrentState->addAvailCategoryToList(*newObj);
            dmCurrentState->setAvailCategory(*newObj);
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



