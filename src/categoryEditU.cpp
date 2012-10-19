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
    //�.�.�.
    //�.�.�.
    AnsiString surname = competitor.getPerson().getSurname();
    AnsiString name = competitor.getPerson().getName().SubString(1,1) + ".";
    AnsiString patronymic = competitor.getPerson().getPatronymic().SubString(1,1);
    patronymic += (patronymic.Length()>0)? "." : " ";
    AnsiString female = competitor.getPerson().getFemale()?"(�) " : " ";
    AnsiString snp = female + surname + " " + name + " " +patronymic;

    //�������� ��������� � �������

    //�������� ���
    grid->Cells[0][addIndex] = snp;

    //�������� �������� �������
    TRequest *request = dmCurrentState->getRequestById(competitor.getRequest().getId());
    if(request){
        grid->Cells[1][addIndex] = request->getClub().getName();
        }
    else{
        grid->Cells[1][addIndex] = "-- ��� ������ --";
        }

    //�������� ������� ����������
    grid->Cells[2][addIndex] = competitor.getSkill().getShortDescription();

    //�������� ������� / ���
    grid->Cells[3][addIndex] = IntToStr(YearsPassCalculator(
                                                        competitor.getPerson().getDob()
                                                        )) + " / " +
                                FloatToStrF(competitor.getWeight(),
                                            ffFixed, 4, 1);

}



bool ShowGridCompetitorList(TStringGrid *grid, TList *list){

    //���������� �� ������ � ���������� ����������

    //���������� ������ � �������
    if(list->Count)
        grid->RowCount = list->Count + 1;
    else{
        //������ ���������� �����������
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
    //������� ������� ���������������� ������ ��� ��������� � ��������� ���
    TList * unFV = competitor.getUncategoryFightVersion();

    //��������� �� ������ �� �������������� ������ ������ � ��������� ���
    AnsiString asFV="";
    for(int i = 0; i < (unFV->Count - 1); i++){
        asFV += ((TFightVersion*)unFV->Items[i])->getCode() + ", ";
        }
    if(unFV->Count > 0){
        asFV+= ((TFightVersion*)unFV->Items[unFV->Count - 1])->getCode();
        }
    destroyList(unFV, etFIGHTVERSION);

    //��������� ������ ������
   grid->Cells[colIndex][addIndex] = asFV; 
}


void addExtendedFightVersion(TCompetitor competitor, int addIndex, int colIndex, TStringGrid *grid){
    //������� �������������� ������  ��� ��������� � ��������� ���
    TList * exFV = competitor.getExtendedFightVersion();

    //��������� �� ������ �������������� ������ ������ � ��������� ���
    AnsiString asFV="";
    for(int i = 0; i < (exFV->Count - 1); i++){
        asFV += ((TFightVersion*)exFV->Items[i])->getCode() + ", ";
        }
    if(exFV->Count > 0){
        asFV+= ((TFightVersion*)exFV->Items[exFV->Count - 1])->getCode();
        }
    destroyList(exFV, etFIGHTVERSION);
    //��������� ������ ������
   grid->Cells[colIndex][addIndex] = asFV;
}


bool ShowGridUncategoryCompetitorList(TStringGrid *grid, TList *list){
    //���������� �� ������ � ���������� ����������

    //���������� ������ � �������
    if(list->Count)
        grid->RowCount = list->Count + 1;
    else{
        //������ ���������� �����������
        grid->RowCount = 2;
        grid->Rows[1]->Clear();
        return false;
        }

    for(int cn = 0; cn < list->Count; cn++){
        addToGridCompetitorList(*((TCompetitor*)list->Items[cn]), cn + 1,  grid);
        addUncategoryFightVersion(*((TCompetitor*)list->Items[cn]), cn + 1, 4/* ������������� ������� */, grid);
        addExtendedFightVersion(*((TCompetitor*)list->Items[cn]), cn + 1, 5/* ��������� ������� */, grid);
        }
    //���������� ������
    return true;
}


void createCategoryIndexFVComboBox(TList *category, TComboBox *cbFightVersion, map<AnsiString, TCategory*> &catIndex){

    cbFightVersion->Clear();
    catIndex.clear();
    //���������� �� ������ ��������� � ��������� ���������� ������
    for(int wa = 0; wa < category->Count; wa++){
        //����� ���������
        TCategory *curCategory = (TCategory*)category->Items[wa];
        //��������� ������ � ������� [sA - eA / sW - eW]

        AnsiString acCategory = AnsiString().sprintf("%02d", curCategory->getAvailCategory().getStartAge());
        acCategory += " - " + AnsiString().sprintf("%02d", curCategory->getAvailCategory().getEndAge());
        acCategory += " / " + FloatToStrF(curCategory->getAvailCategory().getStartWeight(),
                                            ffFixed, 1, 1);
        acCategory += " - " + FloatToStrF(curCategory->getAvailCategory().getEndWeight(),
                                            ffFixed, 1, 1);

        //��������� ������ ������ ������
        AnsiString acFightVersion = curCategory->getFightVersion().getCode().Trim();
        //���������, ������� �� ��� ����� ������, ���� ��� ��������� �� � ������
        bool find = false;
        for(int i = 0; i < cbFightVersion->Items->Count; i++){
            if(!acFightVersion.AnsiCompare(cbFightVersion->Items->Strings[i])){find = true; break;};
            }
        if(!find){
            //�� ������� � ������, ���������
            cbFightVersion->Items->Add(acFightVersion);
            }
        //���������� ���� ��� �������������� ���������
        AnsiString indexKey = acCategory + "_" + acFightVersion;
        //��������� ������
        catIndex[indexKey] = curCategory;
        }
    cbFightVersion->Sorted = true;
}



void createAgeWeightComboBoxByFV(TComboBox *cbCategory, TList *category,
                                 TComboBox *cbFightVersion){

    cbCategory->Clear();
    //��� ����� ������ ������ ��������� ������
    AnsiString fightVersion = cbFightVersion->Text;
    //���������� �� ������ ��������� � ��������� ���������� ������
    for(int wa = 0; wa < category->Count; wa++){
        //����� ���������
        TCategory *curCategory = (TCategory*)category->Items[wa];
        //��������� ������ ������ ��� ���������
        AnsiString acFightVersion = curCategory->getFightVersion().getCode().Trim();
        if(!fightVersion.AnsiCompare(acFightVersion)){
            //��������� ������ � ������� [sA - eA / sW - eW]
            AnsiString acCategory = AnsiString().sprintf("%02d", curCategory->getAvailCategory().getStartAge());
            acCategory += " - " + AnsiString().sprintf("%02d", curCategory->getAvailCategory().getEndAge());
            acCategory += " / " + FloatToStrF(curCategory->getAvailCategory().getStartWeight(),
                                                ffFixed, 1, 1);
            acCategory += " - " + FloatToStrF(curCategory->getAvailCategory().getEndWeight(),
                                                ffFixed, 1, 1);
            //��������� ��������� � ������
            cbCategory->Items->Add(acCategory);
            }
        }
    cbCategory->Sorted = true;
}




void setCategoryTableHeader(TStringGrid *grid){
    grid->ColCount = 4; grid->FixedCols = 0;
    grid->RowCount = 2; grid->FixedRows = 1;
    grid->Cells[0][0] = "�.�.�";
    grid->Cells[1][0] = "�������";
    grid->Cells[2][0] = "������� ����������";
    grid->Cells[3][0] = "������� / ���";
}


void setUncategoryTableHeader(TStringGrid *grid){
    grid->ColCount = 6; grid->FixedCols = 0;
    grid->RowCount = 2; grid->FixedRows = 1;
    grid->Cells[0][0] = "�.�.�";
    grid->Cells[1][0] = "�������";
    grid->Cells[2][0] = "������� ����������";
    grid->Cells[3][0] = "������� / ���";
    grid->Cells[4][0] = "�������������� ������";
    grid->Cells[5][0] = "����������� ������";
}


//---------------------------------------------------------------------------
__fastcall TfrmCategoryEdit::TfrmCategoryEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryEdit::FormResize(TObject *Sender)
{
    //�������� ������ �������
    pnlCategoryFirst->Width = frmCategoryEdit->ClientWidth / 2;
    grboxUncategory->Width = frmCategoryEdit->ClientWidth * 0.62;
    pnlUncategory->Height = frmCategoryEdit->ClientHeight * 0.45;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryEdit::FormCreate(TObject *Sender)
{
    //���������� ��������� ������
    setCategoryTableHeader(strgrdCategoryFirst);
    setCategoryTableHeader(strgrdCategorySecond);
    setUncategoryTableHeader(strgrdUncategory);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryEdit::FormShow(TObject *Sender)
{
    //-- ��� ����������� ����� ������������ ��������� ���������
    InitFields();
}
//---------------------------------------------------------------------------





void TfrmCategoryEdit::InitFields(void){
    //-- ��������� �� ������ ���������� ��������� � �������� ������
    chboxFemaleCategory->Checked = false;
    TList *category = dmCurrentState->getMaleCategoryList();
    createCategories(category);
    //�������� ������ ������� ��������� ���������
    AnsiString indexKey = cmboxAvailCategoryFirst->Items->Strings[0];
    indexKey += "_" + cmboxFightVersionFirst->Items->Strings[0];
    TCategory *currentCategory = categoryIndex[indexKey];
    //���������� ������ ���������� � ����������
    ShowCompetitorListFirst(currentCategory);
    ShowCompetitorListSecond(currentCategory);
    //��������� ������ ���������� �� �������� � ���������
    ShowUncategoryCompetitorList();
}

void TfrmCategoryEdit::createCategories(TList *category){
    //������ ����� � ���������
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
    //���� ������ ������� ������ ���������� ������ � ������ ����
    if(chboxCompetitorSearch->Checked){
        createSearchedCategories(edtCompetitorSearch->Text);
        }
}


void TfrmCategoryEdit::createSearchedCategories(AnsiString surname){
    TList *category = TCategory::getExtendedByCompetitionIdSurname(dmCurrentState->getCompetition().getId(), surname);
    //������ ����� � ���������
    map<AnsiString, TCategory*> searchedCategoryIndex;
    createCategoryIndexFVComboBox(category, cmboxFightVersionFirst, searchedCategoryIndex);
    cmboxFightVersionFirst->ItemIndex = 0;
    createAgeWeightComboBoxByFV(cmboxAvailCategoryFirst, category, cmboxFightVersionFirst);
    cmboxAvailCategoryFirst->ItemIndex = 0;

}




void __fastcall TfrmCategoryEdit::chboxFemaleCategoryClick(TObject *Sender)
{
TList *category;
    //-- �������� ������ ��������� �� ��������������
    if(!chboxFemaleCategory->Checked){
        category = dmCurrentState->getMaleCategoryList();
        }
    else{
        category = dmCurrentState->getFemaleCategoryList();
        }
    //������ ����� � ���������
    createCategories(category);

    //��������� ������ �����
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    ShowUncategoryCompetitorList();
    //�������� ������� ������
    chboxCompetitorSearch->Checked = false;
    edtCompetitorSearch->Clear();
}
//---------------------------------------------------------------------------



void TfrmCategoryEdit::ShowCompetitorListFirst(TCategory* category){
    if(category == NULL){
        //������ ���������� �����������
        strgrdCategoryFirst->RowCount = 2;
        strgrdCategoryFirst->Rows[1]->Clear();
        bbtnToSecond->Enabled = false;
        bbtnMakeUncategoryFirst->Enabled = false;
        //�������� ������ ������ ��������� ���������
        bbtnPrintCategoryFirst->Enabled = false;
        bbtnPrintTreeFirst->Enabled = false;   
        return;
        }
    //��������� ������ ���������� � ���������
    destroyList(competitorListFirst, etCOMPETITOR);
    competitorListFirst = TCompetitor::getExtendedByCategoryId(category->getId());
    //���������� ������
    if(ShowGridCompetitorList(strgrdCategoryFirst, competitorListFirst)){
        //��������� ���������� �������� ��� �����������
        bbtnToSecond->Enabled = true;
        bbtnMakeUncategoryFirst->Enabled = true;
        //�������� ������ ������ ��������� ���������
        bbtnPrintCategoryFirst->Enabled = true;
        bbtnPrintTreeFirst->Enabled = true;
        }
    else{
        bbtnToSecond->Enabled = false;
        bbtnMakeUncategoryFirst->Enabled = false;
        //�������� ������ ������ ��������� ���������
        bbtnPrintCategoryFirst->Enabled = false;
        bbtnPrintTreeFirst->Enabled = false;
        }
}


void TfrmCategoryEdit::ShowCompetitorListSecond(TCategory* category){
    if(category == NULL){
        //������ ���������� �����������
        strgrdCategorySecond->RowCount = 2;
        strgrdCategorySecond->Rows[1]->Clear();
        bbtnToFirst->Enabled = false;
        bbtnMakeUncategorySecond->Enabled = false;
        //�������� ������ ������ ��������� ���������
        bbtnPrintCategorySecond->Enabled = false;
        bbtnPrintTreeSecond->Enabled = false;
        return;
        }
    //��������� ������ ���������� � ���������
    destroyList(competitorListSecond, etCOMPETITOR);
    competitorListSecond = TCompetitor::getExtendedByCategoryId(category->getId());
    //���������� ������
    if(ShowGridCompetitorList(strgrdCategorySecond, competitorListSecond)){
        //��������� ���������� �������� ��� �����������
        bbtnToFirst->Enabled = true;
        bbtnMakeUncategorySecond->Enabled = true;
        //�������� ������ ������ ��������� ���������
        bbtnPrintCategorySecond->Enabled = true;
        bbtnPrintTreeSecond->Enabled = true;
        }
    else{
        bbtnToFirst->Enabled = false;
        bbtnMakeUncategorySecond->Enabled = false;
        //�������� ������ ������ ��������� ���������
        bbtnPrintCategorySecond->Enabled = false;
        bbtnPrintTreeSecond->Enabled = false;
        }
}


void TfrmCategoryEdit::ShowUncategoryCompetitorList(void){
    //��������� ������ ���������� ��� ���������
//    destroyList(uncategoryCompetitorList, etCOMPETITOR);
//    uncategoryCompetitorList = TCompetitor::getExtendedUncategoryByCompetitionId(dmCurrentState->getCompetition().getId(),
//                                                                                chboxFemaleCategory->Checked);
    dmCurrentState->createUncategoryCompetitorList(dmCurrentState->getCompetition());
    uncategoryCompetitorList = dmCurrentState->getUncategoryCompetitorList(chboxFemaleCategory->Checked);
    //���������� ������
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
    //�������� ������ ������� ��������� ���������
    AnsiString indexKey = weightAgeList->Items->Strings[weightAgeList->ItemIndex];
    indexKey += "_" + fightVersionList->Items->Strings[fightVersionList->ItemIndex];
    return catIndex[indexKey];
}


void TfrmCategoryEdit::setUndestributedCategory(TComboBox * cmboxCategory,
                                                TComboBox * cmboxFightVersion){

    //���������� �������� ������ ������� � ���������� ���������
    cmboxFightVersionUncategory->ItemIndex = cmboxFightVersion->ItemIndex;
    cmboxAvailCategoryUncategory->Items = cmboxCategory->Items; 
    cmboxAvailCategoryUncategory->ItemIndex = cmboxCategory->ItemIndex;
}

void __fastcall TfrmCategoryEdit::changeCompetitorListFirst(TObject *Sender)
{
    //���������� ������ ���������� � ����������
    ShowCompetitorListFirst(getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex));
    setUndestributedCategory(cmboxAvailCategoryFirst, cmboxFightVersionFirst);
}
//---------------------------------------------------------------------------


void __fastcall TfrmCategoryEdit::cmboxFightVersionFirstChange(
      TObject *Sender)
{
    TList *category;
    if(!chboxFemaleCategory->Checked){
        //��������� ���� �� �����
        if(chboxCompetitorSearch->Checked){
            category = TCategory::getExtendedByCompetitionIdSurname(dmCurrentState->getCompetition().getId(), edtCompetitorSearch->Text);
        } else{
            category = dmCurrentState->getMaleCategoryList();
            }
        }
    else{
        //��������� ���� �� �����
        if(chboxCompetitorSearch->Checked){
            category = TCategory::getExtendedByCompetitionIdSurname(dmCurrentState->getCompetition().getId(), edtCompetitorSearch->Text);
        } else{
            category = dmCurrentState->getFemaleCategoryList();
            }
        }

    //���������� ������ ������ ��� ������� ������
    createAgeWeightComboBoxByFV(cmboxAvailCategoryFirst, category, cmboxFightVersionFirst);
    cmboxAvailCategoryFirst->ItemIndex = 0;
    changeCompetitorListFirst(Sender);
}


//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::changeCompetitorListSecond(TObject *Sender)
{
    //���������� ������ ���������� � ����������
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

    //���������� ������ ������ ��� ������� ������
    createAgeWeightComboBoxByFV(cmboxAvailCategorySecond, category, cmboxFightVersionSecond);
    cmboxAvailCategorySecond->ItemIndex = 0;
    changeCompetitorListSecond(Sender);        
}
//---------------------------------------------------------------------------



TList * TfrmCategoryEdit::getSelectedCompetitorsId(TStringGrid *grid, TList *list){

    //��������� ������ ������� ��������
    TGridCoord first = grid->Selection.TopLeft;
    TGridCoord last = grid->Selection.BottomRight;
    
    TList * compet = new TList();
    for(int i = first.Y; i <= last.Y; i++){
        TCompetitor * newComp = new TCompetitor();
        *newComp = *((TCompetitor*)list->Items[i-1]);  
        compet->Add(newComp);
        }
    //������� ������ �������������� ����������
    return compet;
}



void __fastcall TfrmCategoryEdit::bbtnToSecondClick(TObject *Sender)
{

    //�������� ���������, �� ������� ��������� ����������
    TCategory *fromCategory = getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex);
    TCategory *toCategory = getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex);
    if(toCategory==NULL){
        //���� ��������� ��� ���, ������� �� 
        toCategory = createNewCategory(cmboxAvailCategorySecond, cmboxFightVersionSecond);
        }

    //���� � �� �� ��������� ������ �� ������
    if(fromCategory->getId() == toCategory->getId())return;

    //����������� ���������� ���������� � ������ ��������� (����� �� �����)
    TList *compt = getSelectedCompetitorsId(strgrdCategoryFirst, competitorListFirst);

    //������� ���������� �� ���������
    fromCategory->eraseCompetitors(compt);

    //�������� ���������� � ��������� ���������������� � ���������
    toCategory->setCompetitors(compt);

    //������� ��������� ������� ����������
    destroyList(compt, etCOMPETITOR);

    //����������� ������ ����������
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    //��������� ������ ���������� �� �������� � ���������
    ShowUncategoryCompetitorList();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnToFirstClick(TObject *Sender)
{
   //�������� ���������, �� ������� ��������� ����������
    TCategory *fromCategory = getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex);
    TCategory *toCategory = getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex);
    if(toCategory==NULL){
        toCategory = createNewCategory(cmboxAvailCategoryFirst, cmboxFightVersionFirst);
        }

    //���� � �� �� ��������� ������ �� ������
    if(fromCategory->getId() == toCategory->getId())return;

    //����������� ���������� ���������� � ������ ��������� (����� �� �����)
    TList *compt = getSelectedCompetitorsId(strgrdCategorySecond, competitorListSecond);


    //������� ���������� �� ���������
    fromCategory->eraseCompetitors(compt);

    //�������� ���������� � ��������� ���������������� � ���������
    toCategory->setCompetitors(compt);

    //������� �������������� ����������
    destroyList(compt, etCOMPETITOR);

    //����������� ������ ����������
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    //��������� ������ ���������� �� �������� � ���������
    ShowUncategoryCompetitorList();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnMakeUncategoryFirstClick(
      TObject *Sender)
{
    //����������, ����� ���������� �� ����� ������� �� ��������� � ������� �� �� ����
    //�������� ���������, �� ������� ��������� ����������
    TCategory *fromCategory = getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex);

    //����������� ���������� ���������� � ������ ��������� (����� �� �����)
    TList *compt = getSelectedCompetitorsId(strgrdCategoryFirst, competitorListFirst);

    //������� ���������� �� ���������
    fromCategory->eraseCompetitors(compt);

    destroyList(compt, etCOMPETITOR);

    //����������� ������ ����������
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    //��������� ������ ���������� �� �������� � ���������
    ShowUncategoryCompetitorList();
}
//---------------------------------------------------------------------------


void __fastcall TfrmCategoryEdit::bbtnMakeUncategorySecondClick(
      TObject *Sender)
{
    //����������, ����� ���������� �� ����� ������� �� ��������� � ������� �� �� ����
    //�������� ���������, �� ������� ��������� ����������
    TCategory *fromCategory = getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex);

    //����������� ���������� ���������� � ������ ��������� (����� �� �����)
    TList *compet = getSelectedCompetitorsId(strgrdCategorySecond, competitorListSecond);


    //������� ���������� �� ���������
    fromCategory->eraseCompetitors(compet);

    destroyList(compet, etCOMPETITOR);
    
    //����������� ������ ����������
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    //��������� ������ ���������� �� �������� � ���������
    ShowUncategoryCompetitorList();
}
//---------------------------------------------------------------------------


TCategory* TfrmCategoryEdit::createNewCategory(TComboBox *weightAgeList, TComboBox *fightVersionList){
    //�������� ��������� ��������� � ������ ������
    AnsiString weightAge = weightAgeList->Items->Strings[weightAgeList->ItemIndex];
    AnsiString fightVersion = fightVersionList->Items->Strings[fightVersionList->ItemIndex];
    int startAge = StrToInt(weightAge.SubString(1, 2));
    int endAge = StrToInt(weightAge.SubString(6, 2));

    /////todo: ��������� ��������� �������� 
    AnsiString onlyWeight = weightAge.SubString(11, weightAge.Length() - 10);
    double startWeight = StrToFloat(onlyWeight.SubString(1, onlyWeight.Pos(" - ")));
    double endWeight  = StrToFloat(onlyWeight.SubString(onlyWeight.Pos(" - ") + 2, onlyWeight.Length() - onlyWeight.Pos(" - ") + 2));

    //�������� ������� ��� � �������, ��� ����, ����� ����� ��������� ���������
    int availCategoryId = TAvailCategory::checkForAvailCategory((startAge + endAge) / 2,
                                                              (startWeight + endWeight) / 2,
                                                              chboxFemaleCategory->Checked);

    int fightVersionId = dmCurrentState->findFightVersionByCode(fightVersion).getId();

    TCategory *category = new TCategory(availCategoryId, fightVersionId, dmCurrentState->getCompetition().getId());
    category->store(); 

    //�������� ������ ������� ��������� ���������
    AnsiString indexKey = weightAgeList->Items->Strings[weightAgeList->ItemIndex];
    indexKey += "_" + fightVersionList->Items->Strings[fightVersionList->ItemIndex];
    //�������� ��������� � ������ 
    categoryIndex[indexKey] = category;
    dmCurrentState->addCategoryToList(*category); 

    //������� ��������� ��������� 
    return category;
}

void __fastcall TfrmCategoryEdit::bbtnInCategoryClick(TObject *Sender)
{
    //������ ��������� ���������� � ��������� ���������

    //����������, ����� ���������� �� ����� ��������� � ���������
    TCategory *toCategory = getCategoryByIndex(cmboxAvailCategoryUncategory, cmboxFightVersionUncategory, categoryIndex);

    //���� ����� ��������� ����������, ������� ��
    if(toCategory==NULL){
        toCategory = createNewCategory(cmboxAvailCategoryUncategory, cmboxFightVersionUncategory);
        }


    //�������� �������������� ����������� ������� ����� �������� � ���������
    TList *compt = getSelectedCompetitorsId(strgrdUncategory, uncategoryCompetitorList);

    //�������� ���������� � ���������
    toCategory->setCompetitors(compt);

    //������� ����������, ������� ���� ���������� 
    destroyList(compt, etCOMPETITOR);

    //����������� ������ ����������
    changeCompetitorListFirst(Sender);
    changeCompetitorListSecond(Sender);
    //��������� ������ ���������� �� �������� � ���������
    ShowUncategoryCompetitorList();


}
//---------------------------------------------------------------------------


void SortCategories(void){

    //�������� ������ ���� ���������
    TList *categories = dmCurrentState->getCategoryList();
    //��������� �� ���������� � �������� ����������
    for(int i=0; i < categories->Count; i++){
        try{
            ((TCategory*)categories->Items[i])->sortitionCategory();
            }
        catch(AnsiString message){
            //���������� ��������� �� ������
            MessageDlg(message,
               mtError, TMsgDlgButtons() << mbOK, 0);
            }
        }
}


void __fastcall TfrmCategoryEdit::bbtnPrintAllCategoryClick(
      TObject *Sender)
{
    //
    // �������� ��������� �� ���� ���������� ��� ������� ������������
    //

    //�������� ���������� ���� ���������
    SortCategories();
    //������� � ������ ��������� ��� ������
    frmCategoryToPrintSelect->PrintProtocols();  
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPrintCategoryFirstClick(
      TObject *Sender)
{
    //
    // ������ ��������� � ������ ������ ���������
    //

    //�������� ���������, ������� ����� ������
    TCategory *printCategory = getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex);

    try{
        printCategory->sortitionCategory();
        }
    catch(AnsiString message){
        //���������� ��������� �� ������
        MessageDlg(message,
        mtError, TMsgDlgButtons() << mbOK, 0);
        }
    dmReportDataSource->finalReport = false; 
    dmReportDataSource->setCategoryToPrintById(printCategory->getId());
    //���������� �������� ���������
    frmCategoryReport->qrCategory->Preview();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPrintCategorySecondClick(
      TObject *Sender)
{
    //
    // ������ ��������� �� ������ ������ ���������
    //

    //�������� ���������, ������� ����� ������
    TCategory* printCategory = getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex);

    try{
        printCategory->sortitionCategory();
        }
    catch(AnsiString message){
        //���������� ��������� �� ������
        MessageDlg(message,
        mtError, TMsgDlgButtons() << mbOK, 0);
        }
    dmReportDataSource->finalReport = false;
    dmReportDataSource->setCategoryToPrintById(printCategory->getId());
    //���������� �������� ���������
    frmCategoryReport->qrCategory->Preview();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPrintTreeSecondClick(TObject *Sender)
{
    //
    // ������ ��������� �� ������ ������ ���������
    //

    //�������� ���������, ������� ����� ������
    TCategory *printCategory = getCategoryByIndex(cmboxAvailCategorySecond, cmboxFightVersionSecond, categoryIndex);

    try{
        printCategory->sortitionCategory();
        }
    catch(AnsiString message){
        //���������� ��������� �� ������
        MessageDlg(message,
        mtError, TMsgDlgButtons() << mbOK, 0);
        }
    dmReportDataSource->finalReport = false;
    dmReportDataSource->setCategoryToPrintById(printCategory->getId());
    //���������� �������� ���������
    frmCategoryTreeReport->qrTreeCategory->Preview();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPrintTreeFirstClick(TObject *Sender)
{
    //
    // ������ ��������� � ������ ������ ���������
    //

    //�������� ���������, ������� ����� ������
    TCategory* printCategory = getCategoryByIndex(cmboxAvailCategoryFirst, cmboxFightVersionFirst, categoryIndex);

    try{
        printCategory->sortitionCategory();
        }
    catch(AnsiString message){
        //���������� ��������� �� ������
        MessageDlg(message,
        mtError, TMsgDlgButtons() << mbOK, 0);
        }
    dmReportDataSource->finalReport = false;
    dmReportDataSource->setCategoryToPrintById(printCategory->getId());
    //���������� �������� ���������
    frmCategoryTreeReport->qrTreeCategory->Preview();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPrintAllCategoryTreeClick(TObject *Sender)
{
    //
    // �������� ��������� �� ���� ���������� ��� ������� ������������
    //

    //�������� ���������� ���� ���������
    SortCategories();
    //������� � ������ ��������� ��� ������
    frmCategoryToPrintSelect->PrintFightTrees(); 
}
//---------------------------------------------------------------------------




void __fastcall TfrmCategoryEdit::bbtnUncategoryPrintClick(TObject *Sender)
{
    //�������� ������ ���������������� � �������������� � ������ ����������
    dmReportDataSource->setUncategoryListQueryByCompetitionId(dmCurrentState->getCompetition().getId());
    frmUncategoryListReport->qrUncategoryList->Preview();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnPairsListClick(TObject *Sender)
{
    //�������� ���������� ���� ���������
    SortCategories();
    // ������� � ����� ����������� ������� ��� //
    frmCategoryToPrintSelect->PrintPairsOrder();
}
//---------------------------------------------------------------------------


void __fastcall TfrmCategoryEdit::btnAddAvailCategoryClick(TObject *Sender)
{
    //�������� ��������� � ������� ����� ������������ ����������
    frmManuallyAddCategoryEdit->female = chboxFemaleCategory->Checked;
    if(frmManuallyAddCategoryEdit->ShowModal()==mrOk){
        //��������� ����� ���������
        if(MessageDlg("��������� ���������. ��������� ���������������� ����������?",
            mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes){
            //-- ������������ ���������� �� ������ ����������������
            TCategory::destributeCompetitors(
                            dmCurrentState->getUncategoryCompetitorList(chboxFemaleCategory->Checked),
                            dmCurrentState->getCompetition()
                            );
            //��������� � ������ ������� ���������
            //�������� ���� ��������� ���������, ���������� �� ������
            dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
            //�������� ���������� ��������� �� �����
            TList *category; 
            if(!chboxFemaleCategory->Checked){
                category = dmCurrentState->getMaleCategoryList();
                }
            else{
                category = dmCurrentState->getFemaleCategoryList();
                }
            //������ ����� � ���������
            createCategories(category);

            //��������� ������ �����
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
    //�������� ������ �������/���������� ��� ����������������
    TList *category;
    if(!chboxFemaleCategory->Checked)
        category = dmCurrentState->getMaleCategoryList();
    else
        category = dmCurrentState->getFemaleCategoryList();

    //���������� ������ ������ ��� ������ ���������������� ���������
    createAgeWeightComboBoxByFV(cmboxAvailCategoryUncategory, category,
                                cmboxFightVersionUncategory);
    cmboxAvailCategoryUncategory->ItemIndex = 0;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCategoryEdit::chboxCompetitorSearchClick(
      TObject *Sender)
{
    if(chboxCompetitorSearch->Checked){
        //������ ����� � ���������
        createSearchedCategories(edtCompetitorSearch->Text);
        }
    else{
        TList *category;
        //-- �������� ������ ��������� �� ��������������
        if(!chboxFemaleCategory->Checked){
            category = dmCurrentState->getMaleCategoryList();
            }
        else{
            category = dmCurrentState->getFemaleCategoryList();
            }
        //������ ����� � ���������
        createCategories(category);
        }

    //��������� ������ �����
    changeCompetitorListFirst(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::edtCompetitorSearchChange(
      TObject *Sender)
{
    //�������� ������� ������
    chboxCompetitorSearch->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryEdit::bbtnManualDrawClick(TObject *Sender)
{
    frmManualDraw->ShowModal();
}
//---------------------------------------------------------------------------

