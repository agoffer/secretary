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
    //Установим выборку категорий
//    dmReportDataSource->setCategoriesToPrintByCompetition(dmCurrentState->getCompetition().getId());
    dmReportDataSource->setCategoriesFromList(categories);
    //Напечатать протоколы категорий
    qrCategory->Preview();
}







void __fastcall TfrmCategoryReport::qrdbtFemalePrint(TObject *sender,
      AnsiString &Value)
{
    if(Value=="T"){
        Value  = "Ж";
        }
    else{
        Value = "";
        }
}
//---------------------------------------------------------------------------



void __fastcall TfrmCategoryReport::qrdbtCategoryStartWeightPrint(
      TObject *sender, AnsiString &Value)
{
    //Если печатается значение 0 - заменить его словом ДО
    if(StrToInt(Value) < 1){
        Value = "до";
        }    
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryReport::qrdbtCategoryEndWeightPrint(
      TObject *sender, AnsiString &Value)
{
    //Если указан большой вес, заменим на "и выше"
    if(StrToInt(Value) > 450){
        Value = "и выше"; 
        }    
}
//---------------------------------------------------------------------------

