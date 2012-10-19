//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "currentStateDM.h"
#include "competitionEditU.h"
#include "competitionRankEditU.h"
#include "competitionRankDM.h"
#include "competitionDM.h"
#include "dataSourceDM.h"




//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCompetitionEdit *frmCompetitionEdit;
//---------------------------------------------------------------------------
__fastcall TfrmCompetitionEdit::TfrmCompetitionEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

/* TODO: Убрать этот обработчик. Редактирование уровней соревнований
выполняется через конфигуратор в главном меню. 
void __fastcall TfrmCompetitionEdit::bbtnAddCompetitionRankClick(
      TObject *Sender)
{
    frmCompetitionRankEdit->ShowModal();
    //Если добавили запись, обновить список
    if(frmCompetitionRankEdit->ModalResult == mrOk){
        //Уничтожить список статусов соревнований
        destroyCompetitionRankList();
        //Создать список соревнований заново
        createCompetitionRankList();
        //Установить добавленную запись, как текущую
        cmboxCompetitionRank->Text =
            frmCompetitionRankEdit->lbledtCompetitionRankDescription->Text;
            cmboxCompetitionRank->ItemIndex =cmboxCompetitionRank->Items->Count - 1;
        }
}
*/
//---------------------------------------------------------------------------

void TfrmCompetitionEdit::createCompetitionRankList(void){
    //Получить список статуса соревнований из базы данных
    competitionRankList = TCompetitionRank::getAll();
    //Сформировать список
    cmboxCompetitionRank->Items->Clear();
    for(int i=0; i < competitionRankList->Count; i++){
        cmboxCompetitionRank->Items->Add(((TCompetitionRank*)competitionRankList->Items[i])->getDescription());
        }
    if(cmboxCompetitionRank->Items->Count){
        //Выберем первое значение по умолчанию
        cmboxCompetitionRank->Text = cmboxCompetitionRank->Items->Strings[0];
        cmboxCompetitionRank->ItemIndex = 0;
        } 
}
//---------------------------------------------------------------------------


void __fastcall TfrmCompetitionEdit::FormShow(TObject *Sender)
{
    //Установить начальное значение полей (при добавлении) 
    InitFields();
}
//---------------------------------------------------------------------------

void TfrmCompetitionEdit::InitFields(void){
    //Создать список статусов соревнований
    createCompetitionRankList();
    //Установить текущую дату, в полях выбора
    dtpBeginCompetitionDate->Date = Now();
    dtpEndCompetitionDate->Date = Now();
    //Очистить содержимое поля комментария
    memCompetitionComments->Clear();
}
//---------------------------------------------------------------------------

void TfrmCompetitionEdit::destroyCompetitionRankList(void){
    //Очистим листбокс
    cmboxCompetitionRank->Items->Clear();
    //Удалим список
     destroyList(competitionRankList, etCOMPETITIONRANK);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionEdit::FormHide(TObject *Sender)
{
    //Удалить список статусов соревнований
    destroyCompetitionRankList();
}
//---------------------------------------------------------------------------


void __fastcall TfrmCompetitionEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   //Пользователь сохраняет данные?
    if(ModalResult == mrOk){
        //Получим статус проводимых соревнований
        int competitionRankId = 0;
        if(competitionRankList){
            competitionRankId =
                ((TCompetitionRank*)competitionRankList->Items[cmboxCompetitionRank->ItemIndex])->getId();
            }

        //Создать сохраняемый объект
        TCompetition *newObj = new TCompetition(dtpBeginCompetitionDate->Date,
                                                    dtpEndCompetitionDate->Date,
                                                    competitionRankId,
                                                    memCompetitionComments->Text);
        //Сообщение об ошибке
        AnsiString errmess;
        //Проверить созданный объект
        if(newObj->valid(errmess)){
            //Сохранить в базе
            newObj->store();
            newObj->extend(*(TCompetitionRank*)competitionRankList->Items[cmboxCompetitionRank->ItemIndex]);             
            //Установить соревнования
            dmCurrentState->setCompetition(*newObj);
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


