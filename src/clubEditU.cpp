//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "clubEditU.h"
#include "personDM.h"
#include "personEditU.h"
#include "clubCtrl.h"
#include "currentStateDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmClubEdit *frmClubEdit;
//---------------------------------------------------------------------------
__fastcall TfrmClubEdit::TfrmClubEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmClubEdit::btnAddPersonClick(TObject *Sender)
{
    //Запомнить текущего субъекта
    dmCurrentState->setPerson(TPerson::getCurrent());  
    //Добавить субъекта в базу данных
    frmPersonEdit->ShowModal();
    //Переоткрыть таблицу и получить
    lbledtPersonQuickSearchChange(Sender);
    //Сделать активным текущего персоналия
    dmCurrentState->getPerson().makeCurrent();
}
//---------------------------------------------------------------------------
void __fastcall TfrmClubEdit::dbgrdPersonListTitleClick(TColumn *Column)
{
    //Установить условие фильтра
    dmPersonDAO->setFilterCondition(lbledtPersonQuickSearch->Text);
   //Отсортировать таблицу, по выбранному столбцу
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
}
//---------------------------------------------------------------------------


void __fastcall TfrmClubEdit::lbledtPersonQuickSearchChange(TObject *Sender)
{
    //Применить фильтр отбора фамилий
    dmPersonDAO->setFilterCondition(lbledtPersonQuickSearch->Text);
    dmPersonDAO->filterByField(ptfSurname);
}
//---------------------------------------------------------------------------
void __fastcall TfrmClubEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //Сохраняем объект, либо просто выходим с формы
   //Пользователь сохраняет данные?
    if(ModalResult == mrOk){
        //Получим представителя/руководителя команды
        //Создать сохраняемый объект
        TClub *newObj = new TClub(lbledtClubName->Text, lbledtClubShortName->Text,
                                    lbledtClubCity->Text,
                                    lbledtClubCountry->Text,
                                    dmCurrentState->getPerson().getId(),
                                    memClubAdditions->Text);
        //Сообщение об ошибке
        AnsiString errmess;
        //Проверить созданный объект
        if(newObj->valid(errmess)){
            //Сохранить в базе
            newObj->store();
            dmCurrentState->setClub(*newObj); 
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
//---------------------------------------------------------------------------


void TfrmClubEdit::initFields(void){
    //Очистить поля
    lbledtClubName->Clear();
    lbledtClubCity->Clear();
    lbledtClubCountry->Clear();
    memClubAdditions->Clear();
    lbledtPersonQuickSearch->Clear(); 



}
void __fastcall TfrmClubEdit::FormShow(TObject *Sender)
{
    //Инициализировать поля начальными значениями
    initFields();     
}
//---------------------------------------------------------------------------

