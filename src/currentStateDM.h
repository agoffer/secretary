//---------------------------------------------------------------------------

#ifndef CurrentStateDMH
#define CurrentStateDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "competitionCtrl.h"
#include "fightVersionCtrl.h"
#include "skillCtrl.h"
#include "requestCtrl.h"
#include "categoryCtrl.h"
#include "availCategoryCtrl.h"
#include "competitorCtrl.h"
#include "resultCtrl.h"

#include <map.h>
//---------------------------------------------------------------------------
class TdmCurrentState : public TDataModule
{
__published:	// IDE-managed Components
private:	// User declarations
    //-- ������� ������������, � �������� ����������� ������
    TCompetition Competition;

    //-- ������� ����������
    TPerson Person;

    //-- ������� ����
    TClub Club;

    //-- ������� ������
    TRequest Request;

    //-- ������� ��������� ���������
    TAvailCategory AvailCategory;

    //-- ������� ������ ������
    TFightVersion FightVersion;

    //--������ ������ ������
    TList* fightVersionList;
    //-- ��������������� �� ������������� ������ ������ ������
    map<int, TFightVersion*> fightVersionMap;

    //-- ����� ����� �� ����� �� ������������ �� ��������
    map<int, int> scoreRankingShooting;

    //-- ����� ����� �� ����� �� ������������ �� ����������� ���
    map<int, int> scoreRankingFighting;

    //--������ ������� ����������
    TList* skillList;
    //-- ��������������� �� ������������� ������ ������� ����������
    map<int, TSkill*> skillMap;

    //-- ������ ���� ������ �� ������������
    TList *requestList;
    //-- ��������������� �� ������������� ������ ������
    map<int, TRequest*> requestMap;

    //������ ��������� ���������
    TList *allAvailCategoryList;
    //-- ��������������� �� ������������� ������ ��������� ���������
    map<int, TAvailCategory*> availCategoryMap;
    TList *femaleAvailCategoryList;
    TList *maleAvailCategoryList;

    //-- ������ ���� ���������, ��������� �� ������������
    TList *categoryList;
    //-- ��������������� �� ������������� ������ ��������� �� ������������
    map<int, TCategory*> categoryMap;
    TList *femaleCategoryList;
    TList *maleCategoryList;

    //-- ������ ���������� �� �������� �� � ���� ���������
    TList *femaleUncategoryCompetitorList;
    TList *maleUncategoryCompetitorList;

    //-- �������� ������ ������� ����������
    void createSkillList(void);

    //-- �������� ������ ������ ������
    void createFightVersionList(void);

    //-- �������� ������ ������� ����������
    void createAvailCategoryList(void);

    //-- �������� ������ ������ �� �������������
    void createRequestList(TCompetition competition);

    //������� ����� ����� �� ������������
    void createScoreRankMap(int competitionRank);




public:		// User declarations
    __fastcall TdmCurrentState(TComponent* Owner);
    __fastcall ~TdmCurrentState(void);

    //-- �������� ������ ��������� �� �������������
    void createCategoryList(TCompetition competition);
    //-- ���������� ������� ������������
    void setCompetition(TCompetition competition);
    //-- �������� ������� ������������
    TCompetition& getCompetition(void){return Competition;}
    //-- ���������� �������� ����������
    void setPerson(TPerson person){Person = person;}
    //-- �������� �������� ����������
    TPerson& getPerson(void){return Person;}
    //-- ���������� ������� ����
    void setClub(TClub club){Club = club;}
    //-- �������� ������� ����
    TClub& getClub(void){return Club;}
    //-- ���������� ������� ��������� ������
    void setAvailCategory(TAvailCategory availCategory){AvailCategory = availCategory;}
    //-- �������� ������� ��������� ������
    TAvailCategory& getAvailCategory(void){return AvailCategory;}
    //-- ���������� ������� ������ ������
    void setFightVersion(TFightVersion fightVersion){FightVersion = fightVersion;}
    //-- �������� ������� ����� ������
    TFightVersion& getFightVersion(void){return FightVersion;}
    //-- ���������� ������� ������
    void setRequest(TRequest request){Request = request;}
    //-- �������� ������� ������
    TRequest& getRequest(void){return Request;}

    //-- ������� ������ ������ ������
    TList* getFightVersionList(void){if(fightVersionList->Count <= 0)createFightVersionList();return fightVersionList;}
    //-- �������� ������ ������ � ��� ��������������� ������
    void addFightVersionToList(TFightVersion fightVersion);
    //-- ����� ������ ������ �� ��������� ������������
    TFightVersion findFightVersionByCode(AnsiString code);

    //-- ������� ������ ������ ������
    TList* getSkillList(void){if(skillList->Count <= 0)createSkillList(); return skillList;}
    //-- �������� ������� ���������� � ��� ��������������� ������
    void addSkillToList(TSkill skill);

    //-- �������� ������ � ��� ��������������� ������
    void addRequestToList(TRequest request);
    //-- �������� ������ ������
    TList* getRequestList(void){return requestList;}
    //-- �������� ������ �� ��������������
    TRequest *getRequestById(int requestId);

    //-- �������� ��������� � ��� ��������������� ������
    void addCategoryToList(TCategory category);

    //-- �������� ������ ���������
    TList* getCategoryList(void){return categoryList;}
    TList* getFemaleCategoryList(void){return femaleCategoryList;}
    TList* getMaleCategoryList(void){return maleCategoryList;}
    //-- ������� ��������� �� ��������� ����������������
    TCategory *getCategoryById(int categoryId);


    //-- ������� ������ ���� ��������� ���������
    TList* getAllAvailCategoryList(void){if(allAvailCategoryList->Count <= 0)
                                            createAvailCategoryList();
                                            return allAvailCategoryList;}
    //-- ������� ������ �������  ��������� ���������
    TList* getMaleAvailCategoryList(void){if(maleAvailCategoryList->Count <= 0)
                                            createAvailCategoryList();
                                            return maleAvailCategoryList;}
    //-- ������� ������ �������  ��������� ���������
    TList* getFemaleAvailCategoryList(void){if(femaleAvailCategoryList->Count <= 0)
                                            createAvailCategoryList();
                                            return femaleAvailCategoryList;}
    //-- �������� ��������� ��������� � ������
    void addAvailCategoryToList(TAvailCategory inAvailCategory);

    //-- �������� ������ ���������� ������������ �� �������� � ���������
    TList* getUncategoryCompetitorList(bool female){return female?femaleUncategoryCompetitorList :
                                                                  maleUncategoryCompetitorList;}
    //-- �������� ��������� � ������ �� �������� �� � ���� ���������
    void addUncategoryCompetitorToList(TCompetitor competitor, bool female);
    //-- ������� ������ ���������� �� �������������� �� ����������
    void createUncategoryCompetitorList(TCompetition competition);

    //������� ���������� �����, ������������ ������
    // disciplineId: 0 ��������, 1 ���������� ���
    int getScoreForRank(int rank, int disciplineId);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmCurrentState *dmCurrentState;
//---------------------------------------------------------------------------
#endif
