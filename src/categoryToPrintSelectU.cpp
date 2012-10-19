//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "competitorPairsReportU.h"
#include "categoryReportU.h"
#include "categoryTreeReportU.h"
#include "categoryFinalReportU.h"
#include "reportDataSourceDM.h"

#include "categoryToPrintSelectU.h"
#include "currentStateDM.h"
#include "competitorCtrl.h"
#include "categoryCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCategoryToPrintSelect *frmCategoryToPrintSelect;



//---------------------------------------------------------------------------
__fastcall TfrmCategoryToPrintSelect::TfrmCategoryToPrintSelect(TComponent* Owner)
    : TForm(Owner)
{
    pairsOrderTitle = "Выбор категорий для печати - \"Списка пар\"";
    protocolTitle = "Выбор категорий для печати - \"Протоколов\"";;
    fightTreeTitle = "Выбор категорий для печати - \"Деревьев боев\"";;
    finalProtocolTitle = "Выбор категорий для печати - \"Протоколы с результатами\""; 

}

void TfrmCategoryToPrintSelect::createNotPrintedListBox(TList *categories, bool isIndexedFill){
    lbNotPrintedCategories->Clear();
    if(isIndexedFill){
        categoryOrder.clear();
        }
    for(int i=0; i < categories->Count; i++){
        //Текущая категория
        TCategory * curCategory = (TCategory*)categories->Items[i];
        //Если в категории есть участники добавляем в список
        if(!curCategory->getCompetitorsAmount()) continue;
        //Определить название для категории
        AnsiString asCategory = AnsiString().sprintf("%02d", curCategory->getAvailCategory().getStartAge());
        asCategory += " - " + AnsiString().sprintf("%02d", curCategory->getAvailCategory().getEndAge());

        asCategory += " лет ";

        //Проверить вес , если это 500 или ноль скорректировать фразу
        double startWeight = curCategory->getAvailCategory().getStartWeight();
        double endWeight = curCategory->getAvailCategory().getEndWeight();

        if(startWeight > 1){
            asCategory += " / " + FloatToStrF(startWeight,
                                            ffFixed, 1, 1);
            }
        else{
            asCategory += " / до ";
            }
        if (endWeight > 450){
            asCategory += " кг и выше";
            }
        else{
            asCategory += ((startWeight > 1)? AnsiString(" - ") : AnsiString("")) +
            FloatToStrF(endWeight, ffFixed, 1, 1);
            asCategory += " кг. ";
            }

        //Получаем боевую версию
        AnsiString asFightVersion = curCategory->getFightVersion().getCode().Trim();
        //Сформируем полное название для категории
        asCategory = asFightVersion + "  " + asCategory;
        if(curCategory->getAvailCategory().getFemale()){
            //Если категория женская, отметим это
            asCategory = "(Ж)  " + asCategory;
            }
        lbNotPrintedCategories->AddItem(asCategory, (TObject*)curCategory);
        if(isIndexedFill){
            //Запомнить индекс
            categoryOrder[asCategory] = curCategory;
            }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::FormShow(TObject *Sender)
{
    // Определить список категорий, который будем сортировать //
    TList *category = dmCurrentState->getCategoryList();
    category->Sort(compareCategories);
    lbPrintedCategories->Clear();
    createNotPrintedListBox(category, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::bbtnCategoryToPrintClick(TObject *Sender)
{
    //Перенести категории из нераспределенных в упорядоченные
    lbNotPrintedCategories->MoveSelection(lbPrintedCategories);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::bbtnCategoryToNotPrintedClick(TObject *Sender)
{
    //Убрать категории из упорядоченного списка
    lbPrintedCategories->MoveSelection(lbNotPrintedCategories);
    //Отсортировать и перестроить список непечатаемых категорий
    TList *toSort = new TList();
    toSort->Clear();
    //Формируем список категорий  
    for(int i=0; i < lbNotPrintedCategories->Count; i++){
        toSort->Add(categoryOrder[lbNotPrintedCategories->Items->Strings[i]]);
        }
    //Сортируем список категорий 
    toSort->Sort(compareCategories);
    //Пересоздать список непечатаемых категорий
    createNotPrintedListBox(toSort, false);   //Индекс не трогаем
    delete (TList*)toSort;       
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::bbtnCategoryUpClick(TObject *Sender)
{
    //Сдвинуть выделенынй блок вверх
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::bbtnCategoryDownClick(TObject *Sender)
{
    //Сдвинуть вниз выделенный блок
}



TList * TfrmCategoryToPrintSelect::toTList(map<AnsiString, TCategory*> co, TListBox *lb){
    //Берем список и заполняем его значениями
    TList* list = new TList();
    list->Clear();
    for(int c=0; c < lb->Count; c++){
        //Найдем категорию, которую будем выводить
        TCategory *curCategory = co[lb->Items->Strings[c]];
        //Проверить сколько участников в категории, если меньше двух не печатать
        if(curCategory->getCompetitorsAmount()< 2){
            continue;
            }
        list->Add(curCategory);
        }
    //Вернуть полученный список 
    return list;     
}


//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::bbtnPrintClick(TObject *Sender)
{
//получить список категорий
TList *listToPrint = toTList(categoryOrder, lbPrintedCategories);
    dmReportDataSource->finalReport = false;
    if(listToPrint->Count){
        switch(reportType){
            //Печатаем список пар
            case rtPAIRSORDER :
                frmCompetitorPairsReport->PreviewPairsOrder(categoryOrder, lbPrintedCategories);
                break;
            //Печатаем деревья
            case rtFIGHTTREE :
                frmCategoryTreeReport->PreviewFightTrees(listToPrint);
                break;
            //Печатаем протоколы
            case rtPROTOCOL :
                frmCategoryReport->PreviewProtocols(listToPrint);
                break;
            //Печатаем протоколы
            case rtFINALPROTOCOL :
                dmReportDataSource->finalReport = true;
                frmCategoryFinalReport->PreviewFinalProtocols(listToPrint);
            }
        }
    else{
        MessageDlg("В выбранных категориях, количество участников меньше двух!",
        mtWarning, TMsgDlgButtons() << mbOK, 0);
        }
    delete (TList*)listToPrint; 
}
//---------------------------------------------------------------------------



void TfrmCategoryToPrintSelect::PrintPairsOrder(void){
    //Печатаем список пар
    reportType = rtPAIRSORDER;
    //Установим заголовок окна
    Caption = pairsOrderTitle;
    ShowModal(); 
}

void TfrmCategoryToPrintSelect::PrintProtocols(void){
    //Печатаем протоколы
    reportType = rtPROTOCOL;
    //Установим заголовок окна
    Caption = protocolTitle;
    ShowModal();
}

void TfrmCategoryToPrintSelect::PrintFinalProtocols(void){
    //Печатаем заключительные протоколы
    reportType = rtFINALPROTOCOL;
    //Установим заголовок окна
    Caption = finalProtocolTitle;
    ShowModal();
}

void TfrmCategoryToPrintSelect::PrintFightTrees(void){
    //Печатаем деревья
    reportType = rtFIGHTTREE;
    //Установим заголовок окна
    Caption = fightTreeTitle;
    ShowModal();
}

