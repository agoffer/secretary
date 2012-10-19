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
    //-- Установка (очистка) полей
    void initFields(void);
    //--Сбросить поля быстрого поиска
    void QuickSearchClear(void);
    //Изменить состояние таблиц поиска в соответствии с фильтрами и выбранными сущностями 
    void changePersonSearchTableState(void);
    void changeClubSearchTableState(void);

public:		// User declarations
    //-- Сбросить функцию обратного вызова
    void resetCallback(void);
    //-- Установить функцию обратного вызова
    void setCallback(void);

    __fastcall TfrmRequestEdit(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRequestEdit *frmRequestEdit;


//--[Обратрый вызов] перешли к новой записи
extern void clubRecordMoveAction(void);
//--[Обратрый вызов] перешли к новой записи
extern void personRecordMoveAction(void);

//---------------------------------------------------------------------------
#endif
