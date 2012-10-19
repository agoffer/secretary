//---------------------------------------------------------------------------

#ifndef competitorCategoryResultEditUH
#define competitorCategoryResultEditUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <dbcgrids.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>

#include <map.h>
#include "categoryCtrl.h"
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmCompetitorCategoryResultEdit : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grboxCompetitorSelection;
    TDBGrid *dbgrdCompetitors;
    TGroupBox *grboxSelectCategory;
    TLabel *lblAvailCategoryFirst;
    TLabel *lblFightVersionFirst;
    TComboBox *cmboxAvailCategory;
    TComboBox *cmboxFightVersion;
    TCheckBox *chboxFemaleCategory;
    TComboBox *cmboxFightWOKnifeRank;
    TComboBox *cmboxFightWKnifeRank;
    TBitBtn *bbtnClose;
    TLabel *lblFightWKnifeRank;
    TLabel *lblFightWOKnifeRank;
    TBitBtn *bbtnEnterResult;
    TLabel *lblModifiedShootRank;
    TGroupBox *grboxCompetitorResult;
    TDBText *dbtxtSurname;
    TDBText *dbtxtName;
    TDBText *dbtxtClubName;
    TLabel *lblShootRank;
    TComboBox *cmboxShootRank;
    TComboBox *cmboxCommonRank;
    TLabel *lblCommonRank;
    TBitBtn *bbtnAutoCalculateCommonRank;
    TBitBtn *bbtnAtoCalculateShootRank;
    TLabel *lblModifiedFightWOKnifeRank;
    TLabel *lblModifiedFightWKnifeRank;
    TLabel *lblModifiedCommonRank;
    TStaticText *sttxtShootScore;
    TStaticText *sttxtFightWOKnifeScore;
    TStaticText *sttxtFightWKnifeScore;
    TStaticText *sttxtCommonScore;
    TBitBtn *bbtnPrintCurrentCategory;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall changeCompetitorList(TObject *Sender);
    void __fastcall chboxFemaleCategoryClick(TObject *Sender);
    void __fastcall bbtnCloseClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall bbtnEnterResultClick(TObject *Sender);
    void __fastcall cmboxFightWOKnifeRankChange(TObject *Sender);
    void __fastcall cmboxShootRankChange(TObject *Sender);
    void __fastcall cmboxFightWKnifeRankChange(TObject *Sender);
    void __fastcall cmboxCommonRankChange(TObject *Sender);
    void __fastcall bbtnAtoCalculateShootRankClick(TObject *Sender);
    void __fastcall bbtnAutoCalculateCommonRankClick(TObject *Sender);
    void __fastcall cmboxFightVersionChange(TObject *Sender);
    void __fastcall bbtnPrintCurrentCategoryClick(TObject *Sender);
private:	// User declarations
    //-- ������������� �����, ���������� �����
    void InitFields(void);
    //-- �������� ������� ����, ��� ��������� ���������
    void HideResultChange(void);
    //-- ��������� ���������� ������ ������������ ���������
    void createCategories(TList *category);
    //-- ���������� ������ ���������� � ���������
    void ShowCompetitorList(TCategory* category);
    //-- ������� ������ ���� ��� ���������
    void createRankList(TComboBox *cmboxRank, int rankCount);

    //��������� ���������� ��������
    void calculateShootRanks(TList* compList, int categoryId);
    void calculateCommonRanks(TList *compList, int categoryId);

    void showResultScores(void);          

    void setCallback(void);
    void resetCallback(void); 

    //-- ������ �������� ���������� �� ����� (������ �������������� ���������)
    map<AnsiString, TCategory*> categoryIndex;

    //������� ��������, ��� �������� ������������� ���������
    TCompetitor currentCompetitor;
    //�������, ��������� ���������
    TCategory *currentCategory;
    //������� ������ ���������� � ������������
    TList *currentCompetitorList; 

    //������� ����, ��� ���������� ����������
    bool resultModified;
public:		// User declarations
    __fastcall TfrmCompetitorCategoryResultEdit(TComponent* Owner);

    //������� ���������, ����������� �����, ��������� �������������
    void changeCompetitor(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCompetitorCategoryResultEdit *frmCompetitorCategoryResultEdit;
//---------------------------------------------------------------------------

void competitorToCategoryResultRecordMoveAction(void);
#endif
