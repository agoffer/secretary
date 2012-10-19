//---------------------------------------------------------------------------

#ifndef categoryDMH
#define categoryDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>

#include "competitorCtrl.h"
#include "categoryCtrl.h"
//---------------------------------------------------------------------------
class TdmCategoryDAO : public TDataModule
{
__published:	// IDE-managed Components
    TDataSource *dsCategoryExtended;
    TIBQuery *ibqCategoryExtendedTable;
    TIBQuery *ibqCategoryAll;
    TIBQuery *ibqCategory;
    TDataSource *dsCategoryTable;
    TDataSource *dsCategory;
    TIBQuery *ibqCompetitorToCategory;
private:	// User declarations
    //-- Определить начальный запрос для получения всех данных из таблицы
    void initCategoryTable(void);

    //-- Добавить запись об участнике, при добавлении ему новой боевой версии 
    void addFightVersionToCompetitor(int competitorId, int categoryId);
public:		// User declarations
    __fastcall TdmCategoryDAO(TComponent* Owner);

    //-- Вернуть текущю запись для таблицы
    TCategory getCurrent(void);
    //-- Сделать запись текущей в таблице
    void makeCurrent(TCategory obj);

    //-- Вернуть все категории для текущих соревновний
    TList * getByCompetitionId(int competitionId);


    //-- Вернуть все категории (в расширенной форме), для текущих соревнований
    TList * getExtendedByCompetitionId(int competitionId);


    //-- Вернуть все категории (в расширенной форме), для текущих соревнований и участника 
    TList * getExtendedByCompetitionIdSurname(int competitionId, AnsiString surname);

    //-- Попытаться поместить участника в существующую категорию
    bool putCompetitor(double weight, int age, bool female, int fightVersionId,
                        int competitionId, int competitorId);


    //-- Получить запись по идентификатору
    void getById(int id, TCategory &obj);

    //--Сохранить объект в базе данных
    //@param obj объект который требуется сохранить
    void store(TCategory &obj);

    //--Удалить объект из базе данных
    //@param obj объект который требуется удалить
    void erase(TCategory &obj);

    //--Удалить категории для заданных соревнований 
    //@param compid  идентификатор соревнований 
    void deleteCategoriesByCompId(int compid);

    //--Устнаовить для категории участников
    //@param id категории
    //@param ids список участников в категории
    void setCompetitors(int id, TList * ids);

    //--Добавить участника в категорию
    void addCompetitor(int idCompetitor, int idCategory);

    //-- Удалить участников из категории
    //@param ids - идентификаторы участников
    //@param count - количество участников
    void eraseCompetitors(int id, TList *ids);

    //-- Получить список участников в категории 
    //@param id идентификатор категории
    //@param count участников, в категории
    TList* getCompetitors(int id);

    //-- Получить количество участников в категории
    //@param id идентификатор категории
    int getCompetitorsAmount(int id);

    //-- Получить данные из категории для жеребьевки
    //@param id идентификатор категории
    //@param count количество записей, в категории
    TList* getSortionDataByCategory(int id);

    //-- Сохранить результаты жеребьевки для категории
    //@param id - идентификатор категории для которой выполнялась жеребьевка
    //@param sortionOrder - список участников в порядке жеребьевки
    //@param skillOrderDataAmnt - количество участников в категории  
    void storeSortionOrder(int id, int *sortionOrder, int amnt);

    //-- Вынести участника из категорий
    void uncategory(int competitorId);

    //-- Методы получения и установки типа жеребьевки (ручная, автоматическая) 
    void setDrawType(TCategory category, char drawType);
    char getDrawType(TCategory category); 
};

//---------------------------------------------------------------------------
extern PACKAGE TdmCategoryDAO *dmCategoryDAO;
//---------------------------------------------------------------------------
#endif
