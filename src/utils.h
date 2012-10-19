//---------------------------------------------------------------------------

#ifndef utilsH
#define utilsH


#include <vcl.h>



//-- ��������� �� ������� ��������� ������
typedef void (*CallbackFunction)(void);

enum TEntityType{
etCOMPETITOR,
etCATEGORY,
etAVAILCATEGORY,
etREQUEST,
etFIGHTVERSION,
etSKILL,
etCOMPETITIONRANK,
etSORTIONDATA
};


//-- ������� ����������� �������
extern int YearsPassCalculator(TDateTime date);

//-- ������� ����������� ��������� ������������� ������������ ��������
extern AnsiString FormatFloatValueText(AnsiString value);

//-- ������� ������� �������� � ������ � ������� ��� 
extern void destroyList(TList *list, TEntityType listtype);

//-- ������� ������� �������� � ������
extern void clearList(TList *list);



//---------------------------------------------------------------------------
#endif
