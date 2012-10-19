//---------------------------------------------------------------------------

#ifndef availCategoryDMH
#define availCategoryDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>


#include "availCategoryCtrl.h"
//---------------------------------------------------------------------------
class TdmAvailCategoryDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqAvailCategoryAll;
    TIBQuery *ibqAvailCategory;
    TDataSource *dsAvailCategoryTable;
    TDataSource *dsAvailCategoryQuery;
private:	// User declarations
    //-- ���������� ��������� ������ ��� ������������ ������ �������
    void initAvailCategoryTable(void);
public:		// User declarations
    __fastcall TdmAvailCategoryDAO(TComponent* Owner);

    //-- ���������� ������� ��������� ���������, ��� ������/������  
    void setCategoryTable(int startAge, int endAge,
                                                double startWeight,
                                                double endWeight, bool female);

    //-- ��������� ������ � ���� ������
    //@param obj ����������� ������
    void store(TAvailCategory &obj);

    //������� ������ �� ���� 
    void remove(TAvailCategory obj);

    //-- �������� ��� ������� �� ���� ������
    //@return ��� ������� �� ���� ������, null ���� �� ���
    TList* getAll(void);

    //-- �������� ������� ���������� �� ��������������
    //@param id �������������
    //@param obj ������, � ������� ������ �����������
    void getById(int id, TAvailCategory &obj);

    //-- ������� ������� ��������� � �������
    TAvailCategory getCurrent(void);
    //-- ������� � ������� �����
    void makeCurrent(TAvailCategory obj); 


    //-- ������� ��������� ���������, � ������� �������� ��������
    int getAvailCategoryId(double weight, int age, bool female);     
};
//---------------------------------------------------------------------------
extern PACKAGE TdmAvailCategoryDAO *dmAvailCategoryDAO;
//---------------------------------------------------------------------------
#endif
