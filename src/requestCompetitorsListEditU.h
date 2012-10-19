//---------------------------------------------------------------------------

#ifndef requestCompetitorsListEditUH
#define requestCompetitorsListEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>


#include "competitorDM.h"
#include "personDM.h"
#include "fightVersionCtrl.h"
#include "skillCtrl.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmRequestCompetitorsListEdit : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grboxCompetitorsList;
    TStringGrid *strgrdCompetitorsList;
    TPanel *pnlCompetitor;
    TGroupBox *grboxCompetitorEdit;
    TLabel *lblDOB;
    TLabel *lblWeight;
    TLabel *lblSkill;
    TLabel *lblFightVersion;
    TLabeledEdit *lbledtSurname;
    TLabeledEdit *lbledtName;
    TLabeledEdit *lbledtPatronymic;
    TDateTimePicker *dtpDOB;
    TMaskEdit *medtWeight;
    TComboBox *cmboxSkill;
    TButton *btnAddSkill;
    TButton *btnAddFightVersion;
    TCheckListBox *chlstboxFightVersion;
    TBitBtn *bbtnAddCompetitor;
    TBitBtn *bbtnCloseList;
    TGroupBox *grboxPersonQuickSearch;
    TDBGrid *dbgrdPersonList;
    TBitBtn *bbtnToEditBox;
    TLabel *lblFullAge;
    TStaticText *sttxtFullAge;
    TBitBtn *bbtnUpdateCompetitor;
    TBitBtn *bbtnCancelCompetitor;
    TCheckBox *chboxFemale;
    TPanel *pnlButtons;
    TBitBtn *bbtnEdit;
    TBitBtn *bbtnDelete;
    TBitBtn *bbtnPrintRequest;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnAddSkillClick(TObject *Sender);
    void __fastcall btnAddFightVersionClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall lbledtSurnameChange(TObject *Sender);
    void __fastcall bbtnToEditBoxClick(TObject *Sender);
    void __fastcall dtpDOBChange(TObject *Sender);
    void __fastcall bbtnAddCompetitorClick(TObject *Sender);
    void __fastcall medtWeightExit(TObject *Sender);
    void __fastcall bbtnDeleteClick(TObject *Sender);
    void __fastcall bbtnEditClick(TObject *Sender);
    void __fastcall bbtnUpdateCompetitorClick(TObject *Sender);
    void __fastcall bbtnCancelCompetitorClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    //-- ������������� �����
    void InitFields(void);
    //-- �������� ����, ����� ������ ������ ���������
    void clearFields(void);
    //-- ������� ������ ������ ������
    void createFightVersionList(void);
    //-- ������� ������ ������ ������
    void destroyFightVersionList(void);
    //-- ������� ������ ������� ����������
    void createSkillList(void);
    //-- ������� ������ ������� ����������
    void destroySkillList(void);
    

    //-- �������� ��������� ������ ������ � ������������ � ���������
    void changePersonSearchTableState(void);

    //-- ��������� ���� ��������� �� ������� �������� ���������
    void fillCompetitorPerson(void);

    //-- �������� �� ����� ������ �� ��������� � �������� �� ���� ������
    bool CompetitorIntoDatabase(TPerson& obj, TCompetitor *newCompetitor);

    //-- ������������ ������ �������������� ������ ������ ��� ���������
    int *createFightVersionIdList(int &count);
    //-- �������� ������, � ������� ��������� ��������
    void checkedFightVersion(TList *tocheck);

    //-- ������� ������� ����������, �� ��������� �������������� 
    void selectSkillById(int id);


    //-- �������� ������� �� �������
    void setEditMode(void);
    void closeEditMode(void);

    //-- �������� ������������
    TList *competitorsList;



public:		// User declarations
    __fastcall TfrmRequestCompetitorsListEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRequestCompetitorsListEdit *frmRequestCompetitorsListEdit;


//--������������� ��������� � grid ������� ����������
extern void setCompetitorTableHeader(TStringGrid *grid);
//-- �������� ���������� ��������� �  �������
extern void addToCompetitorStringGrid(TCompetitor competitor, int addIndex, TStringGrid *grid);
//-- ������� ��������� �� �������
extern void deleteFromCompetitorStringGrid(int delIndex, TStringGrid *grid);
//-- ������� ������ � ������� �� �������� ������
TList* createCompetitorsList(int requestId, TStringGrid *grid);
//-- �������� ������� ����� (���������� ������)
void clearStrGrid(TStringGrid *grid);






//---------------------------------------------------------------------------
#endif
