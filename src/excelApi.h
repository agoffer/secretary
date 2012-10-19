//---------------------------------------------------------------------------

#ifndef excelApiH
#define excelApiH

#include <vcl.h>


//����� ��� �������� ���������� � Excel


class TExcelApp{
private:
    Variant App, //Excel ����������
            Sh, //������� ����
            Range; //�������� �����

    //��� �����, � ������� ����� ����������� ����� 
    AnsiString fileToSave;

//������������ � Excel
void ExcelInit(AnsiString File);

public:

    TExcelApp(AnsiString templateName, AnsiString saveFileName);
    ~TExcelApp();  

    //-- �������� ������, ������ �������� ������
    void toExcelByCellNameOffs(const char *Exc, int off, String data);
    void toExcelByCellName(const char *Exc, double data);
    void toExcelByCellName(const char *Exc, int data);
    void toExcelByCellName(const char *Exc, AnsiString data);
    //-- �������� ������ � �� ��������
    void InsertRows(AnsiString range, int rowAmnt);
    //-- �������� ������, �������� ���������� ������
    void toExcelByRowCol(int c1,int c2, String data);
    void toExcelByRowCol(int c1,int c2, Variant data);

    //-- �������� � Excel ������ ��������
    Variant toExcelArrayToRange(Variant varArray, int r1, int c1, int r2, int c2);
    Variant toExcelArrayToRange(Variant varArray, AnsiString range, int cols, int rows);
    Variant toExcelArrayToRange(Variant varArray, AnsiString range, int offset, int cols, int rows);         

    //-- ������� ������� ������
    Variant createVariantArray(int row, int col);
};


//---------------------------------------------------------------------------
#endif
