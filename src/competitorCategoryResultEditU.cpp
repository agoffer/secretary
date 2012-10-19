//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "competitorCategoryResultEditU.h"
#include "resultDM.h"
#include "categoryEditU.h"
#include "currentStateDM.h"
#include "reportDataSourceDM.h"
#include "categoryFinalReportU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


//��������� ��������� �����, ��� ������� ����������� �������� 
bool crossInclude;
//��������� �����������
int __fastcall compareShootResults(void *fstItem, void *secItem);
int __fastcall compareCommonResults(void *fstItem, void *secItem);

TfrmCompetitorCategoryResultEdit *frmCompetitorCategoryResultEdit;
//---------------------------------------------------------------------------
__fastcall TfrmCompetitorCategoryResultEdit::TfrmCompetitorCategoryResultEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCompetitorCategoryResultEdit::FormShow(TObject *Sender)
{
    InitFields();
}
//---------------------------------------------------------------------------


void TfrmCompetitorCategoryResultEdit::HideResultChange(void){
    //�������� ������� ��������� ����������
    lblModifiedShootRank->Hide();
    lblModifiedFightWOKnifeRank->Hide();
    lblModifiedFightWKnifeRank->Hide();
    lblModifiedCommonRank->Hide();
    //��������� �������� ��������� �� ���������
    resultModified = false;
    //��������� ������ ������
    bbtnEnterResult->Enabled = false;
}

void TfrmCompetitorCategoryResultEdit::InitFields(void){
    //-- ��������� �� ������ ���������� ��������� � �������� ������
    chboxFemaleCategory->Checked = false;
    TList *category = dmCurrentState->getMaleCategoryList();
    createCategories(category);
    //��������� �� �������
    HideResultChange();

    currentCompetitorList = NULL;

    //��������� ������� ��������� ������
    setCallback();
    //���������� ������
    changeCompetitorList(NULL);
}

void TfrmCompetitorCategoryResultEdit::createCategories(TList *category){
    //������ ����� � ���������
    createCategoryIndexFVComboBox(category, cmboxFightVersion, categoryIndex);
    cmboxFightVersion->ItemIndex = 0;
    createAgeWeightComboBoxByFV(cmboxAvailCategory, category, cmboxFightVersion);  
    cmboxAvailCategory->ItemIndex = 0;
}



void __fastcall TfrmCompetitorCategoryResultEdit::changeCompetitorList(
      TObject *Sender)
{
    currentCategory = getCategoryByIndex(cmboxAvailCategory,
                        cmboxFightVersion,
                        categoryIndex); 
    ShowCompetitorList(currentCategory);
    //������� ���������
    changeCompetitor(); 

}
//---------------------------------------------------------------------------

void TfrmCompetitorCategoryResultEdit::ShowCompetitorList(TCategory* category){
    if(category == NULL){
        //������ ���������� �����������
        dbgrdCompetitors->DataSource = NULL;
        cmboxFightWKnifeRank->Clear();
        cmboxFightWOKnifeRank->Clear();
        return;
        }
    //��������� ������ ���������� � ���������
    //�������������� ������� ������ ������ ���������� � ���������
    if(currentCompetitorList!=NULL){
        destroyList(currentCompetitorList, etCOMPETITOR);
        currentCompetitorList = NULL; 
        }
    currentCompetitorList = dmResultDAO->setCompetitorCategoryResultTable(category->getId());
    if(currentCompetitorList->Count > 0){
        //���������� ������
        dbgrdCompetitors->DataSource = dmResultDAO->dsCompetitorToCategoryResult;
        //����������� ������ ����, ������� �����������
        createRankList(cmboxFightWOKnifeRank, currentCompetitorList->Count);
        createRankList(cmboxFightWKnifeRank, currentCompetitorList->Count);
        createRankList(cmboxShootRank, currentCompetitorList->Count);
        createRankList(cmboxCommonRank, currentCompetitorList->Count);
        }
    else{
        //�������� ������
        dbgrdCompetitors->DataSource = NULL;
        cmboxFightWKnifeRank->Clear();
        cmboxFightWOKnifeRank->Clear();
        cmboxShootRank->Clear();
        cmboxCommonRank->Clear();
    }
}


void TfrmCompetitorCategoryResultEdit::createRankList(TComboBox *cmboxRank, int rankCount){
    //������� ������
    cmboxRank->Clear();
    cmboxRank->Items->Add("");
    for(int i=1; i <= rankCount; i++){
        cmboxRank->Items->Add(IntToStr(i));
        }
}


void __fastcall TfrmCompetitorCategoryResultEdit::chboxFemaleCategoryClick(
      TObject *Sender)
{
TList *category;
    //-- �������� ������ ��������� �� ��������������
    if(!chboxFemaleCategory->Checked){
        category = dmCurrentState->getMaleCategoryList();
        }
    else{
        category = dmCurrentState->getFemaleCategoryList();
        }
    //������ ����� � ���������
    createCategories(category);
    //��������� ������ �����
    changeCompetitorList(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::bbtnCloseClick(
      TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------


void TfrmCompetitorCategoryResultEdit::changeCompetitor(void){

    //���� �� ���������� ���������, �� ��������� ����� ���������
    if(currentCategory==NULL)
        return;
    //���������� ����� �������� ���������
    resetCallback();

   //������� ������ ���������
    int currentCompetitorId = TResult::getCurrentCompetitorId();

    //��������� ������������ ����������
    HideResultChange();
    currentCompetitor.getById(currentCompetitorId);

    //��������� ���������� ��� ���������
    currentCompetitor.loadResult(currentCategory->getId());

    //���������� ���������� ���������� � ��������� ������
    int fwok = currentCompetitor.result.getFightWOKnifeRank();
    int fwk = currentCompetitor.result.getFightWKnifeRank();
    int sht = currentCompetitor.result.getShootRank();
    int cmmn = currentCompetitor.result.getCommonRank();
    cmboxFightWOKnifeRank->Text = fwok > 0 ? IntToStr(fwok) : AnsiString("");
    cmboxFightWKnifeRank->Text = fwk > 0 ? IntToStr(fwk) : AnsiString("");
    cmboxShootRank->Text = sht > 0 ? IntToStr(sht) : AnsiString("");
    cmboxCommonRank->Text = cmmn > 0 ? IntToStr(cmmn) : AnsiString("");

    showResultScores();

    setCallback();
}


void TfrmCompetitorCategoryResultEdit::showResultScores(void){
    //���������� ���������� ���������� � ��������� ������
    AnsiString fwok = cmboxFightWOKnifeRank->Text; int ifwok;
    AnsiString fwk = cmboxFightWKnifeRank->Text;   int ifwk;
    AnsiString sht = cmboxShootRank->Text;         int isht;
    AnsiString cmmn = cmboxCommonRank->Text;       int icmmn;

    if(fwok.IsEmpty()){ifwok = 0;}
    else{ifwok = dmCurrentState->getScoreForRank(StrToInt(fwok));}
    if(fwk.IsEmpty()){ifwk = 0;}
    else{ifwk = dmCurrentState->getScoreForRank(StrToInt(fwk));}
    if(sht.IsEmpty()){isht = 0;}
    else{isht = dmCurrentState->getScoreForRank(StrToInt(sht));}
    if(cmmn.IsEmpty()){icmmn = 0;}
    else{icmmn = ifwok + ifwk + isht;}

    sttxtShootScore->Caption=IntToStr(isht);
    sttxtFightWOKnifeScore->Caption=IntToStr(ifwok);
    sttxtFightWKnifeScore->Caption=IntToStr(ifwk);
    sttxtCommonScore->Caption=IntToStr(icmmn);
}



void competitorToCategoryResultRecordMoveAction(void){
    //����� ������ ��������
    if(frmCompetitorCategoryResultEdit->Active){
        //������� �������� ���������
        frmCompetitorCategoryResultEdit->changeCompetitor();
        }

}




void TfrmCompetitorCategoryResultEdit::setCallback(void){
    TResult::setRecordMoveCallback(competitorToCategoryResultRecordMoveAction);
}


void TfrmCompetitorCategoryResultEdit::resetCallback(void){
    TResult::setRecordMoveCallback(NULL);
}



void __fastcall TfrmCompetitorCategoryResultEdit::FormClose(
      TObject *Sender, TCloseAction &Action)
{
    //������� �����


    //��������� ������������ ����������
    HideResultChange();

    //������� ������ ���������� ������� ���������
    if(currentCompetitorList!=NULL){
        destroyList(currentCompetitorList, etCOMPETITOR);
        currentCompetitorList=NULL;
        }


    //�������� ����� �� �������
    resetCallback();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::bbtnEnterResultClick(
      TObject *Sender)
{

    //��������� ���������� �������� ���������
    if(resultModified){

        resetCallback();


        //������� ������ ���������
        int currentCompetitorId = TResult::getCurrentCompetitorId();

        //���������� ���������� ���������� � ��������� ������
        AnsiString fwok = cmboxFightWOKnifeRank->Text;
        AnsiString fwk = cmboxFightWKnifeRank->Text;
        AnsiString sht = cmboxShootRank->Text;
        AnsiString cmmn = cmboxCommonRank->Text;

        if(fwok.IsEmpty()){fwok = "0";}
        if(fwk.IsEmpty()){fwk = "0";}
        if(sht.IsEmpty()){sht = "0";}
        if(cmmn.IsEmpty()){cmmn = "0";}

        currentCompetitor.result.setFightWOKnifeRank(
                            StrToInt(fwok));
        currentCompetitor.result.setFightWKnifeRank(
                            StrToInt(fwk));
        currentCompetitor.result.setShootRank(
                            StrToInt(sht));
        currentCompetitor.result.setCommonRank(
                            StrToInt(cmmn));

        //�������� ��������� ���������
        currentCompetitor.storeResult(currentCategory->getId());
        //���������� ������ ���������� �����
        ShowCompetitorList(currentCategory);

        //���������� ��������� ������ ��� ��������
        TResult::setCurrentCompetitorById(currentCompetitorId);

        cmboxFightWOKnifeRank->Text = !fwok.AnsiCompare("0") ? AnsiString("") : fwok;
        cmboxFightWKnifeRank->Text = !fwk.AnsiCompare("0") ? AnsiString("") : fwk;
        cmboxShootRank->Text = !sht.AnsiCompare("0") ? AnsiString("") : sht;
        cmboxCommonRank->Text = !cmmn.AnsiCompare("0") ? AnsiString("") : cmmn;

        showResultScores();

        HideResultChange();

        setCallback();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::cmboxFightWOKnifeRankChange(
      TObject *Sender)
{
    //��������� ��������� ���������
    resultModified = true;
    lblModifiedFightWOKnifeRank->Show();
    //��������� ������ ������ 
    bbtnEnterResult->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::cmboxShootRankChange(
      TObject *Sender)
{
    //��������� ��������� ���������
    resultModified = true;
    lblModifiedShootRank->Show();
    //��������� ������ ������ 
    bbtnEnterResult->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::cmboxFightWKnifeRankChange(
      TObject *Sender)
{
    //��������� ��������� ���������
    resultModified = true;
    lblModifiedFightWKnifeRank->Show();
    //��������� ������ ������ 
    bbtnEnterResult->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::cmboxCommonRankChange(
      TObject *Sender)
{
    //��������� ��������� ���������
    resultModified = true;
    lblModifiedCommonRank->Show();
    //��������� ������ ������
    bbtnEnterResult->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::bbtnAtoCalculateShootRankClick(
      TObject *Sender)
{
    // ������ ����������� ��������, � ������ ������ ��� ���������� //
    calculateShootRanks(currentCompetitorList, currentCategory->getId());
    //���������� ���������� ������
    ShowCompetitorList(currentCategory);

    changeCompetitor();
}
//---------------------------------------------------------------------------


void TfrmCompetitorCategoryResultEdit::calculateShootRanks(TList *compList, int categoryId){
int btnRes;
//���������� ������ �� �����������
bool crossInclude = false;
    //�������� � ������������, ��������� ����� ��� ���?
    btnRes = MessageDlg("��������� ���������� ������?",
                        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0);
    if(btnRes != mrNo){
        //������������ ����� ��������� �����
        crossInclude = true;
        }


    //�������� ����������� ���� �����������
    for(int i=0; i < compList->Count; i++){
        TCompetitor *competitor = (TCompetitor*)(compList->Items[i]);
        //��������� ��������
        if(competitor->result.getShootScore() < 0){
            //�������� � ���, ��� �������� ��� ����������
            btnRes = MessageDlg("�������� " +
                        competitor->getPerson().getSurname() +
                        " " + competitor->getPerson().getName() +
                        " �� ����� ���������� �� ��������! ���������� ������ ����?",
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
            if(btnRes != mrYes){
                //������������, �� ��������� ������ ����
                return;
                }
            }
        //���� ����������, ��������� ������� ���������� ������
        if(crossInclude &&
            (
            (competitor->result.getCrossTime().AnsiCompare(AnsiString(":  ."))==0)
            ||
            (competitor->result.getCrossTime().Trim().AnsiCompare(AnsiString(""))==0)
            ||
            (competitor->result.getCrossTime().Trim().AnsiCompare(AnsiString("00:00.00"))==0)
            )){
            //�������� � ���, ��� ��� ��������� �� ���������� ����� ������
                        btnRes = MessageDlg("�������� " +
                        competitor->getPerson().getSurname() +
                        " " + competitor->getPerson().getName() +
                        " �� ����� ���������� �� �����! ���������� ������ ����?",
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
            if(btnRes != mrYes){
                //������������, �� ��������� ������ ����
                return;
                }
            }
        }

    //����������� ���������� �� �����������
    compList->Sort(compareShootResults);

    //���������� ����� ����������, � ������������ � ���������������
    for(int i=0; i < compList->Count; i++){
        TCompetitor * competitor = (TCompetitor*)compList->Items[i];
        competitor->result.setShootRank(i + 1);
        competitor->storeResult(categoryId);
        }
}


int __fastcall compareShootResults(void *fstItem, void *secItem){
    if(((TCompetitor *)fstItem)->result.getShootScore() >
       ((TCompetitor *)secItem)->result.getShootScore()){
        return -1;
        }
    else if(((TCompetitor *)fstItem)->result.getShootScore() <
            ((TCompetitor *)secItem)->result.getShootScore()){
            return 1;
            }
         else{
            //���� ����������� ���������� ������, ��������� ��
            if(crossInclude){
                return -(((TCompetitor *)fstItem)->result.getCrossTime().
                AnsiCompare(((TCompetitor *)secItem)->result.getCrossTime()));
                }
            else{
                //����� ����������
                return 0;
                }
            }
}




void __fastcall TfrmCompetitorCategoryResultEdit::bbtnAutoCalculateCommonRankClick(
      TObject *Sender)
{
    // ������ ����� ���� �� ���� ����� ������������ //
    calculateCommonRanks(currentCompetitorList, currentCategory->getId());
    //���������� ���������� ������
    ShowCompetitorList(currentCategory);

    changeCompetitor();  
}
//---------------------------------------------------------------------------

void TfrmCompetitorCategoryResultEdit::calculateCommonRanks(TList *compList,
                                                            int categoryId){
//��������� ���������� �������������
int btnRes;

    //��������� ������� ���� ��: �������� � ����, ��� ���������� ���������
    for(int i=0; i < compList->Count; i++){
        TCompetitor *competitor = (TCompetitor*)(compList->Items[i]);
        //����� �� ��������
        if(competitor->result.getShootRank() <= 0){
            //�������� � ���, ��� �������� ��� ����������
            btnRes = MessageDlg("�������� " +
                        competitor->getPerson().getSurname() +
                        " " + competitor->getPerson().getName() +
                        " �� ����� ����� �� ��������! ���������� ������ ����?",
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
            if(btnRes != mrYes){
                //������������, �� ��������� ������ ����
                return;
                }
            }



        //����� �� �� ��� ��
        if(competitor->result.getFightWOKnifeRank() <= 0){
            //�������� � ���, ��� �������� ��� ����������
            btnRes = MessageDlg("�������� " +
                        competitor->getPerson().getSurname() +
                        " " + competitor->getPerson().getName() +
                        " �� ����� ����� �� �� ��� ��! ���������� ������ ����?",
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
            if(btnRes != mrYes){
                //������������, �� ��������� ������ ����
                return;
                }
            }

        //����� �� �� c ��
        if(competitor->result.getFightWKnifeRank() <= 0){
            //�������� � ���, ��� �������� ��� ����������
            btnRes = MessageDlg("�������� " +
                        competitor->getPerson().getSurname() +
                        " " + competitor->getPerson().getName() +
                        " �� ����� ����� �� �� c ��! ���������� ������ ����?",
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0);
            if(btnRes != mrYes){
                //������������, �� ��������� ������ ����
                return;
                }
            }
        }

    //����� ���������� ������ ����
    compList->Sort(compareCommonResults);
    //���������� ����� ����������, � ������������ � ���������������
    for(int i=0; i < compList->Count; i++){
        TCompetitor * competitor = (TCompetitor*)compList->Items[i];
        competitor->result.setCommonRank(i + 1);
        competitor->storeResult(categoryId);
        }
}


int __fastcall compareCommonResults(void *fstItem, void *secItem){
//��������� ���� ��� ������� ���������
int fstRank =  ((TCompetitor *)fstItem)->result.getShootRank();
int fstScore = dmCurrentState->getScoreForRank(fstRank);
    fstRank =  ((TCompetitor *)fstItem)->result.getFightWOKnifeRank();
    fstScore += dmCurrentState->getScoreForRank(fstRank);
    fstRank =  ((TCompetitor *)fstItem)->result.getFightWKnifeRank();
    fstScore += dmCurrentState->getScoreForRank(fstRank);
//��������� ���� ��� ������� ���������
int secRank =  ((TCompetitor *)secItem)->result.getShootRank();
int secScore = dmCurrentState->getScoreForRank(secRank);
    secRank =  ((TCompetitor *)secItem)->result.getFightWOKnifeRank();
    secScore += dmCurrentState->getScoreForRank(secRank);
    secRank =  ((TCompetitor *)secItem)->result.getFightWKnifeRank();
    secScore += dmCurrentState->getScoreForRank(secRank);


    if( fstScore > secScore ){
        return -1;
        }
    else if( fstScore < secScore ){
            return 1;
            }
         else{
            //��� ������ �����, ��������� ������ �� ��� ��
            int fstWOKRank =  ((TCompetitor *)fstItem)->result.getFightWOKnifeRank();
            int secWOKRank =  ((TCompetitor *)secItem)->result.getFightWOKnifeRank();
            if(fstWOKRank > secWOKRank){
                return 1;
                }
            else if(fstWOKRank < secWOKRank){
                return -1;
                }
            return 0;
            }
}

void __fastcall TfrmCompetitorCategoryResultEdit::cmboxFightVersionChange(
      TObject *Sender)
{
    TList *category;
    if(!chboxFemaleCategory->Checked)
        category = dmCurrentState->getMaleCategoryList();
    else
        category = dmCurrentState->getFemaleCategoryList();

    //���������� ������ ������ ��� ������� ������
    createAgeWeightComboBoxByFV(cmboxAvailCategory, category, cmboxFightVersion);
    cmboxAvailCategory->ItemIndex = 0;
    changeCompetitorList(Sender);    
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitorCategoryResultEdit::bbtnPrintCurrentCategoryClick(
      TObject *Sender)
{
    //
    // ������ ��������� � ������ ������ ���������
    //

    //�������� ���������, ������� ����� ������
    TCategory *printCategory = getCategoryByIndex(cmboxAvailCategory, cmboxFightVersion, categoryIndex);

    dmReportDataSource->finalReport = true;
    dmReportDataSource->setCategoryToPrintById(printCategory->getId());
    //���������� �������� ���������
    frmCategoryFinalReport->qrCategory->Preview();
}
//---------------------------------------------------------------------------


