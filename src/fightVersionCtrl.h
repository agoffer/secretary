//---------------------------------------------------------------------------

#ifndef fightVersionCtrlH
#define fightVersionCtrlH

#include<vcl.h>

//****************************************//
// Класс представлющий объекты
// "Боевая версия"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 4.12.05
//****************************************//


class TFightVersion{
private:
    //Идентификатор
    int id;
    //Код боевой версии
    AnsiString asCode;
    //Описание, полное название версии 
    AnsiString asDescription;
    //Комментарии
    AnsiString asComments;


    //Для определенных участникам версий признак распределения в категории 
    bool destributed;

// Интерфейс объекта //
public:


    //-- Конструктор
    //@param asCode - код боевой версии 
    //@param asDescription - описание статуса соревнований
    //@param asComments - комментарии
    TFightVersion(AnsiString asCode, AnsiString asInDescription, AnsiString asInComments);
    //-- Конструктор по умолчанию 
    TFightVersion(void){asCode=""; asDescription=""; asComments=""; id=0; destributed=false;}
    //-- Деструктор
    ~TFightVersion(void);

    //--Проверка объекта
    //@return true - если объект допустим, false - если объект не валидный
    bool valid(AnsiString &errmess);

    //-- Сохранение объекта в базе данных
    void store(void);
    //-- Чтение всех объектов из базы данных
    //@return Массив объектов, прочитанных из базы данных,
    //  или null, если объектов в базе не найдено
    static TList* getAll(void);

    //-- Получить боевую версию  по идентификатору
    //@param id Идентификтор статуса, который надо получить
    void getById(int id);

    //-- методы получения и сохранения свойств объекта
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    void setCode(AnsiString asInCode){asCode = asInCode;}
    AnsiString getCode(void){return asCode;}
    AnsiString getDescription(void){return asDescription;}
    void setDescription(AnsiString asInDescription){asDescription = asInDescription;}
    AnsiString getComments(void){return asComments;}
    void setComments(AnsiString asInComments){asComments = asInComments;}

    //-- Для признака распределенности версии в категории
    bool getDestributed(void){return destributed;}
    void setDestributed(bool inDestributed){destributed = inDestributed;}
};




//---------------------------------------------------------------------------
#endif
