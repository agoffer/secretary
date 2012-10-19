//---------------------------------------------------------------------------

#ifndef availCategoryCtrlH
#define availCategoryCtrlH

#include<vcl.h>

#include "competitionCtrl.h"
#include "competitorCtrl.h"
#include "fightVersionCtrl.h"



//****************************************//
// Класс представлющий объекты
// "Доступные категории"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 5.01.06
//****************************************//



class TAvailCategory{
private:
    //Идентификатор
    int id;
    //Начальный возрас в категории
    int startAge;
    //Конечный возраст в категории
    int endAge;
    //Начальный вес в категории
    double startWeight;
    //Конечный вес в категории
    double endWeight;
    //Пол категории
    bool female;  
    //Комментарии
    AnsiString asComments;

// Интерфейс объекта //
public:


    //-- Конструктор
    //@param startAge - начальный возраст
    //@param endAge - конечный возраст
    //@param startWeight - начальный вес
    //@param endWeight - конечный вес
    //@param female - пол
    //@param asComments - комментарии
    TAvailCategory(int inStartAge, int inEndAge, double inStartWeight, double inEndWeight,
                    bool inFemale, AnsiString asInComments);
    //-- Конструктор по умолчанию
    TAvailCategory(void){startAge = 0; endAge = 100; startWeight = 0;
                         endWeight = 500.0; female = false; asComments = ""; id =0;}
    //-- Деструктор
    ~TAvailCategory(void);

    //--Проверка объекта
    //@return true - если объект допустим, false - если объект не валидный
    bool valid(AnsiString &errmess);

    //-- Сохранение объекта в базе данных
    void store(void);

    //-- Удаление объекта в базе данных
    void remove(void);

    //-- Чтение всех объектов из базы данных
    //@return Массив объектов, прочитанных из базы данных,
    //  или null, если объектов в базе не найдено
    static TList* getAll(void);

    //-- Получить уровень мастерства по идентификатору
    //@param id Идентификтор уровня, который надо получить
    void getById(int id);

    //-- Получить текущую доступную категорию в таблице
    static TAvailCategory getCurrent(void);
    //-- Установить текущую категорию 
    void TAvailCategory::makeCurrent(void);



    // функция проверяет возможную принадлежность участника доступрным категориям
    // @param competitor - участник
    // @param fightVersion - версия в которой будет участвовать участник
    // @return категория в которую попал участник. null - если для участника небыла
    // найдена категория
    static int checkForAvailCategory(TCompetitor competitor);
    static int checkForAvailCategory(int age, double weight, bool female);      

    //-- методы получения и сохранения свойств объекта
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    int getStartAge(void){return startAge;}
    void setStartAge(int inStartAge){startAge = inStartAge;}
    int getStartWeight(void){return startWeight;}
    void setStartWeight(int inStartWeight){startWeight = inStartWeight;}
    int getEndAge(void){return endAge;}
    void setEndAge(int inEndAge){endAge = inEndAge;}
    int getEndWeight(void){return endWeight;}
    void setEndWeight(int inEndWeight){endWeight = inEndWeight;}
    bool getFemale(void){return female;}
    void setFemale(bool inFemale){female = inFemale;}
    AnsiString getComments(void){return asComments;}
    void setComments(AnsiString asInComments){asComments = asInComments;}
};


//---------------------------------------------------------------------------
#endif
