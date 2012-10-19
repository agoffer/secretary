//---------------------------------------------------------------------------


#pragma hdrstop

#include "competitionCtrl.h"
#include "competitionDM.h"


TCompetition::TCompetition(TDate inBeginDate, TDate inEndDate,
                int inCompetitionRankId, AnsiString asInComments){
    //Создаем объект
    beginDate = inBeginDate;
    endDate = inEndDate;
    competitionRankId = inCompetitionRankId;
    asComments = asInComments;
    id = 0;
    extended = false;                   
}

TCompetition::~TCompetition(void){

}

bool TCompetition::valid(AnsiString &errmess){
    //Дата начала, должна быть раньше даты окончания
    if(beginDate > endDate){
        errmess = "Дата начала соревнований, должна быть раньше даты окончания!";
        return false;  
        }
    if(!competitionRankId){
        errmess = "Укажите уровень соревнований!";
        return false;  
        }
    //Все нормально
    return true;
}

void TCompetition::store(void){
    dmCompetitionDAO->store(*this);
}

TList* TCompetition::getAll(void){
    return dmCompetitionDAO->getAll();

}

void TCompetition::getById(int id){
    dmCompetitionDAO->getById(id, *this);
}

int TCompetition::getId(void){
    return id;
}

void TCompetition::setId(int inId){
    id = inId; 
}

TDate TCompetition::getBeginDate(void){
    return beginDate; 
}

void TCompetition::setBeginDate(TDate inBeginDate){
    beginDate = inBeginDate; 
}

TDate TCompetition::getEndDate(void){
    return endDate; 
}

void TCompetition::setEndDate(TDate inEndDate){
    endDate = inEndDate; 
}

int TCompetition::getCompetitionRankId(void){
    return competitionRankId;
}

void TCompetition::setCompetitionRankId(int inCompetitionRankId){
    competitionRankId = inCompetitionRankId;
}


AnsiString TCompetition::getComments(void){
    return asComments; 
}

void TCompetition::setComments(AnsiString asInComments){
    asComments = asInComments;
}


void TCompetition::getMinMaxBeginDate(TDateTime &minBeginDate, TDateTime &maxBeginDate){
    dmCompetitionDAO->getMinMaxBeginDate(minBeginDate, maxBeginDate);
}


void TCompetition::getMinMaxEndDate(TDateTime &minBeginDate, TDateTime &maxBeginDate){

}

TCompetition TCompetition::getExtendedCurrent(void){
    return dmCompetitionDAO->getExtendedCurrent(); 
}




//---------------------------------------------------------------------------
#pragma package(smart_init)
