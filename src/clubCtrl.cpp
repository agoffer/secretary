//---------------------------------------------------------------------------


#pragma hdrstop

#include "clubCtrl.h"
#include "clubDM.h"

TClub::TClub(AnsiString asInName, AnsiString asInShortName, 
            AnsiString asInCity, AnsiString asInCountry,
            int inPersonId, AnsiString asInComments){
    //Инициализируем объект
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
    //Проверим допустимость полей объекта
    if(asName.Trim() == ""){
        //Необходимо указать имя клуба
        errmess = "Должно быть указано название организации!";
        return false;  
        }
    //Проверяем, задан ли преставитель команды
    if(!personId){
        errmess = "Не определен преставитель клуба!";
        return false;  
        }
    //Все правильно
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
