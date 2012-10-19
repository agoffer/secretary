//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "personDM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//������� ��������� ������ - ��������� �� �������
CallbackFunction PersonScrollCallback;

TdmPersonDAO *dmPersonDAO;
//---------------------------------------------------------------------------
__fastcall TdmPersonDAO::TdmPersonDAO(TComponent* Owner)
    : TDataModule(Owner)
{
    //�������� ��������� ���������� �� �����
    sortedFieldState = ssUnsort;
    sortedField = ptfNoField;
    //�������� ����������� ����
    filteredField = ptfNoField;
    //������� �������
    filterCondition  = "";

}
//---------------------------------------------------------------------------


void TdmPersonDAO::initPersonTable(TIBQuery *ibq){
    if(ibq->Active){
        ibq->Close();
        }
    ibq->SQL->Clear();
    ibq->SQL->Add("select * from Person ");
}

void TdmPersonDAO::selectFromPersonTable(TIBQuery *ibq, AnsiString sortField, AnsiString filter, bool asc){
    //���� ���� ��������� ������, �������� �� �������
    TPerson current = getCurrent(ibq);
    //��������� ������� ������
    initPersonTable(ibq);
    //������� ������� ������� � ����������
    if(filter.Trim()!="")
        ibq->SQL->Add("where " + filter);
    if(sortField.Trim()!=""){
        ibq->SQL->Add("order by " + sortField);
        ibq->SQL->Add(asc?"asc" : "desc");
        } else{
         ibq->SQL->Add("order by surname asc");
        }
    //��������� ������� � �������������� ���������
    ibq->Open();
    //�������� �� ���� �������
    ibq->Last();
    ibq->First();
    //������ ��������� �� ����� ��������� ������
    if(current.getId()!=0)
        makeCurrent(current, ibq);
}

AnsiString TdmPersonDAO::getFieldName(PersonTableField field){
    switch(field){
        case ptfSurname : return "surname";
        case ptfName : return "name";
        case ptfPatronymic : return "patronymic";
        case ptfPhone : return "phone";
        //�� ��������� ����
        default: return "";
        }
}


void TdmPersonDAO::filterByField(PersonTableField field){
    //������� ��������� ������������� ����
    AnsiString asField = getFieldName(field);
    if(asField.Trim()=="") return;  //���� �� ����������
    //��������� ������ � ��������
    AnsiString condition = asField + " like '%" + filterCondition + "%'";
    //��������� �������������� ������� ����������
    asField = getFieldName(sortedField);
    //��������� ������� � ������������� ��������
    selectFromPersonTable(ibqPersonAll, asField, condition, sortedFieldState != ssDescending);
    //�������� ������� ����������
    filterCondition = "";
    //��������, �� ������ ���� ����������� ����������
    filteredField = field;
}

void TdmPersonDAO::refreshSlaveTable(String filter) {
    //������� ��������� ������������� ���� (��� �������� �������� �� �������� �������)
    AnsiString asField = getFieldName(filteredField);
    //��������� ������ � ��������
    AnsiString condition = asField + " like '%" + filter + "%'";
    //��������� �������������� ������� ����������
    asField = getFieldName(sortedField);
    //��������� ������� � ������������� ��������
    selectFromPersonTable(ibqPersonSlaveTable, asField, condition, sortedFieldState != ssDescending);
}




void TdmPersonDAO::sortByField(PersonTableField field){
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
    selectFromPersonTable(ibqPersonAll, asField, condition, sortedFieldState != ssDescending);
    //�������� ������
    filterCondition="";
    //�������� ����, �� �������� ����������� ����������
    sortedField = field;
}




void TdmPersonDAO::store(TPerson &obj){
AnsiString updateQuery =
"update Person set surname = :surname, name = :name, patronymic = :patronymic,\
 dob = :dob, female = :female, phone = :phone, additions = :additions\
 where id = :id";
AnsiString insertQuery =
"insert into Person(surname, name, patronymic, dob, female, phone, additions)\
 values(:surname, :name, :patronymic,:dob, :female, :phone, :additions)";
AnsiString searchIdQuery =
"select id from Person where surname=:surname and name=:name and \
 patronymic=:patronymic and dob=:dob and female=:female and phone=:phone and \
 additions=:additions";
    //������� ������ ��� ���������� ������� � ���� ������
    ibqPerson->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    if(obj.getId() > 0){
        //��������
        ibqPerson->SQL->Add(updateQuery);
        ibqPerson->ParamByName("id")->AsInteger = obj.getId();
        }
    else{
        //��������
        ibqPerson->SQL->Add(insertQuery);
        }
    ibqPerson->ParamByName("surname")->AsString = obj.getSurname();
    ibqPerson->ParamByName("name")->AsString = obj.getName();
    ibqPerson->ParamByName("patronymic")->AsString = obj.getPatronymic();
    ibqPerson->ParamByName("dob")->AsDateTime = obj.getDob();
    ibqPerson->ParamByName("female")->AsString = ((obj.getFemale())?'T':'F');
    ibqPerson->ParamByName("phone")->AsString = obj.getPhone();
    ibqPerson->ParamByName("additions")->AsString = obj.getAdditions();
    //��������� ������
    ibqPerson->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //��������� � ����
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //���� ���� ��������� ����� ������, ������ �� �������������
    if(!obj.getId()){
        //�������� �� ������� ��������� ����������� ������
        ibqPerson->SQL->Clear();
        ibqPerson->SQL->Add(searchIdQuery);
        ibqPerson->ParamByName("surname")->AsString = obj.getSurname();
        ibqPerson->ParamByName("name")->AsString = obj.getName();
        ibqPerson->ParamByName("patronymic")->AsString = obj.getPatronymic();
        ibqPerson->ParamByName("dob")->AsDateTime = obj.getDob();
        ibqPerson->ParamByName("female")->AsString = ((obj.getFemale())?'T':'F');
        ibqPerson->ParamByName("phone")->AsString = obj.getPhone();
        ibqPerson->ParamByName("additions")->AsString = obj.getAdditions();
        ibqPerson->Open();
        obj.setId(ibqPerson->FieldByName("id")->AsInteger);
        ibqPerson->Close();
        }
}

TPerson TdmPersonDAO::getCurrent(){
    return getCurrent(ibqPersonAll);
}

TPerson TdmPersonDAO::getCurrentSlave(){
    return getCurrent(ibqPersonSlaveTable);
}


TPerson TdmPersonDAO::getCurrent(TIBQuery *ibq){
//������������ ������
TPerson result;
    result.setId(0);    //���������� ������ �� ��������
    //���� ������� �������, �������� ������� ������
    if(ibq->State != dsInactive){
        result.setId(ibq->FieldByName("id")->AsInteger);
        result.setSurname(ibq->FieldByName("surname")->AsString);
        result.setName(ibq->FieldByName("name")->AsString);
        result.setPatronymic(ibq->FieldByName("patronymic")->AsString);
        result.setDob(ibq->FieldByName("dob")->AsDateTime);
        result.setFemale(ibq->FieldByName("female")->AsString =='T'?true:false);
        result.setPhone(ibq->FieldByName("phone")->AsString);
        result.setAdditions(ibq->FieldByName("additions")->AsString);
        }
    //������� ���������
    return result;
}

bool TdmPersonDAO::deleteCurrent(void){
AnsiString deleteQuery = "delete from Person where id = :personid";
    //���� ������� �������, �������� ������� ������
    if(ibqPersonAll->State != dsInactive){
      //������� ������ ��� ���������� ������� � ���� ������
        ibqPerson->SQL->Clear();
        ibqPerson->SQL->Add(deleteQuery);
        ibqPerson->ParamByName("personid")->AsString = ibqPersonAll->FieldByName("id")->AsInteger;
        //��������� ������
        ibqPerson->ExecSQL();
        return true;
        }
    else{
      return false;
      }
}


bool TdmPersonDAO::likeAs(TPerson &obj){
bool find = false;//��������� ������
AnsiString searchQuery =
"select id from Person where surname = :surname and \
                             name = :name and \
                             patronymic = :patronymic";

    //������� ������ ��� ���������� ������� � ���� ������
    ibqPerson->SQL->Clear();
    ibqPerson->SQL->Add(searchQuery);
    ibqPerson->ParamByName("surname")->AsString = obj.getSurname();
    ibqPerson->ParamByName("name")->AsString = obj.getName();
    ibqPerson->ParamByName("patronymic")->AsString = obj.getPatronymic();
    //��������� ������
    ibqPerson->Open();
    //���� ���� �������� ������, �������� ������������� � ������� ������
    if(ibqPerson->RecordCount){
        obj.setId(ibqPersonAll->FieldByName("id")->AsInteger);
        find = true;
        }
    //�������
    ibqPerson->Close();
    //������� �� �������
    return find;
}

void TdmPersonDAO::makeCurrent(TPerson obj){
    makeCurrent(obj, ibqPersonAll);
}

void TdmPersonDAO::makeCurrent(TPerson obj, TIBQuery *ibq){
    //���� ������� �� ������ ������
    if(ibq->Active){
        if(obj.getId() > 0){
            ibq->Locate("id", obj.getId(), TLocateOptions());
            }
        }
}


void TdmPersonDAO::setScrollCallback(CallbackFunction cbf){
    PersonScrollCallback = cbf;
}



void __fastcall TdmPersonDAO::ibqPersonAllAfterScroll(TDataSet *DataSet)
{
    //���� ���������� ������� ��������� ������, �������� ��
    if(PersonScrollCallback){
        PersonScrollCallback();
        }

}
//---------------------------------------------------------------------------

/**
 * ��������� ������ �� ����� �������, ������� �� ������.
 * @param from ������ ������� �����
 * @param to ������ �������� ������
 */
void TdmPersonDAO::changePersonalData(TIBQuery *from, TIBQuery *to) {
    int fromId = from->FieldByName("id")->AsInteger;
    int toId = to->FieldByName("id")->AsInteger;
    //������� ������� � ������� CLUB
    replacePersonInCertainTable("CLUB", "personId", fromId, toId);
    //������� ������ � ������� COMPETITIOR
    replacePersonInCertainTable("COMPETITOR", "personId", fromId, toId);
    //������� ������ � ������� REQUEST
    replacePersonInCertainTable("REQUEST", "personId", fromId, toId);
    //������� ����, �������� ��������
    deleteCurrent();
    // ��������� ����������
        if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}
//---------------------------------------------------------------------------

/**
 * ������ ������������ ������ � �������� �������.
 * @param tableName �������, � ������� �������� ������
 * @param fieldName ����, �� �������� �������� ������
 * @param personIdFrom ������������� �������, ������� ����� ��������
 * @param personIdTo ������������� �������, �� ������� ����� ��������
 */
void TdmPersonDAO::replacePersonInCertainTable(AnsiString tableName, AnsiString fieldName, int personIdFrom, int personIdTo) {
    // ������������ ������, ��� ������ �������� ������������ ������
    AnsiString updateQuery = "update " + tableName + " set " + fieldName + " = " + personIdFrom + " where "
                            + fieldName + " = " + personIdTo;
    //������� ������ ��� ���������� ������� � ���� ������
    ibqPerson->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    ibqPerson->SQL->Add(updateQuery);
    //��������� ������
    ibqPerson->ExecSQL();
}
//---------------------------------------------------------------------------







