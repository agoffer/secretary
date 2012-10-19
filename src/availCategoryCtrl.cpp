//---------------------------------------------------------------------------


#pragma hdrstop

#include "availCategoryCtrl.h"
#include "availCategoryDM.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TAvailCategory::TAvailCategory(int inStartAge, int inEndAge, double inStartWeight,
                               double inEndWeight, bool inFemale,
                               AnsiString asInComments){
    id = 0;
    startAge = inStartAge;
    endAge = inEndAge;
    startWeight = inStartWeight;
    endWeight = inEndWeight;
    female = inFemale;
    asComments = asInComments;
}


TAvailCategory::~TAvailCategory(void){

}


void TAvailCategory::store(void){
    //��������� ������ � ���������
    dmAvailCategoryDAO->store(*this);
}


bool TAvailCategory::valid(AnsiString &errmess){

    /////////////////�������� ������� 


    //��� ���������
    return true;
}


TList* TAvailCategory::getAll(void){
    //�������� ��� ������� �� ���������
    return dmAvailCategoryDAO->getAll();
}

void TAvailCategory::getById(int id){
    dmAvailCategoryDAO->getById(id, *this);
}



int TAvailCategory::checkForAvailCategory(TCompetitor competitor){
    //��������, � ����� ��������� ����� ��������� ���������
    int age = YearsPassCalculator(competitor.getPerson().getDob());
    return dmAvailCategoryDAO->getAvailCategoryId(competitor.getWeight(), age,
                                                  competitor.getPerson().getFemale());
}

int TAvailCategory::checkForAvailCategory(int age, double weight, bool female){
    //��������, � ����� ��������� ����� ��������� ���������
    return dmAvailCategoryDAO->getAvailCategoryId(weight, age, female);
}


TAvailCategory TAvailCategory::getCurrent(void){
    return dmAvailCategoryDAO->getCurrent();
}


void TAvailCategory::makeCurrent(void){
    dmAvailCategoryDAO->makeCurrent(*this);
}

void TAvailCategory::remove(void){
  //������� ������ �� ���� ������
  dmAvailCategoryDAO->remove(*this);
}


