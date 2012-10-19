//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "availCategoryFullEditU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAvailCategoryFullEdit *frmAvailCategoryFullEdit;
//---------------------------------------------------------------------------
__fastcall TfrmAvailCategoryFullEdit::TfrmAvailCategoryFullEdit(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*

TODO: It has to be implemented and completed.



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
//---------------------------------------------------------------------------

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


void TfrmManuallyAddCategoryEdit::InitFields(void){
    //-- ��� �������� � �����, �������������� ������� �����������
    setAvailCategoryTable(-1, -1, -1, -1);
    //������� ������ ������ ������
    createFightVersionList();
    mskedtStartAge->Clear();
    mskedtEndAge->Clear();
    mskedtStartWeight->Clear();
    mskedtEndWeight->Clear();
}


void TfrmManuallyAddCategoryEdit::setAvailCategoryTable(int sa, int ea, double sw, double ew){
        dmAvailCategoryDAO->setCategoryTable(sa, ea, sw, ew, female);
}

void TfrmManuallyAddCategoryEdit::getValidValues(int &sa, int &ea, double &sw, double &ew){
    try{
        //������� ��������� �������
        sa = StrToInt(mskedtStartAge->Text);
    }catch(EConvertError *e){
        sa = -1;
        }
    try{
        //������� �������� �������
        ea = StrToInt(mskedtEndAge->Text);
    }catch(EConvertError *e){
        ea = -1;
        }
    try{
        //������� ��������� ���
        sw = StrToFloat(FormatFloatValueText(mskedtStartWeight->Text));
    }catch(EConvertError *e){
        sw = -1;
        }
    try{
        //������� �������� ���
        ew = StrToFloat(FormatFloatValueText(mskedtEndWeight->Text));
    }catch(EConvertError *e){
        ew = -1;
        }
}



void __fastcall TfrmManuallyAddCategoryEdit::mskedtSearchChange(
      TObject *Sender)
{
    //-- ������������� ���������
    int sa=-1, ea=-1;
    double sw=-1, ew=-1;
    getValidValues(sa, ea, sw, ew);
    setAvailCategoryTable(sa, ea, sw, ew);
}
//---------------------------------------------------------------------------

*/
