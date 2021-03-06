//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include <excel_2k.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::bToExcelClick(TObject *Sender)
{
    MakeReport();
}
//---------------------------------------------------------------------------
// ������ � Exel
void TForm1::MakeReport()
{
    int Rnum = 1;

    ExcelInit("");

     // ��������� ������ � A1 �� E1
    Rang = Sh.OlePropertyGet("Range", "A1:E1");
    Rang.OleProcedure("Merge");

    // ��������� �������������� ������ font ��� ��������� �����
    Rang.OlePropertySet("Value", "����� � �������� ������");
    Rang.OlePropertyGet("Font").OlePropertySet("Name", "Verdana");
    Rang.OlePropertyGet("Font").OlePropertySet("Size", 18);
    Rang.OlePropertyGet("Font").OlePropertySet("Bold", true);

    // ��������� ����� � ���� ������� �� ������
    Rang.OlePropertySet("HorizontalAlignment", 3);
    Rang.OlePropertySet("VerticalAlignment", 2);

    // ������������� ������ ������ ������ 60
    Rang.OlePropertySet("RowHeight", 60);

     // ��������� ����
    Rang = Sh.OlePropertyGet("Range", "A1:E1");
    Rang.OlePropertyGet("Interior").OlePropertySet("ColorIndex",4);

     // ���������� ������ ��������
    Sh.OlePropertyGet("Columns").OlePropertyGet("Item",1).OlePropertySet("ColumnWidth", 12);
    Sh.OlePropertyGet("Columns").OlePropertyGet("Item",2).OlePropertySet("ColumnWidth", 25);
    Sh.OlePropertyGet("Columns").OlePropertyGet("Item",3).OlePropertySet("ColumnWidth", 8);
    Sh.OlePropertyGet("Columns").OlePropertyGet("Item",4).OlePropertySet("ColumnWidth", 10);
    Sh.OlePropertyGet("Columns").OlePropertyGet("Item",5).OlePropertySet("ColumnWidth", 10);

    Rnum = 2;
    toExcelCell(Rnum,1,String("����"));
    toExcelCell(Rnum,2,String("������������"));
    toExcelCell(Rnum,3,String("����������"));
    toExcelCell(Rnum,4,String("���� �� �������"));
    toExcelCell(Rnum,5,String("�����"));


    Rnum = 3;
    int i;
    for(i=Rnum; i<(Rnum+30); i++){
    // ������������� ������ ���� ��� ������
    Sh.OlePropertyGet("Cells", i,1).OlePropertySet("NumberFormat", "��.��.����");
       // ������� ������
       toExcelCell(i, 1, Variant(Now() + i));
    // ������������� ������ ������ ��� ������
    Sh.OlePropertyGet("Cells", i,2).OlePropertySet("NumberFormat", "@");
       AnsiString s = "������ "+IntToStr(i+1)+"% ��������";
       toExcelCell(i, 2, String(s));
    // ���������� ������ � ������
    Sh.OlePropertyGet("Cells", i,2).OlePropertySet("HorizontalAlignment", 4);
    // ��� 4 - �� ������ ����, 2 - �� �������, 3 - �� ������)

    // ��� ��-������� ��� ����� �������� ���
    // Rang = Sh.OlePropertyGet("Cells",i,2);
    // Rang.OlePropertySet("HorizontalAlignment",4);


    // ������������� ������ ����� ��� ������
    Sh.OlePropertyGet("Cells", i,3).OlePropertySet("NumberFormat", "0");
       toExcelCell(i, 3, Variant(i*2+3));
      // ������������� ������ ����� ��� ������
    Sh.OlePropertyGet("Cells", i,4).OlePropertySet("NumberFormat", "0.00");
       toExcelCell(i, 4, Variant(i*17.5+1));
      // ������������� ������ ����� ��� ������
    Sh.OlePropertyGet("Cells", i,5).OlePropertySet("NumberFormat", "0.00");
       toExcelCell(i, 5, Variant((i*2+3) * (i*17.5+1)));
       }

    Rnum = i;
    toExcelCell(Rnum,1,String("�����"));
    formulaExcel(Rnum, 3, 30);
    formulaExcel(Rnum, 5, 30);

    // ��� �������
    toExcelCell(Rnum+1,1,String("����� 5%"));
    App.OlePropertyGet("Cells", Rnum+1, 5).OlePropertySet("Formula", String("=E33*5%").c_str());

    // � ������� ������������� ������
    Sh.OlePropertyGet("Cells", 1, 7).OlePropertySet("Orientation", 90);
    Sh.OlePropertyGet("Cells", 1, 7).OlePropertySet("Value", "Hello !");

//----------------------
// ������ - ������ �� ����������� ������, � ����� ����� ������� ������
// ����� �������� ������ ��������������� � ������ ������, �� ��� ��������� ������.
// ����� ������������ ���������� ������, � ��������� ���������� ������� (Range) ����� �������.

    Variant Cell1, Cell2, ArrayData;
    int Bounds[4] = {0,9,0,4};
    // ������� ���������� ������, ������� �������� ��������� �������
    ArrayData = VarArrayCreate(Bounds, 3,  varVariant);
    for(int i=0; i<9; i++){   // ����� ��������� ������ � ���� ������
         ArrayData.PutElement(i, i,0);
         ArrayData.PutElement("02.01.2003", i,1);
         ArrayData.PutElement("��� %"+IntToStr(i), i,2);
         ArrayData.PutElement(4*i, i,3);
         ArrayData.PutElement("���� 177", i,4);
         }
   Cell1 = Sh.OlePropertyGet("Cells",38,1);
   Cell2 = Sh.OlePropertyGet("Cells",47,5);
   Rang = Sh.OlePropertyGet("Range", Cell1,Cell2);
   Rang.OlePropertySet("HorizontalAlignment", 3);
   Rang.OlePropertySet("VerticalAlignment", 2);
   Rang.OlePropertySet("Value", ArrayData);
//----------------------

    // ������� ��� �������
    if(!App.IsEmpty())App.OlePropertySet("Visible",true);
}

//------------------------------------------------------------------------
void __fastcall TForm1::toExcelCell(int Row,int Column, AnsiString data)
{
  try {
    Variant  cur = Sh.OlePropertyGet("Cells", Row,Column);
    cur.OlePropertySet("Value", data.c_str());
  } catch(...) { ; }
}/* toExcelCell() */
//------------------------------------------------------------------------
void __fastcall TForm1::toExcelCell(int Row,int Column, Variant data)
{
  try {
    Variant  cur = Sh.OlePropertyGet("Cells", Row,Column);
    cur.OlePropertySet("Value", data);
  } catch(...) { ; }
}/* toExcelCell() */
//---------------------------------------------------------------------------
void __fastcall TForm1::formulaExcel(int sRow, int sColumn, int row)
{
   try {
    App.OlePropertyGet("Cells", sRow, sColumn).OlePropertySet("FormulaR1C1", ("=����(R[-"+AnsiString(row)+"]C:R[-1]C)").c_str());
  } catch(...) { ; }
}/* formulaExcel() */
//---------------------------------------------------------------------------

void __fastcall TForm1::ExcelInit(String File)
{
  try {

   App=Variant::GetActiveObject("Excel.Application");
  } catch(...) {
     try { App=Variant::CreateObject("Excel.Application"); } catch (...) {
      Application->MessageBox("���������� ������� Microsoft Excel!"
      " �������� ����� ���������� �� ���������� �� �����������.","������",MB_OK+MB_ICONERROR);
  } }
  try {

    if(File!="")
     App.OlePropertyGet("WorkBooks").OleProcedure("Open",File);
    else{
     // ���������� ���������� ������ � ����� (1)
     App.OlePropertySet("SheetsInNewWorkbook", 1);
     App.OlePropertyGet("WorkBooks").OleProcedure("add");
     }
     Sh=App.OlePropertyGet("WorkSheets",1);
     // ������������� ������� = 75%
    App.OlePropertyGet("ActiveWindow").OlePropertySet("Zoom", 75);
     // ���� �������� ������ �����
    Sh = App.OlePropertyGet("Worksheets").OlePropertyGet("Item", 1);
    Sh.OlePropertySet("Name", "��� ���� ������");
  } catch(...) {
    Application->MessageBox("������ �������� ����� Microsoft Excel!","������",MB_OK+MB_ICONERROR);
  }
}/* ExcelInit() */
//---------------------------------------------------------------------------
// �������� �������� ������
Variant __fastcall TForm1::fromExcelCell(int Row, int Column)
{
       try{
       Variant result,cur;
       cur = Sh.OlePropertyGet("Cells",Row,Column);
       result = cur.OlePropertyGet("Value");
       return result;
          }catch(...) {;}
}
//-------------------

// �������� ������� �� ������
Variant __fastcall TForm1::fromExcelFormula(int Row, int Column)
{
       try{
       Variant result,cur;
       cur = Sh.OlePropertyGet("Cells",Row,Column);
       result = cur.OlePropertyGet("Formula");
       return result;
          }catch(...) {;}
}
//-------------------
// �������� �������� � ������� �� ������ 34,5
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Label3->Caption = fromExcelCell(34,5);
    Label4->Caption = fromExcelFormula(34,5);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    Variant Chart;
    Chart=App.OlePropertyGet("Charts").OleFunction("Add");
    Chart.OlePropertySet("ChartType",65);
    Chart.OleProcedure("SetSourceData",Sh.OlePropertyGet("Range",Sh.OlePropertyGet("Cells",3,3),Sh.OlePropertyGet("Cells",32,3)),2);
    Chart.OlePropertyGet("SeriesCollection",1).OlePropertySet("XValues",Sh.OlePropertyGet("Range",Sh.OlePropertyGet("Cells",3,3),Sh.OlePropertyGet("Cells",32,3)));
    Chart.OleProcedure("Location",2,Sh.OlePropertyGet("Name"));
    Sh.OlePropertyGet("ChartObjects",1).OlePropertySet("Top",Sh.OlePropertyGet("UsedRange").OlePropertyGet("Height")+25);
    Sh.OlePropertyGet("ChartObjects",1).OlePropertySet("left",10);
    Sh.OlePropertyGet("Cells",1,1).OleProcedure("Select");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
int m = 31;
AnsiString s = "A2:E"+IntToStr(m+1);

// ������ ������ � ��������� �����
App.OlePropertyGet("Range", s.c_str()).OlePropertyGet("Borders").OlePropertySet("LineStyle", 1);

// ������������ ������ � ������ 34,5
// LineStyle - ���������� ��� ����� (� ��� - 1 - ��������)
// Border - ���������� ������ - 1 �����, 2 ������, 3 ������, 4 �����
// Weigh - ���������� ������� �������
// ColorIndex - ��� ���������� ���� ����� ������� (3 - �������, 4 - ������� � �.�.)
// �������� ���  Border = 4 (������ ����� ������� ������ 34,5)
Sh.OlePropertyGet("Cells",34,5).OlePropertyGet("Borders",4).OlePropertySet("LineStyle",1);
Sh.OlePropertyGet("Cells",34,5).OlePropertyGet("Borders",4).OlePropertySet("Weight", 3);
Sh.OlePropertyGet("Cells",34,5).OlePropertyGet("Borders",4).OlePropertySet("ColorIndex", 3);
// ��� ��� ���:  ���  Border = 3 (������� ����� ������� ������ 34,5)
Variant Bord;
Bord = Sh.OlePropertyGet("Cells",34,5).OlePropertyGet("Borders", 3);
Bord.OlePropertySet("LineStyle",1);
Bord.OlePropertySet("Weight",3);
Bord.OlePropertySet("ColorIndex", 4);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button5Click(TObject *Sender)
{
    // ������������� �������
    int zoom = CSpinEdit1->Value;
    App.OlePropertyGet("ActiveWindow").OlePropertySet("Zoom", zoom);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
    // �� ���������� � ������, ���� ����� �������� ��� ����
    App.OlePropertySet("DisplayAlerts", false);

    // ��������� ��������� � ��������� ����
    try{
    App.OlePropertyGet("WorkBooks",1).OleProcedure("SaveAs","Firm.xls");
    }catch(...){
         ShowMessage("�� �������� ��������� ��������� ��������� !");
         }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
    try{
    Sh.OlePropertyGet("PageSetup").OlePropertySet("LeftMargin", 30);
    Sh.OlePropertyGet("PageSetup").OlePropertySet("RightMargin",20);

    Sh.OlePropertyGet("PageSetup").OlePropertySet("PrintTitleRows","$3:$3");
    Sh.OlePropertyGet("PageSetup").OlePropertySet("PrintTitleColumns","$A:$A");
    App.OlePropertyGet("WorkBooks",1).OleProcedure("PrintOut");
      }catch(...){
         ShowMessage("������ ������");
         }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button7Click(TObject *Sender)
{
   // ������� ����� Excel
    try{
    App.OlePropertyGet("WorkBooks",1).OleProcedure("Close");
      }catch(...){
         ShowMessage("�� �������� ���� ������� Excel.");
         }
    // ������� ��� Excel
    App.OleProcedure("Quit");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    Rang.Clear();
    Sh.Clear();
    App.Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
    App.OleProcedure("Run","MyMacros1");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button10Click(TObject *Sender)
{
    Sh.OlePropertyGet("Range", "E34:E34").OlePropertySet("Name","myNameCell");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
    AnsiString newCellName = Edit2->Text;
    Sh.OlePropertyGet("Range", "myNameCell").OlePropertySet("Name", newCellName.c_str());
}
//---------------------------------------------------------------------------

