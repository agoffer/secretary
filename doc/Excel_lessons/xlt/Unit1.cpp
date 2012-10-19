//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

Variant App, Sh;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bOpenClick(TObject *Sender)
{
    SaleMan->Close(); Goods->Close();
    DBase->Connected = false;
    AnsiString sWay = GetCurrentDir();
    DBase->Params->Strings[0] = "PATH=" + sWay;
    DBase->Connected = true;
    SaleMan->Open(); Goods->Open();
}
//---------------------------------------------------------------------------

Variant toExcel(Variant App,const char *Exc, int off, String data)
{
  try {
    App.OlePropertyGet("Range", Exc).OlePropertyGet("Offset", off).OlePropertySet("Value", data.c_str());
  } catch(...) { ; }
}/* toExcel() */
//---------------------------------------------------------------------------
Variant  toExcel(Variant App,const char *Exc, double data)
{
  try {
    App.OlePropertyGet("Range", Exc).OlePropertySet("Value", data);
  } catch(...) { ; }
}/* toExcel() */

//---------------------------------------------------------------------------
Variant  toExcel(Variant App,const char *Exc, int data)
{
  try {
    App.OlePropertyGet("Range", Exc).OlePropertySet("Value", data);
  } catch(...) { ; }
}/* toExcel() */

//---------------------------------------------------------------------------
Variant  toExcel(Variant App,const char *Exc, AnsiString data)
{
  try {
    Variant  cur = App.OlePropertyGet("Range", Exc);
    cur.OlePropertySet("Value", data.c_str());
  } catch(...) { ; }
}/* toExcel() */
//---------------------------------------------------------------------------

void __fastcall TForm1::bToExcelClick(TObject *Sender)
{
    // �������� ����������� ����
    TDate Today = Now();

    // ������������� ���� � ����� �������
     AnsiString sFile = GetCurrentDir()+"\\NaclSf.xlt";

     // �������������� Excel, ��������� ���� ������
     try {
       App=Variant::GetActiveObject("Excel.Application");
     } catch(...) {
     try { App=Variant::CreateObject("Excel.Application"); }
     catch (...) {
      Application->MessageBox("���������� ������� Microsoft Excel!"
      " �������� ����� ���������� �� ���������� �� �����������.","������",MB_OK+MB_ICONERROR);
        }}
     try {
      App.OlePropertyGet("WorkBooks").OleProcedure("Open",sFile.c_str(),0,false,1);
      Sh=App.OlePropertyGet("WorkSheets",1);
     } catch(...) {
      Application->MessageBox("������ �������� ����� Microsoft Excel!","������",MB_OK+MB_ICONERROR);
     }

  // ������� � ������ ������
  // ������� ���������
  toExcel(App,"���������",SaleManID->Value);
  toExcel(App,"��������",Today.DateString());
  toExcel(App,"�������������",SaleManOrg->Value.c_str());
  toExcel(App,"��������",SaleManInn->Value.c_str());

  toExcel(App,"�������",SaleManID->Value);
  toExcel(App,"������",Today.DateString());
  toExcel(App,"��������",SaleManAddr->Value.c_str());
  toExcel(App,"�����������",SaleManOrg->Value.c_str());
  toExcel(App,"������",SaleManInn->Value.c_str());

  // ���������� � n ���������� ������ (����� ��� ����� � ������)
  Goods->First();
  int n = 0;  while(!Goods->Eof) { n++; Goods->Next(); }

  // ��������� � ������ ������ ���������� �����
  Variant C;
  App.OlePropertyGet("WorkSheets",1).OleProcedure("Select");
  C=App.OlePropertyGet("Range","�������");
  C=App.OlePropertyGet("Rows",(int) C.OlePropertyGet("Row")+1);
  for(int i=1;i<n;i++) C.OleProcedure("Insert");

  App.OlePropertyGet("WorkSheets",2).OleProcedure("Select");
  C=App.OlePropertyGet("Range","���������");
  C=App.OlePropertyGet("Rows",(int) C.OlePropertyGet("Row")+1);
  for(int i=1;i<n;i++) C.OleProcedure("Insert");

  // ����� ������ �� ��������� � ��� ������
  Goods->First();
  int i = 0;
  while(!Goods->Eof){
    toExcel(App,"�������",i,GoodsName->Value.c_str());
    toExcel(App,"���������",i,GoodsName->Value.c_str());
    toExcel(App,"�����������",i,i+1);
    toExcel(App,"��������",i,"������");
    toExcel(App,"�������",i,GoodsIzmer->Value.c_str());
    toExcel(App,"���������",i,GoodsIzmer->Value.c_str());
    toExcel(App,"�����",i,GoodsCount->Value);
    toExcel(App,"�������",i,GoodsCount->Value);
    toExcel(App,"������",i,GoodsPrice->Value);
    toExcel(App,"��������",i,GoodsPrice->Value);
    toExcel(App,"�������",i,GoodsPrice->Value*GoodsCount->Value);
    toExcel(App,"���������������",i,(GoodsPrice->Value*GoodsCount->Value*5)/100.);
    toExcel(App,"���������",i,GoodsPrice->Value*GoodsCount->Value);
    toExcel(App,"����������",i,(GoodsPrice->Value*GoodsCount->Value*5)/100.);
    toExcel(App,"������������",i,(GoodsPrice->Value*GoodsCount->Value*5)/100.);
    i++; Goods->Next();
     }

  App.OlePropertySet("Visible",true);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  App.OleProcedure("Quit");
  Sh.Clear();
  App.Clear();
}
//---------------------------------------------------------------------------

