//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "categoryReportU.h"
#include "reportDataSourceDM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCategoryReport *frmCategoryReport;
//---------------------------------------------------------------------------
__fastcall TfrmCategoryReport::TfrmCategoryReport(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void TfrmCategoryReport::PreviewProtocols(TList *categories){
    //��������� ������� ���������
//    dmReportDataSource->setCategoriesToPrintByCompetition(dmCurrentState->getCompetition().getId());
    dmReportDataSource->setCategoriesFromList(categories);
    //���������� ��������� ���������
    qrCategory->Preview();
}







void __fastcall TfrmCategoryReport::qrdbtFemalePrint(TObject *sender,
      AnsiString &Value)
{
    if(Value=="T"){
        Value  = "�";
        }
    else{
        Value = "";
        }
}
//---------------------------------------------------------------------------



void __fastcall TfrmCategoryReport::qrdbtCategoryStartWeightPrint(
      TObject *sender, AnsiString &Value)
{
    //���� ���������� �������� 0 - �������� ��� ������ ��
    if(StrToInt(Value) < 1){
        Value = "��";
        }    
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryReport::qrdbtCategoryEndWeightPrint(
      TObject *sender, AnsiString &Value)
{
    //���� ������ ������� ���, ������� �� "� ����"
    if(StrToInt(Value) > 450){
        Value = "� ����"; 
        }    
}
//---------------------------------------------------------------------------

