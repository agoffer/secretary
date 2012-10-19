//---------------------------------------------------------------------------


#pragma hdrstop

#include "excelApi.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TExcelApp::TExcelApp(AnsiString templateName, AnsiString saveFileName){
    //Подключиться к Excel
    ExcelInit(templateName);
    //Запомнить имя файла, в котором будем сохранять данные
    fileToSave = saveFileName;  
}


TExcelApp::~TExcelApp(){
    // сделать его видимым
    if(!App.IsEmpty())App.OlePropertySet("Visible",true);

    // не спрашивать о замене, если такой документ уже есть
    App.OlePropertySet("DisplayAlerts", false);
    // сохранить изменения в указанный файл
    try{
    App.OlePropertyGet("WorkBooks",1).OleProcedure("SaveAs",fileToSave.c_str());
    }catch(...){
         ShowMessage("Не забудьте сохранить сделанные изменения !");
         }
   // закрыть книгу Excel
    try{
//    App.OlePropertyGet("WorkBooks",1).OleProcedure("Close");
      }catch(...){
         ShowMessage("Не забудьте сами закрыть Excel.");
         }
    // закрыть сам Excel
//    App.OleProcedure("Quit");

    Range.Clear();
    Sh.Clear();
    App.Clear();
}



void TExcelApp::ExcelInit(AnsiString File)
{
  try {          

   App=Variant::GetActiveObject("Excel.Application");
  } catch(...) {
     try { App=Variant::CreateObject("Excel.Application"); } catch (...) {
      MessageDlg("Невозможно открыть Microsoft Excel!"
      " Возможно этого приложения на компьютере не установлено.",
            mtError, TMsgDlgButtons() << mbOK, 0);
    } }
  try {

    if(File!="")
     App.OlePropertyGet("WorkBooks").OleProcedure("Open",File.c_str(),0,false,1);
    else{
     // Определяем количество листов в книге (1)
     App.OlePropertySet("SheetsInNewWorkbook", 1);
     App.OlePropertyGet("WorkBooks").OleProcedure("add");
     }
     Sh=App.OlePropertyGet("WorkSheets",1);
     // Устанавливаем масштаб = 75%
    App.OlePropertyGet("ActiveWindow").OlePropertySet("Zoom", 75);
  } catch(...) {
    MessageDlg("Ошибка открытия книги Microsoft Excel!", mtError, TMsgDlgButtons() << mbOK, 0);
  }
}



void TExcelApp::InsertRows(AnsiString range, int rowAmnt){
  Variant C;
  App.OlePropertyGet("WorkSheets",1).OleProcedure("Select");
  C=App.OlePropertyGet("Range",range.c_str());
  C=App.OlePropertyGet("Rows",(int) C.OlePropertyGet("Row")+1);
  for(int i=1;i<rowAmnt;i++) C.OleProcedure("Insert");
}


void TExcelApp::toExcelByCellNameOffs(const char *Exc, int off, String data)
{
  try {
    App.OlePropertyGet("Range", Exc).OlePropertyGet("Offset", off).OlePropertySet("Value", data.c_str());
  } catch(...) { ; }
}
//---------------------------------------------------------------------------
void TExcelApp::toExcelByCellName(const char *Exc, double data)
{
  try {
    App.OlePropertyGet("Range", Exc).OlePropertySet("Value", data);
  } catch(...) { ; }
}

//---------------------------------------------------------------------------
void TExcelApp::toExcelByCellName(const char *Exc, int data)
{
  try {
    App.OlePropertyGet("Range", Exc).OlePropertySet("Value", data);
  } catch(...) { ; }
}

//---------------------------------------------------------------------------
void TExcelApp::toExcelByCellName(const char *Exc, AnsiString data)
{
  try {
    Variant  cur = App.OlePropertyGet("Range", Exc);
    cur.OlePropertySet("Value", data.c_str());
  } catch(...) { ; }
}
//---------------------------------------------------------------------------

void TExcelApp::toExcelByRowCol(int Row,int Column, AnsiString data)
{
  try {
    Variant  cur = Sh.OlePropertyGet("Cells", Row,Column);
    cur.OlePropertySet("Value", data.c_str());
  } catch(...) { ; }
}
//------------------------------------------------------------------------
void TExcelApp::toExcelByRowCol(int Row,int Column, Variant data)
{
  try {
    Variant  cur = Sh.OlePropertyGet("Cells", Row,Column);
    cur.OlePropertySet("Value", data);
  } catch(...) { ; }
}
//---------------------------------------------------------------------------

Variant TExcelApp::createVariantArray(int row, int col){
    int Bounds[4] = {0,row,0,col};
    // Создаем вариантный массив, который заполним выходными данными
    Variant ArrayData = VarArrayCreate(Bounds, 3,  varVariant);

    return ArrayData;
}

Variant TExcelApp::toExcelArrayToRange(Variant varArray, int r1, int c1, int r2, int c2){
   Variant Cell1 = Sh.OlePropertyGet("Cells",r1,c1);
   Variant Cell2 = Sh.OlePropertyGet("Cells",r2,c2);
   Range = Sh.OlePropertyGet("Range", Cell1,Cell2);
   Range.OlePropertySet("Value", varArray);
   return Range;
}

Variant TExcelApp::toExcelArrayToRange(Variant varArray, AnsiString range, int cols, int rows){

   Variant cell1 = App.OlePropertyGet("Range",range.c_str());
   cell1 = cell1.OlePropertyGet("Offset", 1); 
   Variant cell2 = cell1.OlePropertyGet("Offset", rows, cols);

   Range = Sh.OlePropertyGet("Range", cell1,cell2);
   Range.OlePropertySet("Value", varArray);
   return Range;
}

Variant TExcelApp::toExcelArrayToRange(Variant varArray, AnsiString range, int offset, int cols, int rows){
   Variant cell1 = App.OlePropertyGet("Range",range.c_str());
   cell1 = cell1.OlePropertyGet("Offset", 1 + offset); 
   Variant cell2 = cell1.OlePropertyGet("Offset", rows, cols);

   Range = Sh.OlePropertyGet("Range", cell1,cell2);
   Range.OlePropertySet("Value", varArray);
   return Range;

}

