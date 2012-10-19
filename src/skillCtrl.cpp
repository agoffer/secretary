//---------------------------------------------------------------------------


#pragma hdrstop

#include "skillCtrl.h"
#include "skillDM.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TSkill::TSkill(AnsiString asInShortDescription, AnsiString asInFullDescription,
               AnsiString asInComments, int inWeight){
    id = 0;
    weight = 0;
    asShortDescription = asInShortDescription;
    asFullDescription = asInFullDescription;    
    asComments = asInComments;
}


TSkill::~TSkill(void){

}


void TSkill::store(void){
    //��������� ������ � ���������
    dmSkillDAO->store(*this);
}


bool TSkill::valid(AnsiString &errmess){
    //����������� ��������
    if(asShortDescription.Trim()==""){
        //�� ������ ������������ ����
        errmess="������� �������� �������� ������ ����������!"; 
        return false;
        }
    //����������� ��������
    if(asFullDescription.Trim()==""){
        //�� ������ ������������ ����
        errmess="������� ������ �������� ������ ����������!";
        return false;
        }
    //��� ��������� 
    return true; 
}


TList* TSkill::getAll(void){
    //�������� ��� ������� �� ���������
    return dmSkillDAO->getAll();
}

void TSkill::getById(int id){
    dmSkillDAO->getById(id, *this);
}
