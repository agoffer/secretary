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

void __fastcall TfrmCategoryFinalReport::qrdbtShootingScorePrint(
      TObject *sender, AnsiString &Value)
{
    //ѕосчитать значение балов, за место и отобразить в протоколе
    Value = IntToStr(dmCurrentState->getScoreForRank(StrToInt(Value), 0));
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryFinalReport::qrdbtFightingScorePrint(
      TObject *sender, AnsiString &Value)
{
    //ѕосчитать значение балов, за место и отобразить в протоколе
    Value = IntToStr(dmCurrentState->getScoreForRank(StrToInt(Value), 1));
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryFinalReport::qrdbtCommonScorePrint(
      TObject *sender, AnsiString &Value)
{
    int shootScore =
    dmCurrentState->getScoreForRank(
    dmReportDataSource->ibqRepCategoryFinalCompetitorDetail->FieldByName("shootRank")->AsInteger
                                                   , 0);
    int fightWOKScore =
    dmCurrentState->getScoreForRank(
    dmReportDataSource->ibqRepCategoryFinalCompetitorDetail->FieldByName("fightWOKnifeRank")->AsInteger
                                                   , 1);

    Value = IntToStr(shootScore + fightWOKScore);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryFinalReport::qrdbtFemalePrint(TObject *sender,
      AnsiString &Value)
{
    if(Value=="T"){
        Value  = "∆";
        }
    else{
        Value = "";
        }
}
//---------------------------------------------------------------------------

void TfrmCategoryFinalReport::PreviewFinalProtocols(TList *categories){
    //”становить выбранные категории
    dmReportDataSource->setCategoriesFromList(categories);
    //Ќапечатать протоколы категорий
    qrCategory->Preview();
}





