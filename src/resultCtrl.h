//---------------------------------------------------------------------------

#ifndef ResultCtrlH
#define ResultCtrlH

#include <vcl.h>

#include "utils.h"
#include <map.h>


//****************************************//
// Класс представлющий объекты
// "Результат участника"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 12.06.06
//****************************************//

class TResult{
private:
    //Результаты по разделам //

    //Кросс
    AnsiString crossTime;   //Формат времени H:MM:SS.dd
    //Стрельба
    int shootScore;
    int shootRank;
    //Рукопашный бой с холодным оружием
    int fightWKnifeScore;
    int fightWKnifeRank;
    //Рукопашный бой без холодного оружия
    int fightWOKnifeScore;
    int fightWOKnifeRank;

    //Общий результат соревнований для участника в категории 
    int commonRank;

    //Для случая, когда результат получен в зависимости от категории
    int categoryId;

    // Интерфейс объекта //
public:
    //-- Конструктор
    TResult(void){
        crossTime = "00:00.00";
        commonRank = 0;
        shootScore = -1;
        shootRank = 0;
        fightWKnifeScore = -1;
        fightWKnifeRank = 0;
        fightWOKnifeScore = -1;
        fightWOKnifeRank = 0;

        categoryId = 0; 
    }
    //-- Деструктор
    ~TResult(void);
    //--Проверка объекта
    //@return true - если объект допустим, false - если объект не валидный
    bool valid(AnsiString &errmess);

    //-- Чтение результатов для участника из базы данных
    void getResults(int competitorId);
    //-- Сохранения результатов в базе данных
    void setResults(int competitorId);

    //-- Чтение результатов для участника из базы данных, по категории
    void getResults(int competitorId, int categoryId);
    //-- Сохранения результатов в базе данных
    void setResults(int competitorId, int categoryId);

    //-- Вернуть текущий для таблицы участников с результатами объект
    static int getCurrentCompetitorId(void);
    static void setCurrentCompetitorById(int competitorId);

    //-- Получить шкалу балов для соревнований 
    static void getScoreRanking(map<int, int> & scoreRank, int competitionRank);


    //Кросс
    AnsiString getCrossTime(void){return crossTime;}
    void setCrossTime(AnsiString inCrossTime){crossTime = inCrossTime;}
    //Стрельба
    int getShootScore(void){return shootScore;}
    void setShootScore(int inShootScore){shootScore = inShootScore;}
    int getShootRank(void){return shootRank;}
    void setShootRank(int inShootRank){shootRank = inShootRank;}
    //Рукопашный бой с холодным оружием
    int getFightWKnifeScore(void){return fightWKnifeScore;}
    void setFightWKnifeScore(int inFightWKnifeScore){fightWKnifeScore = inFightWKnifeScore;}
    int getFightWKnifeRank(void){return fightWKnifeRank;}
    void setFightWKnifeRank(int inFightWKnifeRank){fightWKnifeRank = inFightWKnifeRank;}
    //Рукопашный бой без холодного оружия
    int getFightWOKnifeScore(void){return fightWOKnifeScore;}
    void setFightWOKnifeScore(int inFightWOKnifeScore){fightWOKnifeScore = inFightWOKnifeScore;}
    int getFightWOKnifeRank(void){return fightWOKnifeRank;}
    void setFightWOKnifeRank(int inFightWOKnifeRank){fightWOKnifeRank = inFightWOKnifeRank;}
    //Получить категорию, для которой хранятся результаты
    int getCategoryId(void){return categoryId;}

    //Общий результат соревнований, для участника в категории 
    int getCommonRank(void){return commonRank;}
    void setCommonRank(int inCommonRank){commonRank = inCommonRank;}

     //Установка функции обратного вызова для сдвинутой записи
    static void setRecordMoveCallback(CallbackFunction cbf);
};


//---------------------------------------------------------------------------
#endif
