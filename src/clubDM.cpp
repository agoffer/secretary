//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "clubDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//������� ��������� ������ - ��������� �� ������� 
CallbackFunction ClubScrollCallback;

TdmClubDAO *dmClubDAO;
//---------------------------------------------------------------------------
__fastcall TdmClubDAO::TdmClubDAO(TComponent* Owner)
    : TDataModule(Owner)
{
    //�������� ��������� ���������� �� ����� 
    sortedFieldState = ssUnsort;
    sortedField = ctfNoField;
    //�������� ����������� ����
    filteredField = ctfNoField;
    //������� �������
    filterCondition  = "";
}
//---------------------------------------------------------------------------


void TdmClubDAO::initClubTable(void){
    if(ibqClubAll->Active){
        ibqClubAll->Close();     
        }
    ibqClubAll->SQL->Clear();
    ibqClubAll->SQL->Add("select * from Club");
}

void TdmClubDAO::selectFromClubTable(AnsiString sortField, AnsiString filter, bool asc){
    //���� ����, �������� ������� ������
    TClub current = getCurrent();

    //��������� ������� ������
    initClubTable();
    //������� ������� ������� � ����������
    if(filter.Trim()!="")
        ibqClubAll->SQL->Add("where " + filter);
    if(sortField.Trim()!=""){
        ibqClubAll->SQL->Add("order by " + sortField);
        ibqClubAll->SQL->Add(asc?"asc" : "desc");
        }
    //��������� ������� � �������������� ���������
    ibqClubAll->Open();
    //�������� �� ���� �������
    ibqClubAll->Last();
    ibqClubAll->First();

    //������� ������� ������
    makeCurrent(current);
}


AnsiString TdmClubDAO::getFieldName(ClubTableField field){
    switch(field){
        case ctfName : return "name";
        case ctfCountry : return "country";
        case ctfCity : return "city";
        //�� ��������� ����
        default: return "";
        }
}


void TdmClubDAO::filterByField(ClubTableField field){
    //������� ��������� ������������� ����
    AnsiString asField = getFieldName(field);
    if(asField.Trim()=="") return;  //���� �� ����������
    //��������� ������ � ��������
    AnsiString condition = asField + " like '%" + filterCondition + "%'";
    //��������� �������������� ������� ����������
    asField = getFieldName(sortedField);
    //��������� ������� � ������������� ��������
    selectFromClubTable(asField, condition, sortedFieldState != ssDescending);
    //�������� ������� ����������
    filterCondition = "";
    //��������, �� ������ ���� ����������� ����������
    filteredField = field; 
}



void TdmClubDAO::sortByField(ClubTableField field){
AnsiString condition;
AnsiString asField;
    //���������, ���� ����� ������� ������� �������
    if(filterCondition.Trim()!=""){
        //������� � ����������� �� ��������� ����
        asField = getFieldName(filteredField);
        if(asField.Trim()!=""){
            condition = asField + " like '%" + filterCondition + "%'";
            }
        }
    //����, �� �������� ����� ��������� ����������
    //���� ��� �� ���������� ����������� ����, ������� ����������� ����������
    if(field != sortedField){
        sortedFieldState = ssUnsort;
        }
    asField = getFieldName(field);
    //��������� ��������� �������
    if(sortedFieldState == ssUnsort){
        //����������� �� �����������
        sortedFieldState = ssAscending;
        }
    else{
        //����������� �� ����������� ��� ��������, � ����������� �� ���. ���������
        if(sortedFieldState == ssAscending)
            sortedFieldState = ssDescending;
        else
            sortedFieldState = ssAscending;
        }
    //������� ������ �������
    selectFromClubTable(asField, condition, sortedFieldState != ssDescending);
    //�������� ������
    filterCondition="";
    //�������� ����, �� �������� ����������� ����������
    sortedField = field;
}




void TdmClubDAO::store(TClub &obj){
AnsiString updateQuery =
"update Club set name = :name, shortname = :shortname, country = :country,\
 city = :city, personId = :personId, comments = :comments\
 where id = :id";
AnsiString insertQuery =
"insert into Club(name, shortname, country, city, personId, comments)\
 values(:name, :shortname, :country, :city, :personId, :comments)";
AnsiString searchIdQuery =
"select id from Club where name=:name and shortname=:shortname and \
 country=:country and city=:city and personId=:personId and \
  comments=:comments";

    //������� ������ ��� ���������� ������� � ���� ������
    ibqClub->SQL->Clear();
    if(obj.getId() > 0){
        //��������
        ibqClub->SQL->Add(updateQuery);
        ibqClub->ParamByName("id")->AsInteger = obj.getId();
        }
    else{
        //��������
        ibqClub->SQL->Add(insertQuery);
        }
    ibqClub->ParamByName("name")->AsString = obj.getName();
    ibqClub->ParamByName("shortname")->AsString = obj.getShortName();
    ibqClub->ParamByName("country")->AsString = obj.getCountry();
    ibqClub->ParamByName("city")->AsString = obj.getCity();
    ibqClub->ParamByName("personId")->AsInteger = obj.getPersonId();
    ibqClub->ParamByName("comments")->AsString = obj.getComments();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //��������� ������
    ibqClub->ExecSQL();
    //�������� ������ � ����
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //���� ���� ��������� ����� ������, ������ �� �������������
    if(!obj.getId()){
        //�������� �� ������� ��������� ����������� ������
        ibqClub->SQL->Clear();
        ibqClub->SQL->Add(searchIdQuery);                
        ibqClub->ParamByName("name")->AsString = obj.getName();
        ibqClub->ParamByName("shortname")->AsString = obj.getShortName();
        ibqClub->ParamByName("country")->AsString = obj.getCountry();
        ibqClub->ParamByName("city")->AsString = obj.getCity();
        ibqClub->ParamByName("personId")->AsInteger = obj.getPersonId();
        ibqClub->ParamByName("comments")->AsString = obj.getComments();
        ibqClub->Open();
        obj.setId(ibqClub->FieldByName("id")->AsInteger);
        ibqClub->Close();        
        }
}


TClub TdmClubDAO::getCurrent(void){
//������������ ������
TClub result;
    result.setId(0);    //���������� ������ �� ��������
    //���� ������� �������, �������� ������� ������
    if(ibqClubAll->State != dsInactive){
        result.setId(ibqClubAll->FieldByName("id")->AsInteger);
        result.setName(ibqClubAll->FieldByName("name")->AsString);
        result.setShortName(ibqClubAll->FieldByName("shortname")->AsString);        
        result.setCountry(ibqClubAll->FieldByName("country")->AsString);
        result.setCity(ibqClubAll->FieldByName("city")->AsString);
        result.setPersonId(ibqClubAll->FieldByName("personId")->AsInteger);
        result.setComments(ibqClubAll->FieldByName("comments")->AsString);
        }
    //������� ���������
    return result;
}

void TdmClubDAO::makeCurrent(TClub obj){
int res;
    if(ibqClubAll->Active){
        //���� ������� �� ������ ������
        if(obj.getId() > 0){
            ibqClubAll->Locate("id", obj.getId(), TLocateOptions());
            }
        }
}


void TdmClubDAO::setScrollCallback(CallbackFunction cbf){
    ClubScrollCallback = cbf;
}




void __fastcall TdmClubDAO::ibqClubAllAfterScroll(TDataSet *DataSet)
{
    //���� ���������� ������� ��������� ������, �������� ��
    if(ClubScrollCallback){
        ClubScrollCallback();
        }
}




//---------------------------------------------------------------------------

