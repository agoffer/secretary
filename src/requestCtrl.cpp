//---------------------------------------------------------------------------


#pragma hdrstop

#include "requestCtrl.h"

#include "requestDM.h"


void TRequest::extend(TPerson inPerson, TClub inClub){
    person = inPerson;
    club = inClub;
    //���������� ������� ����������
    extended = true;
}

TRequest::TRequest(
            int inCompetitionId, int inClubId,
            int inPersonId, AnsiString asInComments){
    //�������������� ������
    competitionId = inCompetitionId;
    clubId = inClubId;
    personId = inPersonId;
    asComments = asInComments;
    id = 0;
    //���������� ������ �� ��������
    extended = false;
    club.setId(0);
    person.setId(0);               
}

TRequest::~TRequest(void){

}

bool TRequest::valid(AnsiString &errmess){
    //�������� ������������ ����� �������
    if(!personId){
        //���������� ������� �������������
        errmess = "�� ��������� ������������� ����������� �������� ������!";
        return false;
        }
    //��������� ����� �� ����
    if(!clubId){
        errmess = "�� ���������� ����������� �������� ������!";
        return false;
        }
    //��� ���������
    return true;
}

void TRequest::store(void){
   dmRequestDAO->store(*this);
}

TRequest TRequest::getCurrent(void){
    return dmRequestDAO->getCurrent();
}


void TRequest::makeCurrent(void){
    return dmRequestDAO->makeCurrent(*this);
}


TList* TRequest::getAll(void){

}

void TRequest::deleteById(int requestId){
    dmRequestDAO->deleteById(requestId);
}


TList* TRequest::getByCompetitionId(int competitionId){
    return dmRequestDAO->getByCompetitionId(competitionId);
}

TList* TRequest::getExtendedByCompetitionId(int competitionId){
    return dmRequestDAO->getExtendedByCompetitionId(competitionId);
}



void TRequest::getById(int id){
}


//---------------------------------------------------------------------------

#pragma package(smart_init)
