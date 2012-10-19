//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTable *SaleMan;
        TTable *Goods;
        TDatabase *DBase;
        TIntegerField *SaleManID;
        TStringField *SaleManOrg;
        TStringField *SaleManAddr;
        TStringField *SaleManInn;
        TIntegerField *GoodsID;
        TIntegerField *GoodsIDSale;
        TStringField *GoodsName;
        TStringField *GoodsIzmer;
        TFloatField *GoodsCount;
        TCurrencyField *GoodsPrice;
        TButton *bToExcel;
        TDBGrid *Grid;
        TDataSource *dsSaleMan;
        TDBGrid *GGrid;
        TLabel *Label1;
        TDataSource *dsGoods;
        TLabel *Label2;
        TButton *bOpen;
        void __fastcall bOpenClick(TObject *Sender);
        void __fastcall bToExcelClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
