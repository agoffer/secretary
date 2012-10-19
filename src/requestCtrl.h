//---------------------------------------------------------------------------

#ifndef requestCtrlH
#define requestCtrlH

#include <vcl.h>

#include "clubCtrl.h"
#include "personCtrl.h"


//****************************************//
// Класс представлющий объекты
// "Заявка"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 30.11.05
//****************************************//

class TRequest{
private:
    //Идентификатор
    int id;
    //Идентификатор соревнования 
    int competitionId;
    //Идентификатор клуба, подающего заявку
    int clubId;
    //Идентификатор представителя клуба 
    int personId;
    //Комментарии и дополнительная информация
    AnsiString asComments;


    //--Расширенные поля
    bool extended; 
    TClub club;
    TPerson person; 

    
// Интерфейс объекта //
public:


    //-- Конструктор
    //@param competitionId - идентификатор соревнования 
    //@param clubId - идентификатор клуба
    //@param personId - Идентификатор представителя клуба
    //@param asComments - дополнительная информация
    TRequest(int inCompetitionId, int inClubId,
             int inPersonId, AnsiString asIComments);
    //-- Конструктор по умолчанию
    TRequest(void){ competitionId = 0; clubId = 0;
                    personId = 0; asComments = "";
                    id = 0;
                }
    //-- Деструктор
    ~TRequest(void);

    //--Проверка объекта
    //@return true - если объект допустим, false - если объект не валидный
    bool valid(AnsiString &errmess);

    //-- Сохранение объекта в базе данных
    void store(void);
    //-- Чтение всех объектов из базы данных
    //@return Массив объектов, прочитанных из базы данных,
    //  или null, если объектов в базе не найдено
    static TList* getAll(void);

    //--- Удалить
    static void deleteById(int requestId);


    //-- Получить список заявок на участия в определенных соревнованиях
    //@param competitionId идентификатор соревнований, для которого получаем заявки
    //@param &reccount [out] - сколько записей было получено  
    //@return список заявок на участие в соревнованиях
    static TList* getByCompetitionId(int competitionId);


    //-- Получить список заявок по соревнованию, в расширенной форме (получаем представителей и клубы)
    //@param competitionId идентификатор соревнований, для которого получаем заявки
    //@param &reccount [out] - сколько записей было получено  
    //@return список заявок на участие в соревнованиях
    static TList* getExtendedByCompetitionId(int competitionId);

    //-- Вернуть текущий для таблицы объект
    static TRequest getCurrent(void);
    //-- Установить запись как текущую в таблице
    void makeCurrent(void);


    //-- Загрузить объект из хранилища
    //@param id идентификатор записи, которую загрузить
    void getById(int id);


    //-- Определяем, был ли объект расширен
    bool isExtended(void){return extended;}

    //-- методы получения и сохранения свойств объекта
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    int getClubId(void){return clubId;}
    void setClubId(int inClubId){clubId = inClubId;}
    int getCompetitionId(void){return competitionId;}
    void setCompetitionId(int inCompetitionId){competitionId = inCompetitionId;}
    int getPersonId(void){return personId;}
    void setPersonId(int inPersonId){personId = inPersonId;}
    AnsiString getComments(void){return asComments;}
    void setComments(AnsiString asInComments){asComments = asInComments;}

    //-- Методы возвращающие расширенные поля
    TClub getClub(void){return club;}
    TPerson  getPerson(void){return person;}
    //-- Расширить объект подобъектами 
    void extend(TPerson inPerson, TClub inClub);
};                                                                  




//---------------------------------------------------------------------------
#endif
