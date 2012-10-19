//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "availCategoryDM.h"
#include "dataSourceDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmAvailCategoryDAO *dmAvailCategoryDAO;
//---------------------------------------------------------------------------
__fastcall TdmAvailCategoryDAO::TdmAvailCategoryDAO(TComponent* Owner)
        : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------


void TdmAvailCategoryDAO::initAvailCategoryTable(){
    if(ibqAvailCategoryAll->Active){
        ibqAvailCategoryAll->Close(); 
        }
    ibqAvailCategoryAll->SQL->Clear();
    ibqAvailCategoryAll->SQL->Add("select * from AvailableCategory");
}

void TdmAvailCategoryDAO::setCategoryTable(int startAge, int endAge,
                                                double startWeight,
                                                double endWeight, bool female){
    initAvailCategoryTable();
    ibqAvailCategoryAll->SQL->Add(" where ");
    if(!female){
        ibqAvailCategoryAll->SQL->Add(" female='F'");
        }
    else{
        ibqAvailCategoryAll->SQL->Add(" female='T'");
        }
    //�������� ��������� �������� � �������� ������� �������
    if(startAge > 0){
        ibqAvailCategoryAll->SQL->Add(" and startage >= " + IntToStr(startAge));
        }
    if(endAge > 0){
        ibqAvailCategoryAll->SQL->Add(" and endage <= " + IntToStr(endAge));
        }
    if(startWeight > 0){
        ibqAvailCategoryAll->SQL->Add(" and startweight >= " + FloatToStr(startWeight));
        }
    if(endWeight > 0){
        ibqAvailCategoryAll->SQL->Add(" and endweight <= " + FloatToStr(endWeight));
        }

    ibqAvailCategoryAll->SQL->Add(" order by startage, startweight");
    ibqAvailCategoryAll->Open();
}


void TdmAvailCategoryDAO::store(TAvailCategory &obj){
AnsiString updateQuery =
"update AvailableCategory set startAge = :startAge, endAge = :endAge, \
 startWeight, endWeight, female = :female, comments = :comments \
 where id = :id";
AnsiString insertQuery =
"insert into AvailableCategory(startAge, endAge, startWeight, \
 endWeight, female, comments) \
 values(:startAge, :endAge, :startWeight, :endWeight, :female, :comments)";
AnsiString searchIdQuery =
"select id from AvailableCategory where startAge=:startAge and \
 endAge=:endAge and startWeight=:startWeight and endWeight=:endWeight and \
 female=:female and comments=:comments";
    //������� ������ ��� ���������� ������� � ���� ������
    ibqAvailCategory->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    if(obj.getId() > 0){
        //��������
        ibqAvailCategory->SQL->Add(updateQuery);
        ibqAvailCategory->ParamByName("id")->AsInteger = obj.getId();
    }
    else{
        //��������
        ibqAvailCategory->SQL->Add(insertQuery);
    }
    ibqAvailCategory->ParamByName("startAge")->AsInteger = obj.getStartAge();
    ibqAvailCategory->ParamByName("endAge")->AsInteger = obj.getEndAge();
    ibqAvailCategory->ParamByName("startWeight")->AsFloat = obj.getStartWeight();
    ibqAvailCategory->ParamByName("endWeight")->AsFloat = obj.getEndWeight();
    ibqAvailCategory->ParamByName("female")->AsString = ((obj.getFemale())?'T':'F');
    ibqAvailCategory->ParamByName("comments")->AsString = obj.getComments();
    //��������� ������

    ibqAvailCategory->ExecSQL();

    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� ���������� ������
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //���� ���� ��������� ����� ������, ������ �� �������������
    if(!obj.getId()){
        //�������� �� ������� ��������� ����������� ������
        ibqAvailCategory->SQL->Clear();
        ibqAvailCategory->SQL->Add(searchIdQuery); 
        ibqAvailCategory->ParamByName("startAge")->AsInteger = obj.getStartAge();
        ibqAvailCategory->ParamByName("endAge")->AsInteger = obj.getEndAge();
        ibqAvailCategory->ParamByName("startWeight")->AsFloat = obj.getStartWeight();
        ibqAvailCategory->ParamByName("endWeight")->AsFloat = obj.getEndWeight();
        ibqAvailCategory->ParamByName("female")->AsString = ((obj.getFemale())?'T':'F');
        ibqAvailCategory->ParamByName("comments")->AsString = obj.getComments();
        ibqAvailCategory->Open();
        obj.setId(ibqAvailCategory->FieldByName("id")->AsInteger);
        ibqAvailCategory->Close();
        }
}

TList*  TdmAvailCategoryDAO::getAll(void){
AnsiString selectQuery =
"select id, startAge, endAge, startWeight, endWeight, female, comments \
 from AvailableCategory";
    //������� ������ ��� ��������� �������� �� ����
    ibqAvailCategory->SQL->Clear();
    ibqAvailCategory->SQL->Add(selectQuery);
    //�������� ������ �� ���� ������
    ibqAvailCategory->Open();

    //������� ������� �� ���������� ���������� �� ���� ������
    TList* resultList = new TList();
    resultList->Clear();
    ibqAvailCategory->First();
     for(int i = 0; i < ibqAvailCategory->RecordCount; i++){
        TAvailCategory *result = new TAvailCategory();
        result->setId(ibqAvailCategory->FieldByName("id")->AsInteger);
        result->setStartAge(ibqAvailCategory->FieldByName("startAge")->AsInteger);
        result->setEndAge(ibqAvailCategory->FieldByName("endAge")->AsInteger);
        result->setStartWeight(ibqAvailCategory->FieldByName("startWeight")->AsFloat);
        result->setEndWeight(ibqAvailCategory->FieldByName("endWeight")->AsFloat);
        result->setFemale(ibqAvailCategory->FieldByName("female")->AsString =='T'?true:false);
        result->setComments(ibqAvailCategory->FieldByName("comments")->AsString);
        //������� � ������
        resultList->Add(result);
        //�������� � ��������� ������
        ibqAvailCategory->Next();
        }
     //������ �������������� ���������
     ibqAvailCategory->Close();
     return resultList;
}


void TdmAvailCategoryDAO::getById(int id, TAvailCategory &obj){
AnsiString selectQuery =
"select id, startAge, endAge, startWeight, endWeight, female, comments \
 from AvailableCategory where id = :id";
    //������� ������ ��� ��������� �������� �� ����
    ibqAvailCategory->SQL->Clear();
    ibqAvailCategory->SQL->Add(selectQuery);
    ibqAvailCategory->ParamByName("id")->AsInteger = id;
    //�������� ������ �� ���� ������
    ibqAvailCategory->Open();
    if(ibqAvailCategory->RecordCount){
        obj.setId(ibqAvailCategory->FieldByName("id")->AsInteger);
        obj.setStartAge(ibqAvailCategory->FieldByName("startAge")->AsInteger);
        obj.setEndAge(ibqAvailCategory->FieldByName("endAge")->AsInteger);
        obj.setStartWeight(ibqAvailCategory->FieldByName("startWeight")->AsFloat);
        obj.setEndWeight(ibqAvailCategory->FieldByName("endWeight")->AsFloat);
        obj.setFemale(ibqAvailCategory->FieldByName("female")->AsString =='T'?true:false);
        obj.setComments(ibqAvailCategory->FieldByName("comments")->AsString);
        }
    //������ �� ��������, ������� null
    else{
        //�������� ������
        setmem(&obj, sizeof(obj), 0);
        }
    //������� ���������
    ibqAvailCategory->Close();
}

int TdmAvailCategoryDAO::getAvailCategoryId(double weight, int age, bool female){
//��������� �������
int result = 0;
    //������ ��� ������������� ���������
AnsiString selectQuery =
"select id from AvailableCategory avcat where avcat.startWeight < :weight and \
 avcat.endWeight >= :weight and avcat.startAge <= :age and avcat.endAge >= :age and \
 avcat.female = :female";
    ibqAvailCategory->SQL->Clear();
    ibqAvailCategory->SQL->Add(selectQuery);
    //���������� ��������� �������
    ibqAvailCategory->ParamByName("weight")->AsFloat = weight;
    ibqAvailCategory->ParamByName("age")->AsInteger = age;
    ibqAvailCategory->ParamByName("female")->AsString = female?'T':'F';
    //��������� ������
    ibqAvailCategory->Open();
    ibqAvailCategory->First();
    if(ibqAvailCategory->RecordCount){
        //���� �������� ���������
        result = ibqAvailCategory->FieldByName("id")->AsInteger;
        }
    //������� ���������
    ibqAvailCategory->Close();
    //������� ���������
    return result;
}

TAvailCategory TdmAvailCategoryDAO::getCurrent(void){
//������������ ������
TAvailCategory result;
    result.setId(0);    //���������� ������ �� ��������
    //���� ������� �������, �������� ������� ������
    if(ibqAvailCategoryAll->State != dsInactive){
        result.setId(ibqAvailCategoryAll->FieldByName("id")->AsInteger);
        result.setStartAge (ibqAvailCategoryAll->FieldByName("startage")->AsInteger);
        result.setEndAge(ibqAvailCategoryAll->FieldByName("endage")->AsInteger);
        result.setStartWeight(ibqAvailCategoryAll->FieldByName("startweight")->AsFloat);
        result.setEndWeight(ibqAvailCategoryAll->FieldByName("endweight")->AsFloat);
        result.setFemale(ibqAvailCategoryAll->FieldByName("female")->AsString =='T'?true:false);
        result.setComments(ibqAvailCategoryAll->FieldByName("comments")->AsString);
        }
    //������� ���������
    return result;
}


void TdmAvailCategoryDAO::makeCurrent(TAvailCategory obj){
    //���� ������� �� ������ ������
    if(ibqAvailCategoryAll->Active){
        if(obj.getId() > 0){
            ibqAvailCategoryAll->Locate("id", obj.getId(), TLocateOptions());
            }
        }
}

void TdmAvailCategoryDAO::remove(TAvailCategory obj){
String deleteQuery = "delete from AvailableCategory ac where ac.id=:id";
    //���� ������� �� ������ ������
    if(obj.getId() > 0){
      ibqAvailCategory->SQL->Clear();
      ibqAvailCategory->SQL->Add(deleteQuery);
      //���������� ��������� �������
      ibqAvailCategory->ParamByName("id")->AsInteger = obj.getId();
      ibqAvailCategory->ExecSQL();
      //������� ���������
      ibqAvailCategory->Close();
      }
}


