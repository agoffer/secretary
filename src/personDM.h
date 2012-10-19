//---------------------------------------------------------------------------

#ifndef personDMH
#define personDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>

#include "dataSourceDM.h"
#include "personCtrl.h"

#include "utils.h"
//---------------------------------------------------------------------------

//--���� ������� (����������, ����������) 
enum PersonTableField{ptfNoField, ptfSurname, ptfName, ptfPatronymic, ptfPhone}; 


class TdmPersonDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqPersonAll;
    TIBQuery *ibqPerson;
    TDataSource *dsPersonTable;
    TDataSource *dsPersonQuery;
    TDataSource *dsPersonSlaveTable;
    TIBQuery *ibqPersonSlaveTable;
    void __fastcall ibqPersonAllAfterScroll(TDataSet *DataSet);
private:	// User declarations
    //-- ���������� ��������� ������ ��� ��������� ���� ������ �� �������
    void initPersonTable(TIBQuery *ibq);
    //-- ���������� ��������� ������������� ����
    AnsiString getFieldName(PersonTableField field);




    //-- ������������ ������� � ������������� ���������
    //@param sortField ��� ����, �� �������� ���������� ����������
    //@param filter �������������� ������� �������
    //@param asc ����������� ����������
    void selectFromPersonTable(TIBQuery *ibq, AnsiString sortField, AnsiString filter, bool asc);

    //-- ������� ������ ������ ��� �������
    TPerson getCurrent(TIBQuery *ibq);

    //-- ������� ������ ������� � �������
    void makeCurrent(TPerson obj, TIBQuery *ibq);

    // -- ������� ������������ ������ � �������� �������.
    void replacePersonInCertainTable(AnsiString tableName, AnsiString fieldName, int personIdFrom, int personIdTo);


    //-- ��������� ��������������� �����
    SortState sortedFieldState;
    //-- �������������� ������� �������
    AnsiString filterCondition;
    //-- ����, �� �������� ����������� ������������
    PersonTableField filteredField;
    //-- ����, �� �������� ���������� ����������
    PersonTableField sortedField;

public:		// User declarations
    __fastcall TdmPersonDAO(TComponent* Owner);

    //-- ���������� ������� � ���� ������
    //@param obj ������, ������� ����������� � ���� ������
    void store(TPerson &obj);

    //-- ������� ������� ������ �� �������
    bool deleteCurrent(void);

    //-- ������� ������ ������ ��� �������
    TPerson getCurrent();

    //-- ������� ������� ������ �� ����������� �������
    TPerson getCurrentSlave();

    //-- ������� ������ ������� � �������
    void makeCurrent(TPerson obj);

    //-- ���������, ���� �� ����� ������� � ���� (��������� �� ������� ����� � ��������)
    bool likeAs(TPerson &obj);

    //-- ���������� ������� �� �����
    void sortByField(PersonTableField field);

    // -- �������� ������ ����������� �������,
    void refreshSlaveTable(AnsiString filter);

    //-- ��������� ������ ��� ����������
    //@param condition ������ �� ������� ����������� ���������� �������
    void setFilterCondition(AnsiString condition){
        filterCondition = condition;
        }
    //-- ������, �� ������� ������ � ������
    void filterByField(PersonTableField field);

    //-- ��������� ������� ��������� ������
    void setScrollCallback(CallbackFunction cbf);

    //-- ������ ������������ ������ ��������� �� ������� from �������� � ������� to
    void changePersonalData(TIBQuery *from, TIBQuery *to);

};
//---------------------------------------------------------------------------
extern PACKAGE TdmPersonDAO *dmPersonDAO;
//---------------------------------------------------------------------------
#endif
