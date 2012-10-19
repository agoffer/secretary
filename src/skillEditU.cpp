//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "skillEditU.h"
#include "skillCtrl.h"
#include "currentStateDM.h"
#include "dataSourceDM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSkillEdit *frmSkillEdit;
//---------------------------------------------------------------------------
__fastcall TfrmSkillEdit::TfrmSkillEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSkillEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   //Пользователь сохраняет данные?
    if(ModalResult == mrOk){
        //Создать сохраняемый объект
        TSkill *newObj = new TSkill(lbledtShortDescription->Text,
                                    lbledtFullDescription->Text,
                                    memComments->Text,
                                    StrToInt(medtWeight->Text.Trim()));
        //Сообщение об ошибке
        AnsiString errmess;
        //Проверить созданный объект
        if(newObj->valid(errmess)){
            //Сохранить в базе
            newObj->store();
            //Сохранить в памяти
            dmCurrentState->addSkillToList(*newObj);            
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
void __fastcall TfrmSkillEdit::FormShow(TObject *Sender)
{
    //Установить начальное значение полей (при добавлении) 
    InitFields();    
}
//---------------------------------------------------------------------------


void TfrmSkillEdit::InitFields(void){
    //Очистить поля ввода
    lbledtFullDescription->Clear();
    lbledtShortDescription->Clear();
    memComments->Clear();
    medtWeight->Clear();
}




