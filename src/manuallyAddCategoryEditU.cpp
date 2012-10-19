//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "manuallyAddCategoryEditU.h"
#include "availCategoryEditU.h"
#include "fightVersionEditU.h"
#include "availCategoryDM.h"
#include "categoryEditU.h"
#include "currentStateDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmManuallyAddCategoryEdit *frmManuallyAddCategoryEdit;
//---------------------------------------------------------------------------
__fastcall TfrmManuallyAddCategoryEdit::TfrmManuallyAddCategoryEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmManuallyAddCategoryEdit::bbtnAddAvailCategoryClick(
      TObject *Sender)
{
    //Запомнить текущую доступную категорию
    dmCurrentState->setAvailCategory(dmAvailCategoryDAO->getCurrent());
    //Перейти к добавлению новой категории
    //Перейти к редактору доступных категорий
    if(frmAvailCategoryEdit->ShowModal()==mrOk);
    //Перечитать таблицу
    mskedtSearchChange(NULL);
    //Установить старую или новую запись     
    dmCurrentState->getAvailCategory().makeCurrent();
}
//---------------------------------------------------------------------------
void __fastcall TfrmManuallyAddCategoryEdit::bbtnAddFightVersionClick(
      TObject *Sender)
{

    //Перейти к добавлению новой боевой версии
    if(frmFightVersionEdit->ShowModal()==mrOk){
        //Уничтожить список боевых версий 
        clearFightVersionList();
        //Создать список боевых версий
        createFightVersionList();
        //Установить добавленную запись, как текущую
        cmboxFightVersion->ItemIndex =cmboxFightVersion->Items->Count - 1;
        cmboxFightVersion->Text = cmboxFightVersion->Items->Strings[cmboxFightVersion->ItemIndex]; 
        }
}


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

//---------------------------------------------------------------------------

void __fastcall TfrmManuallyAddCategoryEdit::FormShow(TObject *Sender)
{
    InitFields(); 
}
//---------------------------------------------------------------------------

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


void TfrmManuallyAddCategoryEdit::createFightVersionList(void){
    //Сформировать список
    cmboxFightVersion->Items->Clear();
    for(int i=0; i < dmCurrentState->getFightVersionList()->Count; i++){
        cmboxFightVersion->Items->Add(((TFightVersion*)dmCurrentState->getFightVersionList()->Items[i])->getCode());
        }
    if(cmboxFightVersion->Items->Count){
        //Выберем первое значение по умолчанию
        cmboxFightVersion->Text = cmboxFightVersion->Items->Strings[0];
        cmboxFightVersion->ItemIndex = 0;
        }
    else{
        cmboxFightVersion->ItemIndex = -1;
        }

}

void TfrmManuallyAddCategoryEdit::clearFightVersionList(void){
    //Очистим листбокс
    cmboxFightVersion->Items->Clear();
}
void __fastcall TfrmManuallyAddCategoryEdit::FormHide(TObject *Sender)
{
    //Очистить список
    clearFightVersionList();     
}
//---------------------------------------------------------------------------


void __fastcall TfrmManuallyAddCategoryEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //Создать новую категорию или выйти без создания
   //Пользователь сохраняет данные?
    if(ModalResult == mrOk){
        //Создать сохраняемый объект
        TAvailCategory currentAC =TAvailCategory::getCurrent();
        TFightVersion currentFV = dmCurrentState->findFightVersionByCode(cmboxFightVersion->Text);
        TCategory *newObj = new TCategory(currentAC.getId(),
                                currentFV.getId(),
                                dmCurrentState->getCompetition().getId());
        //Сообщение об ошибке
        AnsiString errmess;
        //Проверить созданный объект
        if(newObj->valid(errmess)){
            //Сохранить в базе
            newObj->store();
            //Расширить категорию
            newObj->extend(currentAC,
                            currentFV,
                            dmCurrentState->getCompetition()                            
                            );
            //Сохранить  категорию в памяти
            dmCurrentState->addCategoryToList(*newObj);
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

void __fastcall TfrmManuallyAddCategoryEdit::bbtnDeleteAvailCategoryClick(
      TObject *Sender)
{
  //Удалить выбранную "доступную категорию"

  TAvailCategory currentAC = TAvailCategory::getCurrent();
  if(MessageDlg(AnsiString("Вы действительно хотите удалить весовую/возрастную категорию: \n") +
  " - Возраст: " + IntToStr(currentAC.getStartAge()) +
  " - " + IntToStr(currentAC.getEndAge()) + " лет;\n" +
  " - Вес: " + FloatToStr(currentAC.getStartWeight()) +
  " - " + FloatToStr(currentAC.getEndWeight()) + " кг;\n" +
  " - " + (currentAC.getFemale() ? "Девушки/Женщины;" : "Юноши/Мужчины;"),
  mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes){
    //Удалить запись в базе
    currentAC.remove(); 
    //Обновить таблицу
    InitFields(); 
  }
}
//---------------------------------------------------------------------------

