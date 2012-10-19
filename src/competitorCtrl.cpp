//---------------------------------------------------------------------------


#pragma hdrstop

#include "competitorCtrl.h"
#include "competitorDM.h"
#include "utils.h"



void TCompetitor::extend(TPerson inPerson, TSkill inSkill, TRequest inRequest){
    person = inPerson;
    skill = inSkill;
    request = inRequest; 
    //Установить признак расширения
    extended = true;
}

TCompetitor::TCompetitor(
            int inPersonId, int inSkillId,
            int inRequestId, double inWeight){
    //Инициализируем объект
    requestId = inRequestId;
    skillId = inSkillId;
    personId = inPersonId;
    weight = inWeight;
    id = 0;
    //Изначально объект не расширен
    extended = false;
    skill.setId(0);
    person.setId(0);
    request.setId(0);
}

TCompetitor::~TCompetitor(void){

}

bool TCompetitor::valid(AnsiString &errmess){
    //Проверим допустимость полей объекта
    if(!personId){
        //Необходимо указать личность участника
        errmess = "Не определена личность участника соревнования!";
        return false;
        }
    //Проверяем задан ли уровень мастерства
    if(!skillId){
        errmess = "Не определен уровень мастерства участника!";
        return false;
        }
    //Проверяем задан ли вес участника 
    if(weight < 10){
        errmess = "Не задан вес участника участника!";
        return false;
        }
    //Все правильно
    return true;
}

void TCompetitor::store(void){
   dmCompetitorDAO->store(*this);
}

void TCompetitor::erase(void){
   dmCompetitorDAO->erase(*this);
}


TCompetitor TCompetitor::getCurrent(void){
    return dmCompetitorDAO->getCurrent();
}


void TCompetitor::makeCurrent(void){
    return dmCompetitorDAO->makeCurrent(*this);
}


TCompetitor TCompetitor::getExtendedTableCurrent(void){
    return dmCompetitorDAO->getExtendedTableCurrent();
}


void TCompetitor::makeExtendedTableCurrent(void){
    return dmCompetitorDAO->makeExtendedTableCurrent(*this);
}


TList* TCompetitor::getAll(void){

}

TList* TCompetitor::getByRequestId(int requestId){
    return dmCompetitorDAO->getByRequestId(requestId);
}

TList* TCompetitor::getByCompetitionId(int competitionId){
    return dmCompetitorDAO->getByCompetitionId(competitionId);
}

TList* TCompetitor::getExtendedByCompetitionId(int competitionId){
    return dmCompetitorDAO->getExtendedByCompetitionId(competitionId);
}

TList* TCompetitor::getExtendedUncategoryByCompetitionId(int competitionId, bool female){
    return dmCompetitorDAO->getExtendedUncategoryByCompetitionId(competitionId, female); 
}


TList* TCompetitor::getExtendedByRequestId(int requestId){
    return dmCompetitorDAO->getExtendedByRequestId(requestId);
}

TList* TCompetitor::getExtendedByCategoryId(int categoryId){
    return dmCompetitorDAO->getExtendedByCategoryId(categoryId);
}


void TCompetitor::getById(int id){
    return dmCompetitorDAO->getById(id, *this);
}


void TCompetitor::setFightVersion(int *ids, int count){
    dmCompetitorDAO->setFightVersion(id, ids, count);
}


TList* TCompetitor::getFightVersion(void){
    return dmCompetitorDAO->getFightVersion(id);
}

TList* TCompetitor::getUncategoryFightVersion(void){
    return dmCompetitorDAO->getUncategoryFightVersion(id);
}

TList* TCompetitor::getExtendedFightVersion(void){
    return dmCompetitorDAO->getExtendedFightVersion(id);
}


void TCompetitor::eraseFightVersion(void){
    dmCompetitorDAO->eraseFightVersion(id);
}


void TCompetitor::setRecordMoveCallback(CallbackFunction cbf){
    dmCompetitorDAO->setScrollCallback(cbf);
}

void TCompetitor::loadResult(void){
    result.getResults(id);
}

void TCompetitor::storeResult(void){
    result.setResults(id);
}

void TCompetitor::loadResult(int categoryId){
    result.getResults(id, categoryId);
}

void TCompetitor::storeResult(int categoryId){
    result.setResults(id, categoryId);
}





//---------------------------------------------------------------------------

#pragma package(smart_init)

