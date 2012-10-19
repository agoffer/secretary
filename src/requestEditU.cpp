//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "requestEditU.h"
#include "requestDM.h"
#include "requestCtrl.h"
#include "clubDM.h"
#include "personDM.h"
#include "clubEditU.h"
#include "clubCtrl.h"
#include "personEditU.h"
#include "currentStateDM.h"
#include "mainFormU.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmRequestEdit *frmRequestEdit;

//---------------------------------------------------------------------------
__fastcall TfrmRequestEdit::TfrmRequestEdit(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::dbgrdClubListTitleClick(TColumn *Column)
{
    resetCallback();
    //Отсортировать таблицу по выбранному столбцу
    //Установим дополнительные условия фильтрации
    dmPersonDAO->setFilterCondition(lbledtClubQuickSearch->Text);
    switch(Column->Index){
        //Сортируем по имени клуба
        case 0 :
            dmClubDAO->sortByField(ctfName);
            break;
        //Сортировать по названию города
        case 1 :
            dmClubDAO->sortByField(ctfCity);
            break;
        //Сортировать по стране
        case 2 :
            dmClubDAO->sortByField(ctfCountry);
            break;
        }
    //Установить текущую запись
    dmCurrentState->getClub().makeCurrent();
    setCallback();
}

void TfrmRequestEdit::changePersonSearchTableState(void){
    //Применить фильтр отбора фамилий
    dmPersonDAO->setFilterCondition(lbledtPersonQuickSearch->Text);
    dmPersonDAO->filterByField(ptfSurname);
    //Сделать запись текущей в таблице
    dmCurrentState->getPerson().makeCurrent();
}

void TfrmRequestEdit::changeClubSearchTableState(void){
    //Применить фильтр отбора фамилий
    dmClubDAO->setFilterCondition(lbledtClubQuickSearch->Text);
    dmClubDAO->filterByField(ctfName);
    //Сделать запись текущей в таблице
    dmCurrentState->getClub().makeCurrent();
}

//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::btnAddClubClick(TObject *Sender)
{
    resetCallback();
    //Сбросить поля быстрого поиска
    dmCurrentState->setClub(TClub::getCurrent());
    dmCurrentState->setPerson(TPerson::getCurrent());
//    dbgrdPersonList->DataSource = NULL;
//    dbgrdClubList->DataSource = NULL;
    QuickSearchClear();
    //Добавить новый клуб в базу данных
    frmClubEdit->ShowModal();
    changeClubSearchTableState();
    changePersonSearchTableState();
//    dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;
//    dbgrdClubList->DataSource = dmClubDAO->dsClubTable;
    setCallback();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::btnAddPersonClick(TObject *Sender)
{

    resetCallback();
    //Сросить поля быстрого поиска
    dmCurrentState->setClub(TClub::getCurrent());
    dmCurrentState->setPerson(TPerson::getCurrent());
//    dbgrdPersonList->DataSource = NULL;
//    dbgrdClubList->DataSource = NULL;
    QuickSearchClear();
    //Добавить субъект в базу данных
    frmPersonEdit->ShowModal();
    changePersonSearchTableState();
    changeClubSearchTableState();
//    dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;
//    dbgrdClubList->DataSource = dmClubDAO->dsClubTable;
    setCallback();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::dbgrdPersonListTitleClick(TColumn *Column)
{
    resetCallback();
    //Отсортировать таблицу, по выбранному столбцу
    //Установим дополнительные условия фильтрации
    dmPersonDAO->setFilterCondition(lbledtPersonQuickSearch->Text);
    switch(Column->Index){
        //Сортируем по фамилии
        case 0 :
            dmPersonDAO->sortByField(ptfSurname);
            break;
        //Сортировать по имени
        case 1 :
            dmPersonDAO->sortByField(ptfName);
            break;
        //Сортировать по отчеству
        case 2 :
            dmPersonDAO->sortByField(ptfPatronymic);
            break;
        //Сортировать по номеру телефона
        case 3 :
            dmPersonDAO->sortByField(ptfPhone);

        }
    //Сделать запись текущей в таблице
    dmCurrentState->getPerson().makeCurrent();
    setCallback();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::lbledtPersonQuickSearchChange(
      TObject *Sender)
{
    dbgrdPersonList->DataSource = NULL;
    //Применить фильтр отбора фамилий
    changePersonSearchTableState();
    dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestEdit::FormShow(TObject *Sender)
{
    //Установить начальные значения (при добавлении)
    initFields();
    //Установить функции обратного вызова для навигации по таблицам
    setCallback();
}
//---------------------------------------------------------------------------


void TfrmRequestEdit::initFields(void){
    //Очистить необходимые поля
    QuickSearchClear();
    //Привязать таблицы к элементам управления
//    dbgrdClubList->DataSource = dmClubDAO->dsClubTable;
//    dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;

}
//---------------------------------------------------------------------------

void TfrmRequestEdit::QuickSearchClear(void){
    lbledtPersonQuickSearch->Clear();
    lbledtClubQuickSearch->Clear();
}


void __fastcall TfrmRequestEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //Сбросим функции обратного вызова
    resetCallback();
    //Отвязать таблицы от элемента управления
//    dbgrdClubList->DataSource = NULL;
//    dbgrdPersonList->DataSource = NULL;
    //Сохраняем объект, либо просто выходим с формы
   //Пользователь сохраняет данные?
    if(ModalResult == mrOk){
        //Создать сохраняемый объект
        TRequest *newObj = new TRequest(dmCurrentState->getCompetition().getId(),
                                        dmCurrentState->getClub().getId(),
                                        dmCurrentState->getPerson().getId(),
                                        memRequestComments->Text
                                        );

        //Сообщение об ошибке
        AnsiString errmess;
        //Проверить созданный объект
        if(newObj->valid(errmess)){
            //Сохранить в базе
            newObj->store();
            newObj->extend(dmCurrentState->getPerson(), dmCurrentState->getClub());
            //Запомним заявку в памяти
            dmCurrentState->addRequestToList(*newObj);
            dmCurrentState->setRequest(*newObj);
            }
        //Объект задан не верно, уничтожить
        else{
            //Отобразить сообщение об ошибке
            MessageDlg(errmess,
                   mtError, TMsgDlgButtons() << mbOK, 0);

            //Запретить закрытие окна
            Action = caNone;
            }
        //Удалить объект
        delete newObj;
        }
}

void TfrmRequestEdit::setCallback(void){
    TClub::setRecordMoveCallback(clubRecordMoveAction);
    TPerson::setRecordMoveCallback(personRecordMoveAction);
    //Привязать таблицы к элементам управления
    dbgrdClubList->DataSource = dmClubDAO->dsClubTable;
    dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;
}

void TfrmRequestEdit::resetCallback(void){

    TClub::setRecordMoveCallback(NULL);
    TPerson::setRecordMoveCallback(NULL);

    //Отвязать таблицы к элементам управления
    dbgrdClubList->DataSource = NULL;
    dbgrdPersonList->DataSource = NULL;
}
//---------------------------------------------------------------------------


void __fastcall TfrmRequestEdit::lbledtClubQuickSearchChange(
      TObject *Sender)
{
    dbgrdClubList->DataSource = NULL;
    //Применить фильтр отбора фамилий
    changeClubSearchTableState();
    dbgrdClubList->DataSource = dmClubDAO->dsClubTable;
}
//---------------------------------------------------------------------------

void clubRecordMoveAction(void){
    //Когда форама активная
    if(frmRequestEdit->Active){
        //Если действительно произошел переход на другой клуб
        if(TClub::getCurrent().getId() != dmCurrentState->getClub().getId()){
            //Запретить реакцию на изменение персоны
            TPerson::setRecordMoveCallback(NULL);
            frmRequestEdit->dbgrdPersonList->DataSource = NULL;
            //Выбрать персону, в соответствии с выбранным клубом
            TPerson::makeCurrent(TClub::getCurrent().getPersonId());
            //Сделать ее текущей
            dmCurrentState->setPerson(TPerson::getCurrent());
            //Выбрать клуб
            dmCurrentState->setClub(TClub::getCurrent());
            //Вернуть обработку измения таблицы с персонами
            TPerson::setRecordMoveCallback(personRecordMoveAction);
            frmRequestEdit->dbgrdPersonList->DataSource = dmPersonDAO->dsPersonTable;
            }
        }
}

void personRecordMoveAction(void){
    //Когда форама активная
    if(frmRequestEdit->Active){
        //Поменять, если произошла действительно смена представителя
        if(dmCurrentState->getPerson().getId() != TPerson::getCurrent().getId()){
            //Выбрать персону, в соответствии с выбранным клубом
            dmCurrentState->setPerson(TPerson::getCurrent());
            }
        }
}


