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


//��� ���������, ������� ����� ��������� 
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
    //-- ������ �������� ���������� �� ����� (������ �������������� ���������)
    map<AnsiString, TCategory*> categoryOrder;
    //��� ������, ������� ����� �������� 
    TReportType reportType;

    //-- ��������� ������� �� map
    TList * toTList(map<AnsiString, TCategory*> co, TListBox *lb);

    //-- ��������� ����
    AnsiString pairsOrderTitle;
    AnsiString protocolTitle;
    AnsiString finalProtocolTitle;    
    AnsiString fightTreeTitle;

    //��������� ������ �� ���������� ��������� 
    void createNotPrintedListBox(TList *categories, bool isIndexedFill);

public:		// User declarations
    __fastcall TfrmCategoryToPrintSelect(TComponent* Owner);
    //-- ������ ������ ���
    void PrintPairsOrder(void);
    //-- ������ ����������
    void PrintProtocols(void);
    //-- ������ �������������� ����������
    void PrintFinalProtocols(void);
    //������ "��������"
    void PrintFightTrees(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCategoryToPrintSelect *frmCategoryToPrintSelect;
//---------------------------------------------------------------------------
#endif
