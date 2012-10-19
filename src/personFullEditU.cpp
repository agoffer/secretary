//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "personFullEditU.h"
#include "personDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPersonFullEdit *frmPersonFullEdit;
//---------------------------------------------------------------------------
__fastcall TfrmPersonFullEdit::TfrmPersonFullEdit(TComponent* Owner)
    : TForm(Owner)
{
}

void __fastcall TfrmPersonFullEdit::FormShow(TObject *Sender)
{
    //������������� �����.
    InitForm();
}
//---------------------------------------------------------------------------

/**
 * ������������� ����� ��� �������� ����.
 * ����� ��������������� ����� � DataSourse
 * ��� ������ � �����������, � ��� �� ���������
 * ������, ��������������� ����� � �.�.
 */
void TfrmPersonFullEdit::InitForm() {
    initTables();
}

void TfrmPersonFullEdit::initTables() {
    //������� ������ �������
    dmPersonDAO->setScrollCallback(NULL);
    lbledtLeftPaneSurnameFilter->Text = "";
    changeMasterTable("", "");
    changeSlaveTable("", "");
    onScrollPopulateEditFields();
    // ���������� ������� ��������� ������, ������� �����
    // ��������� ���� ��� ��������������, ��� ��������� ������ � ����������
    dmPersonDAO->setScrollCallback(onScrollPopulateEditFields);
}

/**
 * �������� ��������� ����������� �������, � ������� ��� ������.
 * ������ �������� � ����������� � ������������� ��������.
 */
void TfrmPersonFullEdit::changeSlaveTable(AnsiString surnameFilter, AnsiString nameFilter) {
    dbgrdPersonToUseList->DataSource = NULL;
    dmPersonDAO->refreshSlaveTable(surnameFilter);
    dbgrdPersonToUseList->DataSource = dmPersonDAO->dsPersonSlaveTable;
}

/**
 * �������� ��������� ������� �������, � ������� ��� ��������������.
 * ������ �������� � ����������� � ������������� ��������.
 */
void TfrmPersonFullEdit::changeMasterTable(AnsiString surnameFilter, AnsiString nameFilter) {
    dbgrdPersonEditList->DataSource  = NULL;
    //��������� ������ ������ �������
    dmPersonDAO->setFilterCondition(surnameFilter);
    dmPersonDAO->filterByField(ptfSurname);
    dbgrdPersonEditList->DataSource = dmPersonDAO->dsPersonTable;
}


void __fastcall TfrmPersonFullEdit::lbledtLeftPaneSurnameFilterChange(
      TObject *Sender)
{
    AnsiString filterText = lbledtLeftPaneSurnameFilter->Text;
    lbledtRightPaneSurnameFilter->Text = filterText;
    changeMasterTable(filterText, "");
}
//---------------------------------------------------------------------------



void __fastcall TfrmPersonFullEdit::lbledtRightPaneSurnameFilterChange(
      TObject *Sender)
{
    AnsiString filterText = lbledtRightPaneSurnameFilter->Text;
    changeSlaveTable(filterText, "");
}
//---------------------------------------------------------------------------

/**
 * �������� ��������� �������. ��� ���� ��������� ��� ������
 ���������� � ������ ��������. ��� ������� � �������������, ������ � �.�.
 */
void __fastcall TfrmPersonFullEdit::bbtnDeleteClick(TObject *Sender)
{
    // ������� ������ ����� ����, ��� ����������� �� ����
    TPerson personToDelete = dmPersonDAO->getCurrent();
    AnsiString warningMessage = "�� ����������� ������� �������: \n" +
    personToDelete.getSurname() +  " " +
    personToDelete.getName() + " " +
    personToDelete.getPatronymic() + ", " +
    personToDelete.getDob() + "\n������ � ��� ����� ������� ��� ������, " +
    "� ������� ��� ����������� - ���������, ������ � �.�.\n" +
    "�������� ������� �������� ������� ������� ������.\n�� ������������� ����������� �� ��������?";
    if(mrYes == MessageDlg(warningMessage, mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0)) {
        dmPersonDAO->deleteCurrent();
        initTables();
        }
}
//---------------------------------------------------------------------------



void onScrollPopulateEditFields(void) {
    TPerson selectedPerson = dmPersonDAO->getCurrent();
    frmPersonFullEdit->lbledtSurname->Text = selectedPerson.getSurname();
    frmPersonFullEdit->lbledtName->Text = selectedPerson.getName();
    frmPersonFullEdit->lbledtPatronymic->Text = selectedPerson.getPatronymic();
    frmPersonFullEdit->dtpDOB->Date = selectedPerson.getDob();
    frmPersonFullEdit->chboxFemale->Checked = selectedPerson.getFemale();
    frmPersonFullEdit->memComments->Text = selectedPerson.getAdditions();
    frmPersonFullEdit->lbledtPhone->Text = selectedPerson.getPhone();
}

void __fastcall TfrmPersonFullEdit::bbtnUpdateClick(TObject *Sender)
{
    TPerson selectedPerson = dmPersonDAO->getCurrent();
    // �������� ���������� ������ ������ �������
    selectedPerson.setSurname(lbledtSurname->Text);
    selectedPerson.setName(lbledtName->Text);
    selectedPerson.setPatronymic(lbledtPatronymic->Text);
    selectedPerson.setDob(dtpDOB->Date);
    selectedPerson.setFemale(chboxFemale->Checked);
    selectedPerson.setPhone(lbledtPhone->Text);
    selectedPerson.setAdditions(memComments->Text);
    // � ��������
    dmPersonDAO->store(selectedPerson);
    // ����������� ������� � ������� �������� ������� ������
    initTables();
    dmPersonDAO->makeCurrent(selectedPerson);
}
//---------------------------------------------------------------------------

/**
 * ������ ������ ����� �������, ������� ������.
 */
void __fastcall TfrmPersonFullEdit::bbtnReplaceClick(TObject *Sender)
{
    // ������� ������ ������, ��� ����������� ����������
    TPerson personToDelete = dmPersonDAO->getCurrent();
    TPerson personToUse = dmPersonDAO->getCurrentSlave();

    AnsiString warningMessage = "������ �������: \n" +
    personToDelete.getSurname() +  " " +
    personToDelete.getName() + " " +
    personToDelete.getPatronymic() + ", " +
    personToDelete.getDob() + "\n\n����� �������� ������� ������ �������: \n" +
    personToUse.getSurname() +  " " +
    personToUse.getName() + " " +
    personToUse.getPatronymic() + ", " +
    personToUse.getDob() +
    "\n\n��������� ��������?";
    if(mrYes == MessageDlg(warningMessage, mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0)) {
        dmPersonDAO->changePersonalData(dmPersonDAO->ibqPersonSlaveTable, dmPersonDAO->ibqPersonAll);
        initTables();
        AnsiString infoMessage = "������ �������: \n" +
            personToDelete.getSurname() +  " " +
            personToDelete.getName() + " " +
            personToDelete.getPatronymic() + ", " +
            personToDelete.getDob() + "\n ���� ������� ��������.";
            MessageDlg(infoMessage, mtInformation, TMsgDlgButtons() << mbOK, 0);
        }
}
//---------------------------------------------------------------------------

