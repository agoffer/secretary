//---------------------------------------------------------------------------

#ifndef requestDMH
#define requestDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>
#include <IBTable.hpp>

#include "requestCtrl.h"
//---------------------------------------------------------------------------

class TdmRequestDAO : public TDataModule
{
__published:	// IDE-managed Components
    TDataSource *dsRequestTable;
    TIBQuery *ibqRequest;
    TDataSource *dsRequestQuery;
    TIBQuery *ibqRequestAll;
private:	// User declarations
    //-- Определить начальный запрос для получения всех данных из таблицы
    void initRequestTable(void);
public:		// User declarations
    __fastcall TdmRequestDAO(TComponent* Owner);

    //-- Вернуть текущю запись для таблицы
    TRequest getCurrent(void);
    //-- Сделать запись текущей в таблице
    void makeCurrent(TRequest obj);

    //-- Вернуть все заявки, для текущего соревнования
    TList * getByCompetitionId(int competitionId);

    //-- Вернуть все заявки (в расширенной форме), для текущего соревнования
    TList * getExtendedByCompetitionId(int competitionId);


    //--Сохранить объект в базе данных
    //@param obj объект который требуется сохранить
    void store(TRequest &obj);

    //-- Удалить заявку с заданым идентификатором
    void deleteById(int requestId);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmRequestDAO *dmRequestDAO;
//---------------------------------------------------------------------------
#endif
