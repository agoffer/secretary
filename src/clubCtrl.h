//---------------------------------------------------------------------------

#ifndef clubCtrlH
#define clubCtrlH

#include <vcl.h>


#include "utils.h"

//****************************************//
// Класс представлющий объекты
// "Клуб"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 26.11.05
//****************************************//

class TClub{
private:
    //Идентификатор
    int id;
    //Название клуба
    AnsiString asName;
    //Короткое название команды
    AnsiString asShortName;
    //Город из которого клуб
    AnsiString asCity;
    //Страна из которой клуб
    AnsiString asCountry;
    //Идентификатор представителя клуба
    int personId;
    //Комментарии и дополнительная информация
    AnsiString asComments;


// Интерфейс объекта //
public:


    //-- Конструктор
    //@param asName  - название клуба
    //@param asCity - город клуба
    //@param asCountry - страна клуба
    //@param personId - Идентификатор представителя клуба
    //@param asComments - дополнительная информация
    TClub(AnsiString asInName, AnsiString asInShortName, AnsiString asInCity,
            AnsiString asInCountry, int inPersonId,
            AnsiString asIComments);
    //-- Конструктор по умолчанию
    TClub(void){ asName = ""; asShortName = ""; asCity = ""; asCountry = "";
                    personId = 0; asComments = "";
                    id = 0;
                }
    //-- Деструктор
    ~TClub(void);

    //--Проверка объекта
    //@return true - если объект допустим, false - если объект не валидный
    bool valid(AnsiString &errmess);

    //-- Сохранение объекта в базе данных
    void store(void);
    //-- Чтение всех объектов из базы данных
    //@return Массив объектов, прочитанных из базы данных,
    //  или null, если объектов в базе не найдено
    static TList* getAll(void);

    //-- Вернуть текущий для таблицы объект
    static TClub getCurrent(void);
    //-- Установить запись как текущую в таблице
    void makeCurrent(void);      
    

    //-- Загрузить объект из хранилища
    //@param id идентификатор записи, которую загрузить
    static TClub getById(int id); 

    //-- методы получения и сохранения свойств объекта
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    AnsiString getName(void){return asName;}
    void setName(AnsiString asInName){asName = asInName;}
    AnsiString getShortName(void){return asShortName;}
    void setShortName(AnsiString asInShortName){asShortName = asInShortName;}
    AnsiString getCity(void){return asCity;}
    void setCity(AnsiString asInCity){asCity = asInCity;}
    AnsiString getCountry(void){return asCountry;}
    void setCountry(AnsiString asInCountry){asCountry = asInCountry;}
    int getPersonId(void){return personId;} 
    void setPersonId(int inPersonId){personId = inPersonId;}
    AnsiString getComments(void){return asComments;}
    void setComments(AnsiString asInComments){asComments = asInComments;}


    //Установка функции обратного вызова для сдвинутой записи
    static void setRecordMoveCallback(CallbackFunction cbf);
  
};



//---------------------------------------------------------------------------
#endif
