//---------------------------------------------------------------------------

#ifndef skillDMH
#define skillDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>


#include "skillCtrl.h"
//---------------------------------------------------------------------------
class TdmSkillDAO : public TDataModule
{
__published:	// IDE-managed Components
    TIBQuery *ibqSkillAll;
    TIBQuery *ibqSkill;
    TDataSource *dsSkillTable;
    TDataSource *dsSkillQuery;
private:	// User declarations
    //-- ���������� ��������� ������ ��� ������������ ������ �������
    void initSkillTable(void);
public:		// User declarations
    __fastcall TdmSkillDAO(TComponent* Owner);
    //-- ��������� ������ � ���� ������
    //@param obj ����������� ������
    void store(TSkill &obj);

    //-- �������� ��� ������� �� ���� ������
    //@return ��� ������� �� ���� ������, null ���� �� ���
    TList* getAll(void);

    //-- �������� ������� ���������� �� ��������������
    //@param id �������������
    //@param obj ������, � ������� ������ �����������
    void getById(int id, TSkill &obj);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmSkillDAO *dmSkillDAO;
//---------------------------------------------------------------------------
#endif
