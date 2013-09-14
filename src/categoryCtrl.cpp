//---------------------------------------------------------------------------

#pragma hdrstop

#include "categoryCtrl.h"
#include "categoryDM.h"
#include "currentStateDM.h"
#include "utils.h"

//���������� ���������� � ������
const int COMPETITORS_IN_TREE = 32;

//���������� ������� ���������� ���, �� ������ 
bool desc = false;

int criticalPairs[32] = {0 /* �� ������������ */, 0 /* �� ������������ */,
//                 3    4    5    6    7    8    9   10   11   12   13   14   15   16
                   1,   2,   1,   2,   3,   4,   1,   2,   5,   6,   3,   4,   7,   8,
//                17   18   19   20   21   22   23   24   25   26   27   28   29   30
                   1,   2,   9,  10,   5,   6,  11,  12,   3,   4,  13,  14,   7,   8,
//                31   32
                  15,  16
                        };

void getCriticalPairsIndexes(int &bottomIndex, int &topIndex, int dataAmnt){
    //������� ������� � ����������� �� ���������� ����������
    switch(dataAmnt){
        case 32  :;
        case 31  :;
        case 30  :bottomIndex = 16; break;
        case 29  :bottomIndex = 15; break;
        case 28  :;
        case 27  :;
        case 26  : bottomIndex = 14; break;
        case 25  : bottomIndex = 13; break;
        case 24  :;
        case 23  :;
        case 22  : bottomIndex = 12; break;
        case 21  : bottomIndex = 11; break;
        case 20  :;
        case 19  :;
        case 18  : bottomIndex = 10; break;
        case 17  : bottomIndex = 9; break;
        case 16 :;
        case 15 :;
        case 14 : bottomIndex = 8; break;
        case 13 : bottomIndex = 7; break;
        case 12 : bottomIndex = 6; break;
        case 11 : bottomIndex = 5; break;
        case 10 : bottomIndex = 6; break;
        case 9  : bottomIndex = 5; break;
        case 8  :;
        case 7  :;
        case 6  : bottomIndex = 4; break;
        case 5  : bottomIndex = 3; break;
        case 4  : bottomIndex = 2; break;
        case 3  : bottomIndex = 2;
        }
    topIndex = dataAmnt - 1; 
}


//---------------------------------------------------------------------------


void TCategory::extend(void){
    //�������� ����������� ���� 
    if(availCategoryId)
        availCategory.getById(availCategoryId);
    if(fightVersionId)
        fightVersion.getById(fightVersionId);
    if(competitionId)
        competition.getById(competitionId);
    //���������� ������� ����������
    extended = true;
}

void TCategory::extend(TAvailCategory inAvailCategory, TFightVersion inFightVersion, TCompetition inCompetition){

    availCategory = inAvailCategory;
    availCategoryId = inAvailCategory.getId();

    fightVersion = inFightVersion;
    fightVersionId = inFightVersion.getId();


    competition.getById(competitionId);
    competitionId = inCompetition.getId();

    //���������� ������� ����������
    extended = true;
}

TCategory::TCategory(int inAvailCategoryId, int inFightVersionId, int inCompetitionId){
    //�������������� ������
    availCategoryId = inAvailCategoryId;
    fightVersionId = inFightVersionId;
    competitionId = inCompetitionId;
    id = 0;
    //���������� ������ �� ��������
    extended = false;
    availCategory.setId(0);
    fightVersion.setId(0);
    competition.setId(0);
}

TCategory::~TCategory(void){
}

bool TCategory::valid(AnsiString &errmess){
    //�������� ������������ ����� �������
    //��� ���������
    return true;
}

void TCategory::store(void){
   dmCategoryDAO->store(*this);
}

TCategory TCategory::getCurrent(void){
    return dmCategoryDAO->getCurrent();
}


void TCategory::makeCurrent(void){
    return dmCategoryDAO->makeCurrent(*this);
}


TList* TCategory::getAll(void){
        return NULL;
}

//-- ������� ��� ��������� (� ����������� �����), ��� ������� ������������
TList * TCategory::getExtendedByCompetitionId(int competitionId){
    return dmCategoryDAO->getExtendedByCompetitionId(competitionId);
}

//-- ������� ��� ��������� (� ����������� �����), ��� ������� ������������,
//-- � ������� ������������ �������� � �������� : surname
TList * TCategory::getExtendedByCompetitionIdSurname(int competitionId, AnsiString surname){
    return dmCategoryDAO->getExtendedByCompetitionIdSurname(competitionId, surname);
}



void TCategory::getById(int id){
    dmCategoryDAO->getById(id, *this);
}

bool TCategory::checkForDistribution(TCompetition competition){
    int count = 0;
    TList* categories = dmCategoryDAO->getByCompetitionId(competition.getId());
    if(categories->Count!=0){
        count = categories->Count;
        destroyList(categories, etCATEGORY);
        }
    return (count != 0);
}

void TCategory::addCompetitor(TCompetitor inCompetitor){
    dmCategoryDAO->addCompetitor(inCompetitor.getId(), id);
}

void TCategory::setCompetitors(TList *ids){
    dmCategoryDAO->setCompetitors(id, ids);
}

void TCategory::eraseCompetitors(TList *ids){
    dmCategoryDAO->eraseCompetitors(id, ids); 
}


void TCategory::putInAvailCategory(TCompetitor competitor, TFightVersion fightVersion, TCompetition competition){
    //���������, ������� �� �������� � ��������� ���������
    int checkAvailCategoryId = TAvailCategory::checkForAvailCategory(competitor);

    //���� �������� ����� � ��������� ���������, �������� ������ ���������
    if(checkAvailCategoryId){
        //�������� ���������
        this->availCategoryId = checkAvailCategoryId;
        this->fightVersionId = fightVersion.getId();
        this->competitionId = competition.getId();
        this->id = 0;
        //�������� ��������� � ���� ������
        this->store();
        //��������� ��������� � ���������
        this->addCompetitor(competitor);
        }
    else{
        //��������� �� �������
        id = 0;
        }
}


bool TCategory::putInCreatedCategory(TCompetitor competitor, TFightVersion fightVersion, TCompetition competition){
    //���������, �������� �� �������� � ��� ��������� ���������
    int age = YearsPassCalculator(competitor.getPerson().getDob());
    return  dmCategoryDAO->putCompetitor(competitor.getWeight(), age,
                        competitor.getPerson().getFemale(), fightVersion.getId(),
                        competition.getId(), competitor.getId());
}



void TCategory::destributeCompetitors(TRequest request, TCompetition competition){

    //��������� ������ ���������� �� ������ ��� ������������
    TList* competitorsList = TCompetitor::getExtendedByRequestId(request.getId());
    int competitorCount = competitorsList->Count;

    // -- ��� ������� ���������, ������������� ��� ������ ������ � �������� �� ����������

    for(int comp=0; comp < competitorCount; comp++){
        //�������� ������ ������ ������ ��� �������� ���������
        int fightVersionCount;
        TCompetitor *curCompetitor = (TCompetitor*)competitorsList->Items[comp];
        TList *fvids = curCompetitor->getFightVersion();

        //���������� �� ������ ������ ������ - �������, ���� �� ����� �������� ���������
        for(int fv = 0; fv < fvids->Count; fv++){

            //����� �� �� �������� ��������� � ������������ ��������� ?
            if(!putInCreatedCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition)){
                //�� ������ �������� � ��� ��������� ���������
                //������� �������� � ���� �� ��������� � ��������� ����� ���������
                TCategory newCategory;
                newCategory.putInAvailCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition);
                //���� ���� �������� ��������� �������� �� � ������ ��������� ���������,
                // � ��������� ������ - �������� � ������ �� �������� � ���������
                if(!newCategory.getId()){
                    //�������� �� �������� � ���������
                    break;  //��������� ��� ���� ���
                    }
                }
            }
        }
    //������� ������ ����������
    destroyList(competitorsList, etCOMPETITOR);
}



void TCategory::destributeCompetitors(TList *competitorsList, TCompetition competition){

    //���������� ����������
    int competitorCount = competitorsList->Count;

    // -- ��� ������� ���������, ������������� ��� ������ ������ � �������� �� ����������

    for(int comp=0; comp < competitorCount; comp++){
        //�������� ������ ������ ������ ��� �������� ���������
        int fightVersionCount;
        TCompetitor *curCompetitor = (TCompetitor*)competitorsList->Items[comp];
        TList *fvids = curCompetitor->getFightVersion();

        //���������� �� ������ ������ ������ - �������, ���� �� ����� �������� ���������
        for(int fv = 0; fv < fvids->Count; fv++){

            //����� �� �� �������� ��������� � ������������ ��������� ?
            if(!putInCreatedCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition)){
                //�� ������ �������� � ��� ��������� ���������
                //������� �������� � ���� �� ��������� � ��������� ����� ���������
                TCategory newCategory;
                newCategory.putInAvailCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition);
                //���� ���� �������� ��������� �������� �� � ������ ��������� ���������,
                // � ��������� ������ - �������� � ������ �� �������� � ���������
                if(!newCategory.getId()){
                    //�������� �� �������� � ���������
                    break;  //��������� ��� ���� ���
                    }
                }
            }
        }
}



void TCategory::destributeCompetitor(TCompetitor competitor, TCompetition competition){

        //�������� ������ ������ ������ ��� �������� ���������
        TList *fvids = competitor.getFightVersion();

        //���������� �� ������ ������ ������ - �������, ���� �� ����� �������� ���������
        for(int fv = 0; fv < fvids->Count; fv++){
            //����� �� �� �������� ��������� � ������������ ��������� ?
            if(!putInCreatedCategory(competitor, *((TFightVersion*)fvids->Items[fv]), competition)){
                //�� ������ �������� � ��� ��������� ���������
                //������� �������� � ���� �� ��������� � ��������� ����� ���������
                TCategory newCategory;
                newCategory.putInAvailCategory(competitor, *((TFightVersion*)fvids->Items[fv]), competition);
                //���� ���� �������� ��������� �������� �� � ������ ��������� ���������,
                // � ��������� ������ - �������� � ������ �� �������� � ���������
                if(!newCategory.getId()){
                    //�������� �� �������� � ���������
                    break;  //��������� ��� ���� ���
                    }
                }
            }
}





void TCategory::destributeCompetitors(TCompetition competition){

    //��������� ������ ���������� ��� ������������
    TList* competitorsList = TCompetitor::getExtendedByCompetitionId(competition.getId());
    int competitorCount = competitorsList->Count;

    // -- ��� ������� ���������, ������������� ��� ������ ������ � �������� �� ����������

    for(int comp=0; comp < competitorCount; comp++){
        //�������� ������ ������ ������ ��� �������� ���������
        int fightVersionCount;
        TCompetitor *curCompetitor = (TCompetitor*)competitorsList->Items[comp];
        TList *fvids = curCompetitor->getFightVersion();

        //���������� �� ������ ������ ������ - �������, ���� �� ����� �������� ���������
        for(int fv = 0; fv < fvids->Count; fv++){

            //����� �� �� �������� ��������� � ������������ ��������� ?
            if(!putInCreatedCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition)){
                //�� ������ �������� � ��� ��������� ���������
                //������� �������� � ���� �� ��������� � ��������� ����� ���������
                TCategory newCategory;
                newCategory.putInAvailCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition);
                //���� ���� �������� ��������� �������� �� � ������ ��������� ���������,
                // � ��������� ������ - �������� � ������ �� �������� � ���������
                if(!newCategory.getId()){
                    //�������� �� �������� � ���������
                    break;  //��������� ��� ���� ���
                    }
                }
            }
        }
    //������� ������ ����������
    destroyList(competitorsList, etCOMPETITOR);
}



/*

int __fastcall sortionCompareClub(void *fstItem, void *secItem){
    if(((TSortionData *)fstItem)->clubId > ((TSortionData *)secItem)->clubId){
        //������ ���� � ������� ���������������
        return 1;
        }
    else if(((TSortionData *)fstItem)->clubId < ((TSortionData *)secItem)->clubId){
            //������ ���� � ������� ���������������
            return -1;
            }
         else{
            //���������� �����
            return 0;
            }
}

*/

int __fastcall sortionCompareSkill(void *fstItem, void *secItem){
    if(((TSortionData *)fstItem)->skillWeight > ((TSortionData *)secItem)->skillWeight){
        //������ ������� ������
        return -1;
        }
    else if(((TSortionData *)fstItem)->skillWeight < ((TSortionData *)secItem)->skillWeight){
            //������ ������� ������
            return 1;
            }
         else{
            //���������� ������
            return 0;
            }
}

/*
int __fastcall sortionCompareClubSkill(void *fstItem, void *secItem){
    if(((TSortionData *)fstItem)->clubId > ((TSortionData *)secItem)->clubId){
//    if(((TSortionData *)fstItem)->skillWeight > ((TSortionData *)secItem)->skillWeight){
        //������ ������ �������
        return -1;
        }
    else if(((TSortionData *)fstItem)->clubId < ((TSortionData *)secItem)->clubId){
//    else if(((TSortionData *)fstItem)->skillWeight < ((TSortionData *)secItem)->skillWeight){
            //������ ������ �������
            return 1;
            }
         else{
            //���������� ����� ��������� ������
//            if(((TSortionData *)fstItem)->skillWeight > ((TSortionData *)secItem)->skillWeight){
            if(((TSortionData *)fstItem)->clubId > ((TSortionData *)secItem)->clubId){
                //������ ������� ������
                return -1;
                }
            else if(((TSortionData *)fstItem)->skillWeight < ((TSortionData *)secItem)->skillWeight){
//            else if(((TSortionData *)fstItem)->clubId < ((TSortionData *)secItem)->clubId){
                //������ ������� ������
                return 1;
                }
                else{
                    //���������� ������
                    return 0;
                    }
            }
}

*/


int __fastcall compareCategories(void *fstItem, void *secItem){
    TCategory * fst = (TCategory*)fstItem;
    TCategory * sec = (TCategory*)secItem;

    //������� ���������� ��� ����������
    if(fst->getAvailCategory().getFemale() < sec->getAvailCategory().getFemale())
        //������ ��������� �������
        return -1;
    else if(fst->getAvailCategory().getFemale() > sec->getAvailCategory().getFemale())
        //������ ��������� �������
        return 1;


    //������� ������ ������
    if(fst->getFightVersionId() < sec->getFightVersionId())
        return -1;
    else if(fst->getFightVersionId() > sec->getFightVersionId())
        return 1;

    //���������� ��������
    if(fst->getAvailCategory().getStartAge() < sec->getAvailCategory().getStartAge())
        //������� ������� ������
        return -1;
    else if(fst->getAvailCategory().getStartAge() > sec->getAvailCategory().getStartAge())
        //������� ������� ������
        return 1;
    //���������� ����
    if(fst->getAvailCategory().getStartWeight() < sec->getAvailCategory().getStartWeight())
        //��� ������� ������
        return -1;
    else if(fst->getAvailCategory().getStartWeight() > sec->getAvailCategory().getStartWeight())
        //��� ������� ������
        return 1;


    //��������� ����������
    return 0;
}



/*
void TCategory::sortitionCategory(void){

//������ �� ��������� ��������������� �� ���������� � ������
int skillOrderDataAmnt;
TSortionData * skillOrderData = dmCategoryDAO->getSortionDataByCategory(this->id,
                                                skillOrderDataAmnt);

//����� "����� ������"
TList *leftBranch = new TList();
//������ "����� ������"
TList *rightBranch = new TList();

    //����������� ���������� �� ������ ������
    for(int i=0; i < skillOrderDataAmnt; i++){
        //������������ ������ � ��������
        if(i % 2){
            //������ �� ������ �����
            rightBranch->Add(&skillOrderData[i]);
            }
        else{
            //�������� �� ����� �����
            leftBranch->Add(&skillOrderData[i]);
            }
        }
    //��������� ������ ����� �� ������
//    leftBranch->Sort(sortionCompareClub);
//    leftBranch->Sort(sortionCompareSkill);
//    rightBranch->Sort(sortionCompareClub);
//     rightBranch->Sort(sortionCompareSkill);

//     leftBranch->Sort(sortionCompareClubSkill);
//     rightBranch->Sort(sortionCompareClubSkill);

    //���������� ������ ���������� � ���������, � ������� ����������� ����������
    int *sortionOrder = new int[skillOrderDataAmnt];

    //��������� ��������������
    int r=0;
    int l=0; //������� ��������� �� ������
    for(int i = 0; i < skillOrderDataAmnt; i++){
        if(i % 2){
            //���� ����� ������, ��������� � ������ �����
            sortionOrder[i] = ((TSortionData *)rightBranch->Items[r])->competitorId;
            r++;
            }
        else{
            //���� ����� ��������, ��������� � ����� �����
            sortionOrder[i] = ((TSortionData *)leftBranch->Items[l])->competitorId;
            l++;
            }
        }

    //��������� ������� ���������� ���������� � ���������
    dmCategoryDAO->storeSortionOrder(this->id, sortionOrder, skillOrderDataAmnt);

    //������� ��� ���������, ������� ��������������
    delete []  skillOrderData;
    delete [] sortionOrder;
    delete leftBranch;
    delete rightBranch;
}
*/


int searchAnotherClub(TList * branch, int startpos){
//������ ���������� ���������
int foundIndex= -1; //������ �� �������
int tobeg = startpos - 1, toend = startpos + 1;
//��� ��������� � ������ ������
int inUp = true;
    //���� �� ������� ������� � ������ � � �����, ��������
    while((tobeg >= 0) || (toend < branch->Count)){
        //��������� ����
        if(inUp){
            //���������, ���� ������ ������ ������ ���������� � ������ �������
            if(tobeg < 0){
                inUp = !inUp;
                continue;
                }
            if( (((TSortionData*)branch->Items[startpos])->clubId !=
                ((TSortionData*)branch->Items[tobeg])->clubId) &&
                (!((TSortionData*)branch->Items[tobeg])->onTree)){
                //����� ���������� ������
                foundIndex = tobeg;
                //��������� �����
                break;
                }
            //���������� � ������
            tobeg --;
            //���� ���� ��� ���� ��������� � ����� ����������� ������� ������
            if(toend < branch->Count){
                //����������� ������� ��������
                inUp = !inUp;
                }
            }
        //��������� ����
        else{
            //���������, ���� ������ ������ ���-�� ��-�� ���������� � ������ �������
            if(toend > (branch->Count - 1)){
                inUp = !inUp;
                continue;
                }
            if( (((TSortionData*)branch->Items[startpos])->clubId !=
                ((TSortionData*)branch->Items[toend])->clubId) &&
                (!((TSortionData*)branch->Items[toend])->onTree)){
                //����� ���������� ������
                foundIndex = toend;
                //��������� �����
                break;
                }
            //���������� � ������
            toend ++;
            //���� ���� ��� ���� ��������� � ������ ����������� ������ ������
            if(tobeg >=0){
                //����������� ������� ��������
                inUp = !inUp;
                }
            }
        }
    //������� ��������� ������
    return foundIndex;
}


void TCategory::sortitionCategory(void){

    //���������, ���� �� ��������� ���������� ��� ���������� ������?
    char drawType = this->getDrawType();
    if((DT_AUTO == drawType) || (DT_MANUAL == drawType)){
        //�� ���� ��������� ����������
        return;
        }

 

//������ �� ��������� ��������������� �� ���������� � ������
TList * skillClubOrderData = dmCategoryDAO->getSortionDataByCategory(this->id);
int dataAmnt = skillClubOrderData->Count;
    //�������� �� ���������� ���������� ����������
    if(dataAmnt > COMPETITORS_IN_TREE){
        destroyList(skillClubOrderData, etSORTIONDATA);
        //������������ ����� ����������! ���������� ��������� �����������
        throw "����� ���������� � \"������\" �� ����� ���� ������ " + IntToStr(COMPETITORS_IN_TREE) + "!";
        }

//����� "����� ������"
TList *leftBranch = new TList();
    leftBranch->Clear();
//������ "����� ������"
TList *rightBranch = new TList();
    rightBranch->Clear();

    //����������� ���������� �� ������ ������
    for(int i=0; i < dataAmnt; i++){
        //����������, �������� �� ��������� � ������
        ((TSortionData*)skillClubOrderData->Items[i])->onTree = false;
        //������������ ������ � ��������
        if(i % 2){
            //������ �� ������ �����
            rightBranch->Add((TSortionData*)skillClubOrderData->Items[i]);
            }
        else{
            //�������� �� ����� �����
            leftBranch->Add((TSortionData*)skillClubOrderData->Items[i]);
            }
        }

    //���������� ������ ���������� � ���������, � ������� ����������� ����������
    int *sortionOrder = new int[dataAmnt];

    if(dataAmnt > 2){
        //������������� �� ������ ����������
        leftBranch->Sort(sortionCompareSkill);
        rightBranch->Sort(sortionCompareSkill);


        //��������� � ����� ��������� ����������� ����
        int bottomIndex = -1; int topIndex = -1;
        getCriticalPairsIndexes(bottomIndex, topIndex, dataAmnt);

        bool beenSwap;

        //���������� �� �����, ���� ���� ������������
            do{
            //������������ �� �����
            beenSwap = false;
            //�������� ����� � ������ ����
            int begind = leftBranch->Count - 1;
            //���������� �� �����
            for(int i = leftBranch->Count; i > leftBranch->Count / 2; i--){
                //��� ��������� ������� � ����������
                int sp = i * 2 - 1;
                //����� �� ��������� ����� ���������
                if((sp < (bottomIndex + 1)) || (sp > (topIndex+1)))
                    //���, ������ ��������� �� ����
                    break;
                //���������, ���������� �� ����
                //������� ������� ��������� ����
                TSortionData * fst = (TSortionData *) leftBranch->Items[i - 1];
                //���� �� ��� �����������, ���������� ���
                if(fst->onTree)
                    continue;
                //��������� ������� � ������� ������� ��������� ����
                int secpos = criticalPairs[sp - 1] / 2;
                TSortionData * sec = (TSortionData *) leftBranch->Items[secpos];
                //��������� �� ������ �����, ����� ������ ������������
                if(fst->clubId == sec->clubId){
                    //����� ��������� ������������
                    beenSwap = true;
                    //������ ��������� � �����, � ������� ����� ������ ������������
                    int swpind;
                    //���� ��������� �� ������� �����
                    swpind = searchAnotherClub(leftBranch, secpos);
                    if(swpind >= 0){
                        //����  ����� ������ ������������ � �����
                        leftBranch->Exchange(secpos, swpind);
                        //����� ����� ��������
                        fst = (TSortionData *) leftBranch->Items[i - 1];
                        sec = (TSortionData *) leftBranch->Items[secpos];
                        }
                        //��������, ��� ���� ������������
                        fst->onTree = true;
                        sec->onTree = true;
    //                else{
    //                    //��������, ��� ���� ������������
    //                    fst->onTree = true;
    //                    sec->onTree = true;
    //                    }
                    }
                }
            }while(beenSwap);

        //������ ������������ ������ �����

        //���������� �� �����, ���� ���� ������������
            do{
            //������������ �� �����
            beenSwap = false;
            //�������� ����� � ������ ����
            int begind = rightBranch->Count - 1;
            //���������� �� �����
            for(int i = rightBranch->Count; i > rightBranch->Count / 2; i--){
                //��������� � ��������������� ����������
                int sp = i * 2;
                //����� �� ��������� ����� ���������
                if((sp < (bottomIndex + 1)) || (sp > (topIndex+1)))
                    //���, ������ ��������� �� ����
                    break;
                //���������, ���������� �� ����
                //������� ������� ��������� ����
                TSortionData * fst = (TSortionData *) rightBranch->Items[i - 1];
                //���� �� ��� �����������, ���������� ���
                if(fst->onTree)
                    continue;
                //��������� ������� � ������� ������� ��������� ����
                int secpos = criticalPairs[sp - 1] / 2 - 1;
                TSortionData * sec = (TSortionData *) rightBranch->Items[secpos];
                //��������� �� ������ �����, ����� ������ ������������
                if(fst->clubId == sec->clubId){
                    //����� ��������� ������������
                    beenSwap = true;
                    //������ ��������� � �����, � ������� ����� ������ ������������
                    int swpind;
                    //���� ��������� �� ������� �����
                    swpind = searchAnotherClub(rightBranch, secpos);
                    if(swpind >= 0){
                        //����  ����� ������ ������������ � �����
                        rightBranch->Exchange(secpos, swpind);
                        //����� ����� ��������
                        fst = (TSortionData *) rightBranch->Items[i - 1];
                        sec = (TSortionData *) rightBranch->Items[secpos];
                        }
                        //��������, ��� ���� ������������
                        fst->onTree = true;
                        sec->onTree = true;
    //                else{
    //                    //��������, ��� ���� ������������
    //                    fst->onTree = true;
    //                    sec->onTree = true;
    //                    }
                    }
                }
            }while(beenSwap);
        }


    //���������� ���������� �� ������
    int lb=0; int rb=0;
    for(int i =0; i < dataAmnt; i++){
        if(i % 2){
            sortionOrder[i] = ((TSortionData *) rightBranch->Items[rb])->competitorId;
            rb++;
            }
        else{
            sortionOrder[i] = ((TSortionData *) leftBranch->Items[lb])->competitorId;
            lb++;
            }
        }




    //��������� ������� ���������� ���������� � ���������
    dmCategoryDAO->storeSortionOrder(this->id, sortionOrder, dataAmnt);

    //������� ��� ���������, ������� ��������������
    destroyList(skillClubOrderData, etSORTIONDATA);
    delete [] sortionOrder;
    leftBranch->Clear();
    delete (TList*)leftBranch;
    rightBranch->Clear();
    delete (TList*)rightBranch;

    //�������� ��������� ��� ��������������� �������������
    this->setDrawType(DT_AUTO);
}

int TCategory::getCompetitorsAmount(void){
    return dmCategoryDAO->getCompetitorsAmount(id);
}

void TCategory::uncategory(int competitorId){
    dmCategoryDAO->uncategory(competitorId);
}

void TCategory::deleteCategoriesByCompetition(TCompetition competition){
    dmCategoryDAO->deleteCategoriesByCompId(competition.getId());
}

void TCategory::setDrawType(char drawType){
    dmCategoryDAO->setDrawType(*this, drawType);
}

char TCategory::getDrawType(void){
    return dmCategoryDAO->getDrawType(*this);
}








#pragma package(smart_init)




