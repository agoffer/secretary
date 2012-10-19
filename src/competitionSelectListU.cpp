//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "competitionSelectListU.h"
#include "competitionDM.h"
#include "currentStateDM.h"
#include "competitionCtrl.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCompetitionSelectList *frmCompetitionSelectList;
//---------------------------------------------------------------------------
__fastcall TfrmCompetitionSelectList::TfrmCompetitionSelectList(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCompetitionSelectList::FormShow(TObject *Sender)
{
    //-- �������� ����������� � ������������ ���� ������ ������������
    TDateTime max, min;
    TCompetition::getMinMaxBeginDate(min, max);

    dtpBeginDate->DateTime = min;
    dtpEndDate->DateTime = max;

    //������� ������ �� ��������� ���������
    dmCompetitionDAO->selectRangeExtendedCompetitions(dtpBeginDate->DateTime,
                                                     dtpEndDate->DateTime);
}
//---------------------------------------------------------------------------


void __fastcall TfrmCompetitionSelectList::dtpDateChange(
      TObject *Sender)
{
    //���� ��������, ���������� �������
    //������� ������ �� ��������� ���������
    dmCompetitionDAO->selectRangeExtendedCompetitions(dtpBeginDate->DateTime,
                                                     dtpEndDate->DateTime);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionSelectList::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //����� �������� ������������
    if(ModalResult == mrOk){
        //���������� ������� ������������, ��������� � �������
        dmCurrentState->setCompetition(TCompetition::getExtendedCurrent());
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionSelectList::bbtnDeleteCompetitionClick(
      TObject *Sender)
{
    if(MessageDlg("�� ������������� ������ ������� ��������� ������������?", mtConfirmation,
                TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo) {
                    return;
                }
    // ������� ��������� ������������
    dmCompetitionDAO->removeCurrent();
    // �������� ������ � ������� � ��������������
    dtpDateChange(NULL);
}
//---------------------------------------------------------------------------


