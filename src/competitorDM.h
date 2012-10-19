//---------------------------------------------------------------------------

#ifndef competitorDMH
#define competitorDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>

#include "competitorCtrl.h"
#include "utils.h"


//--���� ������� (����������, ����������)
enum CompetitorTableField{ctfSurname, ctfClub_Name};

//---------------------------------------------------------------------------
class TdmCompetitorDAO : public TDataModule
{
__published:	// IDE-managed Components
    TDataSource *dsCompetitorExtended;
    TIBQuery *ibqCompetitorExtendedTable;
    TIBQuery *ibqCompetitorAll;
    TIBQuery *ibqCompetitor;
    TDataSource *dsCompetitorTable;
    TDataSource *dsCompetitor;
    TIBQuery *ibqCompetitorToFightVersion;
    void __fastcall ibqCompetitorExtendedTableAfterScroll(
          TDataSet *DataSet);
private:	// User declarations
    //-- ���������� ��������� ������ ��� ��������� ���� ������ �� �������
    void initCompetitorTable(void);
    void initExtendedCompetitorTable(void);

    //-- ���������� ��������� ������������� ����
    AnsiString getFieldName(CompetitorTableField field);

    //-- �������������� ������� �������
    AnsiString filterCondition_1;
    //-- ����, �� �������� ����������� ������������
    CompetitorTableField filteredField_1;
    //-- �������������� ������� �������
    AnsiString filterCondition_2;
    //-- ����, �� �������� ����������� ������������
    CompetitorTableField filteredField_2;

    //-- ������������ ������� � ������������� ���������
    //@param sortField ��� ����, �� �������� ���������� ����������
    //@param filter �������������� ������� �������
    //@param asc ����������� ����������
    void selectFromCompetitorTable(AnsiString filter);

public:		// User declarations
    __fastcall TdmCompetitorDAO(TComponent* Owner);

    //-- ������� ������ ������ ��� �������
    TCompetitor getCurrent(void);
    //-- ������� ������ ������� � �������
    void makeCurrent(TCompetitor obj);

    //-- ������� ������ ������ ��� ����������� �������
    TCompetitor getExtendedTableCurrent(void);
    //-- ������� ������ ������� � �������
    void makeExtendedTableCurrent(TCompetitor obj);

    //-- ������� ���� ����������, ��� ������� ������
    TList * getByRequestId(int requestId);

    //-- ������� ���� ����������, ��� �������� ������������ 
    TList * getByCompetitionId(int competitionId);

    //-- �������� ��������� - ����� �������������
    void getById(int id, TCompetitor &obj);

    //������� ������� ���������� ��� �������� ������ 
    void formTableByRequestId(int requestId);

    //-- ������� ���� ���������� (� ����������� �����) ��� ������� ������������
    TList * getExtendedByCompetitionId(int competitionId);

    //-- ������� ����������� ������ ���������� �� �������� � ��������� ������������ 
    TList * getExtendedUncategoryByCompetitionId(int competitionId, bool female);

    //-- ������� ���� ���������� (� ����������� �����), ��� ������� ������
    TList * getExtendedByRequestId(int requestId);

    //-- ������� ���� ���������� (� ����������� �����), ��� �������� ��������� 
    TList * getExtendedByCategoryId(int categoryId);


    //--��������� ������ � ���� ������
    //@param obj ������ ������� ��������� ���������
    void store(TCompetitor &obj);

    //--������� ������ �� ���� ������
    //@param obj ������ ������� ��������� ������� 
    void erase(TCompetitor &obj);

    //--���������� ��� ��������� ������ ������
    //@param id ������������� ���������
    //@param ids ������ ������ ������
    void setFightVersion(int id, int * ids, int count);

    //-- ������� ������ ������ ��� ���������
    //@param id - ������������� ���������  
    void eraseFightVersion(int id);

    //-- �������� ������ ������ ������, ��� ��������� 
    //@param id ������������� ���������
    //@param count ����� ������, � ������� ��������� �������� 
    TList* getFightVersion(int id);

    //-- �������� ������ ���������������� ������ ������, ��� ��������� 
    //@param id ������������� ���������
    //@param count ����� ������, ������� �� ������������
    TList* getUncategoryFightVersion(int id);

    //-- �������� ������ ����������� ������ ������, ��� ���������
    //@param id ������������� ���������
    //@param count ����� ������, ������� ���������
    TList* getExtendedFightVersion(int id);

    //-- ��������� ������ ��� ����������
    //@param condition ������ �� ������� ����������� ���������� �������
    void setFilterCondition_1(AnsiString condition){
        filterCondition_1 = condition;
        }
    //-- ������, �� ������� ������ � ������
    void filterByField(int competitionId, CompetitorTableField field_1, CompetitorTableField field_2);

    //-- ��������� ������ ��� ����������
    //@param condition ������ �� ������� ����������� ���������� �������
    void setFilterCondition_2(AnsiString condition){
        filterCondition_2 = condition;
        }
    //-- ������, �� ������� ������ � ������
    void filterByField_1(CompetitorTableField field);

    //-- ��������� ������� ��������� ������
    void setScrollCallback(CallbackFunction cbf);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmCompetitorDAO *dmCompetitorDAO;
//---------------------------------------------------------------------------
#endif
