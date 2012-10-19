//---------------------------------------------------------------------------

#ifndef fightVersionDMH
#define fightVersionDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>

#include "fightVersionCtrl.h"
//---------------------------------------------------------------------------
class TdmFightVersionDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqFightVersionAll;
    TIBQuery *ibqFightVersion;
    TDataSource *dsFightVersionTable;
    TDataSource *dsFightVersionQuery;
private:	// User declarations
    //-- Определить начальный запрос для формирования полной таблицы
    void initFightVersionTable(void);
public:		// User declarations
    __fastcall TdmFightVersionDAO(TComponent* Owner);
    
    //-- Сохраняем объект в базе данных
    //@param obj Сохраняемый объект
    void store(TFightVersion &obj);

    //-- Получить все объекты из базы данных
    //@return Все объекты из базы данных, null если их нет
    TList* getAll(void);

    //-- Получить боевую версию по идентификатору
    //@param id идентификатор
    //@param obj объект, в который данные сохраняются
    void getById(int id, TFightVersion &obj);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmFightVersionDAO *dmFightVersionDAO;
//---------------------------------------------------------------------------
#endif
