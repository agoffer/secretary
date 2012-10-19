//---------------------------------------------------------------------------

#ifndef utilsH
#define utilsH


#include <vcl.h>



//-- Указатель на функцию обратного вызова
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


//-- Функция расчитывает возраст
extern int YearsPassCalculator(TDateTime date);

//-- Функция форматирует текстовое представление вещественной величины
extern AnsiString FormatFloatValueText(AnsiString value);

//-- Функция удаляет элементы в списке и удаляет его 
extern void destroyList(TList *list, TEntityType listtype);

//-- Функция удаляет элементы в списке
extern void clearList(TList *list);



//---------------------------------------------------------------------------
#endif
