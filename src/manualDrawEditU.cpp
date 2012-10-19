//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "manualDrawEditU.h"
#include "categoryEditU.h"
#include "currentStateDM.h"
#include "categoryDM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//Массив позиций участника на форме
// Номер в жеребьевке 1  17 9  19  5  21 11  23  3  25 13 27 7   29  15  31
int position[] = {1, 9, 5, 13, 3, 7, 11, 15, 2, 4, 6, 8, 10, 12, 14, 16};

TfrmManualDraw *frmManualDraw;
//---------------------------------------------------------------------------
__fastcall TfrmManualDraw::TfrmManualDraw(TComponent* Owner)
    : TForm(Owner)
{
}

void __fastcall TfrmManualDraw::FormShow(TObject *Sender)
{
    InitFields();
}
//---------------------------------------------------------------------------


void TfrmManualDraw::InitFields(void){

    treeOrder = NULL;
    //-- Пройдемся по списку полученных категорий и заполним списки
    chboxFemaleCategory->Checked = false;
    TList *category = dmCurrentState->getMaleCategoryList();
    createCategories(category);
    changeCompetitorList(NULL);
}


//---------------------------------------------------------------------------
void __fastcall TfrmManualDraw::FormResize(TObject *Sender)
{
    //Отобразить участников в дереве, согласно жеребьевки
    //С учетом размера окна
    drawCompetitorTree(currentCompetitorList, treeOrder);
}
//---------------------------------------------------------------------------


void TfrmManualDraw::drawCompetitorTree(TList * competitorList, int* order){

    grboxTree->DestroyComponents();

    if(order == NULL) return; //Нет порядка участников

    for(int i=1; i <= competitorList->Count; i++){
        int compOrder = order[i - 1];
        if(compOrder == 0) continue; //Для текущего участник не определен порядок
        TCompetitor *competitor = (TCompetitor*)(competitorList->Items[i-1]);
        TStaticText * competitorSN = new TStaticText(grboxTree);
        competitorSN->Name = "treeCompetitorSN_"+IntToStr(i);
        //Получить атрибуты участника
        AnsiString skill = competitor->getSkill().getShortDescription();
        AnsiString ptr = competitor->getPerson().getPatronymic().SubString(1,1);
        ptr += (ptr.Length()>0)? "." : " ";
        AnsiString snp = competitor->getPerson().getSurname() + " " +
        competitor->getPerson().getName().SubString(1,1) + "." +
        " " + ptr;
        int pos = 0;
        if(compOrder % 2){
            competitorSN->Left = 10;
            pos = position[(compOrder - 1) / 2];
            competitorSN->Top = pos * 30;
            }
        else{
            competitorSN->Left = grboxTree->Width / 2 + 20;
            pos = position[(compOrder / 2) - 1];
            competitorSN->Top = pos * 30;
            }
        // Получить данные клуба для участник
        AnsiString clubName = getClubName(competitor->getRequest().getClubId());
        competitorSN->Caption = snp  + " (" + skill + ") \n(" + clubName + ")";
        // Выводим в две строки, поэтому высота увеличивается в двое
        competitorSN->Height = competitorSN->Height * 2;
        grboxTree->InsertControl(competitorSN);
        }
}

AnsiString TfrmManualDraw::getClubName(int clubId) {
        return TClub::getById(clubId).getName();
}



void TfrmManualDraw::createDrawList(TList *competitorList){
    grboxDrawList->DestroyComponents();
    for(int i=0; i < competitorList->Count; i++){
        TCompetitor *competitor = (TCompetitor*)(competitorList->Items[i]);
        TStaticText * competitorSN = new TStaticText(grboxDrawList);
        TComboBox * drawNumber = new TComboBox(grboxDrawList);

        competitorSN->Name = "competitorSN_"+IntToStr(i);

        //Получить атрибуты участника
        AnsiString skill = competitor->getSkill().getShortDescription();
        AnsiString ptr = competitor->getPerson().getPatronymic().SubString(1,1);
        ptr += (ptr.Length()>0)? "." : " ";
        AnsiString snp = competitor->getPerson().getSurname() + " " +
        competitor->getPerson().getName().SubString(1,1) + "." +
        " " + ptr;
        // Получить данные клуба для участник
        AnsiString clubName = getClubName(competitor->getRequest().getClubId());
        int allowToDisplay = (33 - snp.Length() - skill.Length());
        if (clubName.Length() > allowToDisplay) {
            allowToDisplay /= 2;
            clubName = clubName.SubString(0, allowToDisplay) + "..."
            + clubName.SubString(clubName.Length() - allowToDisplay, clubName.Length());
        }
        competitorSN->Caption = snp  + " (" + skill + ") / (" + clubName + ")";


        drawNumber->Name = "drawNumber_" + IntToStr(i);
        drawNumber->Text = "";
        drawNumber->Width = 40;

        competitorSN->Left = 10;
        competitorSN->Top = 20 + i * 20;
        drawNumber->Left = grboxDrawList->Width - 50;
        drawNumber->Top = 20 +  i * 20;

         // Ограничим строку, чтобы не вылазила на номер
        competitorSN->Width = grboxDrawList->Width - 50;
        grboxDrawList->InsertControl(competitorSN);
        grboxDrawList->InsertControl(drawNumber);
        drawNumber->Items = templateDrawNumber;

        drawNumber->OnChange = changeDrawNumber; 

        //Установить текущее значение в жеребьевке
        drawNumber->ItemIndex = competitor->getSortion() - 1;
        }
}


void TfrmManualDraw::createCategories(TList *category){
    //список весов и возрастов
    createCategoryIndexFVComboBox(category, cmboxFightVersion, categoryIndex);
    cmboxFightVersion->ItemIndex = 0;
    createAgeWeightComboBoxByFV(cmboxAvailCategory, category, cmboxFightVersion);
    cmboxAvailCategory->ItemIndex = 0;
}


void __fastcall TfrmManualDraw::chboxFemaleCategoryClick(TObject *Sender)
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

void __fastcall TfrmManualDraw::changeCompetitorList(TObject *Sender)
{
    bbtnSaveDraw->Enabled = false;
    currentCategory = getCategoryByIndex(cmboxAvailCategory,
                        cmboxFightVersion,
                        categoryIndex);
    //Создать список участников жеребьевки
    if(currentCompetitorList!=NULL){
        destroyList(currentCompetitorList, etCOMPETITOR);
        currentCompetitorList = NULL;
        }
    if(templateDrawNumber != NULL){
        templateDrawNumber->Clear();
        delete templateDrawNumber;
        templateDrawNumber = NULL;
        }
    currentCompetitorList = TCompetitor::getExtendedByCategoryId(currentCategory->getId());
    //Создать участников в списке жеребьевки
    if(treeOrder!=NULL){
        delete[] treeOrder;
        treeOrder = NULL;  
        }
    treeOrder = new int[currentCompetitorList->Count];
    templateDrawNumber = new TStringList();
    for(int i= 1 ; i <= currentCompetitorList->Count; i++){
        templateDrawNumber->Add(IntToStr(i));
        //Установим начальный порядок сортировкпи 
        treeOrder[i - 1] = i;  
        }
    createDrawList(currentCompetitorList);
    drawCompetitorTree(currentCompetitorList, treeOrder);
}
//---------------------------------------------------------------------------

void __fastcall TfrmManualDraw::cmboxFightVersionChange(TObject *Sender)
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


void __fastcall TfrmManualDraw::FormClose(TObject *Sender,
      TCloseAction &Action)
{
     //Очистить списки и структуры перед закрытием
     if(currentCompetitorList!=NULL){
        destroyList(currentCompetitorList, etCOMPETITOR);
        currentCompetitorList = NULL;
        }
    if(templateDrawNumber != NULL){
        templateDrawNumber->Clear();
        delete templateDrawNumber;
        templateDrawNumber = NULL;
        }
    if(treeOrder != NULL){
        delete[] treeOrder;
        treeOrder = NULL; 
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmManualDraw::bbtnSaveDrawClick(TObject *Sender)
{
    // Записать новый порядок жеребьевки //
    int *sortionOrder; 
    try{
    sortionOrder = collectSortionOrder(currentCompetitorList);
    }catch(Exception *e){

        if(MessageDlg("Не выполнена полная жеребьевка участников!\n Продолжить редактировать?",
            mtError, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            //Вернуться к редактированию 
            return;
        else{
            //Отменить изменения 
            changeCompetitorList(NULL);
            bbtnSaveDraw->Enabled = false;
            return;
            }

        }

    //Сохраняем порядок жеребьевки участников в категории
    dmCategoryDAO->storeSortionOrder(currentCategory->getId(), sortionOrder, currentCompetitorList->Count);
    //Отметить категорию как отсортированную вручную
    currentCategory->setDrawType(DT_MANUAL);
    bbtnSaveDraw->Enabled = false;
}
//---------------------------------------------------------------------------


int* TfrmManualDraw::collectSortionOrder(TList * competitorList){

    //Создать массив с порядком сортировки
    int* sortion = new int[competitorList->Count];

    for(int i=0; i < competitorList->Count; i++){
        // Новый номер в жеребьевке
        TComboBox * currentNumberList = (TComboBox*)grboxDrawList->FindChildControl("drawNumber_" + IntToStr(i));
        int drawNumber = currentNumberList->ItemIndex;
        if(drawNumber < 0){
            throw new Exception("EMPTY");
            }
        TCompetitor * currentCompetitor = (TCompetitor*)(competitorList->Items[i]);
        //Установить участника в позицию его сортировки
        sortion[drawNumber] = currentCompetitor->getId();
        }

    return sortion;
}

void __fastcall TfrmManualDraw::changeDrawNumber(TObject *Sender){
    //Изменили позицию участника, определим где, перестроим дерево и т.п.
    TComboBox * currentDrawNumberList = (TComboBox*)Sender;

    //Получить позицию и значение изменяемого элемента
    int position = StrToInt(currentDrawNumberList->Name.SubString(12,
                      currentDrawNumberList->Name.Length() - 11));
    int value = currentDrawNumberList->ItemIndex;

    //Если элементы с таким значением уже имеются, убрать их
    treeOrder[position] = value + 1;
    for(int i=0; i < currentCompetitorList->Count; i++){
        if(i==position) continue;
        TComboBox * otherDrawNumberList = (TComboBox*)grboxDrawList->FindChildControl("drawNumber_" + IntToStr(i));
        if(otherDrawNumberList->ItemIndex == value){
            //Сбросить значение
            otherDrawNumberList->ItemIndex = -1;
            treeOrder[i] = 0;
            }
        }
    //Отобразить новое дерево
    drawCompetitorTree(currentCompetitorList, treeOrder);
    bbtnSaveDraw->Enabled = true;
}


