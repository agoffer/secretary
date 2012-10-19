//---------------------------------------------------------------------------

#include <vcl.h>
#include <strutils.hpp>
#pragma hdrstop

#include "resultEnterEditU.h"
#include "competitorDM.h"

#include "currentStateDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmResultEnterEdit *frmResultEnterEdit;
//---------------------------------------------------------------------------
__fastcall TfrmResultEnterEdit::TfrmResultEnterEdit(TComponent* Owner)
    : TForm(Owner)
{
}

void TfrmResultEnterEdit::changeCompetitorSearchTableState(void){

    //Применить фильтр отбора фамилий
    dmCompetitorDAO->setFilterCondition_1(lbledtCompetitorSurname->Text);
    //Применить фильтр отбора по названию клуба
    dmCompetitorDAO->setFilterCondition_2(lbledtCompetitorClub->Text);
    dmCompetitorDAO->filterByField(dmCurrentState->getCompetition().getId(),
                                   ctfSurname, ctfClub_Name);

    //Сделать запись текущей в таблице
//    dmCurrentState->getClub().makeCurrent(); не пойму, чего это 
    //Сменить текущего участника 
    changeCompetitor(); 

}

//---------------------------------------------------------------------------
void __fastcall TfrmResultEnterEdit::lbledtCompetitorSurnameChange(TObject *Sender)
{
    resetCallback();
    //-- Изменилось поле фильтрации, отфильтровать и выбрать запись
    dbgrdCompetitorList->DataSource = NULL;
    //Применить фильтр отбора фамилий
    changeCompetitorSearchTableState();
    dbgrdCompetitorList->DataSource = dmCompetitorDAO->dsCompetitorExtended;
    setCallback();
    //Показать результат
    showResult();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultEnterEdit::FormShow(TObject *Sender)
{
    //-- Инициализировать форму
    InitFields();
    changeCompetitor();
    showResult();
    setCallback();
}
//---------------------------------------------------------------------------



void TfrmResultEnterEdit::InitFields(void){
    //Очистить поля фильтров
    lbledtCompetitorSurname->Clear();
    lbledtCompetitorClub->Clear();
}


void TfrmResultEnterEdit::changeCompetitor(void){
    //Выбрать нового участника
    currentCompetitor = TCompetitor::getExtendedTableCurrent();
    //Загрузить результаты для участника
    currentCompetitor.loadResult();
}


void competitorResultRecordMoveAction(void){
    //Когда форама активная
    if(frmResultEnterEdit->Active){
        //Сменить текущего участника
        frmResultEnterEdit->changeCompetitor();
        //Отобразить результат
        frmResultEnterEdit->lblNewShootResult->Visible = false;
        frmResultEnterEdit->showResult();
        }

}


void __fastcall TfrmResultEnterEdit::mskedtCompetitorShootScoreChange(
      TObject *Sender)
{
    //Установить метку изменения значения
    lblNewShootResult->Visible = true;
}

void __fastcall TfrmResultEnterEdit::mskedtCompetitorCrossTimeChange(TObject *Sender)
{
    //Установить метку изменения значения
    lblNewCrossResult->Visible = true;
}
//---------------------------------------------------------------------------



void TfrmResultEnterEdit::showResult(void){
    //Отобразить результат стрельбы на форме, для очередного участника
    mskedtCompetitorShootScore->Text = IntToStr(currentCompetitor.result.getShootScore());
    lblNewShootResult->Visible = false;
    //Отобразить результат кросса на форме, для очередного участника
    mskedtCompetitorCrossTime->Text = currentCompetitor.result.getCrossTime();
    lblNewCrossResult->Visible = false;
}

void TfrmResultEnterEdit::storeResult(void){
    //-- Зафиксировать результат для участника
    AnsiString shootRes = frmResultEnterEdit->mskedtCompetitorShootScore->Text.Trim();
    if(shootRes=="") shootRes = "-1"; 
    currentCompetitor.result.setShootScore(StrToInt(shootRes));
    AnsiString crossTime = AnsiReplaceStr(frmResultEnterEdit->mskedtCompetitorCrossTime->Text,
                                            " ", "0");
    currentCompetitor.result.setCrossTime(crossTime);
    currentCompetitor.storeResult();
    lblNewShootResult->Visible = false;
    lblNewCrossResult->Visible = false;    
}


//---------------------------------------------------------------------------

void __fastcall TfrmResultEnterEdit::bbtnAddResultClick(TObject *Sender)
{
    //Сохранить результат
    storeResult();
    //Обновить таблицу участников
    changeCompetitorSearchTableState();
    lbledtCompetitorSurname->SetFocus();
}
//---------------------------------------------------------------------------


void TfrmResultEnterEdit::setCallback(void){
    TCompetitor::setRecordMoveCallback(competitorResultRecordMoveAction);
}


void TfrmResultEnterEdit::resetCallback(void){
    TCompetitor::setRecordMoveCallback(NULL);
}

