//---------------------------------------------------------------------------
#ifndef competitionCtrlH
#define competitionCtrlH

#include "competitionRankCtrl.h"

#include <vcl.h>

//****************************************//
// Класс представлющий объекты
// "Соревнования"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 24.11.05
//****************************************//

class TCompetition{
private:
    //Идентификатор
    int id;
    //Дата начала соревнований
    TDate beginDate;
    //Дата окончания соревнований
    TDate endDate;  
    //Комментарии
    AnsiString asComments;
    //Идентификатор статуса соревнований
    int competitionRankId;

    //Поля расширения
    bool extended; 
    TCompetitionRank competitionRank; 
    
// Интерфейс объекта //
public:


    //-- Конструктор
    //@param inBeginDate - дата начала проведения соревнований
    //@param inEndDate - дата окончания проведения соревнований
    //@param inCompetitionRankId - идент. статуса соревнований
    //@param asInComments - комментарии  
    TCompetition(TDate inBeginDate, TDate inEndDate,
                int inCompetitionRankId, AnsiString asInComments);
    //-- Конструктор по умолчанию
    TCompetition(void){ beginDate = Now();
                            endDate = Now();
                            competitionRankId = 0;
                            asComments = "";
                            id = 0;
                            extended = false; 
                            }
    //-- Деструктор
    ~TCompetition(void);

    //--Проверка объекта
    //@return true - если объект допустим, false - если объект не валидный
    bool valid(AnsiString &errmess);

    //-- Сохранение объекта в базе данных
    void store(void);
    //-- Чтение всех объектов из базы данных
    //@return Массив объектов, прочитанных из базы данных,
    //  или null, если объектов в базе не найдено
    static TList* getAll(void);

    //-- Загрузить объект из хранилища
    //@param id идентификатор записи, которую загрузить
    void getById(int id);

    //-- Получить текущее соревнование из расширенной таблицы
    static TCompetition getExtendedCurrent(void);  

    

    //-- Получить максимальную и минимальную дату начала соревнований
    //@param minBeginDate - минимальная дата начала соревнования
    //@param maxBeginDate - максимальная дата начала соревнования
    static void getMinMaxBeginDate(TDateTime &minBeginDate, TDateTime &maxBeginDate);

    //-- Получить максимальную и минимальную дату окончания соревнований
    //@param minEndDate - минимальная дата окончания соревнования
    //@param maxEndDate - максимальная дата окончания соревнования
    static void getMinMaxEndDate(TDateTime &minBeginDate, TDateTime &maxBeginDate);

    //-- методы получения и сохранения свойств объекта
    int getId(void);
    void setId(int inId);
    TDate getBeginDate(void);
    void setBeginDate(TDate inBeginDate);
    TDate getEndDate(void);
    void setEndDate(TDate inEndDate);
    int getCompetitionRankId(void);
    void setCompetitionRankId(int inCompetitionRankId);
    AnsiString getComments(void);
    void setComments(AnsiString asInComments);

    //-- Определяем, был ли объект расширен
    bool isExtended(void){return extended;}
    //-- Методы возвращающие расширенные поля
    TCompetitionRank getCompetitionRank(void){return competitionRank;}
    //-- Расширить объект подобъектами
    void extend(TCompetitionRank inCompetitionRank){competitionRank = inCompetitionRank; extended = true;};
};



//---------------------------------------------------------------------------
#endif
