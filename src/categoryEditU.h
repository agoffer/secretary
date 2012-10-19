//---------------------------------------------------------------------------

#ifndef categoryEditUH
#define categoryEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Buttons.hpp>

#include "competitorCtrl.h"
#include "categoryCtrl.h"


#include <map.h>
//---------------------------------------------------------------------------
class TfrmCategoryEdit : public TForm
{
__published:	// IDE-managed Components
    TPanel *pnlCategoryFirst;
    TPanel *pnlCategorySecond;
    TPanel *pnlUncategory;
    TGroupBox *grboxSelectedCategoryFirst;
    TGroupBox *grboxSelectedCategorySecond;
    TComboBox *cmboxAvailCategoryFirst;
    TLabel *lblAvailCategoryFirst;
    TLabel *lblFightVersionFirst;
    TComboBox *cmboxFightVersionFirst;
    TLabel *lblAvailCategorySecond;
    TLabel *lblFightVersionSecond;
    TComboBox *cmboxAvailCategorySecond;
    TComboBox *cmboxFightVersionSecond;
    TGroupBox *grboxOperationFirst;
    TGroupBox *grboxOperationSecond;
    TStringGrid *strgrdCategoryFirst;
    TStringGrid *strgrdCategorySecond;
    TGroupBox *grboxUncategory;
    TGroupBox *grboxSelectedCategoryUncategory;
    TLabel *lblAvailCategoryUncategory;
    TLabel *lblFightVersionUncategory;
    TComboBox *cmboxAvailCategoryUncategory;
    TComboBox *cmboxFightVersionUncategory;
    TStringGrid *strgrdUncategory;
    TBitBtn *bbtnToSecond;
    TBitBtn *bbtnMakeUncategoryFirst;
    TBitBtn *bbtnMakeUncategorySecond;
    TBitBtn *bbtnToFirst;
    TBitBtn *bbtnInCategory;
    TButton *btnAddAvailCategory;
    TBitBtn *bbtnPrintCategoryFirst;
    TBitBtn *bbtnPrintCategorySecond;
    TBitBtn *bbtnPrintTreeFirst;
    TBitBtn *bbtnPrintTreeSecond;
    TBitBtn *bbtnUncategoryPrint;
    TGroupBox *grboxCommon;
    TBitBtn *bbtnPrintAllCategoryTree;
    TBitBtn *bbtnPrintAllCategory;
    TBitBtn *bbtnCloseCategoryDistrib;
    TCheckBox *chboxFemaleCategory;
    TBitBtn *bbtnPairsList;
    TGroupBox *grboxCompetitorSearch;
    TEdit *edtCompetitorSearch;
    TCheckBox *chboxCompetitorSearch;
    TBitBtn *bbtnManualDraw;
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall chboxFemaleCategoryClick(TObject *Sender);
    void __fastcall changeCompetitorListFirst(TObject *Sender);
    void __fastcall changeCompetitorListSecond(TObject *Sender);
    void __fastcall bbtnToSecondClick(TObject *Sender);
    void __fastcall bbtnToFirstClick(TObject *Sender);
    void __fastcall bbtnMakeUncategoryFirstClick(TObject *Sender);
    void __fastcall bbtnMakeUncategorySecondClick(TObject *Sender);
    void __fastcall bbtnInCategoryClick(TObject *Sender);
    void __fastcall bbtnPrintAllCategoryClick(TObject *Sender);
    void __fastcall bbtnPrintCategoryFirstClick(TObject *Sender);
    void __fastcall bbtnPrintCategorySecondClick(TObject *Sender);
    void __fastcall bbtnPrintTreeSecondClick(TObject *Sender);
    void __fastcall bbtnPrintTreeFirstClick(TObject *Sender);
    void __fastcall bbtnPrintAllCategoryTreeClick(TObject *Sender);
    void __fastcall bbtnUncategoryPrintClick(TObject *Sender);
    void __fastcall bbtnPairsListClick(TObject *Sender);
    void __fastcall btnAddAvailCategoryClick(TObject *Sender);
    void __fastcall cmboxFightVersionFirstChange(TObject *Sender);
    void __fastcall cmboxFightVersionSecondChange(TObject *Sender);
    void __fastcall cmboxFightVersionUncategoryChange(TObject *Sender);
    void __fastcall chboxCompetitorSearchClick(TObject *Sender);
    void __fastcall edtCompetitorSearchChange(TObject *Sender);
    void __fastcall bbtnManualDrawClick(TObject *Sender);
private:	// User declarations
    //-- ������������ ��������� ���� �����
    void InitFields(void);
    //-- ������ �������� ���������� �� ����� (������ �������������� ���������)
    map<AnsiString, TCategory*> categoryIndex;

    //-- ������ ���������� � ������ ������
    TList *competitorListFirst;
    //-- ������ ���������� �� ������ ������
    TList *competitorListSecond;

    //-- ������ ���������� �� �������� � ���������
    TList *uncategoryCompetitorList;

    //-- ��������� ���������� ������ ������������ ���������
    void createCategories(TList *category);

    //-- ��������� ������ ���������� ������, ����������� �� ������ 
    void createSearchedCategories(AnsiString surname);

    //-- ��������� ������ ������ ���������� � ���������
    void ShowCompetitorListFirst(TCategory* category);
    void ShowCompetitorListSecond(TCategory* category);

    //-- ������� ��������� � ������� ����� ���������� �� �������������� ��������� 
    void setUndestributedCategory(TComboBox* cmboxCategory, TComboBox* cmboxFightVersion); 

    //-- ���������� ������ ���������� �� �������� � ���������
    void ShowUncategoryCompetitorList(void);


    //-- �������� ������ �������� ���������� � �������
    TList * getSelectedCompetitorsId(TStringGrid *grid, TList *list);
    //-- ������� ���������, ������� ������
    TCategory* createNewCategory(TComboBox *weightAgeList, TComboBox *fightVersionList);

public:		// User declarations
    __fastcall TfrmCategoryEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCategoryEdit *frmCategoryEdit;
//---------------------------------------------------------------------------




//-- ���������� ��������� ��� ������� � �����������
void setCategoryTableHeader(TStringGrid *grid);
//-- ���������� ��������� �������, ��� ���������� �� �������� � ���������
void setUncategoryTableHeader(TStringGrid *grid);
//-- ������� ���������� ������ ��������� � ������ ������
void createCategoryIndexFVComboBox(TList *category, TComboBox *cbFightVersion, map<AnsiString, TCategory*> &catIndex);
//-- ������� ������ ��� ���������� ��������� � ������ ������ ������
void createAgeWeightComboBoxByFV(TComboBox *cbCategory, TList *category, TComboBox *cbFightVersion);
//-- �������� ������ ���������, �������� � ���������� �������
TCategory* getCategoryByIndex(TComboBox *weightAgeList, TComboBox *fightVersionList, map<AnsiString, TCategory*>  catIndex);

//--�������� ���������� �� ���� ����������
void SortCategories(void);





#endif
