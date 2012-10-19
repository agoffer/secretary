//---------------------------------------------------------------------------

#ifndef categoryCtrlH
#define categoryCtrlH

#include "availCategoryCtrl.h"
#include "fightVersionCtrl.h"
#include "competitionCtrl.h"
#include "competitorCtrl.h"

//****************************************//
// ����� ������������� �������
// "���������"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 09.01.06
//****************************************//


//��� ���������� ���������� 
const DT_AUTO = 'A';    // �������������� ���������� ����������
const DT_MANUAL = 'M';  // ������ ���������� ����������


//��������� ������������ ��� ���������� ���������� 
typedef struct{
    int  competitorId;
    int  skillWeight;   //������� ����������� ������ ����������
    int  clubId;
    bool onTree;        //������� ����, ��� �������� ��� ����������� � ������
}TSortionData;


class TCategory{
private:
    //�������������
    int id;
    //������������� ��������� ���������
    int availCategoryId;
    //������������� ������ ������
    int fightVersionId;
    //������������� ������������
    int competitionId;

    //-- ����������� ����
    bool extended;
    TAvailCategory availCategory;
    TFightVersion fightVersion;
    TCompetition competition;

// ��������� ������� //

public:


    //-- �����������
    //@param inAvailCategoryId - ������������� ��������� ���������
    //@param inFightVersionId - ������������� ������ ������
    //@param inCompetitionId - ������������� �����������
    TCategory(int inAvailCategoryId, int inFightVersionId, int inCompetitionId);
    //-- ����������� �� ���������
    TCategory(void){ availCategoryId = 0; fightVersionId = 0; competitionId = 0; }
    //-- ����������
    ~TCategory(void);

    //--�������� �������
    //@return true - ���� ������ ��������, false - ���� ������ �� ��������
    bool valid(AnsiString &errmess);

    //-- ���������� ������� � ���� ������
    void store(void);
    //-- ������ ���� �������� �� ���� ������
    //@return ������ ��������, ����������� �� ���� ������,
    //  ��� null, ���� �������� � ���� �� �������
    static TList* getAll(void);

    //-- ������� ������� ��� ������� ������
    static TCategory getCurrent(void);
    //-- ���������� ������ ��� ������� � �������
    void makeCurrent(void);

    //-- ��������� ������ �� ���������
    //@param id ������������� ������, ������� ���������
    void getById(int id);

    //-- �������� ��������� � ���������
    void addCompetitor(TCompetitor inCompetitor);

    //-- �������� ���������� � ��������� 
    void setCompetitors(TList *ids);

    //-- ������� ���������� �� ��������� 
    void eraseCompetitors(TList *ids);    

    //-- ������� ��� ��������� (� ����������� �����), ��� ������� ������������
    static TList* getExtendedByCompetitionId(int competitionId);

    //-- ������� ��� ��������� (� ����������� �����), ��� ������� ������������,
    //-- � ������� ������������ �������� � �������� : surname
    static TList* getExtendedByCompetitionIdSurname(int competitionId, AnsiString surname);

    // ������� �������� �������������� ��������� (� ������ ������) ���
    // ��������� ����������.
    // @param competitor - ��������
    // @param fightVersion - ������ � ������� ����� ����������� ��������
    // @param competition - ������������ � ������� ��������� ��������
    // @return true - ���� ������� ��� ������������ ���������, � ���� �������
    // ��������. � ��������� ������ false
    static bool putInCreatedCategory(TCompetitor competitor, TFightVersion fightVersion, TCompetition competition);
    //������� �������� ��������� ��������� � ��������� ���������
    //@return ���� ��������� �������, �� ������������� ������������� �� ������ ����
    void putInAvailCategory(TCompetitor competitor, TFightVersion fightVersion, TCompetition competition);     


    //-- ������ ��������� � ���������� ������� �������
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    int getAvailCategoryId(void){return availCategoryId;}
    void setAvailCategoryId(int inAvailCategoryId){availCategoryId = inAvailCategoryId;}
    int getFightVersionId(void){return fightVersionId;}
    void setFightVersionId(int inFightVersionId){fightVersionId = inFightVersionId;}
    int getCompetitionId(void){return competitionId;}
    void setCompetitionId(int inCompetitionId){competitionId = inCompetitionId;}

    //-- ������������, ��������� �� ���������� ��� ��������� � ����� ? 
    void setDrawType(char drawType);
    char getDrawType(void);


    //-- ����������, ��� �� ������ ��������
    bool isExtended(void){return extended;}

    //-- ��������� ����������� �����
    TAvailCategory getAvailCategory(void){return availCategory;}
    TFightVersion getFightVersion(void){return fightVersion;}
    TCompetition getCompetition(void){return competition;}

    //-- ���������� ������� ������������ ������
    void extend(void);
    void extend(TAvailCategory inAvailCategory, TFightVersion inFightVersion, TCompetition inCompetition);


    //-- ������� ���������� �� ������������� ���������� �� ���������� --//

    //-- ���������, ���� �� ��� ������������� ��� ������������
    static bool checkForDistribution(TCompetition competition);
    //-- ������������ ���������� �� ����������, ��� ������� ������������
    static void destributeCompetitors(TCompetition competition);
    //-- ������������ ���������� �� ���������� ��� ������ 
    static void destributeCompetitors(TRequest request, TCompetition competition);
    //-- ���������� ��������� � ���������
    static void destributeCompetitor(TCompetitor competitor, TCompetition competition);
    //-- ���������� �������� ������ ���������� � ��������� 
    static void destributeCompetitors(TList *competitorsList, TCompetition competition);
    //-- ������� ��� ��������� ��� ������������ 
    static void deleteCategoriesByCompetition(TCompetition competition);

    //-- ��������� ���������� ��������� 
    void sortitionCategory(void);

    //-- ������� ���������� ���������� � ���������
    int getCompetitorsAmount(void);

    //-- ������� ��������� �� ���� ��������� 
    static void uncategory(int competitorId);
};

//-- ������� ��������� ���� ������������� �������� �� �����
int __fastcall sortionCompareClub(void *fstItem, void *secItem);

//-- ������� ��������� ���� ������� ����������
int __fastcall sortionCompareSkill(void *fstItem, void *secItem);

//-- ������� ��������� �� ����� � ������ 
int __fastcall sortionCompareClubSkill(void *fstItem, void *secItem);

//-- ����� ������� ��� �������� ��� 
void getCriticalPairsIndexes(int &bottomIndex, int &topIndex, int dataAmnt);

//-- ����� ��������������� �����  
int searchAnotherClub(TList * branch, int startpos, int dataAmnt);


//-- ������� ��������� �� �������, ���������� � ������� ���������   
extern int __fastcall compareCategories(void *fstItem, void *secItem);





//---------------------------------------------------------------------------
#endif
