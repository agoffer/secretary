//---------------------------------------------------------------------------

#ifndef categoryDMH
#define categoryDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>

#include "competitorCtrl.h"
#include "categoryCtrl.h"
//---------------------------------------------------------------------------
class TdmCategoryDAO : public TDataModule
{
__published:	// IDE-managed Components
    TDataSource *dsCategoryExtended;
    TIBQuery *ibqCategoryExtendedTable;
    TIBQuery *ibqCategoryAll;
    TIBQuery *ibqCategory;
    TDataSource *dsCategoryTable;
    TDataSource *dsCategory;
    TIBQuery *ibqCompetitorToCategory;
private:	// User declarations
    //-- ���������� ��������� ������ ��� ��������� ���� ������ �� �������
    void initCategoryTable(void);

    //-- �������� ������ �� ���������, ��� ���������� ��� ����� ������ ������ 
    void addFightVersionToCompetitor(int competitorId, int categoryId);
public:		// User declarations
    __fastcall TdmCategoryDAO(TComponent* Owner);

    //-- ������� ������ ������ ��� �������
    TCategory getCurrent(void);
    //-- ������� ������ ������� � �������
    void makeCurrent(TCategory obj);

    //-- ������� ��� ��������� ��� ������� �����������
    TList * getByCompetitionId(int competitionId);


    //-- ������� ��� ��������� (� ����������� �����), ��� ������� ������������
    TList * getExtendedByCompetitionId(int competitionId);


    //-- ������� ��� ��������� (� ����������� �����), ��� ������� ������������ � ��������� 
    TList * getExtendedByCompetitionIdSurname(int competitionId, AnsiString surname);

    //-- ���������� ��������� ��������� � ������������ ���������
    bool putCompetitor(double weight, int age, bool female, int fightVersionId,
                        int competitionId, int competitorId);


    //-- �������� ������ �� ��������������
    void getById(int id, TCategory &obj);

    //--��������� ������ � ���� ������
    //@param obj ������ ������� ��������� ���������
    void store(TCategory &obj);

    //--������� ������ �� ���� ������
    //@param obj ������ ������� ��������� �������
    void erase(TCategory &obj);

    //--������� ��������� ��� �������� ������������ 
    //@param compid  ������������� ������������ 
    void deleteCategoriesByCompId(int compid);

    //--���������� ��� ��������� ����������
    //@param id ���������
    //@param ids ������ ���������� � ���������
    void setCompetitors(int id, TList * ids);

    //--�������� ��������� � ���������
    void addCompetitor(int idCompetitor, int idCategory);

    //-- ������� ���������� �� ���������
    //@param ids - �������������� ����������
    //@param count - ���������� ����������
    void eraseCompetitors(int id, TList *ids);

    //-- �������� ������ ���������� � ��������� 
    //@param id ������������� ���������
    //@param count ����������, � ���������
    TList* getCompetitors(int id);

    //-- �������� ���������� ���������� � ���������
    //@param id ������������� ���������
    int getCompetitorsAmount(int id);

    //-- �������� ������ �� ��������� ��� ����������
    //@param id ������������� ���������
    //@param count ���������� �������, � ���������
    TList* getSortionDataByCategory(int id);

    //-- ��������� ���������� ���������� ��� ���������
    //@param id - ������������� ��������� ��� ������� ����������� ����������
    //@param sortionOrder - ������ ���������� � ������� ����������
    //@param skillOrderDataAmnt - ���������� ���������� � ���������  
    void storeSortionOrder(int id, int *sortionOrder, int amnt);

    //-- ������� ��������� �� ���������
    void uncategory(int competitorId);

    //-- ������ ��������� � ��������� ���� ���������� (������, ��������������) 
    void setDrawType(TCategory category, char drawType);
    char getDrawType(TCategory category); 
};

//---------------------------------------------------------------------------
extern PACKAGE TdmCategoryDAO *dmCategoryDAO;
//---------------------------------------------------------------------------
#endif
