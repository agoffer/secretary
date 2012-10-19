//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainFormU.h"
#include "competitionEditU.h"
#include "requestEditU.h"
#include "requestCompetitorsListEditU.h"
#include "competitionSelectListU.h"
#include "availCategoryEditU.h"
#include "categoryEditU.h"
#include "resultEnterEditU.h"
#include "requestClubReportU.h"
#include "reportDataSourceDM.h"
#include "competitorCategoryResultEditU.h"
#include "categoryToPrintSelectU.h"
#include "manualDrawEditU.h"
#include "availCategoryFullEditU.h"
#include "personFullEditU.h"
#include "competitionRankEditU.h"

#include "currentStateDM.h"
#include "reportDataSourceDM.h"

#include "competitorDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmMainForm *frmMainForm;
//---------------------------------------------------------------------------
__fastcall TfrmMainForm::TfrmMainForm(TComponent* Owner)
    : TForm(Owner)
{
    lbItemIndex = 0;
}



//---------------------------------------------------------------------------
void __fastcall TfrmMainForm::tlbtnNewCompetitionClick(TObject *Sender)
{
    //-- Создать новое соревнование
    frmCompetitionEdit->ShowModal();
    if(frmCompetitionEdit->ModalResult == mrOk){
        //Сбросить состояние всех кнопок 
        EnableDisableWithRequestControls(false);
        EnableDisableWithCategoryControls(false);
        //Отображаем соревнования
        showCompetition();
        positionCompetition();

        //Сделать возможным добавлять заявки
        tlbtnNewRequest->Enabled = true;
        miNewRequest->Enabled = true;
        
        //Обновить список
        lbItemIndex = 0;
        refreshRequestListBox();
        //Удалить список участников
        destroyCompetitorsList();
        // Запретить конфигурацию приложения
        DisableConfiguration();
        }
}
//---------------------------------------------------------------------------


void TfrmMainForm::showCompetition(void){
TCompetition curCompetition = dmCurrentState->getCompetition();
    if(curCompetition.getId()){
        //Отобразим статус соревнований
        lblCompetitionTitle->Caption = curCompetition.getCompetitionRank().getDescription();
        //Установить дату проведения соревнований
        AnsiString competitionDate = curCompetition.getBeginDate().DateString() + " - " +
                                     curCompetition.getEndDate().DateString();
        lblCompetitionDate->Caption = competitionDate;
        }
    //Установить неопределнные значения
    else{
        lblCompetitionTitle->Caption = "Соревнование не определено...";
        lblCompetitionDate->Caption = "(дата проведения не определена)";
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::pnlCompetitionTitleResize(TObject *Sender)
{
    //Выровнять название соревнований по центру экрана
    positionCompetition();
}
//---------------------------------------------------------------------------

void TfrmMainForm::positionCompetition(void){
        lblCompetitionTitle->Left = (pnlCompetitionTitle->Width -
                                    lblCompetitionTitle->Width) / 2;
        lblCompetitionDate->Left =  (pnlCompetitionTitle->Width -
                                    lblCompetitionDate->Width) / 2;
}





void __fastcall TfrmMainForm::tlbtnNewRequestClick(TObject *Sender)
{
    //Добавить новую заявку
    frmRequestEdit->ShowModal();
    //Если заявка добавлена, отобразить ее в списке заявок главной формы
    if(frmRequestEdit->ModalResult == mrOk){
        //Перестроить список заявок на форме
        int requestCount = dmCurrentState->getRequestList()->Count;
        lbItemIndex = requestCount - 1;
        refreshRequestListBox();
        //удалить старый список участников
        destroyCompetitorsList();
        //Создать список участников в заявке
        competitorsList = createCompetitorsList(dmCurrentState->getRequest().getId(), strgrdCompetitorsList);
        //Если есть заявки, то отобразить соотвествующее меню
        if(requestCount > 0){
            EnableDisableWithRequestControls(true); 
            }
        }
}
//---------------------------------------------------------------------------





void TfrmMainForm::refreshRequestListBox(void){
TRequest *current;
    //Очистим список
    lstboxRequest->Clear();
    //Заполним список заново
    for(int i = 0; i < dmCurrentState->getRequestList()->Count; i++){
        //Получить текущую заявку
        current = (TRequest*)(dmCurrentState->getRequestList()->Items[i]);
        //Отобразить основные поля
        lstboxRequest->Items->Add(current->getClub().getName() + "  " +
                               "(" + current->getClub().getCity() + ")");
        }

    //Установить инедкс на выбранную заявку
    lstboxRequest->ItemIndex = lbItemIndex;
}


void __fastcall TfrmMainForm::tlbtnEditRequestCompetitorsClick(
      TObject *Sender)
{
    //Перейти к форме добавления участников к заявке
    frmRequestCompetitorsListEdit->ShowModal();
    //После возврата из редактора заявки, отобразить эту заявку в списке главной формы
    destroyCompetitorsList();
    competitorsList = createCompetitorsList(dmCurrentState->getRequest().getId(), strgrdCompetitorsList);
    //Если появились участники, открыть возможность по распределению
    if(competitorsList->Count){
        tlbtnDistribCategory->Enabled = true;
        miCompetitorsDistrib->Enabled = true;
        miManualDraw->Enabled = true;
        tlbtnManualDraw->Enabled = true;         
        
        }
    //Если есть категории, открыть возможность к распределению
    if(dmCurrentState->getCategoryList()->Count <= 0){
        dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
        }
    if(dmCurrentState->getCategoryList()->Count > 0){
        EnableDisableWithCategoryControls(true);
        }

}
//---------------------------------------------------------------------------

void TfrmMainForm::destroyCompetitorsList(void){
    //Обнулить таблицу
    clearStrGrid(strgrdCompetitorsList);
    destroyList(competitorsList, etCOMPETITOR);
    competitorsList=NULL;
}



void __fastcall TfrmMainForm::FormCreate(TObject *Sender)
{
    //Создать заголовок таблицы участников
    setCompetitorTableHeader(strgrdCompetitorsList);
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainForm::tlbtnArchiveCompetitionClick(TObject *Sender)
{
    // Открыть список соревнований для выбора //
    if(frmCompetitionSelectList->ShowModal() == mrOk){
        //Сбросить состояние всех кнопок
        EnableDisableWithRequestControls(false);
        EnableDisableWithCategoryControls(false);
        //удалить старый список участников
        destroyCompetitorsList();
        dmCurrentState->getRequest().setId(0);
        //Отображаем соревнования
        showCompetition();
        positionCompetition();

        //Сделать возможным добавлять заявки
        tlbtnNewRequest->Enabled = true;
        miNewRequest->Enabled = true;

        //Обновить список
        lbItemIndex = 0;
        refreshRequestListBox();
        //Выбрать текущую заявку
        if(dmCurrentState->getRequestList()->Count){
            dmCurrentState->setRequest(*((TRequest*)dmCurrentState->getRequestList()->Items[lbItemIndex]));
            //Если в загруженном соревновании есть заявки - открыть дополнительные
            EnableDisableWithRequestControls(true);
            }
        //Создать список участников в заявке
        competitorsList = createCompetitorsList(dmCurrentState->getRequest().getId(), strgrdCompetitorsList);
        //Получить обновленный список категорий
        dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
        //Если в загруженном соревновании есть категории открыть элементы управления
        if(dmCurrentState->getCategoryList()->Count > 0){
            EnableDisableWithCategoryControls(true);
            }
        // Запретить конфигурацию приложения
        DisableConfiguration();
        }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::EnableDisableWithCategoryControls(bool endis){
    //-- Распределение участников в категориях
    tlbtnDistribCategory->Enabled = endis;
    miCompetitorsDistrib->Enabled = endis;
    //-- Ручная жеребьевка участников
    tlbtnManualDraw->Enabled = endis;
    miManualDraw->Enabled = endis;
    //-- Печать категорий и деревьев
    miPrintAllCategory->Enabled = endis;
    miPrintAllTrees->Enabled = endis;
    tlbtnPrintAllCategory->Enabled = endis;
    tlbtnPrintAllTrees->Enabled = endis;
    //-- Ввод результата стрельбы и кроса
    miEnterResult->Enabled = endis;
    tlbtnEnterResult->Enabled = endis;
    //-- Результаты по рукопашному бою
    miEnterFightResults->Enabled = endis;
    tlbtnEnterFightResult->Enabled = endis;
    //-- Печать протоколов с результатами
    miPrintFinalCategoryReport->Enabled = endis;
    //-- Печать сводного протокола соревнований
    miExportSummaryProtocol->Enabled = endis;
    //-- Печать списка пар
    miPrintPairs->Enabled = endis;
    tlbtnPrintPairs->Enabled=endis;

}

void __fastcall TfrmMainForm::EnableDisableWithRequestControls(bool endis){
    //-- Редактировать заявку
    tlbtnEditRequestCompetitors->Enabled = endis;
    miEditRequest->Enabled = endis;
    //-- Печать списка команд
    miPrintRequestList->Enabled = endis;
    //-- Удалить заявку
    miDeleteRequest->Enabled = endis;
    tlbtnDeleteRequest->Enabled = endis;
    //-- Разрешить полное перераспределение участников  в категории
    miRedestribComp->Enabled=endis;
}


void __fastcall TfrmMainForm::DisableConfiguration() {
    miConfiguration->Enabled = false;
}


void __fastcall TfrmMainForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //Дейсвительно ли пользователь хочет завершить работу
    if(MessageDlg("Закончить работу с программой?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes){
        //Удалим все созданные динамически объекты
        destroyCompetitorsList();
        }
    else{
        //Нет, продолжаем работу с программой
        Action = caNone;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::lstboxRequestClick(TObject *Sender)
{
    //Пользователь шелкнул по списку, если изменился выбранный
    //элемент, то перегружаем список участников для заявки
    if(lstboxRequest->ItemIndex != lbItemIndex){
        //удалить старый список участников
        destroyCompetitorsList();
        lbItemIndex = lstboxRequest->ItemIndex;
        //Выбрать текущую заявку
        dmCurrentState->setRequest(*((TRequest*)dmCurrentState->getRequestList()->Items[lbItemIndex]));
        //Создать список участников в заявке
        competitorsList = createCompetitorsList(dmCurrentState->getRequest().getId(), strgrdCompetitorsList);

        }
}
//---------------------------------------------------------------------------




void __fastcall TfrmMainForm::miAddAvailCategoryClick(TObject *Sender)
{
    //Перейти к редактору доступных категорий
    frmAvailCategoryEdit->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::miCompetitorsDistribClick(TObject *Sender)
{
    //Получить обновленный список категорий
    dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
    //Отобразить результат распределения
    frmCategoryEdit->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::miEnterResultClick(TObject *Sender)
{
    //Перейти к вводу результатов
    frmResultEnterEdit->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miPrintRequestListClick(TObject *Sender)
{
    //-- Напечатать отчет о командах участвующих в соревнованиях
    dmReportDataSource->setRequestClubListByCompetitionId(dmCurrentState->getCompetition().getId());
    frmRequestClubReport->qrRequestClubList->Preview();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miEnterFightResultsClick(TObject *Sender)
{
    //Получить обновленный список категорий
    dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
    //Перейти к расстановке результатов
    frmCompetitorCategoryResultEdit->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miPrintFinalCategoryReportClick(
      TObject *Sender)
{
    //
    // Печатаем заключительные протоколы по всем категориям
    // для текущих соревнований
    //

    //Перейти к выбору категорий для печати
    frmCategoryToPrintSelect->PrintFinalProtocols();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miExportSummaryProtocolClick(TObject *Sender)
{
    //Вызвать функцию экспорта во внешний exel файл
    dmReportDataSource->summaryProtocolExport(dmCurrentState->getCompetition().getId());
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainForm::tlbtnDeleteRequestClick(TObject *Sender)
{
    //Удаление текущей заявки
    if(MessageDlg("Вы действительно желаете удалить заявку \""
        + dmCurrentState->getRequest().getClub().getName() + "\"?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo){
        //Нет, не удалять заявку
        return;
        }
    //Удалить заявку из базы данных
    TRequest::deleteById(dmCurrentState->getRequest().getId());
    //Удалить заявку и все что с ней связано из памяти
    int currentItIndex = lstboxRequest->ItemIndex;
    dmCurrentState->getRequestList()->Delete(currentItIndex);
    lstboxRequest->DeleteSelected();
    if(lstboxRequest->Count > 0){
        if(lstboxRequest->Count == currentItIndex){
            currentItIndex--;
            }
        lstboxRequest->ItemIndex = currentItIndex;
        lbItemIndex = -1;
        lstboxRequestClick(Sender);
        }
    else{
        destroyCompetitorsList();
        EnableDisableWithRequestControls(false);
        EnableDisableWithCategoryControls(false);
        }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::tlbtnPrintAllCategoryClick(TObject *Sender)
{
    //
    // Печатаем промежуточные протоколы
    // для текущих соревнований
    //
    //Провести жеребьвку текущих категорий
    SortCategories();
    //Перейти к выбору категорий для печати
    frmCategoryToPrintSelect->PrintProtocols();

}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::tlbtnPrintAllTreesClick(TObject *Sender)
{
    //Печать всех деревьев по текущим соревнованиям
    //Перейти к выбору категорий для печати
    //Провести жеребьвку текущих категорий
    SortCategories();
    frmCategoryToPrintSelect->PrintFightTrees();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::tlbtnPrintPairsClick(TObject *Sender)
{
    //Печать списков пар, для текущих соревнований
    //Провести жеребьвку текущих категорий
    SortCategories();
    frmCategoryToPrintSelect->PrintPairsOrder();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miRedestribCompClick(TObject *Sender)
{
    //-- Выполнить полное перераспределение участников для соревнований
    if(MessageDlg(
"Вы действительно желаете распределить участников заново? \n\
Это может привести к потере распределения пользователем и результатов соревнований. \n\
Продолжить?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo){
        //Нет, ничего не делать 
        return;
        }
    //Сначала, удалим все категории для соревнований 
    TCategory::deleteCategoriesByCompetition(dmCurrentState->getCompetition());
    //Выполнить новое перераспределение 
    TCategory::destributeCompetitors(dmCurrentState->getCompetition());
    //Получить обновленный список категорий
    dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
    //Если в загруженном соревновании есть категории открыть элементы управления
    if(dmCurrentState->getCategoryList()->Count > 0){
        EnableDisableWithCategoryControls(true);
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::tlbtnManualDrawClick(TObject *Sender){
    frmManualDraw->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::miAvailableCategoryClick(TObject *Sender)
{
  frmAvailCategoryFullEdit->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainForm::miCompetitionRankClick(TObject *Sender)
{
    frmCompetitionRankEdit->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::miPersonalDataClick(TObject *Sender)
{
    frmPersonFullEdit->ShowModal();
}
//---------------------------------------------------------------------------

