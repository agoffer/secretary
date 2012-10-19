//---------------------------------------------------------------------------

#ifndef requestEditUH
#define requestEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>

#include "personCtrl.h"
#include "clubCtrl.h"
#include "utils.h"
//---------------------------------------------------------------------------
class TfrmRequestEdit : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grboxClub;
    TDBGrid *dbgrdClubList;
    TLabeledEdit *lbledtClubQuickSearch;
    TButton *btnAddClub;
    TGroupBox *grboxRepresentative;
    TDBGrid *dbgrdPersonList;
    TLabeledEdit *lbledtPersonQuickSearch;
    TButton *btnAddPerson;
    TMemo *memRequestComments;
    TLabel *lblRequestComments;
    TBitBtn *bbtnUpdateRequest;
    TBitBtn *bbtnCancelRequest;
    void __fastcall dbgrdClubListTitleClick(TColumn *Column);
    void __fastcall btnAddClubClick(TObject *Sender);
    void __fastcall btnAddPersonClick(TObject *Sender);
    void __fastcall dbgrdPersonListTitleClick(TColumn *Column);
    void __fastcall lbledtPersonQuickSearchChange(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall lbledtClubQuickSearchChange(TObject *Sender);
private:	// User declarations
    //-- ��������� (�������) �����
    void initFields(void);
    //--�������� ���� �������� ������
    void QuickSearchClear(void);
    //�������� ��������� ������ ������ � ������������ � ��������� � ���������� ���������� 
    void changePersonSearchTableState(void);
    void changeClubSearchTableState(void);

public:		// User declarations
    //-- �������� ������� ��������� ������
    void resetCallback(void);
    //-- ���������� ������� ��������� ������
    void setCallback(void);

    __fastcall TfrmRequestEdit(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRequestEdit *frmRequestEdit;


//--[�������� �����] ������� � ����� ������
extern void clubRecordMoveAction(void);
//--[�������� �����] ������� � ����� ������
extern void personRecordMoveAction(void);

//---------------------------------------------------------------------------
#endif
