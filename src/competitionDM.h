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
    //-- ���������� ��������� ������ �� ��������� ���� �������
    void initCompetitionTable(void);
public:		// User declarations
    __fastcall TdmCompetitionDAO(TComponent* Owner);

    //-- ��������� ������������ � ���� ������
    void store(TCompetition &obj);
    //-- �������� ������ ���� ������������ �� ���� ������
    TList* getAll(void);
    //-- �������� ������������ - ����� �������������
    void getById(int id, TCompetition &obj);

    //-- �������� ������ ������ � ����������� �������
    TCompetition getExtendedCurrent(void);

    //-- �������� ������������ � ����������� ���� ������ ������������
    void getMinMaxBeginDate(TDateTime &minBeginDate, TDateTime &maxBeginDate);

    //-- ���������� �������� � ������� ���������� ���������� � ������������
    void selectRangeExtendedCompetitions(TDateTime begin, TDateTime end);

    //-- ������� �������, ��������� ������
    void removeCurrent();

    // -- �������� ������������ �� �� ��������������
    void remove(int id);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmCompetitionDAO *dmCompetitionDAO;
//---------------------------------------------------------------------------
#endif
