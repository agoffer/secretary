//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "categoryDM.h"
#include "availCategoryCtrl.h"
#include "dataSourceDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmCategoryDAO *dmCategoryDAO;
//---------------------------------------------------------------------------
__fastcall TdmCategoryDAO::TdmCategoryDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------

void TdmCategoryDAO::initCategoryTable(void){
    if(ibqCategoryAll->Active){
        ibqCategoryAll->Close(); 
        }
    ibqCategoryAll->SQL->Clear();
    ibqCategoryAll->SQL->Add("select * from Category");
}


void TdmCategoryDAO::getById(int id, TCategory &obj){
AnsiString selectQuery =
"select id, availableCategoryId, fightVersionId, competitionId \
 from Category where id = :id";
    //������� ������ ��� ��������� �������� �� ����
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    ibqCategory->ParamByName("id")->AsInteger = id;
    //�������� ������ �� ���� ������
    ibqCategory->Open();
    if(ibqCategory->RecordCount){
        obj.setId(id);
        obj.setAvailCategoryId(ibqCategory->FieldByName("availableCategoryId")->AsInteger);
        obj.setFightVersionId(ibqCategory->FieldByName("fightVersionId")->AsInteger);
        obj.setCompetitionId(ibqCategory->FieldByName("competitionId")->AsInteger);
        }
    //������ �� ��������, ������� null
    else{
        //�������� ������
        setmem(&obj, sizeof(obj), 0);
        }
    //������� ���������
    ibqCategory->Close(); 
}



void TdmCategoryDAO::store(TCategory &obj){
AnsiString updateQuery =
"update Category set availableCategoryId = :availableCategoryId,\
 fightVersionId = :fightVersionId, competitionId = :competitionId \
 where id = :id";
AnsiString insertQuery =
"insert into Category(availableCategoryId, fightVersionId, competitionId)\
 values(:availableCategoryId, :fightVersionId, :competitionId)";
AnsiString searchIdQuery =
"select id from Category where availableCategoryId=:availableCategoryId and \
 fightVersionId=:fightVersionId and competitionId=:competitionId";
    //������� ������ ��� ���������� ������� � ���� ������
    ibqCategory->SQL->Clear();
    if(obj.getId() > 0){
        //��������
        ibqCategory->SQL->Add(updateQuery);
        ibqCategory->ParamByName("id")->AsInteger = obj.getId();
        }
    else{
        //��������
        ibqCategory->SQL->Add(insertQuery);
        }
    ibqCategory->ParamByName("availableCategoryId")->AsInteger = obj.getAvailCategoryId();
    ibqCategory->ParamByName("fightVersionId")->AsInteger = obj.getFightVersionId();
    ibqCategory->ParamByName("competitionId")->AsInteger = obj.getCompetitionId();
    //��������� ������
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    ibqCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� ���������� ������
        dmDataSource->ibtrSecretaryDB->Commit();
        }    
    //���� ���� ��������� ����� ������, ������ �� �������������
    if(!obj.getId()){
        //�������� �� ������� ��������� ����������� ������
        ibqCategory->SQL->Clear();
        ibqCategory->SQL->Add(searchIdQuery);                 
        ibqCategory->ParamByName("availableCategoryId")->AsInteger = obj.getAvailCategoryId();
        ibqCategory->ParamByName("fightVersionId")->AsInteger = obj.getFightVersionId();
        ibqCategory->ParamByName("competitionId")->AsInteger = obj.getCompetitionId();
        ibqCategory->Open();
        obj.setId(ibqCategory->FieldByName("id")->AsInteger);
        ibqCategory->Close();        
        }

}


void TdmCategoryDAO::erase(TCategory &obj){
AnsiString deleteQuery =
"delete from Category where id = :id";
    //������� ������ ��� ���������� ������� � ���� ������
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(deleteQuery);
    ibqCategory->ParamByName("id")->AsInteger = obj.getId();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //��������� ������
    ibqCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� ���������� ������
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}


void TdmCategoryDAO::deleteCategoriesByCompId(int compid){
AnsiString deleteQuery =
"delete from Category where competitionId = :competitionId";
    //������� ������ ��� ���������� ������� � ���� ������
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(deleteQuery);
    ibqCategory->ParamByName("competitionId")->AsInteger = compid;
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //��������� ������
    ibqCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� ���������� ������
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}


TCategory TdmCategoryDAO::getCurrent(void){
//������������ ������
TCategory result;
    result.setId(0);    //���������� ������ �� ��������
    //���� ������� �������, �������� ������� ������
    if(ibqCategoryAll->State != dsInactive){
        result.setId(ibqCategoryAll->FieldByName("id")->AsInteger);
        result.setAvailCategoryId(ibqCategoryAll->FieldByName("availableCategoryId")->AsInteger);
        result.setFightVersionId(ibqCategoryAll->FieldByName("fightVersionId")->AsInteger);
        result.setCompetitionId(ibqCategoryAll->FieldByName("competitionId")->AsInteger);
        }
    //������� ���������
    return result;
}

void TdmCategoryDAO::makeCurrent(TCategory obj){
int res;
    //���� ������� �������
    if(ibqCategoryAll->State != dsInactive){
        //���� ������� �� ������ ������
        if(obj.getId() > 0){
            ibqCategoryAll->Locate("id", obj.getId(), TLocateOptions());
            }
        }
}


TList * TdmCategoryDAO::getByCompetitionId(int competitionId){
AnsiString selectQuery =
"select id, availableCategoryId, fightVersionId \
 from Category where competitionId=:competitionId";
    //������� ������ ��� ��������� �������� �� ����
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    //������� ������������
    ibqCategory->ParamByName("competitionId")->AsInteger = competitionId;
    //�������� ������ �� ���� ������
    ibqCategory->Open();
    //������� ������� �� ���������� ���������� �� ���� ������
    TList* resultList = new TList();
    resultList->Clear();
    ibqCategory->First();
    for(int i = 0; i < ibqCategory->RecordCount; i++){
        TCategory *result = new TCategory();
        result->setId(ibqCategory->FieldByName("id")->AsInteger);
        result->setAvailCategoryId(ibqCategory->FieldByName("availableCategoryId")->AsInteger);
        result->setFightVersionId(ibqCategory->FieldByName("fightVersionId")->AsInteger);
        result->setCompetitionId(competitionId);
        //�������� � ������
        resultList->Add(result);
        //�������� � ��������� ������
        ibqCategory->Next();
        }
    //������� ���������
    ibqCategory->Close();
    //������ �������������� ���������
    return resultList;
}


TList * TdmCategoryDAO::getExtendedByCompetitionId(int competitionId){
AnsiString selectQuery =
"select \
       cat.id, \
       avcat.id ac_id, \
       avcat.startAge ac_sa, \
       avcat.endAge ac_ea, \
       avcat.startWeight ac_sw, \
       avcat.endWeight ac_ew, \
       avcat.female ac_fem, \
       avcat.comments ac_com, \
       fver.id fv_id, \
       fver.code fv_code, \
       fver.description fv_des, \
       fver.comments fv_com , \
       comp.id c_id, \
       comp.beginDate c_bd, \
       comp.endDate c_ed, \
       comp.competitionRankId c_crid, \
       comp.comments c_com \
       from Category cat, AvailableCategory avcat, FightVersion fver, Competition comp where \
       avcat.id = cat.availableCategoryId and fver.id = cat.fightVersionId \
       and comp.id = cat.competitionId and cat.competitionId = :competitionId";
    //������� ������ ��� ��������� �������� �� ����
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    //������� ������������
    ibqCategory->ParamByName("competitionId")->AsInteger = competitionId;
    //�������� ������ �� ���� ������
    ibqCategory->Open();

    //������� ������� �� ���������� ���������� �� ���� ������
    TList* resultList = new TList();
    resultList->Clear(); 
    ibqCategory->First();
    //������� ����������� ����
    TAvailCategory availCategory;
    TFightVersion fightVersion;
    TCompetition competition;
    for(int i = 0; i < ibqCategory->RecordCount; i++){
        //��������� ��������� (��������� ���������)

        availCategory.setId(ibqCategory->FieldByName("ac_id")->AsInteger);
        availCategory.setStartAge(ibqCategory->FieldByName("ac_sa")->AsInteger);
        availCategory.setEndAge(ibqCategory->FieldByName("ac_ea")->AsInteger);
        availCategory.setStartWeight(ibqCategory->FieldByName("ac_sw")->AsFloat);
        availCategory.setEndWeight(ibqCategory->FieldByName("ac_ew")->AsFloat);
        availCategory.setFemale(ibqCategory->FieldByName("ac_fem")->AsString =='T'?true:false);
        availCategory.setComments(ibqCategory->FieldByName("ac_com")->AsString);

        fightVersion.setId(ibqCategory->FieldByName("fv_id")->AsInteger);
        fightVersion.setCode(ibqCategory->FieldByName("fv_code")->AsString);
        fightVersion.setDescription(ibqCategory->FieldByName("fv_des")->AsString);
        fightVersion.setComments(ibqCategory->FieldByName("fv_com")->AsString);

        competition.setId(ibqCategory->FieldByName("id")->AsInteger);
        competition.setBeginDate(ibqCategory->FieldByName("c_bd")->AsDateTime);
        competition.setEndDate(ibqCategory->FieldByName("c_ed")->AsDateTime);
        competition.setCompetitionRankId(ibqCategory->FieldByName("c_crid")->AsInteger);
        competition.setComments(ibqCategory->FieldByName("c_com")->AsString);

        TCategory * result = new TCategory();

        result->setAvailCategoryId(ibqCategory->FieldByName("ac_id")->AsInteger);
        result->setFightVersionId(ibqCategory->FieldByName("fv_id")->AsInteger);
        result->setCompetitionId(competitionId);
        result->setId(ibqCategory->FieldByName("id")->AsInteger);
        //��������� �������������� ����
        result->extend(availCategory, fightVersion, competition);
        //�������� � ������
        resultList->Add(result);

        //�������� � ��������� ������
        ibqCategory->Next();
        }
    //������� ���������
    ibqCategory->Close();
    //������ �������������� ���������
    return resultList;
}


TList * TdmCategoryDAO::getExtendedByCompetitionIdSurname(int competitionId, AnsiString surname){
AnsiString selectQuery =
"select \
       cat.id, \
       avcat.id ac_id, \
       avcat.startAge ac_sa, \
       avcat.endAge ac_ea, \
       avcat.startWeight ac_sw, \
       avcat.endWeight ac_ew, \
       avcat.female ac_fem, \
       avcat.comments ac_com, \
       fver.id fv_id, \
       fver.code fv_code, \
       fver.description fv_des, \
       fver.comments fv_com , \
       comp.id c_id, \
       comp.beginDate c_bd, \
       comp.endDate c_ed, \
       comp.competitionRankId c_crid, \
       comp.comments c_com \
       from \
       Competitor comptr \
       left join CompetitorToCategory ctc on ctc.competitorId = comptr.id \
       left join Category cat on cat.id = ctc.categoryId \
       left join AvailableCategory avcat on avcat.id = cat.availableCategoryId \
       left join FightVersion fver on fver.id = cat.fightVersionId \
       left join Competition comp on comp.id = cat.competitionId \
       left join Person pers on pers.id = comptr.personId \
       where \
        cat.competitionId = :competitionId \
        and upper(pers.surname) like upper(:surname)";
    //������� ������ ��� ��������� �������� �� ����
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    //������� ������������
    ibqCategory->ParamByName("competitionId")->AsInteger = competitionId;
    //������� ���������
    ibqCategory->ParamByName("surname")->AsString = "%"+surname+"%";
    //�������� ������ �� ���� ������
    ibqCategory->Open();

    //������� ������� �� ���������� ���������� �� ���� ������
    TList* resultList = new TList();
    resultList->Clear();
    ibqCategory->First();
    //������� ����������� ����
    TAvailCategory availCategory;
    TFightVersion fightVersion;
    TCompetition competition;
    for(int i = 0; i < ibqCategory->RecordCount; i++){
        //��������� ��������� (��������� ���������)

        availCategory.setId(ibqCategory->FieldByName("ac_id")->AsInteger);
        availCategory.setStartAge(ibqCategory->FieldByName("ac_sa")->AsInteger);
        availCategory.setEndAge(ibqCategory->FieldByName("ac_ea")->AsInteger);
        availCategory.setStartWeight(ibqCategory->FieldByName("ac_sw")->AsFloat);
        availCategory.setEndWeight(ibqCategory->FieldByName("ac_ew")->AsFloat);
        availCategory.setFemale(ibqCategory->FieldByName("ac_fem")->AsString =='T'?true:false);
        availCategory.setComments(ibqCategory->FieldByName("ac_com")->AsString);

        fightVersion.setId(ibqCategory->FieldByName("fv_id")->AsInteger);
        fightVersion.setCode(ibqCategory->FieldByName("fv_code")->AsString);
        fightVersion.setDescription(ibqCategory->FieldByName("fv_des")->AsString);
        fightVersion.setComments(ibqCategory->FieldByName("fv_com")->AsString);

        competition.setId(ibqCategory->FieldByName("id")->AsInteger);
        competition.setBeginDate(ibqCategory->FieldByName("c_bd")->AsDateTime);
        competition.setEndDate(ibqCategory->FieldByName("c_ed")->AsDateTime);
        competition.setCompetitionRankId(ibqCategory->FieldByName("c_crid")->AsInteger);
        competition.setComments(ibqCategory->FieldByName("c_com")->AsString);

        TCategory * result = new TCategory();

        result->setAvailCategoryId(ibqCategory->FieldByName("ac_id")->AsInteger);
        result->setFightVersionId(ibqCategory->FieldByName("fv_id")->AsInteger);
        result->setCompetitionId(competitionId);
        result->setId(ibqCategory->FieldByName("id")->AsInteger);
        //��������� �������������� ����
        result->extend(availCategory, fightVersion, competition);
        //�������� � ������
        resultList->Add(result);

        //�������� � ��������� ������
        ibqCategory->Next();
        }
    //������� ���������
    ibqCategory->Close();
    //������ �������������� ���������
    return resultList;
}

void TdmCategoryDAO::addFightVersionToCompetitor(int competitorId, int categoryId){
//������, ������� ��������� ��������� ����������� ������ ������
AnsiString insertFightVersionQuery =
 "insert into ExtendedFightVersion(competitorId, fightVersionId) \
 select distinct :competitorId, fightVersionId from CompetitorToFightVersion where \
 fightVersionId = (select fightVersionId from Category where id = :categoryId)";


    //���������� ������ ��� ����������� ���������
    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(insertFightVersionQuery);    
    ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = competitorId;
    ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = categoryId;

    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //��������� ������
    ibqCompetitorToCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� ���������� ������
        dmDataSource->ibtrSecretaryDB->Commit();
        }

}


void TdmCategoryDAO::setCompetitors(int id, TList * ids){
    //�������� � ������� ����� ��������� � ���������
AnsiString insertQuery =
"insert into CompetitorToCategory(categoryId, competitorId) \
 values(:categoryId, :competitorId)";

//������ ��� ���������� �������� ������������� � ������ ������ ���������
AnsiString updateQuery =
"update CompetitorToFightVersion set destributed = 'T' where \
 competitorId = :competitorId and fightVersionId = (select fightVersionId from \
 Category where id = :categoryId)";

//������, ������� ��������� ��������� ������ ������, ��� ���������� � ���������
//� �������������� ��� ������������ ������ �������
AnsiString insertFightVersionQuery_1 =
 "insert into CompetitorToFightVersion(competitorId, fightVersionId, destributed) \
 select distinct ";
AnsiString insertFightVersionQuery_2 =  ", fightVersionId, 'T' from CompetitorToFightVersion where \
 fightVersionId = (select fightVersionId from Category where id = "+ IntToStr(id) +")";
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    for(int i=0; i < ids->Count; i++){
        try{
            //�������� �������� ����� ������ ������ ���������
            ibqCompetitorToCategory->SQL->Clear();
            //���������� ������ ��� ����������� ���������
            ibqCompetitorToCategory->SQL->Add(insertFightVersionQuery_1 +
                                              IntToStr(((TCompetitor*)ids->Items[i])->getId()) +
                                              insertFightVersionQuery_2);

            try{
                ibqCompetitorToCategory->ExecSQL();
                //���� ����� ������ ������ ���� ��������� - ������� �� ����
                if(MessageDlg("�������� <" +((TCompetitor*)ids->Items[i])->getPerson().getSurname() + "> ����������� � ���������, � ������ �������, �� ��������� � ������!\n"+
                        "�������� � ������ ����� ������ ������?" ,
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0)==mrYes){
                    //�������� ��������� � ������ ������ � ������� � ������������ ��������
                    addFightVersionToCompetitor(((TCompetitor*)ids->Items[i])->getId(), id);
                    //����� ����������, ������� ���������� ������ 
                    if(!dmDataSource->ibtrSecretaryDB->Active){
                        dmDataSource->ibtrSecretaryDB->StartTransaction();
                        }
                    }
                else{
                    //"��������" ��������� �������
                    if(dmDataSource->ibtrSecretaryDB->Active){
                        dmDataSource->ibtrSecretaryDB->Rollback();
                        }
                    dmDataSource->ibtrSecretaryDB->StartTransaction();
                    //���������� ��������� ����������
                    continue;
                    }
                }
            catch(EIBInterBaseError *e){
                //��� ��������� ���������� ������ ������ � ������, �������� �� ��������������
                ibqCompetitorToCategory->SQL->Clear();
                ibqCompetitorToCategory->SQL->Add(updateQuery);
                //��������� �������� �������������� ���������
                ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = id;
                //�������� ����������� �������� � �������� ������
                ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = ((TCompetitor*)ids->Items[i])->getId();
                ibqCompetitorToCategory->ExecSQL();
                }

            ibqCompetitorToCategory->SQL->Clear();
            ibqCompetitorToCategory->SQL->Add(insertQuery);
            //��������� �������� �������������� ���������
            ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = id;
            //�������� ����������� �������� � �������� ������
            ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = ((TCompetitor*)ids->Items[i])->getId();
            ibqCompetitorToCategory->ExecSQL();
            }
        catch(EIBInterBaseError *e){
            //"��������" ��������� �������
            if(dmDataSource->ibtrSecretaryDB->Active){
                dmDataSource->ibtrSecretaryDB->Rollback();
                }
            dmDataSource->ibtrSecretaryDB->StartTransaction();
            MessageDlg("������� �������� ��������� � ���������, � ������� �� ��� ������������!\n�������� �� ���������!",
                        mtWarning, TMsgDlgButtons() << mbOK, 0);

            }
        }
    //��������� ���������� ������
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}


void TdmCategoryDAO::addCompetitor(int idCompetitor, int idCategory){
    //�������� � ������� ����� ��������� � ���������
AnsiString insertQuery =
"insert into CompetitorToCategory(competitorId, categoryId) \
values(:competitorId, :categoryId)";
//������ ��� ���������� �������� ������������� � ������ ������ ���������
AnsiString updateQuery =
"update CompetitorToFightVersion set destributed = 'T' where \
 competitorId = :competitorId and fightVersionId = (select fightVersionId from \
 Category where id = :categoryId)";


    //�������� ��������� � ���������

    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }

    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(insertQuery);

    //���������� ������������� ���������
    ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = idCompetitor;
    //��������� �������� �������������� ���������
    ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = idCategory;

    //��������� ������
    ibqCompetitorToCategory->ExecSQL();

    //������� ������� � ���, ��� ��������� ������������
    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(updateQuery);

    //���������� ������������� ���������
    ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = idCompetitor;
    //��������� �������� �������������� ���������
    ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = idCategory;
    //�������� ��������� � ���������
    ibqCompetitorToCategory->ExecSQL();


    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� ���������� ������
        dmDataSource->ibtrSecretaryDB->Commit();
        }

}




TList* TdmCategoryDAO::getCompetitors(int id){
//������ �� ��������� ��������������� ���������� �� ���������
AnsiString selectQuery =
"select competitorId from CompetitorToCategory where \
 CategoryId = :CategoryId";

    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(selectQuery);

    //��������� �������� �������������� ���������
    ibqCompetitorToCategory->ParamByName("CategoryId")->AsInteger = id;
    //��������� ������ � ��������� ������� ������� ��������
    ibqCompetitorToCategory->Open();
    ibqCompetitorToCategory->First();

    TList *resultList = new TList();
    resultList->Clear();
    for(int i=0; i < ibqCompetitorToCategory->RecordCount; i++){
        TCompetitor *result = new TCompetitor();
        //�������� ������ � �������� ���������������
        result->getById(
                    ibqCompetitorToCategory->FieldByName("competitorId")->AsInteger);
        //�������� � ������
        resultList->Add(result);
        //� ��������� ������
        ibqCompetitorToCategory->Next();
        }
    //������� ���������
    ibqCompetitorToCategory->Close();
    return resultList;
}


int TdmCategoryDAO::getCompetitorsAmount(int id){
int result = 0;
//������ �� ��������� ���������� ���������� � ���������
AnsiString selectQuery =
"select count(competitorId) from CompetitorToCategory where \
 CategoryId = :CategoryId";

    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(selectQuery);

    //��������� �������� �������������� ���������
    ibqCompetitorToCategory->ParamByName("CategoryId")->AsInteger = id;
    //��������� ������ � ��������� ������� ������� ��������
    ibqCompetitorToCategory->Open();
    ibqCompetitorToCategory->First();
    if(ibqCompetitorToCategory->RecordCount){
        result =  ibqCompetitorToCategory->FieldByName("count")->AsInteger;
        ibqCompetitorToCategory->Close();
        }
    return result;
}




void TdmCategoryDAO::eraseCompetitors(int id, TList *ids){

    //��������� ������ ��������� ����������
    AnsiString idList;
    for(int i=0; i < ids->Count - 1; i++){
        idList+=IntToStr(((TCompetitor*)ids->Items[i])->getId()) + ",";
        }
    idList += IntToStr(((TCompetitor*)ids->Items[ids->Count-1])->getId());


//������ �� �������� ���������� ��� ���������
AnsiString deleteQuery =
"delete from CompetitorToCategory where \
 categoryId = :categoryId and competitorId in (" + idList + ")";

//������ ��� ���������� �������� ������������� � ������ ������ ���������
AnsiString updateQuery =
"update CompetitorToFightVersion set destributed = 'F' where \
 competitorId in ("+ idList +") and fightVersionId = (select fightVersionId from \
 Category where id = :categoryId)";


    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(deleteQuery);

    //��������� �������� �������������� ���������
    ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = id;
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //��������� ������ �� �������� �������
    ibqCompetitorToCategory->ExecSQL();

    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(updateQuery);

    //��������� �������� �������������� ���������
    ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = id;
    //��������� ������ �� �������� �������
    ibqCompetitorToCategory->ExecSQL();
    //��������� ���������� ������
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}

bool TdmCategoryDAO::putCompetitor(double weight, int age, bool female,
                                    int fightVersionId, int competitionId, int competitorId){

bool added = false;

//������ �� ����������� ���������
AnsiString selectQuery =
"select cat.id from Category cat, AvailableCategory avcat where cat.availableCategoryId = avcat.id and \
 avcat.startWeight < :weight and avcat.endWeight >= :weight and avcat.startAge <= :age and \
 avcat.endAge >= :age and avcat.female = :female and cat.competitionId = :competitionId and \
 cat.fightVersionId = :fightVersionId";

    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    //���������� ���������
    ibqCategory->ParamByName("weight")->AsFloat = weight;
    ibqCategory->ParamByName("age")->AsInteger = age;
    ibqCategory->ParamByName("female")->AsString = (female?'T':'F');
    ibqCategory->ParamByName("competitionId")->AsInteger = competitionId;
    ibqCategory->ParamByName("fightVersionId")->AsInteger = fightVersionId;
    //��������� ������
    ibqCategory->Open();
    ibqCategory->First();
    //���� �� �������� ���������
    if(ibqCategory->RecordCount){
        addCompetitor(competitorId, ibqCategory->FieldByName("id")->AsInteger);
        //�������� �������� � ���������
        added = true;
        }
    ibqCategory->Close();
    //�� �������� ��������� ���������
    return added;
}


TList* TdmCategoryDAO::getSortionDataByCategory(int id){
//���������� �������
TList * resultList = new TList();
resultList->Clear();

//������ �� ��������� ������ ��� ���������� �� ���������
AnsiString selectQuery =
"select \
   ctc.competitorId, \
   sk.weight skillWeight, \
   req.clubId \
from \
   CompetitorToCategory ctc, \
   Competitor cpt, \
   Skill sk, \
   Request req \
where \
   cpt.id = ctc.competitorId and \
   sk.id = cpt.skillId and \
   req.id = cpt.requestId and \
   ctc.categoryId = :categoryId \
order by  req.clubId asc, sk.weight desc";

    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    //���������� ���������
    ibqCategory->ParamByName("categoryId")->AsInteger = id;
    //��������� ������
    ibqCategory->Open();
    ibqCategory->First();
    //���� �� �������� ������

    //������� �������������� ���������
    for(int i=0; i < ibqCategory->RecordCount ; i++){
        TSortionData* result = new TSortionData();
        result->competitorId = ibqCategory->FieldByName("competitorId")->AsInteger;
        result->skillWeight = ibqCategory->FieldByName("skillWeight")->AsInteger;
        result->clubId = ibqCategory->FieldByName("clubId")->AsInteger;

        //�������� � ������
        resultList->Add(result);

        //� ��������� ������
        ibqCategory->Next();
        }
    //������� ���������
    ibqCategory->Close();
    //������� ���������� (��� �� ����������) ������
    return resultList;
}


void TdmCategoryDAO::storeSortionOrder(int id, int *sortionOrder, int amnt){
//������ �� ��������� ������� ����������
AnsiString updateQuery =
"update CompetitorToCategory ctc set sortion=:sortion where \
  ctc.competitorId=:competitorId and ctc.categoryId = :categoryId";

  //���������� ������
  ibqCompetitorToCategory->SQL->Clear();
  ibqCompetitorToCategory->SQL->Add(updateQuery);
  //������� ������� - ���������
  ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = id;

  //���������� �� ������ ���������� � ����������� ������� ����������
    //��������� ��������� ������
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
  for(int sn = 0; sn < amnt; sn++){
    //�������� ���������
    ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = sortionOrder[sn];
    ibqCompetitorToCategory->ParamByName("sortion")->AsInteger = sn + 1;
    ibqCompetitorToCategory->ExecSQL();
    }
  //��������� ���������� ������
  if(dmDataSource->ibtrSecretaryDB->Active){
    dmDataSource->ibtrSecretaryDB->Commit();
    }
}


void TdmCategoryDAO::uncategory(int competitorId){
//������ �� �������� ��������� �� ���������
AnsiString deleteQuery =
"delete from CompetitorToCategory where \
 competitorId = :competitorId";

    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(deleteQuery);

    //��������� �������� �������������� ���������
    ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = competitorId;
    if(!dmDataSource->ibtrSecretaryDB->Active){
        //��������� � ����
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //��������� ������ �� �������� �������
    ibqCompetitorToCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� � ����
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}


void TdmCategoryDAO::setDrawType(TCategory category, char drawType){
AnsiString updateQuery = "update category set drawtype=:drawType where id=:categoryId";
    //������� ������ ��� ���������� ������� � ���� ������
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(updateQuery);
    ibqCategory->ParamByName("categoryId")->AsInteger = category.getId();
    ibqCategory->ParamByName("drawType")->AsString = drawType;
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //��������� ������
    ibqCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� ���������� ������
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}

char TdmCategoryDAO::getDrawType(TCategory category){
AnsiString selectQuery =
"select drawtype from Category where id = :id";
    //������� ������ ��� ��������� �������� �� ����
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    ibqCategory->ParamByName("id")->AsInteger = category.getId();
    //�������� ������ �� ���� ������
    ibqCategory->Open();
    char result;
    if(ibqCategory->RecordCount){
        if(!ibqCategory->FieldByName("drawtype")->AsString.IsEmpty()){
            result = ibqCategory->FieldByName("drawtype")->AsString[1];
            }
        }
    //������� ���������
    ibqCategory->Close();

    return result;
}


