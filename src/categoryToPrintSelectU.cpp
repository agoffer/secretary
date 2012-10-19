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
    pairsOrderTitle = "����� ��������� ��� ������ - \"������ ���\"";
    protocolTitle = "����� ��������� ��� ������ - \"����������\"";;
    fightTreeTitle = "����� ��������� ��� ������ - \"�������� ����\"";;
    finalProtocolTitle = "����� ��������� ��� ������ - \"��������� � ������������\""; 

}

void TfrmCategoryToPrintSelect::createNotPrintedListBox(TList *categories, bool isIndexedFill){
    lbNotPrintedCategories->Clear();
    if(isIndexedFill){
        categoryOrder.clear();
        }
    for(int i=0; i < categories->Count; i++){
        //������� ���������
        TCategory * curCategory = (TCategory*)categories->Items[i];
        //���� � ��������� ���� ��������� ��������� � ������
        if(!curCategory->getCompetitorsAmount()) continue;
        //���������� �������� ��� ���������
        AnsiString asCategory = AnsiString().sprintf("%02d", curCategory->getAvailCategory().getStartAge());
        asCategory += " - " + AnsiString().sprintf("%02d", curCategory->getAvailCategory().getEndAge());

        asCategory += " ��� ";

        //��������� ��� , ���� ��� 500 ��� ���� ��������������� �����
        double startWeight = curCategory->getAvailCategory().getStartWeight();
        double endWeight = curCategory->getAvailCategory().getEndWeight();

        if(startWeight > 1){
            asCategory += " / " + FloatToStrF(startWeight,
                                            ffFixed, 1, 1);
            }
        else{
            asCategory += " / �� ";
            }
        if (endWeight > 450){
            asCategory += " �� � ����";
            }
        else{
            asCategory += ((startWeight > 1)? AnsiString(" - ") : AnsiString("")) +
            FloatToStrF(endWeight, ffFixed, 1, 1);
            asCategory += " ��. ";
            }

        //�������� ������ ������
        AnsiString asFightVersion = curCategory->getFightVersion().getCode().Trim();
        //���������� ������ �������� ��� ���������
        asCategory = asFightVersion + "  " + asCategory;
        if(curCategory->getAvailCategory().getFemale()){
            //���� ��������� �������, ������� ���
            asCategory = "(�)  " + asCategory;
            }
        lbNotPrintedCategories->AddItem(asCategory, (TObject*)curCategory);
        if(isIndexedFill){
            //��������� ������
            categoryOrder[asCategory] = curCategory;
            }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::FormShow(TObject *Sender)
{
    // ���������� ������ ���������, ������� ����� ����������� //
    TList *category = dmCurrentState->getCategoryList();
    category->Sort(compareCategories);
    lbPrintedCategories->Clear();
    createNotPrintedListBox(category, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::bbtnCategoryToPrintClick(TObject *Sender)
{
    //��������� ��������� �� ���������������� � �������������
    lbNotPrintedCategories->MoveSelection(lbPrintedCategories);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::bbtnCategoryToNotPrintedClick(TObject *Sender)
{
    //������ ��������� �� �������������� ������
    lbPrintedCategories->MoveSelection(lbNotPrintedCategories);
    //������������� � ����������� ������ ������������ ���������
    TList *toSort = new TList();
    toSort->Clear();
    //��������� ������ ���������  
    for(int i=0; i < lbNotPrintedCategories->Count; i++){
        toSort->Add(categoryOrder[lbNotPrintedCategories->Items->Strings[i]]);
        }
    //��������� ������ ��������� 
    toSort->Sort(compareCategories);
    //����������� ������ ������������ ���������
    createNotPrintedListBox(toSort, false);   //������ �� �������
    delete (TList*)toSort;       
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::bbtnCategoryUpClick(TObject *Sender)
{
    //�������� ���������� ���� �����
}
//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::bbtnCategoryDownClick(TObject *Sender)
{
    //�������� ���� ���������� ����
}



TList * TfrmCategoryToPrintSelect::toTList(map<AnsiString, TCategory*> co, TListBox *lb){
    //����� ������ � ��������� ��� ����������
    TList* list = new TList();
    list->Clear();
    for(int c=0; c < lb->Count; c++){
        //������ ���������, ������� ����� ��������
        TCategory *curCategory = co[lb->Items->Strings[c]];
        //��������� ������� ���������� � ���������, ���� ������ ���� �� ��������
        if(curCategory->getCompetitorsAmount()< 2){
            continue;
            }
        list->Add(curCategory);
        }
    //������� ���������� ������ 
    return list;     
}


//---------------------------------------------------------------------------
void __fastcall TfrmCategoryToPrintSelect::bbtnPrintClick(TObject *Sender)
{
//�������� ������ ���������
TList *listToPrint = toTList(categoryOrder, lbPrintedCategories);
    dmReportDataSource->finalReport = false;
    if(listToPrint->Count){
        switch(reportType){
            //�������� ������ ���
            case rtPAIRSORDER :
                frmCompetitorPairsReport->PreviewPairsOrder(categoryOrder, lbPrintedCategories);
                break;
            //�������� �������
            case rtFIGHTTREE :
                frmCategoryTreeReport->PreviewFightTrees(listToPrint);
                break;
            //�������� ���������
            case rtPROTOCOL :
                frmCategoryReport->PreviewProtocols(listToPrint);
                break;
            //�������� ���������
            case rtFINALPROTOCOL :
                dmReportDataSource->finalReport = true;
                frmCategoryFinalReport->PreviewFinalProtocols(listToPrint);
            }
        }
    else{
        MessageDlg("� ��������� ����������, ���������� ���������� ������ ����!",
        mtWarning, TMsgDlgButtons() << mbOK, 0);
        }
    delete (TList*)listToPrint; 
}
//---------------------------------------------------------------------------



void TfrmCategoryToPrintSelect::PrintPairsOrder(void){
    //�������� ������ ���
    reportType = rtPAIRSORDER;
    //��������� ��������� ����
    Caption = pairsOrderTitle;
    ShowModal(); 
}

void TfrmCategoryToPrintSelect::PrintProtocols(void){
    //�������� ���������
    reportType = rtPROTOCOL;
    //��������� ��������� ����
    Caption = protocolTitle;
    ShowModal();
}

void TfrmCategoryToPrintSelect::PrintFinalProtocols(void){
    //�������� �������������� ���������
    reportType = rtFINALPROTOCOL;
    //��������� ��������� ����
    Caption = finalProtocolTitle;
    ShowModal();
}

void TfrmCategoryToPrintSelect::PrintFightTrees(void){
    //�������� �������
    reportType = rtFIGHTTREE;
    //��������� ��������� ����
    Caption = fightTreeTitle;
    ShowModal();
}

