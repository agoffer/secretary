//---------------------------------------------------------------------------

#ifndef personCtrlH
#define personCtrlH

#include <vcl.h>

#include "utils.h"

//****************************************//
// Класс представлющий объекты
// "Субъект"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 26.11.05
//****************************************//

class TPerson{
private:
    //Идентификатор
    int id;
    //Фамилия субъекта
    AnsiString asSurname;
    //Имя субъекта
    AnsiString asName;
    //Отчество субъекта
    AnsiString asPatronymic;    
    //Дата рождения субъекта
    TDate dob;
    //Контактный телефон субъекта
    AnsiString asPhone;
    //Признак того, что персона женского пола
    bool female; 
    //Дополнительная информация 
    AnsiString asAdditions;

    
// Интерфейс объекта //
public:


    //-- Конструктор
    //@param asSurname - Фамилия субъекта
    //@param asName - имя субъекта
    //@param asPatronymic - отчество субъекта
    //@param dob - Дата рождения субъекта
    //@param asPhone - телефон субъекта
    //@param asAdditions - дополнительная информация   
    TPerson(AnsiString asInSurname, AnsiString asInName,
            AnsiString asInPatronymic, TDateTime inDob,
            AnsiString asInPhone, bool inFemale, AnsiString asInAdditions);
    //-- Конструктор по умолчанию
    TPerson(void){ asSurname = ""; asName = ""; asPatronymic = "";
                    dob = Now(); asPhone = ""; asAdditions = "";
                    female = false;
                    id = 0;
                }
    //-- Деструктор
    ~TPerson(void);

    //--Проверка объекта
    //@return true - если объект допустим, false - если объект не валидный
    bool valid(AnsiString &errmess);

    //-- Сохранение объекта в базе данных
    void store(void);
    //-- Чтение всех объектов из базы данных
    //@return Массив объектов, прочитанных из базы данных,
    //  или null, если объектов в базе не найдено
    static TPerson* getAll(int &reccount);

    //-- Вернуть текущий для таблицы объект
    static TPerson getCurrent(void);

    //-- Удалить текущую запись в таблице  
    static bool deleteCurrent(void);

    //-- Установить запись как текущую в таблице
    void makeCurrent(void);
    static void makeCurrent(int id);      

    //-- Загрузить объект из хранилища
    //@param id идентификатор записи, которую загрузить
    void getById(int id);

    //-- Проверить, есть ли персона с задаными (фамилия, имя отчество) в базе
    // обновить поля, если есть такая персона
    // @return true если такая персона найдена
    bool likeAs(void);     

    //-- методы получения и сохранения свойств объекта
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    AnsiString getSurname(void){return asSurname;}
    void setSurname(AnsiString asInSurname){asSurname = asInSurname;}
    AnsiString getName(void){return asName;}
    void setName(AnsiString asInName){asName = asInName;}
    AnsiString getPatronymic(void){return asPatronymic;}
    void setPatronymic(AnsiString asInPatronymic){asPatronymic = asInPatronymic;}
    TDate getDob(void){return dob;}
    void setDob(TDate inDob){dob = inDob;}
    bool getFemale(void){return female;}
    void setFemale(bool inFemale){female = inFemale;} 
    AnsiString getAdditions(void){return asAdditions;}
    void setAdditions(AnsiString asInAdditions){asAdditions = asInAdditions;}
    AnsiString getPhone(void){return asPhone;}
    void setPhone(AnsiString asInPhone){asPhone = asInPhone;}


     //Установка функции обратного вызова для сдвинутой записи
    static void setRecordMoveCallback(CallbackFunction cbf);
     
};



//---------------------------------------------------------------------------
#endif
