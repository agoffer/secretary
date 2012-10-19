//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "personEditU.h"
#include "personCtrl.h"
#include "currentStateDM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPersonEdit *frmPersonEdit;
//---------------------------------------------------------------------------
__fastcall TfrmPersonEdit::TfrmPersonEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPersonEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //Пробуем сохранить объект, или закрываем форму
   //Пользователь сохраняет данные?
    if(ModalResult == mrOk){
        //Создать сохраняемый объект
        TPerson *newObj = new TPerson(lbledtSurname->Text,
                                        lbledtName->Text,
                                        lbledtPatronymic->Text,
                                        dtpDOB->Date,
                                        lbledtPhone->Text,
                                        chboxFemale->Checked,
                                        memAdditions->Text);
        //Сообщение об ошибке
        AnsiString errmess;
        //Проверить созданный объект
        if(newObj->valid(errmess)){
            //Сохранить в базе
            newObj->store();
            //Установить текущего участника
            dmCurrentState->setPerson(*newObj);
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


void TfrmPersonEdit::initFields(void){
    //Очистить все поля
    lbledtSurname->Clear();
    lbledtName->Clear();
    lbledtPatronymic->Clear();
    lbledtPhone->Clear();
    memAdditions->Clear();
    chboxFemale->Checked = false; 
    dtpDOB->Date = Now();
}
void __fastcall TfrmPersonEdit::FormShow(TObject *Sender)
{
    //Инициализировать поля начальными значениями
    initFields(); //очистить поля, при добавлении записи     
}
//---------------------------------------------------------------------------


