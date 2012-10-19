//---------------------------------------------------------------------------

#ifndef categoryCtrlH
#define categoryCtrlH

#include "availCategoryCtrl.h"
#include "fightVersionCtrl.h"
#include "competitionCtrl.h"
#include "competitorCtrl.h"

//****************************************//
// Класс представлющий объекты
// "Категория"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 09.01.06
//****************************************//


//Тип жеребьевки участников 
const DT_AUTO = 'A';    // Автоматическая жеребьевка участников
const DT_MANUAL = 'M';  // Ручная жеребьевка участников


//Структура используемая для проведения жеребьевки 
typedef struct{
    int  competitorId;
    int  skillWeight;   //Весовой коэффициент уровня мастерства
    int  clubId;
    bool onTree;        //Признак того, что участник уже распределен в дереве
}TSortionData;


class TCategory{
private:
    //Идентификатор
    int id;
    //Идентификатор доступной категории
    int availCategoryId;
    //Идентификатор боевой версии
    int fightVersionId;
    //Идентификатор соревнования
    int competitionId;

    //-- Расширенные поля
    bool extended;
    TAvailCategory availCategory;
    TFightVersion fightVersion;
    TCompetition competition;

// Интерфейс объекта //

public:


    //-- Конструктор
    //@param inAvailCategoryId - Идентификатор доступной категории
    //@param inFightVersionId - Идентификатор боевой версии
    //@param inCompetitionId - Идентификатор соревноваия
    TCategory(int inAvailCategoryId, int inFightVersionId, int inCompetitionId);
    //-- Конструктор по умолчанию
    TCategory(void){ availCategoryId = 0; fightVersionId = 0; competitionId = 0; }
    //-- Деструктор
    ~TCategory(void);

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
    static TCategory getCurrent(void);
    //-- Установить запись как текущую в таблице
    void makeCurrent(void);

    //-- Загрузить объект из хранилища
    //@param id идентификатор записи, которую загрузить
    void getById(int id);

    //-- Добавить участника в категорию
    void addCompetitor(TCompetitor inCompetitor);

    //-- Добавить участников в категорию 
    void setCompetitors(TList *ids);

    //-- Удалить участников из категории 
    void eraseCompetitors(TList *ids);    

    //-- Вернуть все категории (в расширенной форме), для текущих соревнований
    static TList* getExtendedByCompetitionId(int competitionId);

    //-- Вернуть все категории (в расширенной форме), для текущих соревнований,
    //-- в которых присутствует участник с фамилией : surname
    static TList* getExtendedByCompetitionIdSurname(int competitionId, AnsiString surname);

    // Функция проверки принадлежности участника (в боевой версии) уже
    // созданным категориям.
    // @param competitor - участник
    // @param fightVersion - версия в которой хочет участвовать участник
    // @param competition - соревнования в которых участвует участник
    // @return true - если найдена уже существующая категория, и туда помещен
    // участник. В противном случае false
    static bool putInCreatedCategory(TCompetitor competitor, TFightVersion fightVersion, TCompetition competition);
    //Функция пытается поместить участника в доступную категорию
    //@return если категория создана, то присваивается идентификатор не равный нулю
    void putInAvailCategory(TCompetitor competitor, TFightVersion fightVersion, TCompetition competition);     


    //-- методы получения и сохранения свойств объекта
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    int getAvailCategoryId(void){return availCategoryId;}
    void setAvailCategoryId(int inAvailCategoryId){availCategoryId = inAvailCategoryId;}
    int getFightVersionId(void){return fightVersionId;}
    void setFightVersionId(int inFightVersionId){fightVersionId = inFightVersionId;}
    int getCompetitionId(void){return competitionId;}
    void setCompetitionId(int inCompetitionId){competitionId = inCompetitionId;}

    //-- Определяется, выполнена ли жеребьевка для категории и какая ? 
    void setDrawType(char drawType);
    char getDrawType(void);


    //-- Определяем, был ли объект расширен
    bool isExtended(void){return extended;}

    //-- Получение расширенных полей
    TAvailCategory getAvailCategory(void){return availCategory;}
    TFightVersion getFightVersion(void){return fightVersion;}
    TCompetition getCompetition(void){return competition;}

    //-- Заполнение объекта расширенными полями
    void extend(void);
    void extend(TAvailCategory inAvailCategory, TFightVersion inFightVersion, TCompetition inCompetition);


    //-- Функции отвечающие за распределение участников по категориям --//

    //-- Проверить, есть ли уже распределение для соревнований
    static bool checkForDistribution(TCompetition competition);
    //-- Распределить участников по категориям, для данного соревнования
    static void destributeCompetitors(TCompetition competition);
    //-- Распределить участников по категориям для заявки 
    static void destributeCompetitors(TRequest request, TCompetition competition);
    //-- Определить участника в категорию
    static void destributeCompetitor(TCompetitor competitor, TCompetition competition);
    //-- Определить заданный список участников в категории 
    static void destributeCompetitors(TList *competitorsList, TCompetition competition);
    //-- Удалить все категории для соревнований 
    static void deleteCategoriesByCompetition(TCompetition competition);

    //-- Выполнить жеребьевку категории 
    void sortitionCategory(void);

    //-- Вернуть количество участников в категории
    int getCompetitorsAmount(void);

    //-- Вынести участника из всех категорий 
    static void uncategory(int competitorId);
};

//-- Функция сравнения двух жеребьевочных объектов по клубу
int __fastcall sortionCompareClub(void *fstItem, void *secItem);

//-- Функция сравнения двух уровней мастерства
int __fastcall sortionCompareSkill(void *fstItem, void *secItem);

//-- Функция сравнения по клубу и уровню 
int __fastcall sortionCompareClubSkill(void *fstItem, void *secItem);

//-- Найти индексы для проверки пар 
void getCriticalPairsIndexes(int &bottomIndex, int &topIndex, int dataAmnt);

//-- Поиск несовпадающиего клуба  
int searchAnotherClub(TList * branch, int startpos, int dataAmnt);


//-- Функция сравнения по весовой, возрастной и женской категории   
extern int __fastcall compareCategories(void *fstItem, void *secItem);





//---------------------------------------------------------------------------
#endif
