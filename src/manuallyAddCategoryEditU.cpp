//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "manuallyAddCategoryEditU.h"
#include "availCategoryEditU.h"
#include "fightVersionEditU.h"
#include "availCategoryDM.h"
#include "categoryEditU.h"
#include "currentStateDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmManuallyAddCategoryEdit *frmManuallyAddCategoryEdit;
//---------------------------------------------------------------------------
__fastcall TfrmManuallyAddCategoryEdit::TfrmManuallyAddCategoryEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmManuallyAddCategoryEdit::bbtnAddAvailCategoryClick(
      TObject *Sender)
{
    //��������� ������� ��������� ���������
    dmCurrentState->setAvailCategory(dmAvailCategoryDAO->getCurrent());
    //������� � ���������� ����� ���������
    //������� � ��������� ��������� ���������
    if(frmAvailCategoryEdit->ShowModal()==mrOk);
    //���������� �������
    mskedtSearchChange(NULL);
    //���������� ������ ��� ����� ������     
    dmCurrentState->getAvailCategory().makeCurrent();
}
//---------------------------------------------------------------------------
void __fastcall TfrmManuallyAddCategoryEdit::bbtnAddFightVersionClick(
      TObject *Sender)
{

    //������� � ���������� ����� ������ ������
    if(frmFightVersionEdit->ShowModal()==mrOk){
        //���������� ������ ������ ������ 
        clearFightVersionList();
        //������� ������ ������ ������
        createFightVersionList();
        //���������� ����������� ������, ��� �������
        cmboxFightVersion->ItemIndex =cmboxFightVersion->Items->Count - 1;
        cmboxFightVersion->Text = cmboxFightVersion->Items->Strings[cmboxFightVersion->ItemIndex]; 
        }
}


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

//---------------------------------------------------------------------------

void __fastcall TfrmManuallyAddCategoryEdit::FormShow(TObject *Sender)
{
    InitFields(); 
}
//---------------------------------------------------------------------------

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


void TfrmManuallyAddCategoryEdit::createFightVersionList(void){
    //������������ ������
    cmboxFightVersion->Items->Clear();
    for(int i=0; i < dmCurrentState->getFightVersionList()->Count; i++){
        cmboxFightVersion->Items->Add(((TFightVersion*)dmCurrentState->getFightVersionList()->Items[i])->getCode());
        }
    if(cmboxFightVersion->Items->Count){
        //������� ������ �������� �� ���������
        cmboxFightVersion->Text = cmboxFightVersion->Items->Strings[0];
        cmboxFightVersion->ItemIndex = 0;
        }
    else{
        cmboxFightVersion->ItemIndex = -1;
        }

}

void TfrmManuallyAddCategoryEdit::clearFightVersionList(void){
    //������� ��������
    cmboxFightVersion->Items->Clear();
}
void __fastcall TfrmManuallyAddCategoryEdit::FormHide(TObject *Sender)
{
    //�������� ������
    clearFightVersionList();     
}
//---------------------------------------------------------------------------


void __fastcall TfrmManuallyAddCategoryEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //������� ����� ��������� ��� ����� ��� ��������
   //������������ ��������� ������?
    if(ModalResult == mrOk){
        //������� ����������� ������
        TAvailCategory currentAC =TAvailCategory::getCurrent();
        TFightVersion currentFV = dmCurrentState->findFightVersionByCode(cmboxFightVersion->Text);
        TCategory *newObj = new TCategory(currentAC.getId(),
                                currentFV.getId(),
                                dmCurrentState->getCompetition().getId());
        //��������� �� ������
        AnsiString errmess;
        //��������� ��������� ������
        if(newObj->valid(errmess)){
            //��������� � ����
            newObj->store();
            //��������� ���������
            newObj->extend(currentAC,
                            currentFV,
                            dmCurrentState->getCompetition()                            
                            );
            //���������  ��������� � ������
            dmCurrentState->addCategoryToList(*newObj);
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

void __fastcall TfrmManuallyAddCategoryEdit::bbtnDeleteAvailCategoryClick(
      TObject *Sender)
{
  //������� ��������� "��������� ���������"

  TAvailCategory currentAC = TAvailCategory::getCurrent();
  if(MessageDlg(AnsiString("�� ������������� ������ ������� �������/���������� ���������: \n") +
  " - �������: " + IntToStr(currentAC.getStartAge()) +
  " - " + IntToStr(currentAC.getEndAge()) + " ���;\n" +
  " - ���: " + FloatToStr(currentAC.getStartWeight()) +
  " - " + FloatToStr(currentAC.getEndWeight()) + " ��;\n" +
  " - " + (currentAC.getFemale() ? "�������/�������;" : "�����/�������;"),
  mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes){
    //������� ������ � ����
    currentAC.remove(); 
    //�������� �������
    InitFields(); 
  }
}
//---------------------------------------------------------------------------

