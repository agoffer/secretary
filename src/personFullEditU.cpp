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
    //Инициализация формы.
    InitForm();
}
//---------------------------------------------------------------------------

/**
 * Инициализация формы при открытии окна.
 * Здесь устанавливается связь с DataSourse
 * для таблиц с участниками, а так же очищается
 * фильтр, устанавливается фокус и т.п.
 */
void TfrmPersonFullEdit::InitForm() {
    initTables();
}

void TfrmPersonFullEdit::initTables() {
    //Обновим данные таблицы
    dmPersonDAO->setScrollCallback(NULL);
    lbledtLeftPaneSurnameFilter->Text = "";
    changeMasterTable("", "");
    changeSlaveTable("", "");
    onScrollPopulateEditFields();
    // Установить функцию обратного вызова, которая будет
    // заполнять поля для редактирования, при изменении строки с участником
    dmPersonDAO->setScrollCallback(onScrollPopulateEditFields);
}

/**
 * Изменить состояние подчененной таблицы, с данными для замены.
 * Данные меняются в соответстви с установленным фильтром.
 */
void TfrmPersonFullEdit::changeSlaveTable(AnsiString surnameFilter, AnsiString nameFilter) {
    dbgrdPersonToUseList->DataSource = NULL;
    dmPersonDAO->refreshSlaveTable(surnameFilter);
    dbgrdPersonToUseList->DataSource = dmPersonDAO->dsPersonSlaveTable;
}

/**
 * Изменить состояние главной таблицы, с данными для редактирования.
 * Данные меняются в соответстви с установленным фильтром.
 */
void TfrmPersonFullEdit::changeMasterTable(AnsiString surnameFilter, AnsiString nameFilter) {
    dbgrdPersonEditList->DataSource  = NULL;
    //Применить фильтр отбора фамилий
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
 * Удаление выбранной персоны. При этом удаляются все данные
 свяазанные с данной персоной. Его участие в соревнованиях, заявки и т.п.
 */
void __fastcall TfrmPersonFullEdit::bbtnDeleteClick(TObject *Sender)
{
    // Удаляем только после того, как предупредим об этом
    TPerson personToDelete = dmPersonDAO->getCurrent();
    AnsiString warningMessage = "Вы собираетесь удалить персону: \n" +
    personToDelete.getSurname() +  " " +
    personToDelete.getName() + " " +
    personToDelete.getPatronymic() + ", " +
    personToDelete.getDob() + "\nВместе с ней будут удалены все данные, " +
    "в которых она встречается - участники, заявки и т.п.\n" +
    "Возможно следует заменить персону данными другой.\nВы действительно настаиваете на удалении?";
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
    // Обновить полученную запись новыми данными
    selectedPerson.setSurname(lbledtSurname->Text);
    selectedPerson.setName(lbledtName->Text);
    selectedPerson.setPatronymic(lbledtPatronymic->Text);
    selectedPerson.setDob(dtpDOB->Date);
    selectedPerson.setFemale(chboxFemale->Checked);
    selectedPerson.setPhone(lbledtPhone->Text);
    selectedPerson.setAdditions(memComments->Text);
    // и обновить
    dmPersonDAO->store(selectedPerson);
    // Переоткрыть таблицы и сделать активной текущую запись
    initTables();
    dmPersonDAO->makeCurrent(selectedPerson);
}
//---------------------------------------------------------------------------

/**
 * Замена данных одной персоны, данными другой.
 */
void __fastcall TfrmPersonFullEdit::bbtnReplaceClick(TObject *Sender)
{
    // Получим данные персон, для отображения информации
    TPerson personToDelete = dmPersonDAO->getCurrent();
    TPerson personToUse = dmPersonDAO->getCurrentSlave();

    AnsiString warningMessage = "Данные персоны: \n" +
    personToDelete.getSurname() +  " " +
    personToDelete.getName() + " " +
    personToDelete.getPatronymic() + ", " +
    personToDelete.getDob() + "\n\nБудут заменены данными другой персоны: \n" +
    personToUse.getSurname() +  " " +
    personToUse.getName() + " " +
    personToUse.getPatronymic() + ", " +
    personToUse.getDob() +
    "\n\nВыполнить операцию?";
    if(mrYes == MessageDlg(warningMessage, mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0)) {
        dmPersonDAO->changePersonalData(dmPersonDAO->ibqPersonSlaveTable, dmPersonDAO->ibqPersonAll);
        initTables();
        AnsiString infoMessage = "Данные персоны: \n" +
            personToDelete.getSurname() +  " " +
            personToDelete.getName() + " " +
            personToDelete.getPatronymic() + ", " +
            personToDelete.getDob() + "\n Были успешно заменены.";
            MessageDlg(infoMessage, mtInformation, TMsgDlgButtons() << mbOK, 0);
        }
}
//---------------------------------------------------------------------------

