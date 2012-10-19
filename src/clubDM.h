//---------------------------------------------------------------------------

#ifndef clubDMH
#define clubDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>
#include <IBTable.hpp>

#include "dataSourceDM.h"
#include "clubCtrl.h"
#include "utils.h"
//---------------------------------------------------------------------------

//--���� ������� (����������, ����������)
enum ClubTableField{ctfNoField, ctfName, ctfCountry, ctfCity};


class TdmClubDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqClub;
    TDataSource *dsClubTable;
    TDataSource *dsClubQuery;
    TIBQuery *ibqClubAll;
    void __fastcall ibqClubAllAfterScroll(TDataSet *DataSet);
private:	// User declarations
    //-- ���������� ��������� ������ ��� ��������� ���� ������ �� �������
    void initClubTable(void);

    //-- ���������� ��������� ������������� ����
    AnsiString getFieldName(ClubTableField field);

    //-- ��������� ��������������� �����
    SortState sortedFieldState;
    //-- �������������� ������� �������
    AnsiString filterCondition;
    //-- ����, �� �������� ����������� ������������
    ClubTableField filteredField;
    //-- ����, �� �������� ���������� ����������
    ClubTableField sortedField;


    //-- ������������ ������� � ������������� ���������
    //@param sortField ��� ����, �� �������� ���������� ����������
    //@param filter �������������� ������� �������
    //@param asc ����������� ����������
    void selectFromClubTable(AnsiString sortField, AnsiString filter, bool asc);


public:		// User declarations
    __fastcall TdmClubDAO(TComponent* Owner);


    //-- ������� ������ ������ ��� �������
    TClub getCurrent(void);
    //-- ������� ������ ������� � �������
    void makeCurrent(TClub obj);




    //--��������� ������ � ���� ������
    //@param obj ������ ������� ��������� ���������
    void store(TClub &obj);

    //-- ���������� ������� �� �����
    void sortByField(ClubTableField field);

    //-- ��������� ������ ��� ����������
    //@param condition ������ �� ������� ����������� ���������� �������
    void setFilterCondition(AnsiString condition){
        filterCondition = condition;
        }
    //-- ������, �� ������� ������ � ������
    void filterByField(ClubTableField field);

    //-- ��������� ������� ��������� ������
    void setScrollCallback(CallbackFunction cbf);
};


//---------------------------------------------------------------------------
extern PACKAGE TdmClubDAO *dmClubDAO;
//---------------------------------------------------------------------------
#endif
