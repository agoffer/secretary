//---------------------------------------------------------------------------

#ifndef availCategoryDMH
#define availCategoryDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>


#include "availCategoryCtrl.h"
//---------------------------------------------------------------------------
class TdmAvailCategoryDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqAvailCategoryAll;
    TIBQuery *ibqAvailCategory;
    TDataSource *dsAvailCategoryTable;
    TDataSource *dsAvailCategoryQuery;
private:	// User declarations
    //-- Определить начальный запрос для формирования полной таблицы
    void initAvailCategoryTable(void);
public:		// User declarations
    __fastcall TdmAvailCategoryDAO(TComponent* Owner);

    //-- Определить таблицу доступных категорий, для мужчин/женщин  
    void setCategoryTable(int startAge, int endAge,
                                                double startWeight,
                                                double endWeight, bool female);

    //-- Сохраняем объект в базе данных
    //@param obj Сохраняемый объект
    void store(TAvailCategory &obj);

    //Удалить объект из базы 
    void remove(TAvailCategory obj);

    //-- Получить все объекты из базы данных
    //@return Все объекты из базы данных, null если их нет
    TList* getAll(void);

    //-- Получить уровень мастерства по идентификатору
    //@param id идентификатор
    //@param obj объект, в который данные сохраняются
    void getById(int id, TAvailCategory &obj);

    //-- Вернуть текущую категорию в таблице
    TAvailCategory getCurrent(void);
    //-- Выбрать в таблице текущ
    void makeCurrent(TAvailCategory obj); 


    //-- Вернуть доступную категорию, в которую попадает участник
    int getAvailCategoryId(double weight, int age, bool female);     
};
//---------------------------------------------------------------------------
extern PACKAGE TdmAvailCategoryDAO *dmAvailCategoryDAO;
//---------------------------------------------------------------------------
#endif
