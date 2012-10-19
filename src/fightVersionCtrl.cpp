//---------------------------------------------------------------------------


#pragma hdrstop

#include "fightVersionCtrl.h"
#include "fightVersionDM.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



TFightVersion::TFightVersion(AnsiString asInCode, AnsiString asInDescription, AnsiString asInComments){
    id = 0;
    asCode = asInCode;  
    asDescription = asInDescription;
    asComments = asInComments;
}


TFightVersion::~TFightVersion(void){

}


void TFightVersion::store(void){
    //��������� ������ � ���������
    dmFightVersionDAO->store(*this);
}


bool TFightVersion::valid(AnsiString &errmess){
    //���������� ��� ������ ������
    if(asCode.Trim()==""){
        errmess="������� ��� ������ ������!";
        return false;  
        }
    //����������� ��������
    if(asDescription.Trim()==""){
        errmess="������� �������� ������ ������!";
        return false;
        }
    //��� ��������� 
    return true; 
}


TList* TFightVersion::getAll(void){
    //�������� ��� ������� �� ���������
    return dmFightVersionDAO->getAll();
}

void TFightVersion::getById(int id){
    dmFightVersionDAO->getById(id, *this);
}
