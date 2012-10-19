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
    // получаем сегодняшнюю дату
    TDate Today = Now();

    // устанавливаем путь к файлу шаблона
     AnsiString sFile = GetCurrentDir()+"\\NaclSf.xlt";

     // инициализируем Excel, открываем этот шаблон
     try {
       App=Variant::GetActiveObject("Excel.Application");
     } catch(...) {
     try { App=Variant::CreateObject("Excel.Application"); }
     catch (...) {
      Application->MessageBox("Невозможно открыть Microsoft Excel!"
      " Возможно этого приложения на компьютере не установлено.","Ошибка",MB_OK+MB_ICONERROR);
        }}
     try {
      App.OlePropertyGet("WorkBooks").OleProcedure("Open",sFile.c_str(),0,false,1);
      Sh=App.OlePropertyGet("WorkSheets",1);
     } catch(...) {
      Application->MessageBox("Ошибка открытия книги Microsoft Excel!","Ошибка",MB_OK+MB_ICONERROR);
     }

  // выводим в шаблон данные
  // сначала заголовок
  toExcel(App,"НомерНАКЛ",SaleManID->Value);
  toExcel(App,"ДатаНАКЛ",Today.DateString());
  toExcel(App,"ПоставщикНАКЛ",SaleManOrg->Value.c_str());
  toExcel(App,"ИННПНАКЛ",SaleManInn->Value.c_str());

  toExcel(App,"НомерСФ",SaleManID->Value);
  toExcel(App,"ДатаСФ",Today.DateString());
  toExcel(App,"АдресПСФ",SaleManAddr->Value.c_str());
  toExcel(App,"ПоставщикСФ",SaleManOrg->Value.c_str());
  toExcel(App,"ИННПСФ",SaleManInn->Value.c_str());

  // определяем в n количество товара (строк для ввода в шаблон)
  Goods->First();
  int n = 0;  while(!Goods->Eof) { n++; Goods->Next(); }

  // вставляем в шаблон нужное количество строк
  Variant C;
  App.OlePropertyGet("WorkSheets",1).OleProcedure("Select");
  C=App.OlePropertyGet("Range","ТоварСФ");
  C=App.OlePropertyGet("Rows",(int) C.OlePropertyGet("Row")+1);
  for(int i=1;i<n;i++) C.OleProcedure("Insert");

  App.OlePropertyGet("WorkSheets",2).OleProcedure("Select");
  C=App.OlePropertyGet("Range","ТоварНАКЛ");
  C=App.OlePropertyGet("Rows",(int) C.OlePropertyGet("Row")+1);
  for(int i=1;i<n;i++) C.OleProcedure("Insert");

  // вывод данных из накладной в эти строки
  Goods->First();
  int i = 0;
  while(!Goods->Eof){
    toExcel(App,"ТоварСФ",i,GoodsName->Value.c_str());
    toExcel(App,"ТоварНАКЛ",i,GoodsName->Value.c_str());
    toExcel(App,"НомерППНАКЛ",i,i+1);
    toExcel(App,"СтранаСФ",i,"Россия");
    toExcel(App,"ЕдизмСФ",i,GoodsIzmer->Value.c_str());
    toExcel(App,"ЕдизмНАКЛ",i,GoodsIzmer->Value.c_str());
    toExcel(App,"КолСФ",i,GoodsCount->Value);
    toExcel(App,"КолНАКЛ",i,GoodsCount->Value);
    toExcel(App,"ЦенаСФ",i,GoodsPrice->Value);
    toExcel(App,"ЦенаНАКЛ",i,GoodsPrice->Value);
    toExcel(App,"СтоимСФ",i,GoodsPrice->Value*GoodsCount->Value);
    toExcel(App,"СтоимостьСНДССФ",i,(GoodsPrice->Value*GoodsCount->Value*5)/100.);
    toExcel(App,"ВсегоНАКЛ",i,GoodsPrice->Value*GoodsCount->Value);
    toExcel(App,"СуммаНДССФ",i,(GoodsPrice->Value*GoodsCount->Value*5)/100.);
    toExcel(App,"СуммаНДСНАКЛ",i,(GoodsPrice->Value*GoodsCount->Value*5)/100.);
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

