//---------------------------------------------------------------------------

#ifndef competitionRankCtrlH
#define competitionRankCtrlH

#include<vcl.h>

//****************************************//
// Класс представлющий объекты
// "Статус соерванеия"
// Определены методы управления объектом
// @author Andrey V. Goffer
// @create 23.11.05
//****************************************//


class TCompetitionRank{
private:
    //Идентификатор
    int id;
    //Описание статуса соревнований
    AnsiString asDescription;
    //Комментарии
    AnsiString asComments;
// Интерфейс объекта //
public:


    //-- Конструктор
    //@param asDescription - описание статуса соревнований
    //@param asComments - комментарии
    TCompetitionRank(AnsiString asInDescription, AnsiString asInComments);
    //-- Конструктор по умолчанию 
    TCompetitionRank(void){asDescription=""; asComments=""; id=0;}
    //-- Деструктор
    ~TCompetitionRank(void);

    //--Проверка объекта
    //@return true - если объект допустим, false - если объект не валидный
    bool valid(AnsiString &errmess); 

    //-- Сохранение объекта в базе данных
    void store(void);
    //-- Чтение всех объектов из базы данных
    //@return Список объектов, прочитанных из базы данных,
    //  или null, если объектов в базе не найдено 
    static TList* getAll(void);

    //-- Получить статус соревновний по идентификатору
    //@param id Идентификтор статуса, который надо получить 
    void getById(int id);

    //-- методы получения и сохранения свойств объекта
    int getId(void);
    void setId(int inId);
    AnsiString getDescription(void);
    void setDescription(AnsiString asInDescription);
    AnsiString getComments(void);
    void setComments(AnsiString asInComments);
};


//---------------------------------------------------------------------------
#endif
