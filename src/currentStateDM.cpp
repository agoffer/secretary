//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CurrentStateDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmCurrentState *dmCurrentState;
//---------------------------------------------------------------------------
__fastcall TdmCurrentState::TdmCurrentState(TComponent* Owner)
    : TDataModule(Owner)
{
    skillList = new TList();  
    skillList = getSkillList();
    fightVersionList = new TList();
    fightVersionList = getFightVersionList();
    requestList = new TList(); requestList->Clear();
    femaleCategoryList = new TList();
    maleCategoryList = new TList();
    categoryList = new TList();
    allAvailCategoryList = new TList();
    femaleAvailCategoryList = new TList();
    maleAvailCategoryList = new TList(); 
    allAvailCategoryList = getAllAvailCategoryList();
    femaleUncategoryCompetitorList = new TList(); femaleUncategoryCompetitorList->Clear(); 
    maleUncategoryCompetitorList = new TList(); maleUncategoryCompetitorList->Clear(); 
}
//---------------------------------------------------------------------------

__fastcall TdmCurrentState::~TdmCurrentState(void)
{
        destroyList(requestList, etREQUEST);
        destroyList(fightVersionList, etFIGHTVERSION);
        destroyList(skillList, etSKILL);
        destroyList(categoryList, etCATEGORY);
        delete (TList*)femaleCategoryList;
        delete (TList*)maleCategoryList;
        destroyList(allAvailCategoryList, etAVAILCATEGORY);
        delete (TList*)femaleAvailCategoryList;
        delete (TList*)maleAvailCategoryList;
        destroyList(femaleUncategoryCompetitorList, etCOMPETITOR);
        destroyList(maleUncategoryCompetitorList, etCOMPETITOR);
}

void TdmCurrentState::setCompetition(TCompetition competition){
    //��������� ������� ������������� 
    Competition = competition;
    //������� ������ �������������� ��������� � ������
    createRequestList(competition);
    //������� ����� ����� �� ������������
    createScoreRankMap(competition.getCompetitionRank().getId());
    //��������� ���������
    createCategoryList(competition); 
}



void TdmCurrentState::createScoreRankMap(int competitionRank){
    //��������, ���� ���������� ������ 
    scoreRankingShooting.clear();
    scoreRankingFighting.clear();
    TResult::getScoreRanking(scoreRankingShooting, competitionRank, 0);
    TResult::getScoreRanking(scoreRankingFighting, competitionRank, 1);

}





void TdmCurrentState::addRequestToList(TRequest request){
    //������� ������, ����������� � ������
    TRequest *newObj =  new TRequest();
    //������� ������
    *newObj = request;
    //�������� ������ � ������
    requestList->Add(newObj);
    //�������� � ��������������� ������
    requestMap[request.getId()] = newObj;
}



void TdmCurrentState::createRequestList(TCompetition competition){
    //�������� ������
    destroyList(requestList, etREQUEST);
    requestMap.clear();
    //�������� ������ ��� ������������
    requestList = TRequest::getExtendedByCompetitionId(competition.getId());

    //�������� � ��������������� ������
    for(int i=0; i < requestList->Count; i++){
        TRequest *current = (TRequest*)requestList->Items[i];
        //�������� ��������� ������ � ��������������� ������
        requestMap[current->getId()] = current;
        }
}

void TdmCurrentState::addCategoryToList(TCategory category){
    //������� ���������, ����������� � ������
    TCategory *newObj =  new TCategory();
    //������� ������
    *newObj = category;

    if(category.getAvailCategory().getFemale())
        //������� � ������ ������� ���������
        femaleCategoryList->Add(newObj);
    else
        //������� � ������ ������� ���������
        maleCategoryList->Add(newObj);

    //�������� ��������� � ������
    categoryList->Add(newObj);

    //�������� � ��������������� ������
    categoryMap[category.getId()]  = newObj;
}



void TdmCurrentState::createCategoryList(TCompetition competition){
    //�������� ������
    destroyList(categoryList, etCATEGORY);
    categoryMap.clear();
    //�������� ��������� ��� ������������
    categoryList = TCategory::getExtendedByCompetitionId(competition.getId());
    femaleCategoryList->Clear();
    maleCategoryList->Clear();

    //������� ��������� � ��������������� ������
    for(int i=0; i < categoryList->Count; i++){
        TCategory* current = (TCategory*)categoryList->Items[i];
        //�������� �� ������� � ������� ����������
        if(current->getAvailCategory().getFemale())
            //������� � ������ ������� ���������
            femaleCategoryList->Add(current);
        else
            //������� � ������ ������� ���������
            maleCategoryList->Add(current);

        //������� ������� ��������� � ��������������� ������ ���������
        categoryMap[current->getId()] = current;
        }
}


void TdmCurrentState::addUncategoryCompetitorToList(TCompetitor competitor, bool female){
    //���������, ������������ � ������
    TCompetitor *newObj =  new TCompetitor();
    //������� ������
    *newObj = competitor;
    //�������� ��������� � ������
    female?femaleUncategoryCompetitorList->Add(newObj) : maleUncategoryCompetitorList->Add(newObj);
}


void TdmCurrentState::createUncategoryCompetitorList(TCompetition competition){
    //�������� ������ ���������������� ����������
    destroyList(femaleUncategoryCompetitorList, etCOMPETITOR);
    destroyList(maleUncategoryCompetitorList, etCOMPETITOR);

    femaleUncategoryCompetitorList = TCompetitor::getExtendedUncategoryByCompetitionId(competition.getId(), true);
    maleUncategoryCompetitorList = TCompetitor::getExtendedUncategoryByCompetitionId(competition.getId(), false);
}


void TdmCurrentState::addFightVersionToList(TFightVersion fightVersion){
    //������� ������ ������, ����������� � ������
    TFightVersion *newObj =  new TFightVersion();
    //������� ������
    *newObj = fightVersion;
    //�������� ������ ������ � ������
    fightVersionList->Add(newObj);
    //�������� � ��������������� ������
    fightVersionMap[fightVersion.getId()] = newObj;
}

TFightVersion TdmCurrentState::findFightVersionByCode(AnsiString code){
TFightVersion result; result.setId(0);
    //����� ������ ������ �� ����
    for(int i=0; i < fightVersionList->Count; i++){
        TFightVersion *current = (TFightVersion*)fightVersionList->Items[i];
        if(!current->getCode().AnsiCompare(code)){
            //������� ��������� ���������
            return *current;
            }
        }
    return result; 
}

void TdmCurrentState::createFightVersionList(void){
    //�������� ������
    destroyList(fightVersionList, etFIGHTVERSION);
    fightVersionMap.clear();
    //�������� ������ ������ ������
    fightVersionList = TFightVersion::getAll();

    //������� ��������������� ������
    for(int i=0; i < fightVersionList->Count; i++){
        TFightVersion *current = (TFightVersion*)fightVersionList->Items[i];
        //�������� ������ ������ � ��������������� ������
        fightVersionMap[current->getId()] = current;
        }
}


void TdmCurrentState::addSkillToList(TSkill skill){
    //������� ������� ����������, ����������� � ������
    TSkill *newObj =  new TSkill();
    //������� ������� ����������
    *newObj = skill;
    //�������� ������� ���������� � ������
    skillList->Add(newObj);
    //������� � ��������������� ������
    skillMap[skill.getId()] = newObj;
}


void TdmCurrentState::createSkillList(void){
    //�������� ������
    destroyList(skillList, etSKILL);
    skillMap.clear();
    skillList = TSkill::getAll();
    //������� ��������������� ������
    for(int i=0; i < skillList->Count; i++){
        TSkill *current = (TSkill*)skillList->Items[i];
        skillMap[current->getId()] = current;
        }
}


void TdmCurrentState::addAvailCategoryToList(TAvailCategory inAvailCategory){
    //������� ���������, ����������� � ������
    TAvailCategory *newObj =  new TAvailCategory();
    //������� ������
    *newObj = inAvailCategory;
    //�������� ��������� � ������
    allAvailCategoryList->Add(newObj);
    //�������� � ��������������� ������
    availCategoryMap[inAvailCategory.getId()] = newObj;
    //�������� � ������� ��� ������� ���������
    if(inAvailCategory.getFemale()){
        femaleAvailCategoryList->Add(newObj);
        }
    else{
        maleAvailCategoryList->Add(newObj);
        }
}


void TdmCurrentState::createAvailCategoryList(void){
    //�������� ������
    destroyList(allAvailCategoryList, etAVAILCATEGORY);
    femaleAvailCategoryList->Clear();
    maleAvailCategoryList->Clear();

    availCategoryMap.clear();

    allAvailCategoryList = TAvailCategory::getAll();


    //�������� ��������������� ������
    for(int i=0; i < allAvailCategoryList->Count; i++){
        TAvailCategory *current = (TAvailCategory*)allAvailCategoryList->Items[i];
        //�������� ������ ������ � ������
        availCategoryMap[current->getId()] = current;
        if(current->getFemale()){
            femaleAvailCategoryList->Add(current);
            }
        else{
            maleAvailCategoryList->Add(current);
            }
        }
}


TRequest *TdmCurrentState::getRequestById(int requestId){
    //���������� ������ �� ���������������� ������
    return requestMap[requestId];
}

TCategory *TdmCurrentState::getCategoryById(int categoryId){
    //���������� ������ �� ���������������� ������
    return categoryMap[categoryId];
}


int TdmCurrentState::getScoreForRank(int rank, int disciplineId){
    int score = 0;

    //�������� ���� �� �����
    // ��������
    if(disciplineId == 0) {
        score = scoreRankingShooting[rank];
    } else if (disciplineId == 1) {
        score = scoreRankingFighting[rank];
    }
    return score;  
}



