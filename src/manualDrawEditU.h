//---------------------------------------------------------------------------

#ifndef manualDrawEditUH
#define manualDrawEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Buttons.hpp>

#include "categoryCtrl.h"

//---------------------------------------------------------------------------
class TfrmManualDraw : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grboxTree;
    TGroupBox *grboxDrawList;
    TLabel *lblAvailCategoryFirst;
    TComboBox *cmboxAvailCategory;
    TLabel *lblFightVersionFirst;
    TComboBox *cmboxFightVersion;
    TCheckBox *chboxFemaleCategory;
    TBitBtn *bbtnClose;
    TBitBtn *bbtnSaveDraw;
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall chboxFemaleCategoryClick(TObject *Sender);
    void __fastcall changeCompetitorList(TObject *Sender);
    void __fastcall cmboxFightVersionChange(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall bbtnSaveDrawClick(TObject *Sender);
    //--- Обработчик события, изменение номер в жеребьевке 
    void __fastcall changeDrawNumber(TObject *Sender);
private:
    //-- Список индексов категориий по ключу (строка представляющая категорию)
    map<AnsiString, TCategory*> categoryIndex;
    //-- Текущая, выбранная категория
    TCategory *currentCategory;
    //-- Текущий список участников
    TList * currentCompetitorList;
    //-- Шаблон номеров в жеребьевке
    TStrings *templateDrawNumber;
    //-- Порядок участников в дереве, меняется динамически
    int* treeOrder;  

    //-- Инициализация формы
    void InitFields(void);

    //-- Отобразить на форме участников в дереве
    void drawCompetitorTree(TList *competitorList, int* order);
    //-- Создать список участников для жеребьевки
    void createDrawList(TList *competitorList);

    void createCategories(TList *category);
    //-- Создает массив с порядком сортировки участников
    int* collectSortionOrder(TList * competitorList);

    //-- Получаем имя клуба
    AnsiString getClubName(int clubId);
public:		// User declarations
    __fastcall TfrmManualDraw(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmManualDraw *frmManualDraw;
//---------------------------------------------------------------------------
#endif
