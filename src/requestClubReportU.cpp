//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "requestClubReportU.h"
#include "competitionRankCtrl.h"
#include "currentStateDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmRequestClubReport *frmRequestClubReport;
//---------------------------------------------------------------------------
__fastcall TfrmRequestClubReport::TfrmRequestClubReport(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestClubReport::qrdbtSurnamePrint(TObject *sender,
      AnsiString &Value)
{
    //�.�.�.
    AnsiString surname = Value;
    AnsiString name = dmReportDataSource->ibqRepRequestClubListDetail->FieldByName("name1")->AsString.SubString(1,1) + ".";
    AnsiString patronymic = dmReportDataSource->ibqRepRequestClubListDetail->FieldByName("patronymic")->AsString.SubString(1,1);
    patronymic += (patronymic.Length()>0)? "." : " ";
    Value = surname + " " + name + " " +patronymic;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestClubReport::qrRequestClubListBeforePrint(
      TCustomQuickRep *Sender, bool &PrintReport)
{
   //������������� �������� � ������ 
    counter = 1;

    //��������� ������ ������������
    TCompetitionRank competitionRank;
    competitionRank.getById(dmCurrentState->getCompetition().getCompetitionRankId());
    //���������� ������ ������������
    qrlCompetitionRank->Caption = competitionRank.getDescription();
    //���������� ���� ���������� ������������
    AnsiString competitionDate = dmCurrentState->getCompetition().getBeginDate().DateString() + " - " +
                                 dmCurrentState->getCompetition().getEndDate().DateString();
    qrlCompetitionDate->Caption = competitionDate;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestClubReport::qrdbtClubNamePrint(TObject *sender,
      AnsiString &Value)
{
    Value = IntToStr(counter++) + ". " + Value;     
}
//---------------------------------------------------------------------------
