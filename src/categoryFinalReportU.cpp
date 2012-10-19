//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "categoryFinalReportU.h"
#include "reportDataSourceDM.h"
#include "currentStateDM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCategoryFinalReport *frmCategoryFinalReport;
//---------------------------------------------------------------------------
__fastcall TfrmCategoryFinalReport::TfrmCategoryFinalReport(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryFinalReport::qrdbtScorePrint(
      TObject *sender, AnsiString &Value)
{
    //Посчитать значение балов, за место и отобразить в протоколе
    Value = IntToStr(dmCurrentState->getScoreForRank(StrToInt(Value)));
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryFinalReport::qrdbtCommonScorePrint(
      TObject *sender, AnsiString &Value)
{
    int shootScore =
    dmCurrentState->getScoreForRank(
    dmReportDataSource->ibqRepCategoryFinalCompetitorDetail->FieldByName("shootRank")->AsInteger
                                                   );
    int fightWOKScore =
    dmCurrentState->getScoreForRank(
    dmReportDataSource->ibqRepCategoryFinalCompetitorDetail->FieldByName("fightWOKnifeRank")->AsInteger
                                                   );
    int fightWKScore =
    dmCurrentState->getScoreForRank(
    dmReportDataSource->ibqRepCategoryFinalCompetitorDetail->FieldByName("fightWKnifeRank")->AsInteger
                                                   );

    Value = IntToStr(shootScore + fightWOKScore + fightWKScore);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryFinalReport::qrdbtFemalePrint(TObject *sender,
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

void TfrmCategoryFinalReport::PreviewFinalProtocols(TList *categories){
    //Установить выбранные категории
    dmReportDataSource->setCategoriesFromList(categories);
    //Напечатать протоколы категорий
    qrCategory->Preview();
}




