//---------------------------------------------------------------------------

#ifndef excelApiH
#define excelApiH

#include <vcl.h>


//Класс для объектов работающих с Excel


class TExcelApp{
private:
    Variant App, //Excel приложение
            Sh, //Текущий лист
            Range; //Диапазон ячеек

    //Имя файла, в котором будет сохраняться отчет 
    AnsiString fileToSave;

//Подключиться к Excel
void ExcelInit(AnsiString File);

public:

    TExcelApp(AnsiString templateName, AnsiString saveFileName);
    ~TExcelApp();  

    //-- Вставить данные, ячейка задается именем
    void toExcelByCellNameOffs(const char *Exc, int off, String data);
    void toExcelByCellName(const char *Exc, double data);
    void toExcelByCellName(const char *Exc, int data);
    void toExcelByCellName(const char *Exc, AnsiString data);
    //-- Добавить строку в на странице
    void InsertRows(AnsiString range, int rowAmnt);
    //-- Вставить данные, задается координаты ячейки
    void toExcelByRowCol(int c1,int c2, String data);
    void toExcelByRowCol(int c1,int c2, Variant data);

    //-- Вставить в Excel массив значений
    Variant toExcelArrayToRange(Variant varArray, int r1, int c1, int r2, int c2);
    Variant toExcelArrayToRange(Variant varArray, AnsiString range, int cols, int rows);
    Variant toExcelArrayToRange(Variant varArray, AnsiString range, int offset, int cols, int rows);         

    //-- Создаем вариант массив
    Variant createVariantArray(int row, int col);
};


//---------------------------------------------------------------------------
#endif
