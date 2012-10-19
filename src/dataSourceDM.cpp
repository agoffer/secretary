//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dataSourceDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmDataSource *dmDataSource;
//---------------------------------------------------------------------------
__fastcall TdmDataSource::TdmDataSource(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------



