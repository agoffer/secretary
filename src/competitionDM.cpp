//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "competitionDM.h"
#include "dataSourceDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmCompetitionDAO *dmCompetitionDAO;
//---------------------------------------------------------------------------
__fastcall TdmCompetitionDAO::TdmCompetitionDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------

void TdmCompetitionDAO::initCompetitionTable(void){
    //���� ������� �������, ������� �� ��������������
    if(ibqCompetitionAll->Active){
        ibqCompetitionAll->Close();
        }
    ibqCompetitionAll->SQL->Clear();
    ibqCompetitionAll->SQL->Add("select * from Competition order by begindate desc");
}


void TdmCompetitionDAO::store(TCompetition &obj){
AnsiString updateQuery =
"update Competition set beginDate = :beginDate, endDate = :endDate,\
 competitionRankId = :competitionRankId, comments = :comments\
 where id = :id";
AnsiString insertQuery =
"insert into Competition(beginDate, endDate, competitionRankId, comments)\
 values(:beginDate, :endDate, :competitionRankId,:comments)";

AnsiString searchIdQuery = "select id from Competition where \
  beginDate=:beginDate and endDate=:endDate and competitionRankId=:competitionRankId \
  and comments=:comments";
    //������� ������ �� ���������� ������� � ���� ������
    ibqCompetition->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    if(obj.getId() > 0){
        //��������
        ibqCompetition->SQL->Add(updateQuery);
        ibqCompetition->ParamByName("id")->AsInteger = obj.getId();
    }
    else{
        //��������
        ibqCompetition->SQL->Add(insertQuery);
    }
    ibqCompetition->ParamByName("beginDate")->AsDate = obj.getBeginDate();
    ibqCompetition->ParamByName("endDate")->AsDate = obj.getEndDate();
    ibqCompetition->ParamByName("competitionRankId")->AsInteger = obj.getCompetitionRankId();
    ibqCompetition->ParamByName("comments")->AsString = obj.getComments();
    //��������� ������
    ibqCompetition->ExecSQL();
    //��������� ���������� ������
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //���� ���� ��������� ����� ������, ������ �� �������������
    if(!obj.getId()){
        ibqCompetition->SQL->Clear();
        ibqCompetition->SQL->Add(searchIdQuery);
        //�������� �� ������� ��������� ����������� ������
        ibqCompetition->ParamByName("beginDate")->AsDate = obj.getBeginDate();
        ibqCompetition->ParamByName("endDate")->AsDate = obj.getEndDate();
        ibqCompetition->ParamByName("competitionRankId")->AsInteger = obj.getCompetitionRankId();
        ibqCompetition->ParamByName("comments")->AsString = obj.getComments();
        ibqCompetition->Open();
        obj.setId(ibqCompetition->FieldByName("id")->AsInteger);
        ibqCompetition->Close();
        }
}

TList * TdmCompetitionDAO::getAll(void){
AnsiString selectQuery =
"select id, beginDate, endDate, competitionRankId,comments\
 from Competition order by beginDate desc";
    //������� ������ ��� ��������� �������� �� ����
    ibqCompetition->SQL->Clear();
    ibqCompetition->SQL->Add(selectQuery);
    //�������� ������ �� ���� ������
    ibqCompetition->Open();
    //������� ������� �� ���������� ���������� �� ���� ������
    TList* resultList = new TList();
    resultList->Clear();
    ibqCompetition->First();
    for(int i = 0; i < ibqCompetition->RecordCount; i++){
        //������� ����� �������� "������������"
        TCompetition *result = new TCompetition();
        result->setId(ibqCompetition->FieldByName("id")->AsInteger);
        result->setBeginDate(ibqCompetition->FieldByName("beginDate")->AsDateTime);
        result->setEndDate(ibqCompetition->FieldByName("endDate")->AsDateTime);
        result->setComments(ibqCompetition->FieldByName("comments")->AsString);
        //��������� �� � ������
        resultList->Add(result);
        //�������� � ��������� ������
        ibqCompetition->Next();
        }
    //��������� ��������� ����� ������
    ibqCompetition->Close();
    //������ �������������� ���������
    return resultList;
}

void TdmCompetitionDAO::getById(int id, TCompetition &obj){
AnsiString selectQuery =
"select beginDate, endDate, competitionRankId,comments\
 from Competition where id = :id";
    //������� ������ ��� ��������� �������� �� ����
    ibqCompetition->SQL->Clear();
    ibqCompetition->SQL->Add(selectQuery);
    ibqCompetition->ParamByName("id")->AsInteger = id;
    //�������� ������ �� ���� ������
    ibqCompetition->Open();
    if(ibqCompetition->RecordCount){
        obj.setId(id);
        obj.setBeginDate(ibqCompetition->FieldByName("beginDate")->AsDateTime);
        obj.setEndDate(ibqCompetition->FieldByName("endDate")->AsDateTime);
        obj.setComments(ibqCompetition->FieldByName("comments")->AsString);
        }
    //������ �� ��������, ������� null
    else{
        //�������� ������
        setmem(&obj, sizeof(obj), 0);
        }
    //��������� ���������
    ibqCompetition->Close();
}


void TdmCompetitionDAO::getMinMaxBeginDate(TDateTime &minBeginDate, TDateTime &maxBeginDate){
//������ �� ��������� ���
AnsiString selectQuery = "select max(beginDate), min(beginDate) from competition";
    //������� ������
    ibqCompetition->SQL->Clear();
    ibqCompetition->SQL->Add(selectQuery);
    //��������� ������
    ibqCompetition->Open();

    minBeginDate = ibqCompetition->FieldByName("min")->AsDateTime;
    maxBeginDate = ibqCompetition->FieldByName("max")->AsDateTime;

    //��������� ���������
    ibqCompetition->Close();
}


void TdmCompetitionDAO::selectRangeExtendedCompetitions(TDateTime begin, TDateTime end){
//������ �� ��������� ������������
AnsiString selectQuery=
"select  Competition.id CID, Competition.beginDate, Competition.endDate,\
 Competition.comments CCOMMENTS, Competition.CompetitionRankId, CompetitionRank.description, \
 CompetitionRank.id CRID, CompetitionRank.comments CRCOMMENTS \
 from Competition, CompetitionRank \
 where CompetitionRank.id = Competition.competitionRankId \
 and Competition.beginDate >= :beginDate and Competition.beginDate <= :endDate order by beginDate desc";

    //������� ������ �� ��������� �������
    if(ibqExtendedCompetitionAll->Active)
        ibqExtendedCompetitionAll->Close();

    ibqExtendedCompetitionAll->SQL->Clear();
    ibqExtendedCompetitionAll->SQL->Add(selectQuery);

    //���������� �������� ���
    ibqExtendedCompetitionAll->ParamByName("beginDate")->AsDateTime = begin;
    ibqExtendedCompetitionAll->ParamByName("endDate")->AsDateTime = end;

    ibqExtendedCompetitionAll->Open();
}


TCompetition TdmCompetitionDAO::getExtendedCurrent(void){
//������������ ������
TCompetition result;
    result.setId(0);    //���������� ������ �� ��������
    //���� ������� �������, �������� ������� ������
    if(ibqExtendedCompetitionAll->State != dsInactive){
        result.setId(ibqExtendedCompetitionAll->FieldByName("CID")->AsInteger);
        result.setBeginDate(ibqExtendedCompetitionAll->FieldByName("beginDate")->AsDateTime);
        result.setEndDate(ibqExtendedCompetitionAll->FieldByName("endDate")->AsDateTime);
        result.setCompetitionRankId(ibqExtendedCompetitionAll->FieldByName("competitionRankId")->AsInteger);
        result.setComments(ibqExtendedCompetitionAll->FieldByName("CCOMMENTS")->AsString);
        TCompetitionRank crresult;
        crresult.setId(ibqExtendedCompetitionAll->FieldByName("CRID")->AsInteger);
        crresult.setDescription(ibqExtendedCompetitionAll->FieldByName("description")->AsString);
        crresult.setComments(ibqExtendedCompetitionAll->FieldByName("CRCOMMENTS")->AsString);
        //���������
        result.extend(crresult);
        }
    //������� ���������
    return result;
}

/**
 * ������� �������, ��������� ������.
 */
void TdmCompetitionDAO::removeCurrent() {
    //���� ������� �������, �������� ������� ������
    if(ibqExtendedCompetitionAll->State != dsInactive){
        remove(ibqExtendedCompetitionAll->FieldByName("CID")->AsInteger);
    }
}

void TdmCompetitionDAO::remove(int id) {
 AnsiString deleteQuery = "delete from COMPETITION where ID=:id";
    //������� ������ ��� �������� ������� �� ��
    ibqCompetition->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active) {
        dmDataSource->ibtrSecretaryDB->StartTransaction();
    }
    ibqCompetition->SQL->Add(deleteQuery);
    ibqCompetition->ParamByName("id")->AsInteger = id;
     //��������� ������
    ibqCompetition->ExecSQL();
    //��������� ���������� ������
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
    }
}
