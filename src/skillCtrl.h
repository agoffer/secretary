//---------------------------------------------------------------------------

#ifndef skillCtrlH
#define skillCtrlH

#include<vcl.h>

//****************************************//
// Класс представлющий объекты
// "Уровень мастерства"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 4.12.05
//****************************************//


class TSkill{
private:
    //Идентификатор
    int id;
    //Короткое описание уровня
    AnsiString asShortDescription;
    //Полное описание уровня
    AnsiString asFullDescription;
    //Комментарии
    AnsiString asComments;
    //Весовой коэффициент уровня
    int weight;
// Интерфейс объекта //
public:


    //-- Конструктор
    //@param asShortDescription - короткое описание уровня
    //@param asFullDescription - полное описание
    //@param asComments - комментарии
    //@param weight - весовой коэффициент уровня
    TSkill(AnsiString asInShortDescription, AnsiString asInFullDescription, AnsiString asInComments,
            int inWeight);
    //-- Конструктор по умолчанию
    TSkill(void){asShortDescription=""; asFullDescription=""; asComments=""; weight=0; id=0;}
    //-- Деструктор
    ~TSkill(void);

    //--Проверка объекта
    //@return true - если объект допустим, false - если объект не валидный
    bool valid(AnsiString &errmess); 

    //-- Сохранение объекта в базе данных
    void store(void);
    //-- Чтение всех объектов из базы данных
    //@return Массив объектов, прочитанных из базы данных,
    //  или null, если объектов в базе не найдено 
    static TList* getAll(void);

    //-- Получить уровень мастерства по идентификатору
    //@param id Идентификтор уровня, который надо получить
    void getById(int id); 

    //-- методы получения и сохранения свойств объекта
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    int getWeight(void){return weight;}
    void setWeight(int inWeight){weight = inWeight;}
    AnsiString getShortDescription(void){return asShortDescription;}
    void setShortDescription(AnsiString asInShortDescription){asShortDescription = asInShortDescription;}
    AnsiString getFullDescription(void){return asFullDescription;}
    void setFullDescription(AnsiString asInFullDescription){asFullDescription = asInFullDescription;}

    AnsiString getComments(void){return asComments;}
    void setComments(AnsiString asInComments){asComments = asInComments;}
};


//---------------------------------------------------------------------------
#endif
