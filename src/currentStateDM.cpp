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
    //Сохранить текущие соревнованния 
    Competition = competition;
    //Создать списки соответсвующих категорий и заявок
    createRequestList(competition);
    //Создать шкалу балов за соревнования
    createScoreRankMap(competition.getCompetitionRank().getId());
    //Загрузить категории
    createCategoryList(competition); 
}



void TdmCurrentState::createScoreRankMap(int competitionRank){
    //Очистить, если существуют данные 
    scoreRanking.clear();
    TResult::getScoreRanking(scoreRanking, competitionRank); 
}





void TdmCurrentState::addRequestToList(TRequest request){
    //Создать заявку, добавляемую в список
    TRequest *newObj =  new TRequest();
    //Добавим заявку
    *newObj = request;
    //Добавить заявку в список
    requestList->Add(newObj);
    //Добавить в индексированный список
    requestMap[request.getId()] = newObj;
}



void TdmCurrentState::createRequestList(TCompetition competition){
    //Очистить список
    destroyList(requestList, etREQUEST);
    requestMap.clear();
    //Получить заявки для соревнования
    requestList = TRequest::getExtendedByCompetitionId(competition.getId());

    //Добавить в индексированный список
    for(int i=0; i < requestList->Count; i++){
        TRequest *current = (TRequest*)requestList->Items[i];
        //Добавить очередную заявку в индексированный список
        requestMap[current->getId()] = current;
        }
}

void TdmCurrentState::addCategoryToList(TCategory category){
    //Создать категорию, добавляемую в список
    TCategory *newObj =  new TCategory();
    //Добавим заявку
    *newObj = category;

    if(category.getAvailCategory().getFemale())
        //Добавим в список женских категорий
        femaleCategoryList->Add(newObj);
    else
        //Добавим в список мужских категорий
        maleCategoryList->Add(newObj);

    //Добавить категорию в список
    categoryList->Add(newObj);

    //Добавить в индексированный список
    categoryMap[category.getId()]  = newObj;
}



void TdmCurrentState::createCategoryList(TCompetition competition){
    //Очистить список
    destroyList(categoryList, etCATEGORY);
    categoryMap.clear();
    //Получить категории для соревнования
    categoryList = TCategory::getExtendedByCompetitionId(competition.getId());
    femaleCategoryList->Clear();
    maleCategoryList->Clear();

    //Добавим категории в индексированный список
    for(int i=0; i < categoryList->Count; i++){
        TCategory* current = (TCategory*)categoryList->Items[i];
        //Разнесем по женским и мужским категориям 
        if(current->getAvailCategory().getFemale())
            //Добавим в список женских категорий
            femaleCategoryList->Add(current);
        else
            //Добавим в список мужских категорий
            maleCategoryList->Add(current);

        //Добавим текущую категорию в индексированный список категорий
        categoryMap[current->getId()] = current;
        }
}


void TdmCurrentState::addUncategoryCompetitorToList(TCompetitor competitor, bool female){
    //Участника, добавляемого в список
    TCompetitor *newObj =  new TCompetitor();
    //Добавим заявку
    *newObj = competitor;
    //Добавить категорию в список
    female?femaleUncategoryCompetitorList->Add(newObj) : maleUncategoryCompetitorList->Add(newObj);
}


void TdmCurrentState::createUncategoryCompetitorList(TCompetition competition){
    //Очистить список нераспределенных участников
    destroyList(femaleUncategoryCompetitorList, etCOMPETITOR);
    destroyList(maleUncategoryCompetitorList, etCOMPETITOR);

    femaleUncategoryCompetitorList = TCompetitor::getExtendedUncategoryByCompetitionId(competition.getId(), true);
    maleUncategoryCompetitorList = TCompetitor::getExtendedUncategoryByCompetitionId(competition.getId(), false);
}


void TdmCurrentState::addFightVersionToList(TFightVersion fightVersion){
    //Создать боевую версию, добавляемую в список
    TFightVersion *newObj =  new TFightVersion();
    //Добавим заявку
    *newObj = fightVersion;
    //Добавить боевую версию в список
    fightVersionList->Add(newObj);
    //Добавить в индексированный список
    fightVersionMap[fightVersion.getId()] = newObj;
}

TFightVersion TdmCurrentState::findFightVersionByCode(AnsiString code){
TFightVersion result; result.setId(0);
    //Найти боевую версию по коду
    for(int i=0; i < fightVersionList->Count; i++){
        TFightVersion *current = (TFightVersion*)fightVersionList->Items[i];
        if(!current->getCode().AnsiCompare(code)){
            //Вернуть найденную категорию
            return *current;
            }
        }
    return result; 
}

void TdmCurrentState::createFightVersionList(void){
    //Очистить список
    destroyList(fightVersionList, etFIGHTVERSION);
    fightVersionMap.clear();
    //Получить список боевых версий
    fightVersionList = TFightVersion::getAll();

    //Создать индексированный список
    for(int i=0; i < fightVersionList->Count; i++){
        TFightVersion *current = (TFightVersion*)fightVersionList->Items[i];
        //Добавить боевую версию в индексированный список
        fightVersionMap[current->getId()] = current;
        }
}


void TdmCurrentState::addSkillToList(TSkill skill){
    //Создать уровень мастерства, добавляемую в список
    TSkill *newObj =  new TSkill();
    //Добавим уровень мастерства
    *newObj = skill;
    //Добавить уровень мастерства в список
    skillList->Add(newObj);
    //Добавим в индексированный список
    skillMap[skill.getId()] = newObj;
}


void TdmCurrentState::createSkillList(void){
    //Очистить список
    destroyList(skillList, etSKILL);
    skillMap.clear();
    skillList = TSkill::getAll();
    //Создать индексированный список
    for(int i=0; i < skillList->Count; i++){
        TSkill *current = (TSkill*)skillList->Items[i];
        skillMap[current->getId()] = current;
        }
}


void TdmCurrentState::addAvailCategoryToList(TAvailCategory inAvailCategory){
    //Создать категорию, добавляемую в список
    TAvailCategory *newObj =  new TAvailCategory();
    //Добавим заявку
    *newObj = inAvailCategory;
    //Добавить категорию в список
    allAvailCategoryList->Add(newObj);
    //Добавить в индексированный список
    availCategoryMap[inAvailCategory.getId()] = newObj;
    //Добавить в женскую или мужскую категорию
    if(inAvailCategory.getFemale()){
        femaleAvailCategoryList->Add(newObj);
        }
    else{
        maleAvailCategoryList->Add(newObj);
        }
}


void TdmCurrentState::createAvailCategoryList(void){
    //Очистить список
    destroyList(allAvailCategoryList, etAVAILCATEGORY);
    femaleAvailCategoryList->Clear();
    maleAvailCategoryList->Clear();

    availCategoryMap.clear();

    allAvailCategoryList = TAvailCategory::getAll();


    //Создадим индексированный список
    for(int i=0; i < allAvailCategoryList->Count; i++){
        TAvailCategory *current = (TAvailCategory*)allAvailCategoryList->Items[i];
        //Добавить боевую версию в список
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
    //Определяем заявку по индексированнуму списку
    return requestMap[requestId];
}

TCategory *TdmCurrentState::getCategoryById(int categoryId){
    //Определяем заявку по индексированному списку
    return categoryMap[categoryId];
}


int TdmCurrentState::getScoreForRank(int rank){
    //Отыскать балы по шкале 
    int score = scoreRanking[rank];
    return score;  
}



