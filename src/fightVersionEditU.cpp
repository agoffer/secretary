//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fightVersionEditU.h"
#include "fightVersionCtrl.h"
#include "currentStateDM.h"
#include "dataSourceDM.h" 
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmFightVersionEdit *frmFightVersionEdit;
//---------------------------------------------------------------------------
__fastcall TfrmFightVersionEdit::TfrmFightVersionEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmFightVersionEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   //Пользователь сохраняет данные?
    if(ModalResult == mrOk){
        //Создать сохраняемый объект
        TFightVersion *newObj = new TFightVersion(lbledtCode->Text, lbledtDescription->Text,
                                    memComments->Text);
        //Сообщение об ошибке
        AnsiString errmess;
        //Проверить созданный объект
        if(newObj->valid(errmess)){
            //Сохранить в базе
            newObj->store();
            //Сохранить в памяти
            dmCurrentState->addFightVersionToList(*newObj);
            //Запомнить текущую боевую версию
            dmCurrentState->setFightVersion(*newObj);             
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
void __fastcall TfrmFightVersionEdit::FormShow(TObject *Sender)
{
    //Установить начальное значение полей (при добавлении) 
    InitFields();    
}
//---------------------------------------------------------------------------


void TfrmFightVersionEdit::InitFields(void){
    //Очистить поля ввода
    lbledtCode->Clear();
    lbledtDescription->Clear();
    memComments->Clear();
}
