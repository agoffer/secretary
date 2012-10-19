//---------------------------------------------------------------------------

#ifndef competitorCtrlH
#define competitorCtrlH


#include "personCtrl.h"
#include "requestCtrl.h"
#include "fightVersionCtrl.h"
#include "skillCtrl.h"
#include "resultCtrl.h"

//****************************************//
// Класс представлющий объекты
// "Участник соревнования"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 6.12.05
//****************************************//

class TCompetitor{
private:
    //Идентификатор
    int id;
    //Идентификатор уровня мастерства
    int skillId;
    //Идентификатор персоны представляющей участника
    int personId;
    //Идентификатор заявки в которой подается участник
    int requestId;
    //Вес участника
    double weight;
    //Номер в жеребьевке
    int sortion;


    //--Расширенные поля
    bool extended;
    TRequest request;
    TPerson person;
    TSkill skill;



// Интерфейс объекта //
public:

    //--Результат учатсника соревнования
    TResult result;

    //-- Конструктор
    //@param personId - идентификатор персоны участника
    //@param skillId - идентификатор уровня мастерства участника
    //@param requestId - Идентификатор заявки подающей участника
    //@param weight - вес участника
    TCompetitor(int inPersonId, int inSkillId,
             int inRequestId, double weight);
    //-- Конструктор по умолчанию
    TCompetitor(void){ personId = 0; skillId = 0;
                    requestId = 0; weight = 0;
                    id = 0;
                    //Изначально объект не расширен
                    extended = false;
                    skill.setId(0);
                    person.setId(0);
                    request.setId(0); 
                    }
    //-- Деструктор
    ~TCompetitor(void);

    //--Проверка объекта
    //@return true - если объект допустим, false - если объект не валидный
    bool valid(AnsiString &errmess);

    //-- Сохранение объекта в базе данных
    void store(void);
    //-- Удалить запись из базы данных
    void erase(void); 

    //-- Чтение всех объектов из базы данных
    //@return Массив объектов, прочитанных из базы данных,
    //  или null, если объектов в базе не найдено
    static TList* getAll(void);


    //-- Получить список участников по определенной заявке 
    //@param requestId идентификатор заявки, для которой получаем участников
    //@param &reccount [out] - сколько записей было получено  
    //@return список участников определенных заявкой
    static TList* getByRequestId(int requestId);

    //-- Получить список участников для заданных соревнований 
    //@param competitionId идентификатор соревнования, для которой получаем участников
    //@param &reccount [out] - сколько записей было получено
    //@return список участников определенных заявкой
    static TList* getByCompetitionId(int competitionId);

    //-- Получить список участников c расширенными полями для заданных соревнований
    //@param competitionId идентификатор соревнования, для которой получаем участников
    //@param &reccount [out] - сколько записей было получено
    //@return список участников определенных заявкой
    static TList* getExtendedByCompetitionId(int competitionId);

    //-- Получить спиоск участников соревнования (по идентификатору), с расширенными полями
    // не попавшими ни в одну созданную категорию
    //@param competitionId идентификатор соревнования, для которой получаем участников
    //@param &reccount [out] - сколько записей было получено
    //@return список участников
    static TList* getExtendedUncategoryByCompetitionId(int competitionId, bool female);


    //-- Получить список участников по заявке, в расширенной форме (получаем персону, заявку и уровень мастерства)
    //@param requestId идентификатор заявки, для которой получаем участников
    //@param &reccount [out] - сколько записей было получено
    //@return список участников по заявке
    static TList* getExtendedByRequestId(int requestId);

    //-- Получить список участников в категории, в расширенной форме
    //@param categoryId идентификатор категории,  для которой получаем участников
    //@param &reccount [out] - сколько записей было получено
    //@return список участников в категории
    static TList* getExtendedByCategoryId(int categoryId);

    //-- Вернуть текущий для таблицы объект
    static TCompetitor getCurrent(void);
    //-- Установить запись как текущую в таблице
    void makeCurrent(void);

    //-- Вернуть текущий для таблицы объект
    static TCompetitor getExtendedTableCurrent(void);
    //-- Установить запись как текущую в таблице
    void makeExtendedTableCurrent(void);


    //-- Загрузить объект из хранилища
    //@param id идентификатор записи, которую загрузить
    void getById(int id);

    //-- Устанавливает боевые версии для участника
    //@param ids - идентификаторы боевых версий
    void setFightVersion(int *ids, int count);
    //-- Получить список боевых версий для участника
    TList* getFightVersion(void);
    //-- Получить список нераспределенных боевых версий для участника
    TList* getUncategoryFightVersion(void);
    //-- Получить список добавленных участнику боевых категорий 
    TList* getExtendedFightVersion(void);



    //-- Удалить боевые версии для участника из базы
    void eraseFightVersion(void);

    //-- Определяем, был ли объект расширен
    bool isExtended(void){return extended;}

    //-- методы получения и сохранения свойств объекта
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    int getSkillId(void){return skillId;}
    void setSkillId(int inSkillId){skillId = inSkillId;}
    int getRequestId(void){return requestId;}
    void setRequestId(int inRequestId){requestId = inRequestId;}
    int getPersonId(void){return personId;}
    void setPersonId(int inPersonId){personId = inPersonId;}
    double getWeight(void){return weight;}
    void setWeight(double inWeight){weight = inWeight;}
    int getSortion(void){return sortion;}
    void setSortion(int inSortion){sortion = inSortion;}

    //Методы чтения и сохранения результата
    void loadResult(void);
    void storeResult(void);
    //Методы чтения и сохранения результатов в указанной категории 
    void loadResult(int categoryId);
    void storeResult(int categoryId);

    //-- Методы возвращающие расширенные поля
    TSkill getSkill(void){return skill;}
    TPerson  getPerson(void){return person;}
    TRequest getRequest(void){return request;}
    //-- Расширить объект подобъектами
    void extend(TPerson inPerson, TSkill inSkill, TRequest inRequest);

     //Установка функции обратного вызова для сдвинутой записи
    static void setRecordMoveCallback(CallbackFunction cbf);    
};                                                                  





//---------------------------------------------------------------------------
#endif
