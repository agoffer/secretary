//---------------------------------------------------------------------------


#pragma hdrstop

#include "clubCtrl.h"
#include "clubDM.h"

TClub::TClub(AnsiString asInName, AnsiString asInShortName, 
            AnsiString asInCity, AnsiString asInCountry,
            int inPersonId, AnsiString asInComments){
    //�������������� ������
    asName = asInName;
    asShortName = asInShortName; 
    asCity = asInCity;
    asCountry = asInCountry;
    personId = inPersonId;
    asComments = asInComments;
    id = 0;             
}

TClub::~TClub(void){

}

bool TClub::valid(AnsiString &errmess){
    //�������� ������������ ����� �������
    if(asName.Trim() == ""){
        //���������� ������� ��� �����
        errmess = "������ ���� ������� �������� �����������!";
        return false;  
        }
    //���������, ����� �� ������������ �������
    if(!personId){
        errmess = "�� ��������� ������������ �����!";
        return false;  
        }
    //��� ���������
    return true; 
}

void TClub::store(void){
   dmClubDAO->store(*this);
}

TClub TClub::getCurrent(void){
    return dmClubDAO->getCurrent();
}


void TClub::makeCurrent(void){
    return dmClubDAO->makeCurrent(*this);
}


TList* TClub::getAll(void){
        return NULL;
}


TClub TClub::getById(int id){
    TClub club;
    club.setId(id);
    dmClubDAO->sortByField(ctfNoField); 
    dmClubDAO->makeCurrent(club);
    club = dmClubDAO->getCurrent();

    return club;
}


void TClub::setRecordMoveCallback(CallbackFunction cbf){
    dmClubDAO->setScrollCallback(cbf); 
}




//---------------------------------------------------------------------------

#pragma package(smart_init)
