//---------------------------------------------------------------------------

#ifndef competitionRankDMH
#define competitionRankDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>

#include "competitionRankCtrl.h"
#include <IBTable.hpp>
//---------------------------------------------------------------------------
class TdmCompetitionRankDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqCompetitionRank;
    TDataSource *dsCompetitionRankQuery;
    TDataSource *dsCompetitionRankTable;
    TIBTable *ibtCompetitionRank;
    TDataSource *dsrcScoreRanking;
    TIBTable *ibtScoreRanking;
    void __fastcall ibtCompetitionRankBeforeInsert(TDataSet *DataSet);
    void __fastcall ibtCompetitionRankPostError(TDataSet *DataSet,
          EDatabaseError *E, TDataAction &Action);
    void __fastcall ibtScoreRankingBeforeInsert(TDataSet *DataSet);
    void __fastcall ibtScoreRankingAfterInsert(TDataSet *DataSet);
    void __fastcall ibtScoreRankingBeforePost(TDataSet *DataSet);
    void __fastcall ibtCompetitionRankAfterPost(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
    __fastcall TdmCompetitionRankDAO(TComponent* Owner);
    //-- Сохраняем объект в базе данных
    //@param obj Сохраняемый объект
    void store(TCompetitionRank &obj);

    //-- Получить все объекты из базы данных
    //@return Все объекты из базы данных, null если их нет
    TList* getAll(void);

    //-- Получить статус соревнований по идентификатору
    //@param id идентификатор, статуса, который надо получить
    //@param obj объект, в который данные сохраняются
    void getById(int id, TCompetitionRank &obj);  
};
//---------------------------------------------------------------------------
extern PACKAGE TdmCompetitionRankDAO *dmCompetitionRankDAO;
//---------------------------------------------------------------------------
#endif
