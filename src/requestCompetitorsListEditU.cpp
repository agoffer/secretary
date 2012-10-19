//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "requestCompetitorsListEditU.h"
#include "mainFormU.h"
#include "currentStateDM.h"
#include "skillEditU.h"
#include "fightVersionEditU.h"
#include "categoryCtrl.h"

#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmRequestCompetitorsListEdit *frmRequestCompetitorsListEdit;
//---------------------------------------------------------------------------
__fastcall TfrmRequestCompetitorsListEdit::TfrmRequestCompetitorsListEdit(TComponent* Owner)
    : TForm(Owner)
{
    competitorsList = new TList();

}

//---------------------------------------------------------------------------


void __fastcall TfrmRequestCompetitorsListEdit::FormCreate(TObject *Sender)
{
    //������� ��������� ������ ���������� �� ������
    setCompetitorTableHeader(strgrdCompetitorsList);
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestCompetitorsListEdit::FormShow(TObject *Sender)
{
    //���������� ��������� �������� ����� (��� ����������)
    InitFields();
}
//---------------------------------------------------------------------------


void TfrmRequestCompetitorsListEdit::InitFields(void){

    //�������� ���������
    AnsiString clubName =dmCurrentState->getRequest().getClub().getName();
    frmRequestCompetitorsListEdit->Caption = "������ ���������� '" +
             clubName + "'";
    grboxCompetitorsList->Caption = "��������� '" + clubName + "'";


    //������� ������ ������ ������
    createFightVersionList();

    //������� ������ ������� ����������
    createSkillList();

    //�������� ������ ����������
    strgrdCompetitorsList->RowCount = 2;
    strgrdCompetitorsList->Rows[1]->Clear();
    //�������� ��� ����
    clearFields();
    //���� ��� ����������� ������, ���������� ������ ����������
    competitorsList = createCompetitorsList(dmCurrentState->getRequest().getId(),
                                                 strgrdCompetitorsList);
}


void TfrmRequestCompetitorsListEdit::clearFields(void){
    //�������� ��������� �������
    dmCurrentState->getPerson().setId(0);
    lbledtSurname->Clear();
    lbledtName->Clear();
    lbledtPatronymic->Clear();
    dtpDOB->Date = Now();
    medtWeight->Clear();
    chboxFemale->Checked = false;
    //�������� ���� ����������� ��������
    sttxtFullAge->Caption = "";

    //�������� ���� ������ ������ � ������ ����������
    for(int i=0; i < chlstboxFightVersion->Count; i++){
        chlstboxFightVersion->Checked[i] = false;
        }
    cmboxSkill->ItemIndex = 0;
    //��������� ����� �� ���� ����� �������
    lbledtSurname->SetFocus();
}



//---------------------------------------------------------------------------


void TfrmRequestCompetitorsListEdit::createFightVersionList(void){

    //������������ ������
    chlstboxFightVersion->Items->Clear();
    for(int i=0; i < dmCurrentState->getFightVersionList()->Count; i++){
        chlstboxFightVersion->Items->Add(((TFightVersion*)dmCurrentState->getFightVersionList()->Items[i])->getCode());
        }
}

void TfrmRequestCompetitorsListEdit::destroyFightVersionList(void){
    //������� ��������
    chlstboxFightVersion->Items->Clear();
}



void TfrmRequestCompetitorsListEdit::createSkillList(void){

    //������������ ������
    cmboxSkill->Items->Clear();
    for(int i=0; i < dmCurrentState->getSkillList()->Count; i++){
        cmboxSkill->Items->Add(((TSkill*)dmCurrentState->getSkillList()->Items[i])->getShortDescription());
        }
    if(cmboxSkill->Items->Count){
        //������� ������ �������� �� ���������
        cmboxSkill->Text = cmboxSkill->Items->Strings[0];
        cmboxSkill->ItemIndex = 0;
        }
    else{
        cmboxSkill->ItemIndex = -1;
        }
}

void TfrmRequestCompetitorsListEdit::destroySkillList(void){
    //������� ��������
    cmboxSkill->Items->Clear();
}


void __fastcall TfrmRequestCompetitorsListEdit::btnAddSkillClick(
      TObject *Sender)
{
    //�������� ������� ����������
    frmSkillEdit->ShowModal();
    //���� �������� ������, �������� ������
    if(frmSkillEdit->ModalResult == mrOk){
        //���������� ������ ������� ����������
        destroySkillList();
        //������� ������ ������������ ������
        createSkillList();
        //���������� ����������� ������, ��� �������
        cmboxSkill->Text =
            frmSkillEdit->lbledtShortDescription->Text;
            cmboxSkill->ItemIndex =cmboxSkill->Items->Count - 1;
        }


}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::btnAddFightVersionClick(
      TObject *Sender)
{
    //�������� ������ ������
    frmFightVersionEdit->ShowModal();
    //���� �������� ������, �������� ������
    if(frmFightVersionEdit->ModalResult == mrOk){
        //���������� ������ �������� ������������
        destroyFightVersionList();
        //������� ������ ������������ ������
        createFightVersionList();
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::FormHide(TObject *Sender)
{
    //������� ������ ������� ���������� � ������ ������
    destroySkillList();
    destroyFightVersionList();
    //���������� ������ ����������
    destroyList(competitorsList, etCOMPETITOR);
}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::lbledtSurnameChange(
      TObject *Sender)
{
    //��������� ������ ������ �������
    changePersonSearchTableState();
}
//---------------------------------------------------------------------------


void TfrmRequestCompetitorsListEdit::changePersonSearchTableState(void){
    dbgrdPersonList->DataSource  = NULL;
    //��������� ������ ������ �������
    dmPersonDAO->setFilterCondition(lbledtSurname->Text);
    dmPersonDAO->filterByField(ptfSurname);
    dbgrdPersonList->DataSource =  dmPersonDAO->dsPersonTable;
}


void __fastcall TfrmRequestCompetitorsListEdit::bbtnToEditBoxClick(
      TObject *Sender)
{
    //�������� ���������� �������� ��� ���������
    fillCompetitorPerson();

}
//---------------------------------------------------------------------------


void TfrmRequestCompetitorsListEdit::fillCompetitorPerson(void){
    //�������� ������� �������
    dmCurrentState->setPerson(TPerson::getCurrent());
    //���������� ����, � ������������ � ����������� ����������
    lbledtSurname->Text = dmCurrentState->getPerson().getSurname();
    lbledtName->Text = dmCurrentState->getPerson().getName();
    lbledtPatronymic->Text = dmCurrentState->getPerson().getPatronymic();
    dtpDOB->DateTime = dmCurrentState->getPerson().getDob();
    chboxFemale->Checked = dmCurrentState->getPerson().getFemale();
    //���������� ����� �� �������� �������� ����
    medtWeight->SetFocus();
    TfrmRequestCompetitorsListEdit::dtpDOBChange(NULL);
}

void __fastcall TfrmRequestCompetitorsListEdit::dtpDOBChange(
      TObject *Sender)
{
    //���������� �� ����� ����� ������� ������ ��� ���������
    sttxtFullAge->Caption = IntToStr(YearsPassCalculator(dtpDOB->DateTime));
}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::bbtnAddCompetitorClick(
      TObject *Sender)
{
    //�������, ������� ����� ���������
    TPerson personToStore;
    //����� ��������� ������� �� ����� �� �����
    personToStore.setId(0);
    personToStore.setSurname(lbledtSurname->Text.Trim());
    personToStore.setName(lbledtName->Text.Trim());
    personToStore.setPatronymic(lbledtPatronymic->Text.Trim());
    //���� � ���� ���� ����� �������, �������� ��� �������������
    personToStore.likeAs();

    //������� ������ ���������
    TCompetitor *newCompetitor = new TCompetitor();

    //�������� ��������� � �����, � ���� ������
    if(CompetitorIntoDatabase(personToStore, newCompetitor)){
        //�������� ��������� � ������
        competitorsList->Add(newCompetitor);
        //���������� ��������� � ���������
        TCategory::destributeCompetitor(*newCompetitor, dmCurrentState->getCompetition()); 
        //������� ��������� � ����� string grid
        addToCompetitorStringGrid(*newCompetitor, competitorsList->Count, strgrdCompetitorsList);
        //��������� ���������� �����
        strgrdCompetitorsList->RowCount = competitorsList->Count+1;
        //�������� ����, ��� ����� ������ ���������
        clearFields();
        //���������� ������� ��� �������
        dmCurrentState->setPerson(personToStore); 
        }
}


bool TfrmRequestCompetitorsListEdit::CompetitorIntoDatabase(TPerson& obj, TCompetitor *newCompetitor){
//������� ������
bool invalid = false;
//��������� �� ������
AnsiString errmess;

    //���� ����� ����������� �����������
    obj.setDob(dtpDOB->DateTime);
    //��� ����� ����������� ���������� 
    obj.setFemale(chboxFemale->Checked);    
    //�������� ���������� ������� �������� ���������
    invalid = !obj.valid(errmess);
    //��������� �������������� �������� �� ������� ���������
    int age = YearsPassCalculator(dtpDOB->DateTime);
    if(age > 80){
        //�������� �������� � ������� �������
        errmess = "�������� ������� ����!";
        invalid = true;
        }
    if(age < 5){
        //�������� �������� � ������� �������
        errmess = "�������� ������� �����!";
        invalid = true;
        }

    //������� ��������� � ������� ��������
    int idCount;
    int *fvids = createFightVersionIdList(idCount);
    if(!fvids){
        //������, ������ ���� ������� ���� ���� ���������
        errmess = "�� ������ �� ���� ������ ������!";
        invalid = true;
        }

    //���������, ����� �� ������� ���������� (���� ������� ������)
    if(cmboxSkill->ItemIndex == -1){
        //�� ����� ������� ����������
        errmess = "������� ������� ����������!";
        invalid = true;
        }


    //���������, ����� �� ��� ��������� (���� �������, �� ��������)
    if(medtWeight->Text.Trim()==","){
        //��� �� �����
        errmess = "�� ����� ��� ���������!";
        invalid = true;
        }


    //��������� ������������ ��������� ������, ���� ��� ��������� ���������
    if(invalid){
        //���������� ��������� �� ������
        MessageDlg(errmess,
                    mtError, TMsgDlgButtons() << mbOK, 0);
        //������� ��� ����������� ������
        return false;
        }

    //��������� �������� � ���� ������
    obj.store();

    //������ ��������� � ��������� ��� � ���� ������, ��������� ��� � ������
    int skillId =((TSkill*)dmCurrentState->getSkillList()->Items[cmboxSkill->ItemIndex])->getId();
    newCompetitor->setPersonId(obj.getId());
    newCompetitor->setSkillId(skillId);
    newCompetitor->setRequestId(dmCurrentState->getRequest().getId());
    newCompetitor->setWeight(StrToFloat(medtWeight->Text));

    //��������� ��������� � ���� ������
    newCompetitor->store();
    //���������� ������ ������ ��� ���������
    newCompetitor->setFightVersion(fvids, idCount);
    delete[] fvids;

    //��������� ������ ���������
    newCompetitor->extend(obj, *(TSkill*)dmCurrentState->getSkillList()->Items[cmboxSkill->ItemIndex],
                            dmCurrentState->getRequest());

    //�������� ������� �������� 
    return true;
}




int *TfrmRequestCompetitorsListEdit::createFightVersionIdList(int &count){
    //������� ������ ��� ���� ��������
    int *ids = new int[chlstboxFightVersion->Count];
    count=0;
    //������������� ��� ������ � ������� id ���������� ������
    for(int i=0; i < chlstboxFightVersion->Count; i++){
        if(chlstboxFightVersion->Checked[i]){
            ids[count++] = ((TFightVersion*)dmCurrentState->getFightVersionList()->Items[i])->getId();
            }
        }
    if(count){
        //�������������� ���������
        return (int *)realloc(ids, sizeof(int) * count);
        }
    else{
        return 0;
        }

}


//---------------------------------------------------------------------------


void __fastcall TfrmRequestCompetitorsListEdit::medtWeightExit(
      TObject *Sender)
{
    //��������� �����

    medtWeight->Text = FormatFloatValueText(medtWeight->Text);
}
//---------------------------------------------------------------------------



void __fastcall TfrmRequestCompetitorsListEdit::bbtnDeleteClick(
      TObject *Sender)
{
    //-- ������� ��������� �� ������
    if(MessageDlg("������� ��������� �� ������?", mtConfirmation,
    TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)return;
    //������� �� ������ ���������� � ���� ������
    ((TCompetitor*)competitorsList->Items[strgrdCompetitorsList->Row -1])->erase();
    //������� �� ������ ���������� � ������
    competitorsList->Delete(strgrdCompetitorsList->Row-1);
    //������� �� StringGrid
    deleteFromCompetitorStringGrid(strgrdCompetitorsList->Row, strgrdCompetitorsList);
    //����������� ������� � ��������� 
    changePersonSearchTableState();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::bbtnEditClick(
      TObject *Sender)
{
    //-- �������� ���������� ������������
    //������� � ����� ��������������
    setEditMode();

    TCompetitor* edited = (TCompetitor*)(competitorsList->Items[strgrdCompetitorsList->Row - 1]);

    //������� ����������
    dmCurrentState->setPerson(edited->getPerson()); 

    //����������� ������ �� ������� � ���� �����
    lbledtSurname->Text = edited->getPerson().getSurname();
    lbledtName->Text = edited->getPerson().getName();
    lbledtPatronymic->Text = edited->getPerson().getPatronymic();
    dtpDOB->DateTime = edited->getPerson().getDob();
    chboxFemale->Checked = edited->getPerson().getFemale();
    medtWeight->Text = edited->getWeight();
    selectSkillById(edited->getSkill().getId());
    //�������� �������� �������� � ���� ��� �����������
    dtpDOBChange(NULL);

    TList * fvids = edited->getFightVersion();
    //�������� �� ������ � ���������� ��������
    checkedFightVersion(fvids);
    destroyList(fvids, etFIGHTVERSION);
}


void TfrmRequestCompetitorsListEdit::selectSkillById(int id){
    //���������� �� ������
    for(int i = 0; i < cmboxSkill->Items->Count; i++){
        //����� �������������� ��������, ������� ������� ���� ������� ����������
        if(((TSkill*)dmCurrentState->getSkillList()->Items[i])->getId() == id){
            cmboxSkill->Text = ((TSkill*)dmCurrentState->getSkillList()->Items[i])->getShortDescription();
            cmboxSkill->ItemIndex = i;
            //�������� �����
            break;  
            }
        }
}


void TfrmRequestCompetitorsListEdit::checkedFightVersion(TList *tocheck){
    //���������� �� ������ ��� ������ ����������
    for(int i = 0; i < chlstboxFightVersion->Count; i++){
        //���������� ������� 
        chlstboxFightVersion->Checked[i] = false;
        //���������� �� ������ ������������� ��� ���������
        for(int j = 0; j < tocheck->Count; j++){
            if(((TFightVersion*)dmCurrentState->getFightVersionList()->Items[i])->getId() ==
               ((TFightVersion*)tocheck->Items[j])->getId()){
                //��������
                chlstboxFightVersion->Checked[i] = true;
                }
            }
        }
}



void TfrmRequestCompetitorsListEdit::setEditMode(void){
    //�������� ����������� � �������
    bbtnAddCompetitor->Visible = false;
    bbtnCloseList->Visible = false;
    bbtnUpdateCompetitor->Visible = true;
    bbtnCancelCompetitor->Visible = true;
    //��������� ��������� ������ � ������� ����������
    strgrdCompetitorsList->Enabled = false;       

}


void TfrmRequestCompetitorsListEdit::closeEditMode(void){
    //�������� ����������� � ������� ������
    bbtnAddCompetitor->Visible = true;
    bbtnCloseList->Visible = true;
    bbtnUpdateCompetitor->Visible = false;
    bbtnCancelCompetitor->Visible = false;
    //��������� ��������� ������ � �������
    strgrdCompetitorsList->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::bbtnUpdateCompetitorClick(
      TObject *Sender)
{

    TPerson personToStore = dmCurrentState->getPerson();

    TCompetitor *competitor =(TCompetitor*)competitorsList->Items[strgrdCompetitorsList->Row -1];

    //�������� ��� �������� ��������, � ������������ � ������� �����
    personToStore.setSurname(lbledtSurname->Text.Trim());
    personToStore.setName(lbledtName->Text.Trim());
    personToStore.setPatronymic(lbledtPatronymic->Text.Trim());


    //������ �� ���� ������ ������ ������ ��� ���������
    competitor->eraseFightVersion();
    //������ ��������� �� ���������
    TCategory::uncategory(competitor->getId()); 

    //������� ������� � ���� ������
    if(CompetitorIntoDatabase(personToStore, competitor)){
        //���������� ��������� � ���������
        TCategory::destributeCompetitor(*competitor, dmCurrentState->getCompetition());
        //�������� ����������� � ������� ������
        closeEditMode();
        //�������� ����
        clearFields();
        //�������� �������� � �������
        addToCompetitorStringGrid(*competitor, strgrdCompetitorsList->Row, strgrdCompetitorsList);
        dmCurrentState->setPerson(personToStore);
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::bbtnCancelCompetitorClick(
      TObject *Sender)
{
    if(MessageDlg("�������� ��������� ������?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes){
        //-- �������� ������� ���������
        clearFields();
        closeEditMode();
        }


}
//---------------------------------------------------------------------------




void setCompetitorTableHeader(TStringGrid *grid){
    grid->ColCount = 5; grid->FixedCols = 0;
    grid->RowCount = 2; grid->FixedRows = 1; 
    grid->Cells[0][0] = "�.�.�";
    grid->Cells[1][0] = "������ ���";
    grid->Cells[2][0] = "���";
    grid->Cells[3][0] = "������� ����������";
    grid->Cells[4][0] = "��������� � �������";
}



void deleteFromCompetitorStringGrid(int delIndex, TStringGrid *grid){
    // ������� ������� � �������� �������� //

    //���� ��������� ������������ ��������
    if(grid->RowCount == 2){
        grid->Rows[1]->Clear();
        return;
        }

    //���� ��� �� ��������� ������
    if(delIndex != (grid->RowCount - 1)){
        //������� ��� ������, ������� ��������� ���� �� �� �����
        for(int i = delIndex+1; i < grid->RowCount; i++){
            grid->Rows[i - 1] = grid->Rows[i];
            }
        }
    //������� ��������� �������
    grid->Rows[grid->RowCount - 1]->Clear();
    grid->RowCount--;
}

void clearStrGrid(TStringGrid *grid){
//    for(int i=1; i < grid->RowCount; i++){
//        grid->Rows[i]->Clear();
//        }

    grid->RowCount = 2;
    grid->Rows[1]->Clear();

}



void addToCompetitorStringGrid(TCompetitor competitor, int addIndex, TStringGrid *grid){
    //�.�.�.
    AnsiString surname = competitor.getPerson().getSurname();
    AnsiString name = competitor.getPerson().getName().SubString(1,1) + ".";
    AnsiString patronymic = competitor.getPerson().getPatronymic().SubString(1,1);
    patronymic += (patronymic.Length()>0)? "." : " ";
    AnsiString female = competitor.getPerson().getFemale()?"(�) " : " ";
    AnsiString snp = female + surname + " " + name + " " +patronymic;
    //������ ������

    TList *fvlist = competitor.getFightVersion();
    AnsiString fvstr = "";
    for(int i = 0; i < (fvlist->Count - 1); i++){
        fvstr += ((TFightVersion*)fvlist->Items[i])->getCode() + ", ";
        }
    if(fvlist->Count > 0){
        fvstr+= ((TFightVersion*)fvlist->Items[fvlist->Count - 1])->getCode();
        }
    destroyList(fvlist, etFIGHTVERSION);

    //�������� ��������� � �������

    //�������� ���
    grid->Cells[0][addIndex] = snp;
    //�������� ������ ���
    grid->Cells[1][addIndex] = IntToStr(YearsPassCalculator(
                                                        competitor.getPerson().getDob()
                                                        ));
    //��� ���������
    grid->Cells[2][addIndex] = FloatToStrF(competitor.getWeight(),
                                                            ffFixed, 4, 1);

    //������� ����������
    grid->Cells[3][addIndex] = competitor.getSkill().getShortDescription();
    //������ ������, � ������ ��������� ��������
    grid->Cells[4][addIndex] = fvstr;
}



TList* createCompetitorsList(int requestId, TStringGrid *grid){
    //�������� ������ ���������� �� ���� ������
    TList* list = TCompetitor::getExtendedByRequestId(requestId);


    if(grid==NULL) return list;
    //���������� ������ � �������
    if(list->Count)
        grid->RowCount = list->Count + 1;
    else
        grid->RowCount = list->Count + 2;
    for(int i=0; i < list->Count; i++){
        addToCompetitorStringGrid(*((TCompetitor*)list->Items[i]), i + 1,
                                  grid);
        }

    //������� ��������� (���������� ����� �������� �� ��������� �������)
    return list;
}



void __fastcall TfrmRequestCompetitorsListEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //���������� ��������� �� �������� �����

    if(MessageDlg("��������� ���������� ������ ����������?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo){
        Action = caNone;
        }
    else{
       dbgrdPersonList->DataSource = NULL;
    }
}
//---------------------------------------------------------------------------




