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
// данные в Exel
void TForm1::MakeReport()
{
    int Rnum = 1;

    ExcelInit("");

     // Объединим ячейки с A1 до E1
    Rang = Sh.OlePropertyGet("Range", "A1:E1");
    Rang.OleProcedure("Merge");

    // Установим характеристики шрифта font для выбранных ячеек
    Rang.OlePropertySet("Value", "Отчет о продажах товара");
    Rang.OlePropertyGet("Font").OlePropertySet("Name", "Verdana");
    Rang.OlePropertyGet("Font").OlePropertySet("Size", 18);
    Rang.OlePropertyGet("Font").OlePropertySet("Bold", true);

    // Выровняем текст в этих ячейках по центру
    Rang.OlePropertySet("HorizontalAlignment", 3);
    Rang.OlePropertySet("VerticalAlignment", 2);

    // Устанавливаем ширину первой строки 60
    Rang.OlePropertySet("RowHeight", 60);

     // Установим цвет
    Rang = Sh.OlePropertyGet("Range", "A1:E1");
    Rang.OlePropertyGet("Interior").OlePropertySet("ColorIndex",4);

     // определяем ширину столбцов
    Sh.OlePropertyGet("Columns").OlePropertyGet("Item",1).OlePropertySet("ColumnWidth", 12);
    Sh.OlePropertyGet("Columns").OlePropertyGet("Item",2).OlePropertySet("ColumnWidth", 25);
    Sh.OlePropertyGet("Columns").OlePropertyGet("Item",3).OlePropertySet("ColumnWidth", 8);
    Sh.OlePropertyGet("Columns").OlePropertyGet("Item",4).OlePropertySet("ColumnWidth", 10);
    Sh.OlePropertyGet("Columns").OlePropertyGet("Item",5).OlePropertySet("ColumnWidth", 10);

    Rnum = 2;
    toExcelCell(Rnum,1,String("Дата"));
    toExcelCell(Rnum,2,String("Наименование"));
    toExcelCell(Rnum,3,String("Количество"));
    toExcelCell(Rnum,4,String("Цена за единицу"));
    toExcelCell(Rnum,5,String("Сумма"));


    Rnum = 3;
    int i;
    for(i=Rnum; i<(Rnum+30); i++){
    // устанавливаем формат даты для ячейки
    Sh.OlePropertyGet("Cells", i,1).OlePropertySet("NumberFormat", "ДД.ММ.ГГГГ");
       // выводим данные
       toExcelCell(i, 1, Variant(Now() + i));
    // устанавливаем формат строка для ячейки
    Sh.OlePropertyGet("Cells", i,2).OlePropertySet("NumberFormat", "@");
       AnsiString s = "Молоко "+IntToStr(i+1)+"% жирности";
       toExcelCell(i, 2, String(s));
    // Выравнивам данные в ячейке
    Sh.OlePropertyGet("Cells", i,2).OlePropertySet("HorizontalAlignment", 4);
    // где 4 - по левому краю, 2 - по правому, 3 - по центру)

    // или по-другому это можно записать так
    // Rang = Sh.OlePropertyGet("Cells",i,2);
    // Rang.OlePropertySet("HorizontalAlignment",4);


    // устанавливаем формат числа для ячейки
    Sh.OlePropertyGet("Cells", i,3).OlePropertySet("NumberFormat", "0");
       toExcelCell(i, 3, Variant(i*2+3));
      // устанавливаем формат числа для ячейки
    Sh.OlePropertyGet("Cells", i,4).OlePropertySet("NumberFormat", "0.00");
       toExcelCell(i, 4, Variant(i*17.5+1));
      // устанавливаем формат числа для ячейки
    Sh.OlePropertyGet("Cells", i,5).OlePropertySet("NumberFormat", "0.00");
       toExcelCell(i, 5, Variant((i*2+3) * (i*17.5+1)));
       }

    Rnum = i;
    toExcelCell(Rnum,1,String("Итого"));
    formulaExcel(Rnum, 3, 30);
    formulaExcel(Rnum, 5, 30);

    // еще формула
    toExcelCell(Rnum+1,1,String("Налог 5%"));
    App.OlePropertyGet("Cells", Rnum+1, 5).OlePropertySet("Formula", String("=E33*5%").c_str());

    // и немного вертикального текста
    Sh.OlePropertyGet("Cells", 1, 7).OlePropertySet("Orientation", 90);
    Sh.OlePropertyGet("Cells", 1, 7).OlePropertySet("Value", "Hello !");

//----------------------
// ПРИМЕР - пример не поячеечного вывода, а сразу вывод массива данных
// Можно выводить данные последовательно в каждую ячейку, но это замедляет работу.
// Лучше сформировать вариантный массив, и выполнить присвоение области (Range) этого массива.

    Variant Cell1, Cell2, ArrayData;
    int Bounds[4] = {0,9,0,4};
    // Создаем вариантный массив, который заполним выходными данными
    ArrayData = VarArrayCreate(Bounds, 3,  varVariant);
    for(int i=0; i<9; i++){   // вывод некоторых данных в этот массив
         ArrayData.PutElement(i, i,0);
         ArrayData.PutElement("02.01.2003", i,1);
         ArrayData.PutElement("Сыр %"+IntToStr(i), i,2);
         ArrayData.PutElement(4*i, i,3);
         ArrayData.PutElement("Гост 177", i,4);
         }
   Cell1 = Sh.OlePropertyGet("Cells",38,1);
   Cell2 = Sh.OlePropertyGet("Cells",47,5);
   Rang = Sh.OlePropertyGet("Range", Cell1,Cell2);
   Rang.OlePropertySet("HorizontalAlignment", 3);
   Rang.OlePropertySet("VerticalAlignment", 2);
   Rang.OlePropertySet("Value", ArrayData);
//----------------------

    // сделать его видимым
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
    App.OlePropertyGet("Cells", sRow, sColumn).OlePropertySet("FormulaR1C1", ("=СУММ(R[-"+AnsiString(row)+"]C:R[-1]C)").c_str());
  } catch(...) { ; }
}/* formulaExcel() */
//---------------------------------------------------------------------------

void __fastcall TForm1::ExcelInit(String File)
{
  try {

   App=Variant::GetActiveObject("Excel.Application");
  } catch(...) {
     try { App=Variant::CreateObject("Excel.Application"); } catch (...) {
      Application->MessageBox("Невозможно открыть Microsoft Excel!"
      " Возможно этого приложения на компьютере не установлено.","Ошибка",MB_OK+MB_ICONERROR);
  } }
  try {

    if(File!="")
     App.OlePropertyGet("WorkBooks").OleProcedure("Open",File);
    else{
     // Определяем количество листов в книге (1)
     App.OlePropertySet("SheetsInNewWorkbook", 1);
     App.OlePropertyGet("WorkBooks").OleProcedure("add");
     }
     Sh=App.OlePropertyGet("WorkSheets",1);
     // Устанавливаем масштаб = 75%
    App.OlePropertyGet("ActiveWindow").OlePropertySet("Zoom", 75);
     // Даем название нашему листу
    Sh = App.OlePropertyGet("Worksheets").OlePropertyGet("Item", 1);
    Sh.OlePropertySet("Name", "Наш лист итогов");
  } catch(...) {
    Application->MessageBox("Ошибка открытия книги Microsoft Excel!","Ошибка",MB_OK+MB_ICONERROR);
  }
}/* ExcelInit() */
//---------------------------------------------------------------------------
// получить значение ячейки
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

// получить формулу из ячейки
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
// получаем значение и формулу из ячейки 34,5
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

// рисуем бордюр у выбранных ячеек
App.OlePropertyGet("Range", s.c_str()).OlePropertyGet("Borders").OlePropertySet("LineStyle", 1);

// Отрисовываем бордюр у ячейки 34,5
// LineStyle - определяет тип линии (у нас - 1 - сплошная)
// Border - определяет бордюр - 1 слева, 2 справа, 3 сверху, 4 снизу
// Weigh - определяет толщину бордюра
// ColorIndex - тут определяет цвет линии бордюра (3 - красный, 4 - зеленый и т.д.)
// например для  Border = 4 (нижней линии бордюра ячейки 34,5)
Sh.OlePropertyGet("Cells",34,5).OlePropertyGet("Borders",4).OlePropertySet("LineStyle",1);
Sh.OlePropertyGet("Cells",34,5).OlePropertyGet("Borders",4).OlePropertySet("Weight", 3);
Sh.OlePropertyGet("Cells",34,5).OlePropertyGet("Borders",4).OlePropertySet("ColorIndex", 3);
// или вот так:  для  Border = 3 (верхней линии бордюра ячейки 34,5)
Variant Bord;
Bord = Sh.OlePropertyGet("Cells",34,5).OlePropertyGet("Borders", 3);
Bord.OlePropertySet("LineStyle",1);
Bord.OlePropertySet("Weight",3);
Bord.OlePropertySet("ColorIndex", 4);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button5Click(TObject *Sender)
{
    // Устанавливаем масштаб
    int zoom = CSpinEdit1->Value;
    App.OlePropertyGet("ActiveWindow").OlePropertySet("Zoom", zoom);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
    // не спрашивать о замене, если такой документ уже есть
    App.OlePropertySet("DisplayAlerts", false);

    // сохранить изменения в указанный файл
    try{
    App.OlePropertyGet("WorkBooks",1).OleProcedure("SaveAs","Firm.xls");
    }catch(...){
         ShowMessage("Не забудьте сохранить сделанные изменения !");
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
         ShowMessage("Ошибка печати");
         }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button7Click(TObject *Sender)
{
   // закрыть книгу Excel
    try{
    App.OlePropertyGet("WorkBooks",1).OleProcedure("Close");
      }catch(...){
         ShowMessage("Не забудьте сами закрыть Excel.");
         }
    // закрыть сам Excel
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

