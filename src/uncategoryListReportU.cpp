//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uncategoryListReportU.h"
#include "reportDataSourceDM.h"
#include "currentStateDM.h"
#include "competitionRankCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmUncategoryListReport *frmUncategoryListReport;


//---------------------------------------------------------------------------
__fastcall TfrmUncategoryListReport::TfrmUncategoryListReport(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmUncategoryListReport::qrdbtSurnamePrint(
      TObject *sender, AnsiString &Value)
{
    //Ф.И.О.
    AnsiString surname = Value;
    AnsiString name = dmReportDataSource->ibqRepUncategoryListDetail->FieldByName("name")->AsString.SubString(1,1) + ".";
    AnsiString patronymic = dmReportDataSource->ibqRepUncategoryListDetail->FieldByName("patronymic")->AsString.SubString(1,1);
    patronymic += (patronymic.Length()>0)? "." : " ";
    Value = IntToStr(counter++) + ". " + surname + " " + name + " " +patronymic;

    int competitorId = dmReportDataSource->ibqRepUncategoryListDetail->FieldByName("id")->AsInteger;
    qrlUncategoryFV->Caption =  getUncategoryList(competitorId);
    qrlExtendedFV->Caption =  getExtendedList(competitorId);
}
//---------------------------------------------------------------------------

AnsiString TfrmUncategoryListReport::getExtendedList(int competitorId){
AnsiString selectExtendedQuery =
"select fv.code from fightversion fv, extendedfightversion extfv \
 where fv.id = extfv.fightversionid \
 and extfv.competitorid = :competitorid";
    // сформировать список боевых версий, которые расширяют заявку
    dmReportDataSource->ibqRepExtendedFV->SQL->Clear();
    dmReportDataSource->ibqRepExtendedFV->SQL->Add(selectExtendedQuery);
    dmReportDataSource->ibqRepExtendedFV->ParamByName("competitorId")->AsInteger = competitorId;
    dmReportDataSource->ibqRepExtendedFV->Open();
    //Инициализировать список
    dmReportDataSource->ibqRepExtendedFV->Last();
    dmReportDataSource->ibqRepExtendedFV->First();
    //Сформированный список
    AnsiString extendedFVlist = "";
    for(int i = 0 ; i < (dmReportDataSource->ibqRepExtendedFV->RecordCount - 1); i++){
        extendedFVlist += dmReportDataSource->ibqRepExtendedFV->FieldByName("code")->AsString + ", ";
        //К следующей записи
        dmReportDataSource->ibqRepExtendedFV->Next();
        }
    //Добавляем к списку последнюю запись
    if(dmReportDataSource->ibqRepExtendedFV->RecordCount > 0){
        extendedFVlist += dmReportDataSource->ibqRepExtendedFV->FieldByName("code")->AsString;
        }

    return extendedFVlist;
}

AnsiString TfrmUncategoryListReport::getUncategoryList(int competitorId){
AnsiString selectUncategoryQuery =
"select fv.code from fightversion fv, competitortofightversion fvct \
 where fv.id = fvct.fightversionid and fvct.destributed ='F' \
 and fvct.competitorid = :competitorid";
    // сформировать список нераспределенных боевых версий
    dmReportDataSource->ibqRepUncategoryFV->SQL->Clear();
    dmReportDataSource->ibqRepUncategoryFV->SQL->Add(selectUncategoryQuery);
    dmReportDataSource->ibqRepUncategoryFV->ParamByName("competitorId")->AsInteger = competitorId;
    dmReportDataSource->ibqRepUncategoryFV->Open();
    //Инициализировать список
    dmReportDataSource->ibqRepUncategoryFV->Last();
    dmReportDataSource->ibqRepUncategoryFV->First();
    //Сформированный список
    AnsiString uncategoryFVlist = "";
    for(int i = 0 ; i < (dmReportDataSource->ibqRepUncategoryFV->RecordCount - 1); i++){
        uncategoryFVlist += dmReportDataSource->ibqRepUncategoryFV->FieldByName("code")->AsString + ", ";
        //К следующей записи
        dmReportDataSource->ibqRepUncategoryFV->Next();
        }
    //Добавляем к списку последнюю запись
    if(dmReportDataSource->ibqRepUncategoryFV->RecordCount > 0){
        uncategoryFVlist += dmReportDataSource->ibqRepUncategoryFV->FieldByName("code")->AsString;
        }

    return uncategoryFVlist;
}

void __fastcall TfrmUncategoryListReport::qrUncategoryListBeforePrint(
      TCustomQuickRep *Sender, bool &PrintReport)
{
    //Инициализация счетчика в списке 
    counter = 1;

    //Устновить статус соревнований
    TCompetitionRank competitionRank;
    competitionRank.getById(dmCurrentState->getCompetition().getCompetitionRankId());
    //Установить статус соревнований
    qrlCompetitionRank->Caption = competitionRank.getDescription();
    //Установить дату проведения соревнований
    AnsiString competitionDate = dmCurrentState->getCompetition().getBeginDate().DateString() + " - " +
                                 dmCurrentState->getCompetition().getEndDate().DateString();
    qrlCompetitionDate->Caption = competitionDate;
}
//---------------------------------------------------------------------------


