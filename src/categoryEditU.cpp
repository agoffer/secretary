//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "categoryEditU.h"
#include "manuallyAddCategoryEditU.h"

#include "currentStateDM.h"

#include "categoryReportU.h"
#include "categoryTreeReportU.h"
#include "uncategoryListReportU.h"


#include "reportDataSourceDM.h"
#include "availCategoryCtrl.h"
#include "currentStateDM.h"

#include "categoryToPrintSelectU.h"


#include "categoryFinalReportU.h"

#include "manualDrawEditU.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCategoryEdit *frmCategoryEdit;



void addToGridCompetitorList(TCompetitor competitor, int addIndex, TStringGrid *grid){
    //Ф.И.О.
    //Ф.И.О.
    AnsiString surname = competitor.getPerson().getSurname();
    AnsiString name = competitor.getPerson().getName().SubString(1,1) + ".";
    AnsiString patronymic = competitor.getPerson().getPatronymic().SubString(1,1);
    patronymic += (patronymic.Length()>0)? "." : " ";
    AnsiString female = competitor.getPerson().getFemale()?"(Ж) " : " ";
    AnsiString snp = female + surname + " " + name + " " +patronymic;

    //Добавить участника в таблицу

    //Добавить ФИО
    grid->Cells[0][addIndex] = snp;

    //Добавить название команды
    TRequest *request = dmCurrentState->getRequestById(competitor.getRequest().getId());
    if(request){
        grid->Cells[1][addIndex] = request->getClub().getName();
        }
    else{
        grid->Cells[1][addIndex] = "-- нет заявки --";
        }

    //Добавить уровень мастерства
    grid->Cells[2][addIndex] = competitor.getSkill().getShortDescription();

    //Добавить возраст / вес
    grid->Cells[3][addIndex] = IntToStr(YearsPassCalculator(
                                                        competitor.getPerson().getDob()
                                                        )) + " / " +
                                FloatToStrF(competitor.getWeight(),
                                            ffFixed, 4, 1);

}



bool ShowGridCompetitorList(TStringGrid *grid, TList *list){

    //Проходимся по списку и отображаем участников

    //Отобразить данные в таблице
    if(list->Count)
        grid->RowCount = list->Count + 1;
    else{
        //Список участников отсутствует
        grid->RowCount = 2;
        grid->Rows[1]->Clear();
        return false;
        }

    for(int cn = 0; cn < list->Count; cn++){
        addToGridCompetitorList(*((TCompetitor*)list->Items[cn]), cn + 1,  grid);
        }

    return true; 
}


void addUncategoryFightVersion(TCompetitor competitor, int addIndex, int colIndex, TStringGrid *grid){
    //Получим спиосок нераспределенных версий для участника и отобразим его
    TList * unFV = competitor.getUncategoryFightVersion();

    //Пройдемся по списку не распределенных боевых версий и отобразим его
    AnsiString asFV="";
    for(int i = 0; i < (unFV->Count - 1); i++){
        asFV += ((TFightVersion*)unFV->Items[i])->getCode() + ", ";
        }
    if(unFV->Count > 0){
        asFV+= ((TFightVersion*)unFV->Items[unFV->Count - 1])->getCode();
        }
    destroyList(unFV, etFIGHTVERSION);

    //Отобразим список версий
   grid->Cells[colIndex][addIndex] = asFV; 
}


void addExtendedFightVersion(TCompetitor competitor, int addIndex, int colIndex, TStringGrid *grid){
    //Получим дополнительный версий  для участника и отобразим его
    TList * exFV = competitor.getExtendedFightVersion();

    //Пройдемся по списку дополнительных боевых версий и отобразим его
    AnsiString asFV="";
    for(int i = 0; i < (exFV->Count - 1); i++){
        asFV += ((TFightVersion*)exFV->Items[i])->getCode() + ", ";
        }
    if(exFV->Count > 0){
        asFV+= ((TFightVersion*)exFV->Items[exFV->Count - 1])->getCode();
        }
    destroyList(exFV, etFIGHTVERSION);
    //Отобразим список версий
   grid->Cells[colIndex][addIndex] = asFV;
}


bool ShowGridUncategoryCompetitorList(TStringGrid *grid, TList *list){
    //Проходимся по списку и отображаем участников

    //Отобразить данные в таблице
    if(list->Count)
        grid->RowCount = list->Count + 1;
    else{
        //Список участников отсутствует
        grid->RowCount = 2;
        grid->Rows[1]->Clear();
        return false;
        }

    for(int cn = 0; cn < list->Count; cn++){
        addToGridCompetitorList(*((TCompetitor*)list->Items[cn]), cn + 1,  grid);
        addUncategoryFightVersion(*((TCompetitor*)list->Items[cn]), cn + 1, 4/* предпоследний столбец */, grid);
        addExtendedFightVersion(*((TCompetitor*)list->Items[cn]), cn + 1, 5/* последний столбец */, grid);
        }
    //Отобразили список
    return true;
}


void createCategoryIndexFVComboBox(TList *category, TComboBox *cbFightVersion, map<AnsiString, TCategory*> &catIndex){

    cbFightVersion->Clear();
    catIndex.clear();
    //Проходимся по списку категорий и формируем выпадающий список
    for(int wa = 0; wa < category->Count; wa++){
        //Берем категорию
        TCategory *curCategory = (TCategory*)category->Items[wa];
        //Формируем строку в формате [sA - eA / sW - eW]

        AnsiString acCategory = AnsiString().sprintf("%02d", curCategory->getAvailCategory().getStartAge());
        acCategory += " - " + AnsiString().sprintf("%02d", curCategory->getAvailCategory().getEndAge());
        acCategory += " / " + FloatToStrF(curCategory->getAvailCategory().getStartWeight(),
                                            ffFixed, 1, 1);
        acCategory += " - " + FloatToStrF(curCategory->getAvailCategory().getEndWeight(),
                                            ffFixed, 1, 1);

        //Формируем список боевых версий
        AnsiString acFightVersion = curCategory->getFightVersion().getCode().Trim();
        //Проверяем, создана ли уже такая строка, если нет добавляем ее в список
        bool find = false;
        for(int i = 0; i < cbFightVersion->Items->Count; i++){
            if(!acFightVersion.AnsiCompare(cbFightVersion->Items->Strings[i])){find = true; break;};
            }
        if(!find){
            //Не найдено в списке, добавляем
            cbFightVersion->Items->Add(acFightVersion);
            }
        //Сформируем ключ для инедксирования категории
        AnsiString indexKey = acCategory + "_" + acFightVersion;
        //Запомнить индекс
        catIndex[indexKey] = curCategory;
        }
    cbFightVersion->Sorted = true;
}



void createAgeWeightComboBoxByFV(TComboBox *cbCategory, TList *category,
                                 TComboBox *cbFightVersion){

    cbCategory->Clear();
    //Для какой боевой версии формируем список
    AnsiString fightVersion = cbFightVersion->Text;
    //Проходимся по списку категорий и формируем выпадающий список
    for(int wa = 0; wa < category->Count; wa++){
        //Берем категорию
        TCategory *curCategory = (TCategory*)category->Items[wa];
        //Проверяем боевую версию для категории
        AnsiString acFightVersion = curCategory->getFightVersion().getCode().Trim();
        if(!fightVersion.AnsiCompare(acFightVersion)){
            //Формируем строку в формате [sA - eA / sW - eW]
            AnsiString acCategory = AnsiString().sprintf("%02d", curCategory->getAvailCategory().getStartAge());
            acCategory += " - " + AnsiString().sprintf("%02d", curCategory->getAvailCategory().getEndAge());
            acCategory += " / " + FloatToStrF(curCategory->getAvailCategory().getStartWeight(),
                                                ffFixed, 1, 1);
            acCategory += " - " + FloatToStrF(curCategory->getAvailCategory().getEndWeight(),
                                                ffFixed, 1, 1);
            //Добавляем категорию в список
            cbCategory->Items->Add(acCategory);
            }
        }
    cbCategory->Sorted = true;
}




void setCategoryTableHeader(TStringGrid *grid){
    grid->ColCount = 4; grid->FixedCols = 0;
    grid->RowCount = 2; grid->FixedRows = 1;
    grid->Cells[0][0] = "Ф.И.О";
    grid->Cells[1][0] = "Команда";
    grid->Cells[2][0] = "Уровень мастерства";
    grid->Cells[3][0] = "Возраст / Вес";
}


void setUncategoryTableHeader(TStringGrid *grid){
    grid->ColCount = 6; grid->FixedCols = 0;
    grid->RowCount = 2; grid->FixedRows = 1;
    grid->Cells[0][0] = "Ф.И.О";
    grid->Cells[1][0] = "Команда";
    grid->Cells[2][0] = "Уровень мастерства";
    grid->Cells[3][0] = "Возраст / Вес";
    grid->Cells[4][0] = "Неопределенные версии";
    grid->Cells[5][0] = "Добавленные версии";
}


//---------------------------------------------------------------------------
__fastcall TfrmCategoryEdit::TfrmCategoryEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryEdit::FormResize(TObject *Sender)
{
    //Изменить размер панелей
    pnlCategoryFirst->Width = frmCategoryEdit->ClientWidth / 2;
    grboxUncategory->Width = frmCategoryEdit->ClientWidth * 0.62;
    pnlUncategory->Height = frmCategoryEdit->ClientHeight * 0.45;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryEdit::FormCreate(TObject *Sender)
{
    //Установить заголовки таблиц
    setCategoryTableHeader(strgrdCategoryFirst);
    setCategoryTableHeader(strgrdCategorySecond);
    setUncategoryTableHeader(strgrdUncategory);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryEdit::FormShow(TObject *Sender)
{
    //-- При отображении формы восстановить состояние категорий
    InitFields();
}
//---------------------------------------------------------------------------





void TfrmCategoryEdit::InitFields(void){
    //-- Пройдемся по списку полученных категорий и заполним списки
    chboxFemaleCategory->Checked = false;
    TList *category = dmCurrentState->getMaleCategoryList();
    createCategories(category);
    //Получить индекс текущей выбранной категории
    AnsiString indexKey = cmboxAvailCategoryFirst->Items->Strings[0];
    indexKey += "_" + cmboxFightVersionFirst->Items->Strings[0];
    TCategory *currentCategory = categoryIndex[indexKey];
    //Отобразить списки участников в категориях
    ShowCompetitorListFirst(currentCategory);
    ShowCompetitorListSecond(currentCategory);
    //Отобразим список участников не попавших в категории
    ShowUncategoryCompetitorList();
}

void TfrmCategoryEdit::createCategories(TList *category){
    //список весов и возрастов
    createCategoryIndexFVComboBox(category, cmboxFightVersionFirst, categoryIndex);
    cmboxFightVersionSecond->Items = cmboxFightVersionFirst->Items;
    cmboxFightVersionUncategory->Items = cmboxFightVersionFirst->Items;
    cmboxFightVersionFirst->ItemIndex = 0;
    cmboxFightVersionSecond->ItemIndex = 0;
    cmboxFightVersionUncategory->ItemIndex = 0;
    createAgeWeightComboBoxByFV(cmboxAvailCategoryFirst, category, cmboxFightVersionFirst);
    cmboxAvailCategorySecond->Items = cmboxAvailCategoryFirst->Items;
    cmboxAvailCategoryUncategory->Items = cmboxAvailCategoryFirst->Items;
    cmboxAvailCategoryUncategory->ItemIndex = 0;
    cmboxAvailCategoryFirst->ItemIndex = 0;
    cmboxAvailCategorySecond->ItemIndex = 0;
    //Если задано условие поиска переделать список в первом окне
    if(chboxCompetitorSearch->Checked){
        createSearchedCategories(edtCompetitorSearch->Text);
        }
}


void TfrmCategoryEdit::createSearchedCategories(AnsiString surname){
    TList *category = TCategory::getExtendedByCompetitionIdSurname(dmCurrentState->getCompetition().getId(), surname);
    //список весов и возрастов
    map<AnsiString, TCategory*> searchedCategoryIndex;
    createCategoryIndexFVComboBox(category, cmboxFightVersionFirst, searchedCategoryIndex);
    cmboxFightVersionFirst->ItemIndex = 0;
    createAgeWeightComboBoxByFV(cmboxAvailCategoryFirst, category, cmboxFightVersionFirst);
    cmboxAvailCategoryFirst->ItemIndex = 0;

}




void __fastcall TfrmCategoryEdit::chboxFemaleCategoryClick(TObject *Sender)
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
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    ShowUncategoryCompetitorList();
    //Сбросить условия поиска
    chboxCompetitorSearch->Checked = false;
    edtCompetitorSearch->Clear();
}
//---------------------------------------------------------------------------



void TfrmCategoryEdit::ShowCompetitorListFirst(TCategory* category){
    if(category == NULL){
        //Список участников отсутствует
        strgrdCategoryFirst->RowCount = 2;
        strgrdCategoryFirst->Rows[1]->Clear();
        bbtnToSecond->Enabled = false;
        bbtnMakeUncategoryFirst->Enabled = false;
        //Спрятать кнопки печати отдельной категории
        bbtnPrintCategoryFirst->Enabled = false;
        bbtnPrintTreeFirst->Enabled = false;   
        return;
        }
    //Получисть список участников в категории
    destroyList(competitorListFirst, etCOMPETITOR);
    competitorListFirst = TCompetitor::getExtendedByCategoryId(category->getId());
    //Отобразить список
    if(ShowGridCompetitorList(strgrdCategoryFirst, competitorListFirst)){
        //Разрешить выполнение операций над участниками
        bbtnToSecond->Enabled = true;
        bbtnMakeUncategoryFirst->Enabled = true;
        //Показать кнопки печати отдельной категории
        bbtnPrintCategoryFirst->Enabled = true;
        bbtnPrintTreeFirst->Enabled = true;
        }
    else{
        bbtnToSecond->Enabled = false;
        bbtnMakeUncategoryFirst->Enabled = false;
        //Спрятать кнопки печати отдельной категории
        bbtnPrintCategoryFirst->Enabled = false;
        bbtnPrintTreeFirst->Enabled = false;
        }
}


void TfrmCategoryEdit::ShowCompetitorListSecond(TCategory* category){
    if(category == NULL){
        //Список участников отсутствует
        strgrdCategorySecond->RowCount = 2;
        strgrdCategorySecond->Rows[1]->Clear();
        bbtnToFirst->Enabled = false;
        bbtnMakeUncategorySecond->Enabled = false;
        //Спрятать кнопки печати отдельной категории
        bbtnPrintCategorySecond->Enabled = false;
        bbtnPrintTreeSecond->Enabled = false;
        return;
        }
    //Получисть список участников в категории
    destroyList(competitorListSecond, etCOMPETITOR);
    competitorListSecond = TCompetitor::getExtendedByCategoryId(category->getId());
    //Отобразить список
    if(ShowGridCompetitorList(strgrdCategorySecond, competitorListSecond)){
        //Разрешить выполнение операций над участниками
        bbtnToFirst->Enabled = true;
        bbtnMakeUncategorySecond->Enabled = true;
        //Показать кнопки печати отдельной категории
        bbtnPrintCategorySecond->Enabled = true;
        bbtnPrintTreeSecond->Enabled = true;
        }
    else{
        bbtnToFirst->Enabled = false;
        bbtnMakeUncategorySecond->Enabled = false;
        //Спрятать кнопки печати отдельной категории
        bbtnPrintCategorySecond->Enabled = false;
        bbtnPrintTreeSecond->Enabled = false;
        }
}


void TfrmCategoryEdit::ShowUncategoryCompetitorList(void){
    //Получисть список участников вне категорий
//    destroyList(uncategoryCompetitorList, etCOMPETITOR);
//    uncategoryCompetitorList = TCompetitor::getExtendedUncategoryByCompetitionId(dmCurrentState->getCompetition().getId(),
//                                                                                chboxFemaleCategory->Checked);
    dmCurrentState->createUncategoryCompetitorList(dmCurrentState->getCompetition());
    uncategoryCompetitorList = dmCurrentState->getUncategoryCompetitorList(chboxFemaleCategory->Checked);
    //Отобразить список
    if(
    ShowGridUncategoryCompetitorList(strgrdUncategory, uncategoryCompetitorList)
    ){
     bbtnInCategory->Enabled = true;
        }
    else{
        bbtnInCategory->Enabled = false;
        }
}


TCategory* getCategoryByIndex(TComboBox *weightAgeList, TComboBox *fightVersionList, map<AnsiString, TCategory*>  catIndex){
    //Получить индекс текущей выбранной категории
    AnsiString indexKey = weightAgeList->Items->Strings[weightAgeList->ItemIndex];
    indexKey += "_" + fightVersionList->Items->Strings[fightVersionList->ItemIndex];
    return catIndex[indexKey];
}


void TfrmCategoryEdit::setUndestributedCategory(TComboBox * cmboxCategory,
                                                TComboBox * cmboxFightVersion){

    //Установить значения списка весовых и возрастных категорий
    cmboxFightVersionUncategory->ItemIndex = cmboxFightVersion->ItemIndex;
    cmboxAvailCategoryUncategory->Items = cmboxCategory->Items; 
    cmboxAvailCategoryUncategory->ItemIndex = cmboxCategory->ItemIndex;
}

void __fastcall TfrmCategoryEdit::changeCompetitorListFirst(TObject *Sender)
{
    //Отобразить списки участников в категориях
    ShowCompetitorListFirst(getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex));
    setUndestributedCategory(cmboxAvailCategoryFirst, cmboxFightVersionFirst);
}
//---------------------------------------------------------------------------


void __fastcall TfrmCategoryEdit::cmboxFightVersionFirstChange(
      TObject *Sender)
{
    TList *category;
    if(!chboxFemaleCategory->Checked){
        //Проверяем есть ли поиск
        if(chboxCompetitorSearch->Checked){
            category = TCategory::getExtendedByCompetitionIdSurname(dmCurrentState->getCompetition().getId(), edtCompetitorSearch->Text);
        } else{
            category = dmCurrentState->getMaleCategoryList();
            }
        }
    else{
        //Проверяем есть ли поиск
        if(chboxCompetitorSearch->Checked){
            category = TCategory::getExtendedByCompetitionIdSurname(dmCurrentState->getCompetition().getId(), edtCompetitorSearch->Text);
        } else{
            category = dmCurrentState->getFemaleCategoryList();
            }
        }

    //Поменялась боевая версия для первого списка
    createAgeWeightComboBoxByFV(cmboxAvailCategoryFirst, category, cmboxFightVersionFirst);
    cmboxAvailCategoryFirst->ItemIndex = 0;
    changeCompetitorListFirst(Sender);
}


//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::changeCompetitorListSecond(TObject *Sender)
{
    //Отобразить списки участников в категориях
    ShowCompetitorListSecond(getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex));
    setUndestributedCategory(cmboxAvailCategorySecond, cmboxFightVersionSecond);

}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::cmboxFightVersionSecondChange(
      TObject *Sender)
{
    TList *category;
    if(!chboxFemaleCategory->Checked)
        category = dmCurrentState->getMaleCategoryList();
    else
        category = dmCurrentState->getFemaleCategoryList();

    //Поменялась боевая версия для первого списка
    createAgeWeightComboBoxByFV(cmboxAvailCategorySecond, category, cmboxFightVersionSecond);
    cmboxAvailCategorySecond->ItemIndex = 0;
    changeCompetitorListSecond(Sender);        
}
//---------------------------------------------------------------------------



TList * TfrmCategoryEdit::getSelectedCompetitorsId(TStringGrid *grid, TList *list){

    //Определим строки которые выделены
    TGridCoord first = grid->Selection.TopLeft;
    TGridCoord last = grid->Selection.BottomRight;
    
    TList * compet = new TList();
    for(int i = first.Y; i <= last.Y; i++){
        TCompetitor * newComp = new TCompetitor();
        *newComp = *((TCompetitor*)list->Items[i-1]);  
        compet->Add(newComp);
        }
    //Вернуть список идентификторов участников
    return compet;
}



void __fastcall TfrmCategoryEdit::bbtnToSecondClick(TObject *Sender)
{

    //Получить категорию, из которой переносим участников
    TCategory *fromCategory = getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex);
    TCategory *toCategory = getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex);
    if(toCategory==NULL){
        //Если категории еще нет, создать ее 
        toCategory = createNewCategory(cmboxAvailCategorySecond, cmboxFightVersionSecond);
        }

    //Одна и та же категория ничего не делаем
    if(fromCategory->getId() == toCategory->getId())return;

    //Переместить выделенных участников в другую категорию (слева на право)
    TList *compt = getSelectedCompetitorsId(strgrdCategoryFirst, competitorListFirst);

    //Удалить участников из категории
    fromCategory->eraseCompetitors(compt);

    //Добавить участников с заданными идентификаторами в категорию
    toCategory->setCompetitors(compt);

    //Удалить временные объекты участников
    destroyList(compt, etCOMPETITOR);

    //Перестроить списки участников
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    //Отобразим список участников не попавших в категории
    ShowUncategoryCompetitorList();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnToFirstClick(TObject *Sender)
{
   //Получить категорию, из которой переносим участников
    TCategory *fromCategory = getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex);
    TCategory *toCategory = getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex);
    if(toCategory==NULL){
        toCategory = createNewCategory(cmboxAvailCategoryFirst, cmboxFightVersionFirst);
        }

    //Одна и та же категория ничего не делаем
    if(fromCategory->getId() == toCategory->getId())return;

    //Переместить выделенных участников в другую категорию (слева на право)
    TList *compt = getSelectedCompetitorsId(strgrdCategorySecond, competitorListSecond);


    //Удалить участников из категории
    fromCategory->eraseCompetitors(compt);

    //Добавить участников с заданными идентификаторами в категорию
    toCategory->setCompetitors(compt);

    //Удалить идентификаторы участников
    destroyList(compt, etCOMPETITOR);

    //Перестроить списки участников
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    //Отобразим список участников не попавших в категории
    ShowUncategoryCompetitorList();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnMakeUncategoryFirstClick(
      TObject *Sender)
{
    //Определить, каких участников мы хотим вывести из категории и вывести их от туда
    //Получить категорию, из которой переносим участников
    TCategory *fromCategory = getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex);

    //Переместить выделенных участников в другую категорию (слева на право)
    TList *compt = getSelectedCompetitorsId(strgrdCategoryFirst, competitorListFirst);

    //Удалить участников из категории
    fromCategory->eraseCompetitors(compt);

    destroyList(compt, etCOMPETITOR);

    //Перестроить списки участников
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    //Отобразим список участников не попавших в категории
    ShowUncategoryCompetitorList();
}
//---------------------------------------------------------------------------


void __fastcall TfrmCategoryEdit::bbtnMakeUncategorySecondClick(
      TObject *Sender)
{
    //Определить, каких участников мы хотим вывести из категории и вывести их от туда
    //Получить категорию, из которой переносим участников
    TCategory *fromCategory = getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex);

    //Переместить выделенных участников в другую категорию (слева на право)
    TList *compet = getSelectedCompetitorsId(strgrdCategorySecond, competitorListSecond);


    //Удалить участников из категории
    fromCategory->eraseCompetitors(compet);

    destroyList(compet, etCOMPETITOR);
    
    //Перестроить списки участников
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    //Отобразим список участников не попавших в категории
    ShowUncategoryCompetitorList();
}
//---------------------------------------------------------------------------


TCategory* TfrmCategoryEdit::createNewCategory(TComboBox *weightAgeList, TComboBox *fightVersionList){
    //Получить доступную категорию и боевую версию
    AnsiString weightAge = weightAgeList->Items->Strings[weightAgeList->ItemIndex];
    AnsiString fightVersion = fightVersionList->Items->Strings[fightVersionList->ItemIndex];
    int startAge = StrToInt(weightAge.SubString(1, 2));
    int endAge = StrToInt(weightAge.SubString(6, 2));

    /////todo: Исправить вырезание значений 
    AnsiString onlyWeight = weightAge.SubString(11, weightAge.Length() - 10);
    double startWeight = StrToFloat(onlyWeight.SubString(1, onlyWeight.Pos(" - ")));
    double endWeight  = StrToFloat(onlyWeight.SubString(onlyWeight.Pos(" - ") + 2, onlyWeight.Length() - onlyWeight.Pos(" - ") + 2));

    //Получить средний вес и возраст, для того, чтобы найти доступную категорию
    int availCategoryId = TAvailCategory::checkForAvailCategory((startAge + endAge) / 2,
                                                              (startWeight + endWeight) / 2,
                                                              chboxFemaleCategory->Checked);

    int fightVersionId = dmCurrentState->findFightVersionByCode(fightVersion).getId();

    TCategory *category = new TCategory(availCategoryId, fightVersionId, dmCurrentState->getCompetition().getId());
    category->store(); 

    //Получить индекс текущей выбранной категории
    AnsiString indexKey = weightAgeList->Items->Strings[weightAgeList->ItemIndex];
    indexKey += "_" + fightVersionList->Items->Strings[fightVersionList->ItemIndex];
    //Добавить категорию в список 
    categoryIndex[indexKey] = category;
    dmCurrentState->addCategoryToList(*category); 

    //Вернуть созданную категорию 
    return category;
}

void __fastcall TfrmCategoryEdit::bbtnInCategoryClick(TObject *Sender)
{
    //Внести выбранных участников в выбранную категорию

    //Определить, каких участников мы хотим перенести в категорию
    TCategory *toCategory = getCategoryByIndex(cmboxAvailCategoryUncategory, cmboxFightVersionUncategory, categoryIndex);

    //Если такая категория существует, получим ее
    if(toCategory==NULL){
        toCategory = createNewCategory(cmboxAvailCategoryUncategory, cmboxFightVersionUncategory);
        }


    //Получить идентификаторы усчастников которых будем помещать в категорию
    TList *compt = getSelectedCompetitorsId(strgrdUncategory, uncategoryCompetitorList);

    //Добавить участников в категорию
    toCategory->setCompetitors(compt);

    //Удалить участников, которые были перенесены 
    destroyList(compt, etCOMPETITOR);

    //Перестроить списки участников
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    //Отобразим список участников не попавших в категории
    ShowUncategoryCompetitorList();


}
//---------------------------------------------------------------------------


void SortCategories(void){

    //Получить список всех категорий
    TList *categories = dmCurrentState->getCategoryList();
    //Пройдемся по категориям и выполним жеребьевку
    for(int i=0; i < categories->Count; i++){
        try{
            ((TCategory*)categories->Items[i])->sortitionCategory();
            }
        catch(AnsiString message){
            //Отобразить сообщение об ошибке
            MessageDlg(message,
               mtError, TMsgDlgButtons() << mbOK, 0);
            }
        }
}


void __fastcall TfrmCategoryEdit::bbtnPrintAllCategoryClick(
      TObject *Sender)
{
    //
    // Печатаем протоколы по всем категориям для текущих соревнований
    //

    //Провести жеребьевку всех категорий
    SortCategories();
    //Перейти к выбору категорий для печати
    frmCategoryToPrintSelect->PrintProtocols();  
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPrintCategoryFirstClick(
      TObject *Sender)
{
    //
    // Печать выбранной в первой панели категории
    //

    //Выбираем категорию, которую будем писать
    TCategory *printCategory = getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex);

    try{
        printCategory->sortitionCategory();
        }
    catch(AnsiString message){
        //Отобразить сообщение об ошибке
        MessageDlg(message,
        mtError, TMsgDlgButtons() << mbOK, 0);
        }
    dmReportDataSource->finalReport = false; 
    dmReportDataSource->setCategoryToPrintById(printCategory->getId());
    //Напечатать протокол категории
    frmCategoryReport->qrCategory->Preview();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPrintCategorySecondClick(
      TObject *Sender)
{
    //
    // Печать выбранной во второй панели категории
    //

    //Выбираем категорию, которую будем писать
    TCategory* printCategory = getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex);

    try{
        printCategory->sortitionCategory();
        }
    catch(AnsiString message){
        //Отобразить сообщение об ошибке
        MessageDlg(message,
        mtError, TMsgDlgButtons() << mbOK, 0);
        }
    dmReportDataSource->finalReport = false;
    dmReportDataSource->setCategoryToPrintById(printCategory->getId());
    //Напечатать протокол категории
    frmCategoryReport->qrCategory->Preview();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPrintTreeSecondClick(TObject *Sender)
{
    //
    // Печать выбранной во второй панели категории
    //

    //Выбираем категорию, которую будем писать
    TCategory *printCategory = getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex);

    try{
        printCategory->sortitionCategory();
        }
    catch(AnsiString message){
        //Отобразить сообщение об ошибке
        MessageDlg(message,
        mtError, TMsgDlgButtons() << mbOK, 0);
        }
    dmReportDataSource->finalReport = false;
    dmReportDataSource->setCategoryToPrintById(printCategory->getId());
    //Напечатать протокол категории
    frmCategoryTreeReport->qrTreeCategory->Preview();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPrintTreeFirstClick(TObject *Sender)
{
    //
    // Печать выбранной в первой панели категории
    //

    //Выбираем категорию, которую будем писать
    TCategory* printCategory = getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex);

    try{
        printCategory->sortitionCategory();
        }
    catch(AnsiString message){
        //Отобразить сообщение об ошибке
        MessageDlg(message,
        mtError, TMsgDlgButtons() << mbOK, 0);
        }
    dmReportDataSource->finalReport = false;
    dmReportDataSource->setCategoryToPrintById(printCategory->getId());
    //Напечатать протокол категории
    frmCategoryTreeReport->qrTreeCategory->Preview();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPrintAllCategoryTreeClick(TObject *Sender)
{
    //
    // Печатаем протоколы по всем категориям для текущих соревнований
    //

    //Провести жеребьевку всех категорий
    SortCategories();
    //Перейти к выбору категорий для печати
    frmCategoryToPrintSelect->PrintFightTrees(); 
}
//---------------------------------------------------------------------------




void __fastcall TfrmCategoryEdit::bbtnUncategoryPrintClick(TObject *Sender)
{
    //Печатать список нераспределенных и распределенных в ручную участников
    dmReportDataSource->setUncategoryListQueryByCompetitionId(dmCurrentState->getCompetition().getId());
    frmUncategoryListReport->qrUncategoryList->Preview();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPairsListClick(TObject *Sender)
{
    //Провести жеребьевку всех категорий
    SortCategories();
    // Перейти к форме составления порядка пар //
    frmCategoryToPrintSelect->PrintPairsOrder();
}
//---------------------------------------------------------------------------


void __fastcall TfrmCategoryEdit::btnAddAvailCategoryClick(TObject *Sender)
{
    //Добавить категорию в которую можно распределять участников
    frmManuallyAddCategoryEdit->female = chboxFemaleCategory->Checked;
    if(frmManuallyAddCategoryEdit->ShowModal()==mrOk){
        //Появилась новая категория
        if(MessageDlg("Добавлена категория. Проверить нераспределенных участников?",
            mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes){
            //-- Распределить участников из списка нераспределенных
            TCategory::destributeCompetitors(
                            dmCurrentState->getUncategoryCompetitorList(chboxFemaleCategory->Checked),
                            dmCurrentState->getCompetition()
                            );
            //Сохранить в списке текущих категорий
            //Возможно были добавлены категории, перечитаем их список
            dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
            //Добавить полученную категорию на форму
            TList *category; 
            if(!chboxFemaleCategory->Checked){
                category = dmCurrentState->getMaleCategoryList();
                }
            else{
                category = dmCurrentState->getFemaleCategoryList();
                }
            //список весов и возрастов
            createCategories(category);

            //Отобразим списки снова
            changeCompetitorListFirst(Sender);
            changeCompetitorListSecond(Sender);
            ShowUncategoryCompetitorList();
            }
        }
}
//---------------------------------------------------------------------------







void __fastcall TfrmCategoryEdit::cmboxFightVersionUncategoryChange(
      TObject *Sender)
{
    //Изменить список весовых/возрастных для нераспределенных
    TList *category;
    if(!chboxFemaleCategory->Checked)
        category = dmCurrentState->getMaleCategoryList();
    else
        category = dmCurrentState->getFemaleCategoryList();

    //Поменялась боевая версия для списка нераспределенных категорий
    createAgeWeightComboBoxByFV(cmboxAvailCategoryUncategory, category,
                                cmboxFightVersionUncategory);
    cmboxAvailCategoryUncategory->ItemIndex = 0;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCategoryEdit::chboxCompetitorSearchClick(
      TObject *Sender)
{
    if(chboxCompetitorSearch->Checked){
        //список весов и возрастов
        createSearchedCategories(edtCompetitorSearch->Text);
        }
    else{
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
        }

    //Отобразим списки снова
    changeCompetitorListFirst(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::edtCompetitorSearchChange(
      TObject *Sender)
{
    //Сбросить чекбокс поиска
    chboxCompetitorSearch->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnManualDrawClick(TObject *Sender)
{
    frmManualDraw->ShowModal();
}
//---------------------------------------------------------------------------

