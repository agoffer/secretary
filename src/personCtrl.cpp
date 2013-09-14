//---------------------------------------------------------------------------


#pragma hdrstop

#include "personCtrl.h"
#include "personDM.h"

TPerson::TPerson(AnsiString asInSurname, AnsiString asInName,
            AnsiString asInPatronymic, TDateTime inDob,
            AnsiString asInPhone, bool inFemale, AnsiString asInAdditions){
    //�������������� ������
    asSurname = asInSurname;
    asName = asInName;
    asPatronymic = asInPatronymic;
    dob = inDob;
    asPhone = asInPhone;
    asAdditions = asInAdditions;
    female = inFemale; 
    id = 0;             
}

TPerson::~TPerson(void){

}

bool TPerson::valid(AnsiString &errmess){
    //�������� ������������ ����� �������
    if(asSurname.Trim()==""){
        //���������� ������� �������
        errmess = "������� ������ ���� �������!";
        return false;
        }
    if(asName.Trim() == ""){
        //���������� ������� ���
        errmess = "��� ������ ���� �������!";
        return false;  
        }
    //��� ���������
    return true; 
}

void TPerson::store(void){
    dmPersonDAO->store(*this);
}

TPerson* TPerson::getAll(int &reccount){
        return NULL;
}

TPerson TPerson::getCurrent(void){
    return dmPersonDAO->getCurrent();
}

bool TPerson::deleteCurrent(void){
    return dmPersonDAO->deleteCurrent();
}

void TPerson::makeCurrent(void){
    dmPersonDAO->makeCurrent(*this);
}

void TPerson::makeCurrent(int id){
    //������� ������ ��� ��������� ������� Id
    TPerson obj;
    obj.setId(id);
    //������� ������ � ������ id �������
    dmPersonDAO->makeCurrent(obj); 
}


void TPerson::getById(int id){

}


void TPerson::setRecordMoveCallback(CallbackFunction cbf){
    dmPersonDAO->setScrollCallback(cbf);
}



bool TPerson::likeAs(void){
    return dmPersonDAO->likeAs(*this);
}








//---------------------------------------------------------------------------

#pragma package(smart_init)


