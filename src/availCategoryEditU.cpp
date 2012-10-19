//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "utils.h"

#include "availCategoryEditU.h"
#include "availCategoryCtrl.h"
#include "currentStateDM.h"
#include "dataSourceDM.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAvailCategoryEdit *frmAvailCategoryEdit;






//---------------------------------------------------------------------------
__fastcall TfrmAvailCategoryEdit::TfrmAvailCategoryEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
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
    //Инициализация полей начальными значениями
    initFields();     
}
//---------------------------------------------------------------------------

void TfrmAvailCategoryEdit::initFields(void){
    //Очисить поля возраста
    medtStartAge->Clear();
    medtEndAge->Clear();
    //Очистить поля веса
    medtStartWeight->Clear();
    medtEndWeight->Clear();
    //Установить пол участника по умолчанию (мужской)
    rdgrpGender->ItemIndex = 0;
    //Убрать комментарии
    memComments->Clear();
}

void __fastcall TfrmAvailCategoryEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   //Пробуем сохранить объект, или закрываем форму
   //Пользователь сохраняет данные?
    if(ModalResult == mrOk){
        //Создать сохраняемый объект
        TAvailCategory *newObj = new TAvailCategory(StrToInt(medtStartAge->Text.Trim()),
                                                    StrToInt(medtEndAge->Text.Trim()),
                                                    StrToFloat(medtStartWeight->Text),
                                                    StrToFloat(medtEndWeight->Text),
                                                    rdgrpGender->ItemIndex?true:false,
                                                    memComments->Text);
        //Сообщение об ошибке
        AnsiString errmess;
        //Проверить созданный объект
        if(newObj->valid(errmess)){
            //Сохранить в базе
            newObj->store();
            //Сохранить доступную категорию в памяти
            dmCurrentState->addAvailCategoryToList(*newObj);
            dmCurrentState->setAvailCategory(*newObj);
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



