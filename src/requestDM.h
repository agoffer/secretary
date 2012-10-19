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
    //-- ���������� ��������� ������ ��� ��������� ���� ������ �� �������
    void initRequestTable(void);
public:		// User declarations
    __fastcall TdmRequestDAO(TComponent* Owner);

    //-- ������� ������ ������ ��� �������
    TRequest getCurrent(void);
    //-- ������� ������ ������� � �������
    void makeCurrent(TRequest obj);

    //-- ������� ��� ������, ��� �������� ������������
    TList * getByCompetitionId(int competitionId);

    //-- ������� ��� ������ (� ����������� �����), ��� �������� ������������
    TList * getExtendedByCompetitionId(int competitionId);


    //--��������� ������ � ���� ������
    //@param obj ������ ������� ��������� ���������
    void store(TRequest &obj);

    //-- ������� ������ � ������� ���������������
    void deleteById(int requestId);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmRequestDAO *dmRequestDAO;
//---------------------------------------------------------------------------
#endif
