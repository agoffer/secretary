//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainFormU.h"
#include "competitionEditU.h"
#include "requestEditU.h"
#include "requestCompetitorsListEditU.h"
#include "competitionSelectListU.h"
#include "availCategoryEditU.h"
#include "categoryEditU.h"
#include "resultEnterEditU.h"
#include "requestClubReportU.h"
#include "reportDataSourceDM.h"
#include "competitorCategoryResultEditU.h"
#include "categoryToPrintSelectU.h"
#include "manualDrawEditU.h"
#include "availCategoryFullEditU.h"
#include "personFullEditU.h"
#include "competitionRankEditU.h"

#include "currentStateDM.h"
#include "reportDataSourceDM.h"

#include "competitorDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmMainForm *frmMainForm;
//---------------------------------------------------------------------------
__fastcall TfrmMainForm::TfrmMainForm(TComponent* Owner)
    : TForm(Owner)
{
    lbItemIndex = 0;
}



//---------------------------------------------------------------------------
void __fastcall TfrmMainForm::tlbtnNewCompetitionClick(TObject *Sender)
{
    //-- ������� ����� ������������
    frmCompetitionEdit->ShowModal();
    if(frmCompetitionEdit->ModalResult == mrOk){
        //�������� ��������� ���� ������ 
        EnableDisableWithRequestControls(false);
        EnableDisableWithCategoryControls(false);
        //���������� ������������
        showCompetition();
        positionCompetition();

        //������� ��������� ��������� ������
        tlbtnNewRequest->Enabled = true;
        miNewRequest->Enabled = true;
        
        //�������� ������
        lbItemIndex = 0;
        refreshRequestListBox();
        //������� ������ ����������
        destroyCompetitorsList();
        // ��������� ������������ ����������
        DisableConfiguration();
        }
}
//---------------------------------------------------------------------------


void TfrmMainForm::showCompetition(void){
TCompetition curCompetition = dmCurrentState->getCompetition();
    if(curCompetition.getId()){
        //��������� ������ ������������
        lblCompetitionTitle->Caption = curCompetition.getCompetitionRank().getDescription();
        //���������� ���� ���������� ������������
        AnsiString competitionDate = curCompetition.getBeginDate().DateString() + " - " +
                                     curCompetition.getEndDate().DateString();
        lblCompetitionDate->Caption = competitionDate;
        }
    //���������� ������������� ��������
    else{
        lblCompetitionTitle->Caption = "������������ �� ����������...";
        lblCompetitionDate->Caption = "(���� ���������� �� ����������)";
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::pnlCompetitionTitleResize(TObject *Sender)
{
    //��������� �������� ������������ �� ������ ������
    positionCompetition();
}
//---------------------------------------------------------------------------

void TfrmMainForm::positionCompetition(void){
        lblCompetitionTitle->Left = (pnlCompetitionTitle->Width -
                                    lblCompetitionTitle->Width) / 2;
        lblCompetitionDate->Left =  (pnlCompetitionTitle->Width -
                                    lblCompetitionDate->Width) / 2;
}





void __fastcall TfrmMainForm::tlbtnNewRequestClick(TObject *Sender)
{
    //�������� ����� ������
    frmRequestEdit->ShowModal();
    //���� ������ ���������, ���������� �� � ������ ������ ������� �����
    if(frmRequestEdit->ModalResult == mrOk){
        //����������� ������ ������ �� �����
        int requestCount = dmCurrentState->getRequestList()->Count;
        lbItemIndex = requestCount - 1;
        refreshRequestListBox();
        //������� ������ ������ ����������
        destroyCompetitorsList();
        //������� ������ ���������� � ������
        competitorsList = createCompetitorsList(dmCurrentState->getRequest().getId(), strgrdCompetitorsList);
        //���� ���� ������, �� ���������� �������������� ����
        if(requestCount > 0){
            EnableDisableWithRequestControls(true); 
            }
        }
}
//---------------------------------------------------------------------------





void TfrmMainForm::refreshRequestListBox(void){
TRequest *current;
    //������� ������
    lstboxRequest->Clear();
    //�������� ������ ������
    for(int i = 0; i < dmCurrentState->getRequestList()->Count; i++){
        //�������� ������� ������
        current = (TRequest*)(dmCurrentState->getRequestList()->Items[i]);
        //���������� �������� ����
        lstboxRequest->Items->Add(current->getClub().getName() + "  " +
                               "(" + current->getClub().getCity() + ")");
        }

    //���������� ������ �� ��������� ������
    lstboxRequest->ItemIndex = lbItemIndex;
}


void __fastcall TfrmMainForm::tlbtnEditRequestCompetitorsClick(
      TObject *Sender)
{
    //������� � ����� ���������� ���������� � ������
    frmRequestCompetitorsListEdit->ShowModal();
    //����� �������� �� ��������� ������, ���������� ��� ������ � ������ ������� �����
    destroyCompetitorsList();
    competitorsList = createCompetitorsList(dmCurrentState->getRequest().getId(), strgrdCompetitorsList);
    //���� ��������� ���������, ������� ����������� �� �������������
    if(competitorsList->Count){
        tlbtnDistribCategory->Enabled = true;
        miCompetitorsDistrib->Enabled = true;
        miManualDraw->Enabled = true;
        tlbtnManualDraw->Enabled = true;         
        
        }
    //���� ���� ���������, ������� ����������� � �������������
    if(dmCurrentState->getCategoryList()->Count <= 0){
        dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
        }
    if(dmCurrentState->getCategoryList()->Count > 0){
        EnableDisableWithCategoryControls(true);
        }

}
//---------------------------------------------------------------------------

void TfrmMainForm::destroyCompetitorsList(void){
    //�������� �������
    clearStrGrid(strgrdCompetitorsList);
    destroyList(competitorsList, etCOMPETITOR);
    competitorsList=NULL;
}



void __fastcall TfrmMainForm::FormCreate(TObject *Sender)
{
    //������� ��������� ������� ����������
    setCompetitorTableHeader(strgrdCompetitorsList);
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainForm::tlbtnArchiveCompetitionClick(TObject *Sender)
{
    // ������� ������ ������������ ��� ������ //
    if(frmCompetitionSelectList->ShowModal() == mrOk){
        //�������� ��������� ���� ������
        EnableDisableWithRequestControls(false);
        EnableDisableWithCategoryControls(false);
        //������� ������ ������ ����������
        destroyCompetitorsList();
        dmCurrentState->getRequest().setId(0);
        //���������� ������������
        showCompetition();
        positionCompetition();

        //������� ��������� ��������� ������
        tlbtnNewRequest->Enabled = true;
        miNewRequest->Enabled = true;

        //�������� ������
        lbItemIndex = 0;
        refreshRequestListBox();
        //������� ������� ������
        if(dmCurrentState->getRequestList()->Count){
            dmCurrentState->setRequest(*((TRequest*)dmCurrentState->getRequestList()->Items[lbItemIndex]));
            //���� � ����������� ������������ ���� ������ - ������� ��������������
            EnableDisableWithRequestControls(true);
            }
        //������� ������ ���������� � ������
        competitorsList = createCompetitorsList(dmCurrentState->getRequest().getId(), strgrdCompetitorsList);
        //�������� ����������� ������ ���������
        dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
        //���� � ����������� ������������ ���� ��������� ������� �������� ����������
        if(dmCurrentState->getCategoryList()->Count > 0){
            EnableDisableWithCategoryControls(true);
            }
        // ��������� ������������ ����������
        DisableConfiguration();
        }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::EnableDisableWithCategoryControls(bool endis){
    //-- ������������� ���������� � ����������
    tlbtnDistribCategory->Enabled = endis;
    miCompetitorsDistrib->Enabled = endis;
    //-- ������ ���������� ����������
    tlbtnManualDraw->Enabled = endis;
    miManualDraw->Enabled = endis;
    //-- ������ ��������� � ��������
    miPrintAllCategory->Enabled = endis;
    miPrintAllTrees->Enabled = endis;
    tlbtnPrintAllCategory->Enabled = endis;
    tlbtnPrintAllTrees->Enabled = endis;
    //-- ���� ���������� �������� � �����
    miEnterResult->Enabled = endis;
    tlbtnEnterResult->Enabled = endis;
    //-- ���������� �� ����������� ���
    miEnterFightResults->Enabled = endis;
    tlbtnEnterFightResult->Enabled = endis;
    //-- ������ ���������� � ������������
    miPrintFinalCategoryReport->Enabled = endis;
    //-- ������ �������� ��������� ������������
    miExportSummaryProtocol->Enabled = endis;
    //-- ������ ������ ���
    miPrintPairs->Enabled = endis;
    tlbtnPrintPairs->Enabled=endis;

}

void __fastcall TfrmMainForm::EnableDisableWithRequestControls(bool endis){
    //-- ������������� ������
    tlbtnEditRequestCompetitors->Enabled = endis;
    miEditRequest->Enabled = endis;
    //-- ������ ������ ������
    miPrintRequestList->Enabled = endis;
    //-- ������� ������
    miDeleteRequest->Enabled = endis;
    tlbtnDeleteRequest->Enabled = endis;
    //-- ��������� ������ ����������������� ����������  � ���������
    miRedestribComp->Enabled=endis;
}


void __fastcall TfrmMainForm::DisableConfiguration() {
    miConfiguration->Enabled = false;
}


void __fastcall TfrmMainForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //������������ �� ������������ ����� ��������� ������
    if(MessageDlg("��������� ������ � ����������?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes){
        //������ ��� ��������� ����������� �������
        destroyCompetitorsList();
        }
    else{
        //���, ���������� ������ � ����������
        Action = caNone;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::lstboxRequestClick(TObject *Sender)
{
    //������������ ������� �� ������, ���� ��������� ���������
    //�������, �� ����������� ������ ���������� ��� ������
    if(lstboxRequest->ItemIndex != lbItemIndex){
        //������� ������ ������ ����������
        destroyCompetitorsList();
        lbItemIndex = lstboxRequest->ItemIndex;
        //������� ������� ������
        dmCurrentState->setRequest(*((TRequest*)dmCurrentState->getRequestList()->Items[lbItemIndex]));
        //������� ������ ���������� � ������
        competitorsList = createCompetitorsList(dmCurrentState->getRequest().getId(), strgrdCompetitorsList);

        }
}
//---------------------------------------------------------------------------




void __fastcall TfrmMainForm::miAddAvailCategoryClick(TObject *Sender)
{
    //������� � ��������� ��������� ���������
    frmAvailCategoryEdit->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::miCompetitorsDistribClick(TObject *Sender)
{
    //�������� ����������� ������ ���������
    dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
    //���������� ��������� �������������
    frmCategoryEdit->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::miEnterResultClick(TObject *Sender)
{
    //������� � ����� �����������
    frmResultEnterEdit->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miPrintRequestListClick(TObject *Sender)
{
    //-- ���������� ����� � �������� ����������� � �������������
    dmReportDataSource->setRequestClubListByCompetitionId(dmCurrentState->getCompetition().getId());
    frmRequestClubReport->qrRequestClubList->Preview();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miEnterFightResultsClick(TObject *Sender)
{
    //�������� ����������� ������ ���������
    dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
    //������� � ����������� �����������
    frmCompetitorCategoryResultEdit->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miPrintFinalCategoryReportClick(
      TObject *Sender)
{
    //
    // �������� �������������� ��������� �� ���� ����������
    // ��� ������� ������������
    //

    //������� � ������ ��������� ��� ������
    frmCategoryToPrintSelect->PrintFinalProtocols();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miExportSummaryProtocolClick(TObject *Sender)
{
    //������� ������� �������� �� ������� exel ����
    dmReportDataSource->summaryProtocolExport(dmCurrentState->getCompetition().getId());
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainForm::tlbtnDeleteRequestClick(TObject *Sender)
{
    //�������� ������� ������
    if(MessageDlg("�� ������������� ������� ������� ������ \""
        + dmCurrentState->getRequest().getClub().getName() + "\"?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo){
        //���, �� ������� ������
        return;
        }
    //������� ������ �� ���� ������
    TRequest::deleteById(dmCurrentState->getRequest().getId());
    //������� ������ � ��� ��� � ��� ������� �� ������
    int currentItIndex = lstboxRequest->ItemIndex;
    dmCurrentState->getRequestList()->Delete(currentItIndex);
    lstboxRequest->DeleteSelected();
    if(lstboxRequest->Count > 0){
        if(lstboxRequest->Count == currentItIndex){
            currentItIndex--;
            }
        lstboxRequest->ItemIndex = currentItIndex;
        lbItemIndex = -1;
        lstboxRequestClick(Sender);
        }
    else{
        destroyCompetitorsList();
        EnableDisableWithRequestControls(false);
        EnableDisableWithCategoryControls(false);
        }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::tlbtnPrintAllCategoryClick(TObject *Sender)
{
    //
    // �������� ������������� ���������
    // ��� ������� ������������
    //
    //�������� ��������� ������� ���������
    SortCategories();
    //������� � ������ ��������� ��� ������
    frmCategoryToPrintSelect->PrintProtocols();

}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::tlbtnPrintAllTreesClick(TObject *Sender)
{
    //������ ���� �������� �� ������� �������������
    //������� � ������ ��������� ��� ������
    //�������� ��������� ������� ���������
    SortCategories();
    frmCategoryToPrintSelect->PrintFightTrees();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::tlbtnPrintPairsClick(TObject *Sender)
{
    //������ ������� ���, ��� ������� ������������
    //�������� ��������� ������� ���������
    SortCategories();
    frmCategoryToPrintSelect->PrintPairsOrder();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miRedestribCompClick(TObject *Sender)
{
    //-- ��������� ������ ����������������� ���������� ��� ������������
    if(MessageDlg(
"�� ������������� ������� ������������ ���������� ������? \n\
��� ����� �������� � ������ ������������� ������������� � ����������� ������������. \n\
����������?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo){
        //���, ������ �� ������ 
        return;
        }
    //�������, ������ ��� ��������� ��� ������������ 
    TCategory::deleteCategoriesByCompetition(dmCurrentState->getCompetition());
    //��������� ����� ����������������� 
    TCategory::destributeCompetitors(dmCurrentState->getCompetition());
    //�������� ����������� ������ ���������
    dmCurrentState->createCategoryList(dmCurrentState->getCompetition());
    //���� � ����������� ������������ ���� ��������� ������� �������� ����������
    if(dmCurrentState->getCategoryList()->Count > 0){
        EnableDisableWithCategoryControls(true);
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::tlbtnManualDrawClick(TObject *Sender){
    frmManualDraw->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::miAvailableCategoryClick(TObject *Sender)
{
  frmAvailCategoryFullEdit->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::miExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainForm::miCompetitionRankClick(TObject *Sender)
{
    frmCompetitionRankEdit->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::miPersonalDataClick(TObject *Sender)
{
    frmPersonFullEdit->ShowModal();
}
//---------------------------------------------------------------------------

