//---------------------------------------------------------------------------


#pragma hdrstop

#include "resultCtrl.h"
#include "resultDM.h"


//---------------------------------------------------------------------------

void TResult::getResults(int competitorId){
    dmResultDAO->getResults(competitorId, 0, *this);
}


void TResult::setResults(int competitorId){
    dmResultDAO->setResults(competitorId, 0, *this);
}

void TResult::getResults(int competitorId, int categoryId){
    dmResultDAO->getResults(competitorId, categoryId, *this);
    categoryId = categoryId;
}

void TResult::setResults(int competitorId, int categoryId){
    dmResultDAO->setResults(competitorId, categoryId,  *this);
    categoryId = categoryId;    
}

void TResult::setRecordMoveCallback(CallbackFunction cbf){
    dmResultDAO->setScrollCallback(cbf);
}

int TResult::getCurrentCompetitorId(void){
    return dmResultDAO->getCurrentCompetitorIdFromTable();
}

void TResult::setCurrentCompetitorById(int competitorId){
    return dmResultDAO->setCurrentCompetitorByIdFromTable(competitorId);
}

void TResult::getScoreRanking(map<int, int> &scoreRank, int competitionRank, int disciplineId){
    dmResultDAO->getScoreRanking(scoreRank, competitionRank, disciplineId);
}

TResult::~TResult(void){

}

#pragma package(smart_init)
