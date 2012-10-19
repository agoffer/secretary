//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "availCategoryFullEditU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAvailCategoryFullEdit *frmAvailCategoryFullEdit;
//---------------------------------------------------------------------------
__fastcall TfrmAvailCategoryFullEdit::TfrmAvailCategoryFullEdit(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*

TODO: It has to be implemented and completed.



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
//---------------------------------------------------------------------------

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


void TfrmManuallyAddCategoryEdit::InitFields(void){
    //-- При переходе к форме, инициализируем таблицу категориями
    setAvailCategoryTable(-1, -1, -1, -1);
    //создать список боевых версий
    createFightVersionList();
    mskedtStartAge->Clear();
    mskedtEndAge->Clear();
    mskedtStartWeight->Clear();
    mskedtEndWeight->Clear();
}


void TfrmManuallyAddCategoryEdit::setAvailCategoryTable(int sa, int ea, double sw, double ew){
        dmAvailCategoryDAO->setCategoryTable(sa, ea, sw, ew, female);
}

void TfrmManuallyAddCategoryEdit::getValidValues(int &sa, int &ea, double &sw, double &ew){
    try{
        //Получим начальный возраст
        sa = StrToInt(mskedtStartAge->Text);
    }catch(EConvertError *e){
        sa = -1;
        }
    try{
        //Получим конечный возраст
        ea = StrToInt(mskedtEndAge->Text);
    }catch(EConvertError *e){
        ea = -1;
        }
    try{
        //Получим начальный вес
        sw = StrToFloat(FormatFloatValueText(mskedtStartWeight->Text));
    }catch(EConvertError *e){
        sw = -1;
        }
    try{
        //Получим конечный вес
        ew = StrToFloat(FormatFloatValueText(mskedtEndWeight->Text));
    }catch(EConvertError *e){
        ew = -1;
        }
}



void __fastcall TfrmManuallyAddCategoryEdit::mskedtSearchChange(
      TObject *Sender)
{
    //-- Отфильтровать категории
    int sa=-1, ea=-1;
    double sw=-1, ew=-1;
    getValidValues(sa, ea, sw, ew);
    setAvailCategoryTable(sa, ea, sw, ew);
}
//---------------------------------------------------------------------------

*/
