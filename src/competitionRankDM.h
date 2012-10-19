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
    //-- ��������� ������ � ���� ������
    //@param obj ����������� ������
    void store(TCompetitionRank &obj);

    //-- �������� ��� ������� �� ���� ������
    //@return ��� ������� �� ���� ������, null ���� �� ���
    TList* getAll(void);

    //-- �������� ������ ������������ �� ��������������
    //@param id �������������, �������, ������� ���� ��������
    //@param obj ������, � ������� ������ �����������
    void getById(int id, TCompetitionRank &obj);  
};
//---------------------------------------------------------------------------
extern PACKAGE TdmCompetitionRankDAO *dmCompetitionRankDAO;
//---------------------------------------------------------------------------
#endif
