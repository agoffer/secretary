//---------------------------------------------------------------------------

#ifndef CurrentStateDMH
#define CurrentStateDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "competitionCtrl.h"
#include "fightVersionCtrl.h"
#include "skillCtrl.h"
#include "requestCtrl.h"
#include "categoryCtrl.h"
#include "availCategoryCtrl.h"
#include "competitorCtrl.h"
#include "resultCtrl.h"

#include <map.h>
//---------------------------------------------------------------------------
class TdmCurrentState : public TDataModule
{
__published:	// IDE-managed Components
private:	// User declarations
    //-- Текущие соревнования, с которыми выполняется работа
    TCompetition Competition;

    //-- Текущий персоналий
    TPerson Person;

    //-- Текущий клуб
    TClub Club;

    //-- Текущая заявка 
    TRequest Request;

    //-- Текущая доступная категория
    TAvailCategory AvailCategory;

    //-- Текущая боевая версия 
    TFightVersion FightVersion;

    //--Список боевых версий
    TList* fightVersionList;
    //-- Индексированный по идетификатору список боевых версий
    map<int, TFightVersion*> fightVersionMap;

    //-- Шкала балов за места на соревновании 
    map<int, int> scoreRanking;

    //--Список уровней мастерства
    TList* skillList;
    //-- Индексированный по идетификатору список уровней мастерства
    map<int, TSkill*> skillMap;

    //-- Список всех заявок по соревнованию
    TList *requestList;
    //-- Индексированный по идетификатору список заявок 
    map<int, TRequest*> requestMap;

    //Список доступных категорий
    TList *allAvailCategoryList;
    //-- Индексированный по идетификатору список доступных категорий  
    map<int, TAvailCategory*> availCategoryMap;
    TList *femaleAvailCategoryList;
    TList *maleAvailCategoryList;

    //-- Список всех категорий, созданных на соревновании
    TList *categoryList;
    //-- Индексированный по идетификатору список категорий на соревновании 
    map<int, TCategory*> categoryMap;
    TList *femaleCategoryList;
    TList *maleCategoryList; 

    //-- Список участников не попавших ни в одну категорию
    TList *femaleUncategoryCompetitorList;
    TList *maleUncategoryCompetitorList;

    //-- Получить список уровней мастерства
    void createSkillList(void);

    //-- Получить список боевых версий
    void createFightVersionList(void);

    //-- Получить список уровней мастерства
    void createAvailCategoryList(void);

    //-- Получить список заявок по соревонованию
    void createRequestList(TCompetition competition);

    //Создать шкалу балов за соревнования
    void createScoreRankMap(int competitionRank);    




public:		// User declarations
    __fastcall TdmCurrentState(TComponent* Owner);
    __fastcall ~TdmCurrentState(void);

    //-- Получить список категорий по соревонованию
    void createCategoryList(TCompetition competition);
    //-- Установить текущие соревнования
    void setCompetition(TCompetition competition);
    //-- Получить текущии соревнования
    TCompetition& getCompetition(void){return Competition;}
    //-- Установить текущего персоналия
    void setPerson(TPerson person){Person = person;}
    //-- Получить текущего персоналия
    TPerson& getPerson(void){return Person;}
    //-- Установить текущий клуб
    void setClub(TClub club){Club = club;}
    //-- Получить текущий клуб
    TClub& getClub(void){return Club;}
    //-- Установить текущую доступную версию
    void setAvailCategory(TAvailCategory availCategory){AvailCategory = availCategory;}
    //-- Получить текущую доступную версию 
    TAvailCategory& getAvailCategory(void){return AvailCategory;}
    //-- Установить текущую боевую версию
    void setFightVersion(TFightVersion fightVersion){FightVersion = fightVersion;}
    //-- Получить текущую боеву версию 
    TFightVersion& getFightVersion(void){return FightVersion;}
    //-- Установить текущую заявку
    void setRequest(TRequest request){Request = request;}
    //-- Получить текущую заявку
    TRequest& getRequest(void){return Request;}

    //-- Вернуть список боевых версий
    TList* getFightVersionList(void){if(fightVersionList->Count <= 0)createFightVersionList();return fightVersionList;}
    //-- Добавить боевую версию к уже сформированному списку
    void addFightVersionToList(TFightVersion fightVersion);
    //-- Найти боевую версию по короткому наименованию
    TFightVersion findFightVersionByCode(AnsiString code);

    //-- Вернуть список боевых версий
    TList* getSkillList(void){if(skillList->Count <= 0)createSkillList(); return skillList;}
    //-- Добавить уровень мастерства к уже сформированному списку
    void addSkillToList(TSkill skill);

    //-- Добавить заявку к уже сформированному списку
    void addRequestToList(TRequest request);
    //-- Получить список заявок
    TList* getRequestList(void){return requestList;}
    //-- Получить заявку по идентификатору
    TRequest *getRequestById(int requestId);

    //-- Добавить категорию к уже сформированному списку
    void addCategoryToList(TCategory category);

    //-- Получить список категорий
    TList* getCategoryList(void){return categoryList;}
    TList* getFemaleCategoryList(void){return femaleCategoryList;}
    TList* getMaleCategoryList(void){return maleCategoryList;}
    //-- Вернуть категорию по заданному идентификаторому
    TCategory *getCategoryById(int categoryId);


    //-- Вернуть список всех доступных категорий
    TList* getAllAvailCategoryList(void){if(allAvailCategoryList->Count <= 0)
                                            createAvailCategoryList();
                                            return allAvailCategoryList;}
    //-- Вернуть список мужских  доступных категорий
    TList* getMaleAvailCategoryList(void){if(maleAvailCategoryList->Count <= 0)
                                            createAvailCategoryList();
                                            return maleAvailCategoryList;}
    //-- Вернуть список женских  доступных категорий
    TList* getFemaleAvailCategoryList(void){if(femaleAvailCategoryList->Count <= 0)
                                            createAvailCategoryList();
                                            return femaleAvailCategoryList;}
    //-- Добавить доступную категорию в список
    void addAvailCategoryToList(TAvailCategory inAvailCategory);

    //-- Получить список участников соревнования не попавших в категорию
    TList* getUncategoryCompetitorList(bool female){return female?femaleUncategoryCompetitorList :
                                                                  maleUncategoryCompetitorList;}
    //-- Добавить участника к списку не попавших ни в одну категорию
    void addUncategoryCompetitorToList(TCompetitor competitor, bool female);
    //-- Создать список участников не распределенных по категориям
    void createUncategoryCompetitorList(TCompetition competition);

    //Вернуть количество балов, определяемых местом
    int getScoreForRank(int rank);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmCurrentState *dmCurrentState;
//---------------------------------------------------------------------------
#endif
