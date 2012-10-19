//---------------------------------------------------------------------------

#ifndef personFullEditUH
#define personFullEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

// Функция обратного вызова - при изменении строки в основй таблице, заполняем данные для редактирования
void onScrollPopulateEditFields(void);

class TfrmPersonFullEdit : public TForm
{
__published:	// IDE-managed Components
    TPanel *pnlPersonData;
    TGroupBox *grboxPersonToUseList;
    TDBGrid *dbgrdPersonToUseList;
    TGroupBox *grboxPersonEditList;
    TDBGrid *dbgrdPersonEditList;
    TLabeledEdit *lbledtSurname;
    TLabeledEdit *lbledtName;
    TLabeledEdit *lbledtPatronymic;
    TDateTimePicker *dtpDOB;
    TLabel *lblDOB;
    TCheckBox *chboxFemale;
    TLabeledEdit *lbledtPhone;
    TMemo *memComments;
    TLabel *lblComments;
    TBitBtn *bbtnUpdate;
    TBitBtn *bbtnReplace;
    TBitBtn *bbtnDelete;
    TBitBtn *bbtnClose;
    TGroupBox *GroupBox1;
    TLabeledEdit *lbledtLeftPaneSurnameFilter;
    TLabeledEdit *lbledtRightPaneSurnameFilter;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall lbledtLeftPaneSurnameFilterChange(TObject *Sender);
    void __fastcall lbledtRightPaneSurnameFilterChange(TObject *Sender);
    void __fastcall bbtnDeleteClick(TObject *Sender);
    void __fastcall bbtnUpdateClick(TObject *Sender);
    void __fastcall bbtnReplaceClick(TObject *Sender);
private:	// User declarations
    // Инициализация формы при отображении
    void InitForm();
    void initTables();
    // Сделать выборку данных в таблицах, с учетом фильтров
    void changeMasterTable(AnsiString surnameFilter, AnsiString nameFilter);
    void changeSlaveTable(AnsiString surnameFilter, AnsiString nameFilter);
public:		// User declarations
    __fastcall TfrmPersonFullEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPersonFullEdit *frmPersonFullEdit;
//---------------------------------------------------------------------------
#endif
