//---------------------------------------------------------------------------

#ifndef dataSourceDMH
#define dataSourceDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBDatabase.hpp>


//-- Состояние таблицы
enum SortState{ssUnsort, ssAscending, ssDescending};



//---------------------------------------------------------------------------
class TdmDataSource : public TDataModule
{
__published:	// IDE-managed Components
    TIBDatabase *ibdbSecretaryDB;
    TIBTransaction *ibtrSecretaryDB;
private:	// User declarations
public:		// User declarations
    __fastcall TdmDataSource(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TdmDataSource *dmDataSource;
//---------------------------------------------------------------------------
#endif
