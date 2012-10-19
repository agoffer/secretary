//---------------------------------------------------------------------------


#pragma hdrstop

#include "fightVersionCtrl.h"
#include "fightVersionDM.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



TFightVersion::TFightVersion(AnsiString asInCode, AnsiString asInDescription, AnsiString asInComments){
    id = 0;
    asCode = asInCode;  
    asDescription = asInDescription;
    asComments = asInComments;
}


TFightVersion::~TFightVersion(void){

}


void TFightVersion::store(void){
    //Сохранить объект в хранилище
    dmFightVersionDAO->store(*this);
}


bool TFightVersion::valid(AnsiString &errmess){
    //Отсутсвуте код боевой версии
    if(asCode.Trim()==""){
        errmess="Укажите код боевой версии!";
        return false;  
        }
    //Отсутствует описание
    if(asDescription.Trim()==""){
        errmess="Укажите описание боевой версии!";
        return false;
        }
    //Все нормально 
    return true; 
}


TList* TFightVersion::getAll(void){
    //Получить все объекты из хранилища
    return dmFightVersionDAO->getAll();
}

void TFightVersion::getById(int id){
    dmFightVersionDAO->getById(id, *this);
}
