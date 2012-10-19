//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dataSourceDM.h"
#include "skillDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmSkillDAO *dmSkillDAO;
//---------------------------------------------------------------------------
__fastcall TdmSkillDAO::TdmSkillDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------

void TdmSkillDAO::initSkillTable(){
    if(ibqSkillAll->Active){
        ibqSkillAll->Close(); 
        }
    ibqSkillAll->SQL->Clear();
    ibqSkillAll->SQL->Add("select * from Skill");
}

void TdmSkillDAO::store(TSkill &obj){
AnsiString updateQuery =
"update Skill set shortDescription = :shortDescription,\
 fullDescription = :fullDescription, comments = :comments\
 weight = :weight\
 where id = :id";
AnsiString insertQuery =
"insert into Skill(shortDescription, fullDescription, comments, weight) \
 values(:shortDescription, :fullDescription, :comments, :weight)";
AnsiString searchIdQuery =
"select id from Skill where shortDescription=:shortDescription and \
 fullDescription=:fullDescription and comments=:comments and \
 weight=:weight";
    //������� ������ ��� ���������� ������� � ���� ������
    ibqSkill->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction(); 
        }
    if(obj.getId() > 0){
        //��������
        ibqSkill->SQL->Add(updateQuery);
        ibqSkill->ParamByName("id")->AsInteger = obj.getId();
    }
    else{
        //��������
        ibqSkill->SQL->Add(insertQuery);
    }
    ibqSkill->ParamByName("shortDescription")->AsString = obj.getShortDescription();
    ibqSkill->ParamByName("fullDescription")->AsString = obj.getFullDescription();
    ibqSkill->ParamByName("comments")->AsString = obj.getComments();
    ibqSkill->ParamByName("weight")->AsInteger = obj.getWeight();
    //��������� ������
    ibqSkill->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� � ����
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //���� ���� ��������� ����� ������, ������ �� �������������
    if(!obj.getId()){
        //�������� �� ������� ��������� ����������� ������
        ibqSkill->SQL->Clear();
        ibqSkill->SQL->Add(searchIdQuery);                
        ibqSkill->ParamByName("shortDescription")->AsString = obj.getShortDescription();
        ibqSkill->ParamByName("fullDescription")->AsString = obj.getFullDescription();
        ibqSkill->ParamByName("comments")->AsString = obj.getComments();
        ibqSkill->ParamByName("weight")->AsInteger = obj.getWeight();
        ibqSkill->Open();
        obj.setId(ibqSkill->FieldByName("id")->AsInteger);
        ibqSkill->Close();        
        }
}

TList*  TdmSkillDAO::getAll(void){
AnsiString selectQuery =
"select id, shortDescription, fullDescription, comments, weight from Skill";
    //������� ������ ��� ��������� �������� �� ����
    ibqSkill->SQL->Clear();
    ibqSkill->SQL->Add(selectQuery);
    //�������� ������ �� ���� ������
    ibqSkill->Open();


        //������� ������� �� ���������� ���������� �� ���� ������
        TList* resultList = new TList();
        resultList->Clear(); 
        ibqSkill->First();
        for(int i = 0; i < ibqSkill->RecordCount; i++){
            TSkill * result = new TSkill(); 
            result->setId(ibqSkill->FieldByName("id")->AsInteger);
            result->setShortDescription(ibqSkill->FieldByName("shortDescription")->AsString);
            result->setFullDescription(ibqSkill->FieldByName("fullDescription")->AsString);
            result->setComments(ibqSkill->FieldByName("comments")->AsString);
            result->setWeight(ibqSkill->FieldByName("weight")->AsInteger);

            //�������� � ������
            resultList->Add(result);
            //�������� � ��������� ������
            ibqSkill->Next();
            }
        //������� ���������
        ibqSkill->Close();
        //������ �������������� ���������
        return resultList;
}


void TdmSkillDAO::getById(int id, TSkill &obj){
AnsiString selectQuery =
"select shortDescription, fullDescription, comments, weight\
 from Skill where id = :id";
    //������� ������ ��� ��������� �������� �� ����
    ibqSkill->SQL->Clear();
    ibqSkill->SQL->Add(selectQuery);    
    ibqSkill->ParamByName("id")->AsInteger = id;
    //�������� ������ �� ���� ������
    ibqSkill->Open();
    if(ibqSkill->RecordCount){
        obj.setId(id);
        obj.setShortDescription(ibqSkill->FieldByName("shortDescription")->AsString);
        obj.setFullDescription(ibqSkill->FieldByName("fullDescription")->AsString);
        obj.setComments(ibqSkill->FieldByName("comments")->AsString);
        obj.setWeight(ibqSkill->FieldByName("weight")->AsInteger);
        }
    //������ �� ��������, ������� null
    else{
        //�������� ������
        setmem(&obj, sizeof(obj), 0);
        }
    ibqSkill->Close(); 
}
