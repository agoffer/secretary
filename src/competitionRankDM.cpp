//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "competitionRankDM.h"
#include "dataSourceDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmCompetitionRankDAO *dmCompetitionRankDAO;
//---------------------------------------------------------------------------
__fastcall TdmCompetitionRankDAO::TdmCompetitionRankDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}

/**
TODO: ���������, ��� ��� ������������
*/
void TdmCompetitionRankDAO::store(TCompetitionRank &obj){
AnsiString updateQuery =
"update CompetitionRank set description = :description, comments = :comments\
 where id = :id";
AnsiString insertQuery =
"insert into CompetitionRank(description, comments) values(:description, :comments)";
AnsiString searchIdQuery =
"select id from CompetitionRank where description=:description and comments=:comments";
    //������� ������ ��� ���������� ������� � ���� ������
    ibqCompetitionRank->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    if(obj.getId() > 0){
        //��������
        ibqCompetitionRank->SQL->Add(updateQuery);
        ibqCompetitionRank->ParamByName("id")->AsInteger = obj.getId();
    }
    else{
        //��������
        ibqCompetitionRank->SQL->Add(insertQuery);
    }
    ibqCompetitionRank->ParamByName("description")->AsString = obj.getDescription();
    ibqCompetitionRank->ParamByName("comments")->AsString = obj.getComments();
    //��������� ������
    ibqCompetitionRank->ExecSQL();
    //��������� ���������� ������
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //���� ���� ��������� ����� ������, ������ �� �������������
    if(!obj.getId()){
        //�������� �� ������� ��������� ����������� ������
        ibqCompetitionRank->SQL->Clear();
        ibqCompetitionRank->SQL->Add(searchIdQuery);
        ibqCompetitionRank->ParamByName("description")->AsString = obj.getDescription();
        ibqCompetitionRank->ParamByName("comments")->AsString = obj.getComments();
        ibqCompetitionRank->Open();
        obj.setId(ibqCompetitionRank->FieldByName("id")->AsInteger);
        ibqCompetitionRank->Close();
        }
}

/**
TODO: ���������, ��� ��� ������������
*/
TList*  TdmCompetitionRankDAO::getAll(void){
AnsiString selectQuery =
"select id, description, comments from CompetitionRank";
    //������� ������ ��� ��������� �������� �� ����
    ibqCompetitionRank->SQL->Clear();
    ibqCompetitionRank->SQL->Add(selectQuery);
    //�������� ������ �� ���� ������
    ibqCompetitionRank->Open();

    //������� ������� �� ���������� ���������� �� ���� ������
    TList* resultList = new TList();
    resultList->Clear();
    ibqCompetitionRank->First();
    for(int i = 0; i < ibqCompetitionRank->RecordCount; i++){
        TCompetitionRank * result = new TCompetitionRank();
        result->setId(ibqCompetitionRank->FieldByName("id")->AsInteger);
        result->setDescription(ibqCompetitionRank->FieldByName("description")->AsString);
        result->setComments(ibqCompetitionRank->FieldByName("comments")->AsString);
        //�������� ������ � ������
        resultList->Add(result);
        //�������� � ��������� ������
        ibqCompetitionRank->Next();
        }
    //������� ���������
    ibqCompetitionRank->Close();
    //������ �������������� ���������
    return resultList;
}


void TdmCompetitionRankDAO::getById(int id, TCompetitionRank &obj){
AnsiString selectQuery =
"select description, comments\
 from CompetitionRank where id = :id";
    //������� ������ ��� ��������� �������� �� ����
    ibqCompetitionRank->SQL->Clear();
    ibqCompetitionRank->SQL->Add(selectQuery);
    ibqCompetitionRank->ParamByName("id")->AsInteger = id;
    //�������� ������ �� ���� ������
    ibqCompetitionRank->Open();
    if(ibqCompetitionRank->RecordCount){
        obj.setId(id);
        obj.setDescription(ibqCompetitionRank->FieldByName("description")->AsString);
        obj.setComments(ibqCompetitionRank->FieldByName("comments")->AsString);
        }
    //������ �� ��������, ������� null
    else{
        //�������� ������
        setmem(&obj, sizeof(obj), 0);
        }
    ibqCompetitionRank->Close();
}


//---------------------------------------------------------------------------


/**
 * ����� �������� ������ � ������� ������� �������������, ������
 �������������� ���� ��������������. ������������� ������������ ���������.
*/
void __fastcall TdmCompetitionRankDAO::ibtCompetitionRankBeforeInsert(
      TDataSet *DataSet)
{
    // ����� ��������, ������� �������������� ��������������. ��� ��������� �������
    DataSet->FieldByName("ID")->Required = false;
}
//---------------------------------------------------------------------------

void __fastcall TdmCompetitionRankDAO::ibtCompetitionRankPostError(
      TDataSet *DataSet, EDatabaseError *E, TDataAction &Action)
{
    //���������� ��������� �� ������
    if (DataSet->FieldByName("DESCRIPTION")->Text.IsEmpty()) {
        E->Message = "������� ������������ ������ ���� ������!";
    }
}
//---------------------------------------------------------------------------




void __fastcall TdmCompetitionRankDAO::ibtScoreRankingBeforeInsert(
      TDataSet *DataSet)
{
    // ����� �������� ������, ������� �������������� � ���� ��������������� ������ ������������
    DataSet->FieldByName("COMPETITIONRANKID")->Required = false;
}
//---------------------------------------------------------------------------

void __fastcall TdmCompetitionRankDAO::ibtScoreRankingAfterInsert(
      TDataSet *DataSet)
{
    // ����� ����, ��� ������ ���������, ����������� �������������� ������ ������������
    DataSet->FieldByName("COMPETITIONRANKID")->AssignValue(ibtCompetitionRank->FieldByName("ID")->AsInteger);
}
//---------------------------------------------------------------------------

void __fastcall TdmCompetitionRankDAO::ibtScoreRankingBeforePost(
      TDataSet *DataSet)
{
    //���� ���������� ������ �� �������� ������, �������� �������
    if(DataSet->FieldByName("RANK")->AsInteger == NULL || DataSet->FieldByName("SCORE")->AsInteger == NULL) {
        DataSet->Cancel();
        DataSet->Edit();
    }
}
//---------------------------------------------------------------------------

void __fastcall TdmCompetitionRankDAO::ibtCompetitionRankAfterPost(
      TDataSet *DataSet)
{
    // ����� ������ ���������, ����� �� ������� ���������. ����������� ������� � ������� ����. ������
    if(ibtCompetitionRank->Transaction->Active) {
        ibtCompetitionRank->Transaction->Commit();
        ibtCompetitionRank->Open();
        ibtScoreRanking->Open();
        ibtCompetitionRank->Last();

    }
}
//---------------------------------------------------------------------------

