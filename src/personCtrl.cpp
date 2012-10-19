//---------------------------------------------------------------------------


#pragma hdrstop

#include "personCtrl.h"
#include "personDM.h"

TPerson::TPerson(AnsiString asInSurname, AnsiString asInName,
            AnsiString asInPatronymic, TDateTime inDob,
            AnsiString asInPhone, bool inFemale, AnsiString asInAdditions){
    //Инициализируем объект
    asSurname = asInSurname;
    asName = asInName;
    asPatronymic = asInPatronymic;
    dob = inDob;
    asPhone = asInPhone;
    asAdditions = asInAdditions;
    female = inFemale; 
    id = 0;             
}

TPerson::~TPerson(void){

}

bool TPerson::valid(AnsiString &errmess){
    //Проверим допустимость полей объекта
    if(asSurname.Trim()==""){
        //Необходимо указать фамилию
        errmess = "Фамилия должна быть указана!";
        return false;
        }
    if(asName.Trim() == ""){
        //Необходимо указать имя
        errmess = "Имя должно быть указано!";
        return false;  
        }
    //Все правильно
    return true; 
}

void TPerson::store(void){
    dmPersonDAO->store(*this);
}

TPerson* TPerson::getAll(int &reccount){

}

TPerson TPerson::getCurrent(void){
    return dmPersonDAO->getCurrent();
}

bool TPerson::deleteCurrent(void){
    return dmPersonDAO->deleteCurrent();
}

void TPerson::makeCurrent(void){
    dmPersonDAO->makeCurrent(*this);
}

void TPerson::makeCurrent(int id){
    //Создать объект для установки нужного Id
    TPerson obj;
    obj.setId(id);
    //Сделать запись с нужным id текущей
    dmPersonDAO->makeCurrent(obj); 
}


void TPerson::getById(int id){

}


void TPerson::setRecordMoveCallback(CallbackFunction cbf){
    dmPersonDAO->setScrollCallback(cbf);
}



bool TPerson::likeAs(void){
    return dmPersonDAO->likeAs(*this);
}








//---------------------------------------------------------------------------

#pragma package(smart_init)


