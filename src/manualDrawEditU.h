//---------------------------------------------------------------------------

#ifndef manualDrawEditUH
#define manualDrawEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Buttons.hpp>

#include "categoryCtrl.h"

//---------------------------------------------------------------------------
class TfrmManualDraw : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grboxTree;
    TGroupBox *grboxDrawList;
    TLabel *lblAvailCategoryFirst;
    TComboBox *cmboxAvailCategory;
    TLabel *lblFightVersionFirst;
    TComboBox *cmboxFightVersion;
    TCheckBox *chboxFemaleCategory;
    TBitBtn *bbtnClose;
    TBitBtn *bbtnSaveDraw;
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall chboxFemaleCategoryClick(TObject *Sender);
    void __fastcall changeCompetitorList(TObject *Sender);
    void __fastcall cmboxFightVersionChange(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall bbtnSaveDrawClick(TObject *Sender);
    //--- ���������� �������, ��������� ����� � ���������� 
    void __fastcall changeDrawNumber(TObject *Sender);
private:
    //-- ������ �������� ���������� �� ����� (������ �������������� ���������)
    map<AnsiString, TCategory*> categoryIndex;
    //-- �������, ��������� ���������
    TCategory *currentCategory;
    //-- ������� ������ ����������
    TList * currentCompetitorList;
    //-- ������ ������� � ����������
    TStrings *templateDrawNumber;
    //-- ������� ���������� � ������, �������� �����������
    int* treeOrder;  

    //-- ������������� �����
    void InitFields(void);

    //-- ���������� �� ����� ���������� � ������
    void drawCompetitorTree(TList *competitorList, int* order);
    //-- ������� ������ ���������� ��� ����������
    void createDrawList(TList *competitorList);

    void createCategories(TList *category);
    //-- ������� ������ � �������� ���������� ����������
    int* collectSortionOrder(TList * competitorList);

    //-- �������� ��� �����
    AnsiString getClubName(int clubId);
public:		// User declarations
    __fastcall TfrmManualDraw(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmManualDraw *frmManualDraw;
//---------------------------------------------------------------------------
#endif
