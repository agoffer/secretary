//---------------------------------------------------------------------------

#ifndef categoryToPrintSelectUH
#define categoryToPrintSelectUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

#include <map.h>

#include "categoryCtrl.h"


//Тип протокола, который будет напечатан 
enum TReportType{
rtPAIRSORDER,
rtPROTOCOL,
rtFINALPROTOCOL, 
rtFIGHTTREE
};


//---------------------------------------------------------------------------
class TfrmCategoryToPrintSelect : public TForm
{
__published:	// IDE-managed Components
    TListBox *lbNotPrintedCategories;
    TListBox *lbPrintedCategories;
    TLabel *lblNotPrintedCategories;
    TBitBtn *bbtnCategoryToPrint;
    TBitBtn *bbtnCategoryToNotPrinted;
    TLabel *lblPrintedCategories;
    TBitBtn *bbtnCategoryUp;
    TBitBtn *bbtnCategoryDown;
    TBitBtn *bbtnClose;
    TBitBtn *bbtnPrint;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall bbtnCategoryToPrintClick(TObject *Sender);
    void __fastcall bbtnCategoryToNotPrintedClick(TObject *Sender);
    void __fastcall bbtnCategoryUpClick(TObject *Sender);
    void __fastcall bbtnCategoryDownClick(TObject *Sender);
    void __fastcall bbtnPrintClick(TObject *Sender);
private:	// User declarations
    //-- Список индексов категориий по ключу (строка представляющая категорию)
    map<AnsiString, TCategory*> categoryOrder;
    //Тип отчета, который будем печатать 
    TReportType reportType;

    //-- Формирует списоко из map
    TList * toTList(map<AnsiString, TCategory*> co, TListBox *lb);

    //-- Заголовки окна
    AnsiString pairsOrderTitle;
    AnsiString protocolTitle;
    AnsiString finalProtocolTitle;    
    AnsiString fightTreeTitle;

    //Построить список не печатаемый категорий 
    void createNotPrintedListBox(TList *categories, bool isIndexedFill);

public:		// User declarations
    __fastcall TfrmCategoryToPrintSelect(TComponent* Owner);
    //-- Печать списка пар
    void PrintPairsOrder(void);
    //-- Печать протоколов
    void PrintProtocols(void);
    //-- Печать заключительных протоколов
    void PrintFinalProtocols(void);
    //Печать "деревьев"
    void PrintFightTrees(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCategoryToPrintSelect *frmCategoryToPrintSelect;
//---------------------------------------------------------------------------
#endif
