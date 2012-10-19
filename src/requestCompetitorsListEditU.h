//---------------------------------------------------------------------------

#ifndef requestCompetitorsListEditUH
#define requestCompetitorsListEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>


#include "competitorDM.h"
#include "personDM.h"
#include "fightVersionCtrl.h"
#include "skillCtrl.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmRequestCompetitorsListEdit : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grboxCompetitorsList;
    TStringGrid *strgrdCompetitorsList;
    TPanel *pnlCompetitor;
    TGroupBox *grboxCompetitorEdit;
    TLabel *lblDOB;
    TLabel *lblWeight;
    TLabel *lblSkill;
    TLabel *lblFightVersion;
    TLabeledEdit *lbledtSurname;
    TLabeledEdit *lbledtName;
    TLabeledEdit *lbledtPatronymic;
    TDateTimePicker *dtpDOB;
    TMaskEdit *medtWeight;
    TComboBox *cmboxSkill;
    TButton *btnAddSkill;
    TButton *btnAddFightVersion;
    TCheckListBox *chlstboxFightVersion;
    TBitBtn *bbtnAddCompetitor;
    TBitBtn *bbtnCloseList;
    TGroupBox *grboxPersonQuickSearch;
    TDBGrid *dbgrdPersonList;
    TBitBtn *bbtnToEditBox;
    TLabel *lblFullAge;
    TStaticText *sttxtFullAge;
    TBitBtn *bbtnUpdateCompetitor;
    TBitBtn *bbtnCancelCompetitor;
    TCheckBox *chboxFemale;
    TPanel *pnlButtons;
    TBitBtn *bbtnEdit;
    TBitBtn *bbtnDelete;
    TBitBtn *bbtnPrintRequest;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnAddSkillClick(TObject *Sender);
    void __fastcall btnAddFightVersionClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall lbledtSurnameChange(TObject *Sender);
    void __fastcall bbtnToEditBoxClick(TObject *Sender);
    void __fastcall dtpDOBChange(TObject *Sender);
    void __fastcall bbtnAddCompetitorClick(TObject *Sender);
    void __fastcall medtWeightExit(TObject *Sender);
    void __fastcall bbtnDeleteClick(TObject *Sender);
    void __fastcall bbtnEditClick(TObject *Sender);
    void __fastcall bbtnUpdateCompetitorClick(TObject *Sender);
    void __fastcall bbtnCancelCompetitorClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    //-- Инициализация полей
    void InitFields(void);
    //-- Очистить поля, перед вводом нового участника
    void clearFields(void);
    //-- Создать список боевых версий
    void createFightVersionList(void);
    //-- Удалить список боевых версий
    void destroyFightVersionList(void);
    //-- Создать список уровней мастерства
    void createSkillList(void);
    //-- Удалить список уровней мастерства
    void destroySkillList(void);
    

    //-- Изменить состояние таблиц поиска в соответствии с фильтрами
    void changePersonSearchTableState(void);

    //-- Заполнить поля участника из таблицы выбанной личностью
    void fillCompetitorPerson(void);

    //-- Получить из формы данные об участнике и добавить их базу данных
    bool CompetitorIntoDatabase(TPerson& obj, TCompetitor *newCompetitor);

    //-- Сформировать список идентификторов боевых версий для участника
    int *createFightVersionIdList(int &count);
    //-- Отметить версии, в которых участвует участник
    void checkedFightVersion(TList *tocheck);

    //-- Выбрать уровень мастерства, по заданному идентификатору 
    void selectSkillById(int id);


    //-- Изменить надписи на кнопках
    void setEditMode(void);
    void closeEditMode(void);

    //-- Участник соревнования
    TList *competitorsList;



public:		// User declarations
    __fastcall TfrmRequestCompetitorsListEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRequestCompetitorsListEdit *frmRequestCompetitorsListEdit;


//--Устанавливает заголовок в grid таблице участников
extern void setCompetitorTableHeader(TStringGrid *grid);
//-- Добавить очередного участника в  таблицу
extern void addToCompetitorStringGrid(TCompetitor competitor, int addIndex, TStringGrid *grid);
//-- Удалить участника из таблицы
extern void deleteFromCompetitorStringGrid(int delIndex, TStringGrid *grid);
//-- Создает список в таблице по заданной заявке
TList* createCompetitorsList(int requestId, TStringGrid *grid);
//-- Очистить таблицу строк (освободить память)
void clearStrGrid(TStringGrid *grid);






//---------------------------------------------------------------------------
#endif
