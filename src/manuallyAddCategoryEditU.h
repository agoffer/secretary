//---------------------------------------------------------------------------

#ifndef manuallyAddCategoryEditUH
#define manuallyAddCategoryEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfrmManuallyAddCategoryEdit : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grboxAvailCategory;
    TDBGrid *dbgrAvailCategories;
    TBitBtn *bbtnAddAvailCategory;
    TGroupBox *grboxFightVersion;
    TComboBox *cmboxFightVersion;
    TBitBtn *bbtnAddFightVersion;
    TBitBtn *bbtnCancel;
    TBitBtn *bbtnAddCategory;
    TMaskEdit *mskedtEndAge;
    TMaskEdit *mskedtEndWeight;
    TMaskEdit *mskedtStartAge;
    TMaskEdit *mskedtStartWeight;
    TLabel *lblSearchAge;
    TLabel *lblSearchWeight;
  TBitBtn *bbtnDeleteAvailCategory;
    void __fastcall bbtnAddAvailCategoryClick(TObject *Sender);
    void __fastcall bbtnAddFightVersionClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall mskedtSearchChange(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall bbtnDeleteAvailCategoryClick(TObject *Sender);
private:	// User declarations
    //-- ���������� ������� ��������� ��������� � ����������� �� �������� 
    void setAvailCategoryTable(int sa, int ea, double sw, double ew);
    //-- �������� "����������" �������� ����� �������
    void getValidValues(int &sa, int &ea, double &sw, double &ew);

    //-- ������� ������ ������ ������
    void createFightVersionList(void);
    //-- �������� ������ ������ ������
    void clearFightVersionList(void);
    //-- ������������� ����� 
    void InitFields(void);
public:		// User declarations
    __fastcall TfrmManuallyAddCategoryEdit(TComponent* Owner);
    //������� ������ ������� ���������
    bool female;    
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmManuallyAddCategoryEdit *frmManuallyAddCategoryEdit;
//---------------------------------------------------------------------------
#endif
