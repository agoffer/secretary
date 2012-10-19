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
    //Сохранить объект в хранилище
    dmSkillDAO->store(*this);
}


bool TSkill::valid(AnsiString &errmess){
    //Отсутствует описание
    if(asShortDescription.Trim()==""){
        //Не задано обязательное поле
        errmess="Укажите короткое название уровня мастерства!"; 
        return false;
        }
    //Отсутствует описание
    if(asFullDescription.Trim()==""){
        //Не задано обязательное поле
        errmess="Укажите полное название уровня мастерства!";
        return false;
        }
    //Все нормально 
    return true; 
}


TList* TSkill::getAll(void){
    //Получить все объекты из хранилища
    return dmSkillDAO->getAll();
}

void TSkill::getById(int id){
    dmSkillDAO->getById(id, *this);
}
