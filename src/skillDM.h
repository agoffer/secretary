//---------------------------------------------------------------------------

#ifndef skillDMH
#define skillDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>


#include "skillCtrl.h"
//---------------------------------------------------------------------------
class TdmSkillDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqSkillAll;
    TIBQuery *ibqSkill;
    TDataSource *dsSkillTable;
    TDataSource *dsSkillQuery;
private:	// User declarations
    //-- Определить начальный запрос для формирования полной таблицы
    void initSkillTable(void);
public:		// User declarations
    __fastcall TdmSkillDAO(TComponent* Owner);
    //-- Сохраняем объект в базе данных
    //@param obj Сохраняемый объект
    void store(TSkill &obj);

    //-- Получить все объекты из базы данных
    //@return Все объекты из базы данных, null если их нет
    TList* getAll(void);

    //-- Получить уровень мастерства по идентификатору
    //@param id идентификатор
    //@param obj объект, в который данные сохраняются
    void getById(int id, TSkill &obj);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmSkillDAO *dmSkillDAO;
//---------------------------------------------------------------------------
#endif
