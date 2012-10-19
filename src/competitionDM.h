//---------------------------------------------------------------------------

#ifndef competitionDMH
#define competitionDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>


#include "competitionCtrl.h"
#include <IBTable.hpp>
//---------------------------------------------------------------------------
class TdmCompetitionDAO : public TDataModule
{
__published:	// IDE-managed Components
    TDataSource *dsCompetitoinQuery;
    TIBQuery *ibqCompetition;
    TDataSource *dsCompetitionTable;
    TIBQuery *ibqCompetitionAll;
    TIBQuery *ibqExtendedCompetitionAll;
    TDataSource *dsExtendedCompetitionTable;
private:	// User declarations
    //-- определить начальный запрос на получение всей таблицы
    void initCompetitionTable(void);
public:		// User declarations
    __fastcall TdmCompetitionDAO(TComponent* Owner);

    //-- Сохранить соревнование в базе данных
    void store(TCompetition &obj);
    //-- Получить список всех соревнований из базы данных
    TList* getAll(void);
    //-- Получить соревнование - задан идентификатор
    void getById(int id, TCompetition &obj);

    //-- Получить текущю запись в расширенной таблице
    TCompetition getExtendedCurrent(void);

    //-- Получить максимальную и минимальную дату начала соревнования
    void getMinMaxBeginDate(TDateTime &minBeginDate, TDateTime &maxBeginDate);

    //-- Установить диапазон в таблице раширинной информации о соревновании
    void selectRangeExtendedCompetitions(TDateTime begin, TDateTime end);

    //-- Удалить текущую, выбранную запись
    void removeCurrent();

    // -- Удаление соревнований по их идентификатору
    void remove(int id);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmCompetitionDAO *dmCompetitionDAO;
//---------------------------------------------------------------------------
#endif
