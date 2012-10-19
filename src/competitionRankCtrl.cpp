//---------------------------------------------------------------------------


#pragma hdrstop

#include "competitionRankCtrl.h"
#include "competitionRankDM.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TCompetitionRank::TCompetitionRank(AnsiString asInDescription, AnsiString asInComments){
    id = 0; 
    asDescription = asInDescription;
    asComments = asInComments;
}


TCompetitionRank::~TCompetitionRank(void){

}


void TCompetitionRank::store(void){
    //Сохранить объект в хранилище
    dmCompetitionRankDAO->store(*this);
}


bool TCompetitionRank::valid(AnsiString &errmess){
    //Отсутствует описание
    if(asDescription.Trim()==""){
        //Не задано обязательное поле
        errmess="Укажите статус соревнований!"; 
        return false;
        }
    //Все нормально 
    return true; 
}


TList* TCompetitionRank::getAll(void){
    //Получить все объекты из хранилища
    return dmCompetitionRankDAO->getAll();
}

void TCompetitionRank::getById(int id){
    dmCompetitionRankDAO->getById(id, *this);
}

int TCompetitionRank::getId(void){
    return id; 
}


void TCompetitionRank::setId(int inId){
    id = inId; 
}


AnsiString TCompetitionRank::getDescription(void){
    return asDescription; 
}

void TCompetitionRank::setDescription(AnsiString asInDescription){
    asDescription = asInDescription;
}

AnsiString TCompetitionRank::getComments(void){
    return asComments; 
}

void TCompetitionRank::setComments(AnsiString asInComments){
    asComments = asInComments; 
}
