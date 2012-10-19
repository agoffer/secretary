//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "resultDM.h"
#include "dataSourceDM.h"
#include "competitorCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmResultDAO *dmResultDAO;

//������� ��������� ������ - ��������� �� �������
CallbackFunction CompetitorCategoryResultScrollCallback;

//---------------------------------------------------------------------------
__fastcall TdmResultDAO::TdmResultDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------


void TdmResultDAO::getResults(int competitorId, int categoryId, TResult &result){
AnsiString selectQueryResult =
"select \
       crossTime, shootScore \
 from Result res where res.competitorId = :competitorId";
AnsiString selectQueryCompetitorToCategory =
"select \
      fightWOKnifeRank, fightWOKnifeScore, \
      fightWKnifeRank, fightWKnifeScore, shootRank, commonRank \
 from CompetitorToCategory res where res.competitorId = :competitorId and \
 res.categoryId = :categoryId";

         //��������� �� �����, ������ �������
    result.setCrossTime("00:00.00");
    result.setShootRank(0);
    result.setShootScore(-1);
    result.setFightWOKnifeRank(0);
    result.setFightWOKnifeScore(-1);
    result.setFightWKnifeRank(0);
    result.setFightWKnifeScore(-1);
    result.setCommonRank(0);


    //������� ������ ��� ��������� �������� �� ����
    ibqResult->SQL->Clear();
    ibqResult->SQL->Add(selectQueryResult);
    ibqResult->ParamByName("competitorId")->AsInteger = competitorId;
    //�������� ������ �� ���� ������
    ibqResult->Open();
    ibqResult->First();
    if(ibqResult->RecordCount > 0){
        result.setCrossTime(ibqResult->FieldByName("crossTime")->AsString);
        result.setShootScore(ibqResult->FieldByName("shootScore")->AsInteger);
        }

    //������� ���������
    ibqResult->Close();

    if(categoryId > 0){
        //������� ������ ��� ��������� �������� �� ����
        ibqResult->SQL->Clear();
        ibqResult->SQL->Add(selectQueryCompetitorToCategory);
        ibqResult->ParamByName("competitorId")->AsInteger = competitorId;
        ibqResult->ParamByName("categoryId")->AsInteger = categoryId;
        //�������� ������ �� ���� ������
        ibqResult->Open();
        ibqResult->First();
        if(ibqResult->RecordCount > 0){
            result.setFightWOKnifeRank(ibqResult->FieldByName("fightWOKnifeRank")->AsInteger);
            result.setFightWOKnifeScore(ibqResult->FieldByName("fightWOKnifeScore")->AsInteger);
            result.setFightWKnifeRank(ibqResult->FieldByName("fightWKnifeRank")->AsInteger);
            result.setFightWKnifeScore(ibqResult->FieldByName("fightWKnifeScore")->AsInteger);
            result.setCommonRank(ibqResult->FieldByName("commonRank")->AsInteger);
            result.setShootRank(ibqResult->FieldByName("shootRank")->AsInteger);            
            }

        //������� ���������
        ibqResult->Close();
        }
}


void TdmResultDAO::setResults(int competitorId, int categoryId, TResult result){
AnsiString updateQueryResult =
"update Result set crossTime = :crossTime, \
 shootScore = :shootScore \
 where competitorId = :competitorId";
AnsiString insertQueryResult =
"insert into Result(competitorId, crossTime, shootScore) \
 values(:competitorId, :crossTime,  :shootScore)";
AnsiString searchQueryResult =
"select competitorId from Result where competitorId = :competitorId";

AnsiString updateQueryCompetitorToCategory =
"update CompetitorToCategory set fightWOKnifeRank = :fightWOKnifeRank, \
 shootRank = :shootRank,\
 fightWOKnifeScore = :fightWOKnifeScore, fightWKnifeRank = :fightWKnifeRank, \
 fightWKnifeScore = :fightWKnifeScore, commonRank = :commonRank\
 where competitorId = :competitorId and categoryId = :categoryId";
AnsiString insertQueryCompetitorToCategory =
"insert into CompetitorToCategory (competitorId, categoryId, fightWOKnifeRank, \
  fightWOKnifeScore, fightWKnifeRank, fightWKnifeScore, shootRank, commonRank) \
 values(:competitorId, :categoryId, :fightWOKnifeRank, :fightWOKnifeScore, \
 :fightWKnifeRank, :fightWKnifeScore, :shootRank, :commonRank)";

AnsiString searchQueryCompetitorToCategory =
"select competitorId from CompetitorToCategory where competitorId = :competitorId \
 and categoryId = :categoryId";

int recordCountCompetitorToCategory;
int recordCountResult;

    //����������, ���������� �� ������ ��� ���������
    ibqResult->SQL->Clear();
    //��������
    ibqResult->SQL->Add(searchQueryResult);
    ibqResult->ParamByName("competitorId")->AsInteger = competitorId;
    ibqResult->Open();
    recordCountResult = ibqResult->RecordCount;

    if(categoryId > 0){
        //����������, ���������� �� ������ ��� ��������� - ������� �� ���������
        ibqResult->SQL->Clear();
        //��������
        ibqResult->SQL->Add(searchQueryCompetitorToCategory);
        ibqResult->ParamByName("competitorId")->AsInteger = competitorId;
        ibqResult->ParamByName("categoryId")->AsInteger = categoryId;
        ibqResult->Open();
        recordCountCompetitorToCategory = ibqResult->RecordCount;
        }


    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    ibqResult->SQL->Clear();
    if(recordCountResult > 0){
        ibqResult->SQL->Add(updateQueryResult);
        }
    else{
        ibqResult->SQL->Add(insertQueryResult);
        }

    ibqResult->ParamByName("competitorId")->AsInteger = competitorId;
    ibqResult->ParamByName("crossTime")->AsString = result.getCrossTime();
    ibqResult->ParamByName("shootScore")->AsInteger = result.getShootScore();

    //��������� ������
    ibqResult->ExecSQL();

    if(categoryId > 0){

        ibqResult->SQL->Clear();
        if(recordCountCompetitorToCategory > 0){
            ibqResult->SQL->Add(updateQueryCompetitorToCategory);
            }
        else{
            ibqResult->SQL->Add(insertQueryCompetitorToCategory);
            }

        ibqResult->ParamByName("competitorId")->AsInteger = competitorId;
        ibqResult->ParamByName("categoryId")->AsInteger = categoryId;
        ibqResult->ParamByName("fightWOKnifeRank")->AsInteger = result.getFightWOKnifeRank();
        ibqResult->ParamByName("fightWOKnifeScore")->AsInteger = result.getFightWOKnifeScore();
        ibqResult->ParamByName("fightWKnifeRank")->AsInteger = result.getFightWKnifeRank();
        ibqResult->ParamByName("fightWKnifeScore")->AsInteger = result.getFightWKnifeScore();
        ibqResult->ParamByName("shootRank")->AsInteger = result.getShootRank();
        ibqResult->ParamByName("commonRank")->AsInteger = result.getCommonRank();

        //��������� ������
        ibqResult->ExecSQL();
        }

    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� � ����
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}


TList* TdmResultDAO::setCompetitorCategoryResultTable(int categoryId){
    if(ibqCompetitorToCategoryResultTable->Active){
        ibqCompetitorToCategoryResultTable->Close();
        }
    ibqCompetitorToCategoryResultTable->ParamByName("categoryId")->AsInteger = categoryId;
    ibqCompetitorToCategoryResultTable->Open();
    //�������� ������ ���������� 
    TList * result = new TList();
    result->Clear();
    while(!ibqCompetitorToCategoryResultTable->Eof){
         //������� ���������
         TCompetitor *competitor = new TCompetitor();
         //��������� ������ �� ���������
         competitor->setId(ibqCompetitorToCategoryResultTable->FieldByName("id")->AsInteger);
         competitor->result.setCommonRank(ibqCompetitorToCategoryResultTable->FieldByName("commonRank")->AsInteger);
         competitor->result.setCrossTime(ibqCompetitorToCategoryResultTable->FieldByName("crossTime")->AsString);
         competitor->result.setShootScore(ibqCompetitorToCategoryResultTable->FieldByName("shootScore")->AsInteger);
         competitor->result.setShootRank(ibqCompetitorToCategoryResultTable->FieldByName("shootRank")->AsInteger);
         competitor->result.setFightWOKnifeRank(ibqCompetitorToCategoryResultTable->FieldByName("fightWOKnifeRank")->AsInteger);
         competitor->result.setFightWKnifeRank(ibqCompetitorToCategoryResultTable->FieldByName("fightWKnifeRank")->AsInteger);

         //������� ��� ���������
         TPerson person;
         person.setName(ibqCompetitorToCategoryResultTable->FieldByName("name")->AsString);
         person.setSurname(ibqCompetitorToCategoryResultTable->FieldByName("surname")->AsString);
         TSkill skill;
         TRequest request;
         competitor->extend(person, skill ,request);
         //��������� ��������� � ������
         result->Add(competitor);
         //��������� � ���������� 
         ibqCompetitorToCategoryResultTable->Next();            
        }
    //���������� ������ ������� � ������ 
    ibqCompetitorToCategoryResultTable->First();
    //������� �������������� ������ 
    return result; 
}


void TdmResultDAO::setScrollCallback(CallbackFunction cbf){
    CompetitorCategoryResultScrollCallback = cbf;
}


void __fastcall TdmResultDAO::ibqCompetitorToCategoryResultTableAfterScroll(
      TDataSet *DataSet)
{
    //���� ���������� ������� ��������� ������, �������� ��
    if(CompetitorCategoryResultScrollCallback){
        CompetitorCategoryResultScrollCallback();
        }
}

int TdmResultDAO::getCurrentCompetitorIdFromTable(void){
    //���� ������� �������, �������� ������� ������
    if(ibqCompetitorToCategoryResultTable->State != dsInactive){
        return ibqCompetitorToCategoryResultTable->FieldByName("id")->AsInteger;

        }
    //������� ���������
    return 0;
}


void TdmResultDAO::setCurrentCompetitorByIdFromTable(int competitorId){
    //���� ������� �������, �������� ������� ������
    if(ibqCompetitorToCategoryResultTable->State != dsInactive){
        ibqCompetitorToCategoryResultTable->Locate("id", competitorId, TLocateOptions());
        }
}

void TdmResultDAO::getScoreRanking(map<int, int> &scoreRank, int competitionRank){
AnsiString selectQuery =
"select rank, score from ScoreRanking where competitionRankId = :competitionRankId";
    ibqResult->SQL->Clear();
    ibqResult->SQL->Add(selectQuery);
    ibqResult->ParamByName("competitionRankId")->AsInteger = competitionRank;
    //�������� ������ �� ���� ������
    ibqResult->Open();
    ibqResult->First();
    if(ibqResult->RecordCount > 0){
        for(int i=0; i < ibqResult->RecordCount; i++){
            //�������� ����� �����, �� ������������ 
            int rank = ibqResult->FieldByName("rank")->AsInteger;
            int score = ibqResult->FieldByName("score")->AsInteger;
            scoreRank[rank] = score;
            ibqResult->Next();  
            }
        }

    //������� ���������
    ibqResult->Close();
}


//---------------------------------------------------------------------------

