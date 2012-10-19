//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "competitorCategoryResultEditU.h"
#include "resultDM.h"
#include "categoryEditU.h"
#include "currentStateDM.h"
#include "reportDataSourceDM.h"
#include "categoryFinalReportU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


//Учитывать результат кроса, при расчете результатов стрельбы 
bool crossInclude;
//Сравнение результатов
int __fastcall compareShootResults(void *fstItem, void *secItem);
int __fastcall compareCommonResults(void *fstItem, void *secItem);

TfrmCompetitorCategoryResultEdit *frmCompetitorCategoryResultEdit;
//---------------------------------------------------------------------------
__fastcall TfrmCompetitorCategoryResultEdit::TfrmCompetitorCategoryResultEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCompetitorCategoryResultEdit::FormShow(TObject *Sender)
{
    InitFields();
}
//---------------------------------------------------------------------------


void TfrmCompetitorCategoryResultEdit::HideResultChange(void){
    //Очистить признак изменения результата
    lblModifiedShootRank->Hide();
    lblModifiedFightWOKnifeRank->Hide();
    lblModifiedFightWKnifeRank->Hide();
    lblModifiedCommonRank->Hide();
    //Результат текущего участника не изменялся
    resultModified = false;
    //Запретить кнопку записи
    bbtnEnterResult->Enabled = false;
}

void TfrmCompetitorCategoryResultEdit::InitFields(void){
    //-- Пройдемся по списку полученных категорий и заполним списки
    chboxFemaleCategory->Checked = false;
    TList *category = dmCurrentState->getMaleCategoryList();
    createCategories(category);
    //Результат не изменен
    HideResultChange();

    currentCompetitorList = NULL;

    //Установим функцию обратного вызова
    setCallback();
    //Отобразить список
    changeCompetitorList(NULL);
}

void TfrmCompetitorCategoryResultEdit::createCategories(TList *category){
    //список весов и возрастов
    createCategoryIndexFVComboBox(category, cmboxFightVersion, categoryIndex);
    cmboxFightVersion->ItemIndex = 0;
    createAgeWeightComboBoxByFV(cmboxAvailCategory, category, cmboxFightVersion);  
    cmboxAvailCategory->ItemIndex = 0;
}



void __fastcall TfrmCompetitorCategoryResultEdit::changeCompetitorList(
      TObject *Sender)
{
    currentCategory = getCategoryByIndex(cmboxAvailCategory,
                        cmboxFightVersion,
                        categoryIndex); 
    ShowCompetitorList(currentCategory);
    //Сменить участника
    changeCompetitor(); 

}
//---------------------------------------------------------------------------

void TfrmCompetitorCategoryResultEdit::ShowCompetitorList(TCategory* category){
    if(category == NULL){
        //Список участников отсутствует
        dbgrdCompetitors->DataSource = NULL;
        cmboxFightWKnifeRank->Clear();
        cmboxFightWOKnifeRank->Clear();
        return;
        }
    //Получисть список участников в категории
    //Предварительно удалить старый список участников в категории
    if(currentCompetitorList!=NULL){
        destroyList(currentCompetitorList, etCOMPETITOR);
        currentCompetitorList = NULL; 
        }
    currentCompetitorList = dmResultDAO->setCompetitorCategoryResultTable(category->getId());
    if(currentCompetitorList->Count > 0){
        //Отобразить список
        dbgrdCompetitors->DataSource = dmResultDAO->dsCompetitorToCategoryResult;
        //Перестроить список мест, занятых участриками
        createRankList(cmboxFightWOKnifeRank, currentCompetitorList->Count);
        createRankList(cmboxFightWKnifeRank, currentCompetitorList->Count);
        createRankList(cmboxShootRank, currentCompetitorList->Count);
        createRankList(cmboxCommonRank, currentCompetitorList->Count);
        }
    else{
        //Спрятать список
        dbgrdCompetitors->DataSource = NULL;
        cmboxFightWKnifeRank->Clear();
        cmboxFightWOKnifeRank->Clear();
        cmboxShootRank->Clear();
        cmboxCommonRank->Clear();
    }
}


void TfrmCompetitorCategoryResultEdit::createRankList(TComboBox *cmboxRank, int rankCount){
    //Очистим список
    cmboxRank->Clear();
    cmboxRank->Items->Add("");
    for(int i=1; i <= rankCount; i++){
        cmboxRank->Items->Add(IntToStr(i));
        }
}


void __fastcall TfrmCompetitorCategoryResultEdit::chboxFemaleCategoryClick(
      TObject *Sender)
{
TList *category;
    //-- Изменить список категорий на противоположый
    if(!chboxFemaleCategory->Checked){
        category = dmCurrentState->getMaleCategoryList();
        }
    else{
        category = dmCurrentState->getFemaleCategoryList();
        }
    //список весов и возрастов
    createCategories(category);
    //Отобразим списки снова
    changeCompetitorList(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::bbtnCloseClick(
      TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------


void TfrmCompetitorCategoryResultEdit::changeCompetitor(void){

    //Если не существует категории, не выполнять смену участника
    if(currentCategory==NULL)
        return;
    //Происходит смена текущего участника
    resetCallback();

   //Выбрать нового участника
    int currentCompetitorId = TResult::getCurrentCompetitorId();

    //Установим неизменность результата
    HideResultChange();
    currentCompetitor.getById(currentCompetitorId);

    //Загрузить результаты для участника
    currentCompetitor.loadResult(currentCategory->getId());

    //Установить полученный результаты в выпадющем списке
    int fwok = currentCompetitor.result.getFightWOKnifeRank();
    int fwk = currentCompetitor.result.getFightWKnifeRank();
    int sht = currentCompetitor.result.getShootRank();
    int cmmn = currentCompetitor.result.getCommonRank();
    cmboxFightWOKnifeRank->Text = fwok > 0 ? IntToStr(fwok) : AnsiString("");
    cmboxFightWKnifeRank->Text = fwk > 0 ? IntToStr(fwk) : AnsiString("");
    cmboxShootRank->Text = sht > 0 ? IntToStr(sht) : AnsiString("");
    cmboxCommonRank->Text = cmmn > 0 ? IntToStr(cmmn) : AnsiString("");

    showResultScores();

    setCallback();
}


void TfrmCompetitorCategoryResultEdit::showResultScores(void){
    //Установить полученный результаты в выпадющем списке
    AnsiString fwok = cmboxFightWOKnifeRank->Text; int ifwok;
    AnsiString fwk = cmboxFightWKnifeRank->Text;   int ifwk;
    AnsiString sht = cmboxShootRank->Text;         int isht;
    AnsiString cmmn = cmboxCommonRank->Text;       int icmmn;

    if(fwok.IsEmpty()){ifwok = 0;}
    else{ifwok = dmCurrentState->getScoreForRank(StrToInt(fwok));}
    if(fwk.IsEmpty()){ifwk = 0;}
    else{ifwk = dmCurrentState->getScoreForRank(StrToInt(fwk));}
    if(sht.IsEmpty()){isht = 0;}
    else{isht = dmCurrentState->getScoreForRank(StrToInt(sht));}
    if(cmmn.IsEmpty()){icmmn = 0;}
    else{icmmn = ifwok + ifwk + isht;}

    sttxtShootScore->Caption=IntToStr(isht);
    sttxtFightWOKnifeScore->Caption=IntToStr(ifwok);
    sttxtFightWKnifeScore->Caption=IntToStr(ifwk);
    sttxtCommonScore->Caption=IntToStr(icmmn);
}



void competitorToCategoryResultRecordMoveAction(void){
    //Когда форама активная
    if(frmCompetitorCategoryResultEdit->Active){
        //Сменить текущего участника
        frmCompetitorCategoryResultEdit->changeCompetitor();
        }

}




void TfrmCompetitorCategoryResultEdit::setCallback(void){
    TResult::setRecordMoveCallback(competitorToCategoryResultRecordMoveAction);
}


void TfrmCompetitorCategoryResultEdit::resetCallback(void){
    TResult::setRecordMoveCallback(NULL);
}



void __fastcall TfrmCompetitorCategoryResultEdit::FormClose(
      TObject *Sender, TCloseAction &Action)
{
    //Закрыть форму


    //Установим неизменность результата
    HideResultChange();

    //Удалить список участников текущей категории
    if(currentCompetitorList!=NULL){
        destroyList(currentCompetitorList, etCOMPETITOR);
        currentCompetitorList=NULL;
        }


    //Отвязать форму от таблицы
    resetCallback();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::bbtnEnterResultClick(
      TObject *Sender)
{

    //Сохранить результаты текущего участника
    if(resultModified){

        resetCallback();


        //Выбрать нового участника
        int currentCompetitorId = TResult::getCurrentCompetitorId();

        //Установить полученный результаты в выпадющем списке
        AnsiString fwok = cmboxFightWOKnifeRank->Text;
        AnsiString fwk = cmboxFightWKnifeRank->Text;
        AnsiString sht = cmboxShootRank->Text;
        AnsiString cmmn = cmboxCommonRank->Text;

        if(fwok.IsEmpty()){fwok = "0";}
        if(fwk.IsEmpty()){fwk = "0";}
        if(sht.IsEmpty()){sht = "0";}
        if(cmmn.IsEmpty()){cmmn = "0";}

        currentCompetitor.result.setFightWOKnifeRank(
                            StrToInt(fwok));
        currentCompetitor.result.setFightWKnifeRank(
                            StrToInt(fwk));
        currentCompetitor.result.setShootRank(
                            StrToInt(sht));
        currentCompetitor.result.setCommonRank(
                            StrToInt(cmmn));

        //Сохраним результат участника
        currentCompetitor.storeResult(currentCategory->getId());
        //Отобразить список участников снова
        ShowCompetitorList(currentCategory);

        //Установить выбранную запись как текущуую
        TResult::setCurrentCompetitorById(currentCompetitorId);

        cmboxFightWOKnifeRank->Text = !fwok.AnsiCompare("0") ? AnsiString("") : fwok;
        cmboxFightWKnifeRank->Text = !fwk.AnsiCompare("0") ? AnsiString("") : fwk;
        cmboxShootRank->Text = !sht.AnsiCompare("0") ? AnsiString("") : sht;
        cmboxCommonRank->Text = !cmmn.AnsiCompare("0") ? AnsiString("") : cmmn;

        showResultScores();

        HideResultChange();

        setCallback();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::cmboxFightWOKnifeRankChange(
      TObject *Sender)
{
    //Результат участника изменился
    resultModified = true;
    lblModifiedFightWOKnifeRank->Show();
    //Разрешить кнопку записи 
    bbtnEnterResult->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::cmboxShootRankChange(
      TObject *Sender)
{
    //Результат участника изменился
    resultModified = true;
    lblModifiedShootRank->Show();
    //Разрешить кнопку записи 
    bbtnEnterResult->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::cmboxFightWKnifeRankChange(
      TObject *Sender)
{
    //Результат участника изменился
    resultModified = true;
    lblModifiedFightWKnifeRank->Show();
    //Разрешить кнопку записи 
    bbtnEnterResult->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::cmboxCommonRankChange(
      TObject *Sender)
{
    //Результат участника изменился
    resultModified = true;
    lblModifiedCommonRank->Show();
    //Разрешить кнопку записи
    bbtnEnterResult->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::bbtnAtoCalculateShootRankClick(
      TObject *Sender)
{
    // Расчет результатов стрельбы, с учетом кросса для участников //
    calculateShootRanks(currentCompetitorList, currentCategory->getId());
    //Отобразить результаты заново
    ShowCompetitorList(currentCategory);

    changeCompetitor();
}
//---------------------------------------------------------------------------


void TfrmCompetitorCategoryResultEdit::calculateShootRanks(TList *compList, int categoryId){
int btnRes;
//Результаты кросса не учитываются
bool crossInclude = false;
    //Уточнить у пользователя, учитывать кросс или нет?
    btnRes = MessageDlg("Учитывать результаты кросса?",
                        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0);
    if(btnRes != mrNo){
        //Пользователь решил учитывать кросс
        crossInclude = true;
        }


    //Проверка присутствия всех результатов
    for(int i=0; i < compList->Count; i++){
        TCompetitor *competitor = (TCompetitor*)(compList->Items[i]);
        //Результат стрельбы
        if(competitor->result.getShootScore() < 0){
            //Сообщить о том, что участник без результата
            btnRes = MessageDlg("Участник " +
                        competitor->getPerson().getSurname() +
                        " " + competitor->getPerson().getName() +
                        " не имеет результата по стрельбе! Продолжить расчет мест?",
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
            if(btnRes != mrYes){
                //Остановиться, не выполнять расчет мест
                return;
                }
            }
        //Если необходимо, проверяем наличие результата кросса
        if(crossInclude &&
            (
            (competitor->result.getCrossTime().AnsiCompare(AnsiString(":  ."))==0)
            ||
            (competitor->result.getCrossTime().Trim().AnsiCompare(AnsiString(""))==0)
            ||
            (competitor->result.getCrossTime().Trim().AnsiCompare(AnsiString("00:00.00"))==0)
            )){
            //Сообщить о том, что для участника не определено время кросса
                        btnRes = MessageDlg("Участник " +
                        competitor->getPerson().getSurname() +
                        " " + competitor->getPerson().getName() +
                        " не имеет результата за кросс! Продолжить расчет мест?",
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
            if(btnRes != mrYes){
                //Остановиться, не выполнять расчет мест
                return;
                }
            }
        }

    //Упорядочить участников по результатам
    compList->Sort(compareShootResults);

    //Расставить места участников, в соответствии с упорядочиванием
    for(int i=0; i < compList->Count; i++){
        TCompetitor * competitor = (TCompetitor*)compList->Items[i];
        competitor->result.setShootRank(i + 1);
        competitor->storeResult(categoryId);
        }
}


int __fastcall compareShootResults(void *fstItem, void *secItem){
    if(((TCompetitor *)fstItem)->result.getShootScore() >
       ((TCompetitor *)secItem)->result.getShootScore()){
        return -1;
        }
    else if(((TCompetitor *)fstItem)->result.getShootScore() <
            ((TCompetitor *)secItem)->result.getShootScore()){
            return 1;
            }
         else{
            //Если учитываются результаты кросса, проверить их
            if(crossInclude){
                return -(((TCompetitor *)fstItem)->result.getCrossTime().
                AnsiCompare(((TCompetitor *)secItem)->result.getCrossTime()));
                }
            else{
                //Места одинаковые
                return 0;
                }
            }
}




void __fastcall TfrmCompetitorCategoryResultEdit::bbtnAutoCalculateCommonRankClick(
      TObject *Sender)
{
    // Расчет общих мест по всем видам соревнований //
    calculateCommonRanks(currentCompetitorList, currentCategory->getId());
    //Отобразить результаты заново
    ShowCompetitorList(currentCategory);

    changeCompetitor();  
}
//---------------------------------------------------------------------------

void TfrmCompetitorCategoryResultEdit::calculateCommonRanks(TList *compList,
                                                            int categoryId){
//Результат выбираемый пользователем
int btnRes;

    //Проверить наличие мест по: стрельбе и боям, для участников категории
    for(int i=0; i < compList->Count; i++){
        TCompetitor *competitor = (TCompetitor*)(compList->Items[i]);
        //Место по стрельбе
        if(competitor->result.getShootRank() <= 0){
            //Сообщить о том, что участник без результата
            btnRes = MessageDlg("Участник " +
                        competitor->getPerson().getSurname() +
                        " " + competitor->getPerson().getName() +
                        " не имеет места по стрельбе! Продолжить расчет мест?",
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
            if(btnRes != mrYes){
                //Остановиться, не выполнять расчет мест
                return;
                }
            }



        //Место по РБ без ХО
        if(competitor->result.getFightWOKnifeRank() <= 0){
            //Сообщить о том, что участник без результата
            btnRes = MessageDlg("Участник " +
                        competitor->getPerson().getSurname() +
                        " " + competitor->getPerson().getName() +
                        " не имеет места по РБ без ХО! Продолжить расчет мест?",
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
            if(btnRes != mrYes){
                //Остановиться, не выполнять расчет мест
                return;
                }
            }

        //Место по РБ c ХО
        if(competitor->result.getFightWKnifeRank() <= 0){
            //Сообщить о том, что участник без результата
            btnRes = MessageDlg("Участник " +
                        competitor->getPerson().getSurname() +
                        " " + competitor->getPerson().getName() +
                        " не имеет места по РБ c ХО! Продолжить расчет мест?",
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
            if(btnRes != mrYes){
                //Остановиться, не выполнять расчет мест
                return;
                }
            }
        }

    //Можем продолжать расчет мест
    compList->Sort(compareCommonResults);
    //Расставить места участников, в соответствии с упорядочиванием
    for(int i=0; i < compList->Count; i++){
        TCompetitor * competitor = (TCompetitor*)compList->Items[i];
        competitor->result.setCommonRank(i + 1);
        competitor->storeResult(categoryId);
        }
}


int __fastcall compareCommonResults(void *fstItem, void *secItem){
//Расчитаем балы для первого участника
int fstRank =  ((TCompetitor *)fstItem)->result.getShootRank();
int fstScore = dmCurrentState->getScoreForRank(fstRank);
    fstRank =  ((TCompetitor *)fstItem)->result.getFightWOKnifeRank();
    fstScore += dmCurrentState->getScoreForRank(fstRank);
    fstRank =  ((TCompetitor *)fstItem)->result.getFightWKnifeRank();
    fstScore += dmCurrentState->getScoreForRank(fstRank);
//Расчитаем балы для второго участника
int secRank =  ((TCompetitor *)secItem)->result.getShootRank();
int secScore = dmCurrentState->getScoreForRank(secRank);
    secRank =  ((TCompetitor *)secItem)->result.getFightWOKnifeRank();
    secScore += dmCurrentState->getScoreForRank(secRank);
    secRank =  ((TCompetitor *)secItem)->result.getFightWKnifeRank();
    secScore += dmCurrentState->getScoreForRank(secRank);


    if( fstScore > secScore ){
        return -1;
        }
    else if( fstScore < secScore ){
            return 1;
            }
         else{
            //При равных балах, приоритет отдаем РБ без ХО
            int fstWOKRank =  ((TCompetitor *)fstItem)->result.getFightWOKnifeRank();
            int secWOKRank =  ((TCompetitor *)secItem)->result.getFightWOKnifeRank();
            if(fstWOKRank > secWOKRank){
                return 1;
                }
            else if(fstWOKRank < secWOKRank){
                return -1;
                }
            return 0;
            }
}

void __fastcall TfrmCompetitorCategoryResultEdit::cmboxFightVersionChange(
      TObject *Sender)
{
    TList *category;
    if(!chboxFemaleCategory->Checked)
        category = dmCurrentState->getMaleCategoryList();
    else
        category = dmCurrentState->getFemaleCategoryList();

    //Поменялась боевая версия для первого списка
    createAgeWeightComboBoxByFV(cmboxAvailCategory, category, cmboxFightVersion);
    cmboxAvailCategory->ItemIndex = 0;
    changeCompetitorList(Sender);    
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::bbtnPrintCurrentCategoryClick(
      TObject *Sender)
{
    //
    // Печать выбранной в первой панели категории
    //

    //Выбираем категорию, которую будем писать
    TCategory *printCategory = getCategoryByIndex(cmboxAvailCategory, cmboxFightVersion, categoryIndex);

    dmReportDataSource->finalReport = true;
    dmReportDataSource->setCategoryToPrintById(printCategory->getId());
    //Напечатать протокол категории
    frmCategoryFinalReport->qrCategory->Preview();
}
//---------------------------------------------------------------------------


