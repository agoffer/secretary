//---------------------------------------------------------------------------

#ifndef mainFormUH
#define mainFormUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>

#include "competitionCtrl.h"
#include "requestCtrl.h"
#include "competitorCtrl.h"
#include <Buttons.hpp>


//---------------------------------------------------------------------------
class TfrmMainForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *mmMainMenu;
    TMenuItem *miCompetition;
    TMenuItem *miRequest;
    TMenuItem *miCreateCompetition;
    TMenuItem *miCompetitionArchive;
    TMenuItem *miNewRequest;
    TMenuItem *miEditRequest;
    TMenuItem *miCategory;
    TMenuItem *miConfiguration;
    TMenuItem *miCompetitionRank;
    TMenuItem *miSkill;
    TMenuItem *miFightVersion;
    TMenuItem *miAvailableCategory;
    TStatusBar *stbarMainStatusBar;
    TToolBar *tlbarMainToolBar;
    TPanel *pnlCompetitionTitle;
    TLabel *lblCompetitionTitle;
    TLabel *lblCompetitionDate;
    TGroupBox *grboxCurentRequests;
    TPanel *pnlCurrentTeam;
    TGroupBox *grboxRequestCompetitorList;
    TGroupBox *grboxRepresentative;
    TToolButton *tlbtnNewCompetition;
    TToolButton *tlbtnArchiveCompetition;
    TToolButton *tlsprCompReq;
    TToolButton *tlbtnNewRequest;
    TImageList *imglstMenuIcons;
    TListBox *lstboxRequest;
    TToolButton *tlsprFillReq;
    TToolButton *tlbtnEditRequestCompetitors;
    TStringGrid *strgrdCompetitorsList;
    TMenuItem *miCompetitorsDistrib;
    TMenuItem *miAddCategorySep;
    TToolButton *tlsprDistripCategory;
    TToolButton *tlbtnDistribCategory;
    TMenuItem *miPrintAllCategory;
    TMenuItem *miPrintAllTrees;
    TMenuItem *miPrintSep;
    TToolButton *tlsprPrint;
    TToolButton *tlbtnPrintAllCategory;
    TToolButton *tlbtnPrintAllTrees;
    TToolButton *tlbtnEnterResult;
    TToolButton *tlsprResult;
    TMenuItem *miResults;
    TMenuItem *miEnterResult;
    TMenuItem *miReqSep;
    TMenuItem *miPrintRequestList;
    TMenuItem *miEnterFightResults;
    TMenuItem *miResPrintSep;
    TMenuItem *miPrintFinalCategoryReport;
    TMenuItem *miSummarySep;
    TMenuItem *miExportSummaryProtocol;
    TMenuItem *miDeleteRequest;
    TToolButton *tlbtnDeleteRequest;
    TToolButton *tlbtnEnterFightResult;
    TMenuItem *miPrintPairs;
    TToolButton *tlbtnPrintPairs;
    TMenuItem *miRedestribComp;
    TToolButton *tlsprDrawCategory;
    TMenuItem *miManualDraw;
    TToolButton *tlbtnManualDraw;
  TMenuItem *miExit;
    TMenuItem *miPersonalData;
    void __fastcall tlbtnNewCompetitionClick(TObject *Sender);
    void __fastcall pnlCompetitionTitleResize(TObject *Sender);
    void __fastcall tlbtnNewRequestClick(TObject *Sender);
    void __fastcall tlbtnEditRequestCompetitorsClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall tlbtnArchiveCompetitionClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall lstboxRequestClick(TObject *Sender);
    void __fastcall miAddAvailCategoryClick(TObject *Sender);
    void __fastcall miCompetitorsDistribClick(TObject *Sender);
    void __fastcall miEnterResultClick(TObject *Sender);
    void __fastcall miPrintRequestListClick(TObject *Sender);
    void __fastcall miEnterFightResultsClick(TObject *Sender);
    void __fastcall miPrintFinalCategoryReportClick(TObject *Sender);
    void __fastcall miExportSummaryProtocolClick(TObject *Sender);
    void __fastcall tlbtnDeleteRequestClick(TObject *Sender);
    void __fastcall tlbtnPrintAllCategoryClick(TObject *Sender);
    void __fastcall tlbtnPrintAllTreesClick(TObject *Sender);
    void __fastcall tlbtnPrintPairsClick(TObject *Sender);
    void __fastcall miRedestribCompClick(TObject *Sender);
    void __fastcall tlbtnManualDrawClick(TObject *Sender);
  void __fastcall miAvailableCategoryClick(TObject *Sender);
  void __fastcall miExitClick(TObject *Sender);
        void __fastcall miCompetitionRankClick(TObject *Sender);
    void __fastcall miPersonalDataClick(TObject *Sender);
private:	// User declarations

    //Индекс выбранной заявки в listbox-е
    int lbItemIndex;

    //-- Список участников в выбранной заявке
    TList *competitorsList;


    //-- Отобразить на форме соревнования
    void showCompetition(void);
    //-- Выравнять заголовок соревнований
    void positionCompetition(void);

    //-- Обновить список заявок на форме
    void refreshRequestListBox(void);
    //-- Удалить список участников в заявке (для этой формы)
    void destroyCompetitorsList(void);


    //-- Отобразить или спрятать эл-ты управления , если есть категории
    void __fastcall EnableDisableWithCategoryControls(bool endis);
    //-- Отобразить или спрятать эл-ты управления , если есть заявки
    void __fastcall EnableDisableWithRequestControls(bool endis);
    //-- Запрещать настройку приложения, когда загружено или создано соревнование
    void __fastcall DisableConfiguration();


public:		// User declarations
    __fastcall TfrmMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMainForm *frmMainForm;
//---------------------------------------------------------------------------
#endif
