//---------------------------------------------------------------------------

#ifndef fightVersionDMH
#define fightVersionDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>

#include "fightVersionCtrl.h"
//---------------------------------------------------------------------------
class TdmFightVersionDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqFightVersionAll;
    TIBQuery *ibqFightVersion;
    TDataSource *dsFightVersionTable;
    TDataSource *dsFightVersionQuery;
private:	// User declarations
    //-- ���������� ��������� ������ ��� ������������ ������ �������
    void initFightVersionTable(void);
public:		// User declarations
    __fastcall TdmFightVersionDAO(TComponent* Owner);
    
    //-- ��������� ������ � ���� ������
    //@param obj ����������� ������
    void store(TFightVersion &obj);

    //-- �������� ��� ������� �� ���� ������
    //@return ��� ������� �� ���� ������, null ���� �� ���
    TList* getAll(void);

    //-- �������� ������ ������ �� ��������������
    //@param id �������������
    //@param obj ������, � ������� ������ �����������
    void getById(int id, TFightVersion &obj);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmFightVersionDAO *dmFightVersionDAO;
//---------------------------------------------------------------------------
#endif
