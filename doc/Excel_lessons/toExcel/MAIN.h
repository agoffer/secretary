//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *bToExcel;
        TButton *Button1;
        TLabel *Label3;
        TLabel *Label4;
        TButton *Button2;
        TButton *Button3;
        TButton *Button5;
        TCSpinEdit *CSpinEdit1;
        TButton *Button4;
        TButton *Button6;
        TButton *Button7;
        TButton *Button8;
        TButton *Button10;
        TButton *Button11;
        TEdit *Edit2;
        void __fastcall bToExcelClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
private:	// User declarations
        void __fastcall formulaExcel(int sRow, int sColumn, int row);
        void __fastcall ExcelInit(String File);
        void __fastcall toExcelCell(int c1,int c2, String data);
        void __fastcall toExcelCell(int c1,int c2, Variant data);
        Variant App,Sh,Rang;
        void MakeReport();
        //-----
        Variant __fastcall fromExcelCell(int Row, int Column);
        Variant __fastcall fromExcelFormula(int Row, int Column);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
