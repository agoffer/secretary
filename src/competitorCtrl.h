//---------------------------------------------------------------------------

#ifndef competitorCtrlH
#define competitorCtrlH


#include "personCtrl.h"
#include "requestCtrl.h"
#include "fightVersionCtrl.h"
#include "skillCtrl.h"
#include "resultCtrl.h"

//****************************************//
// ����� ������������� �������
// "�������� ������������"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 6.12.05
//****************************************//

class TCompetitor{
private:
    //�������������
    int id;
    //������������� ������ ����������
    int skillId;
    //������������� ������� �������������� ���������
    int personId;
    //������������� ������ � ������� �������� ��������
    int requestId;
    //��� ���������
    double weight;
    //����� � ����������
    int sortion;


    //--����������� ����
    bool extended;
    TRequest request;
    TPerson person;
    TSkill skill;



// ��������� ������� //
public:

    //--��������� ��������� ������������
    TResult result;

    //-- �����������
    //@param personId - ������������� ������� ���������
    //@param skillId - ������������� ������ ���������� ���������
    //@param requestId - ������������� ������ �������� ���������
    //@param weight - ��� ���������
    TCompetitor(int inPersonId, int inSkillId,
             int inRequestId, double weight);
    //-- ����������� �� ���������
    TCompetitor(void){ personId = 0; skillId = 0;
                    requestId = 0; weight = 0;
                    id = 0;
                    //���������� ������ �� ��������
                    extended = false;
                    skill.setId(0);
                    person.setId(0);
                    request.setId(0); 
                    }
    //-- ����������
    ~TCompetitor(void);

    //--�������� �������
    //@return true - ���� ������ ��������, false - ���� ������ �� ��������
    bool valid(AnsiString &errmess);

    //-- ���������� ������� � ���� ������
    void store(void);
    //-- ������� ������ �� ���� ������
    void erase(void); 

    //-- ������ ���� �������� �� ���� ������
    //@return ������ ��������, ����������� �� ���� ������,
    //  ��� null, ���� �������� � ���� �� �������
    static TList* getAll(void);


    //-- �������� ������ ���������� �� ������������ ������ 
    //@param requestId ������������� ������, ��� ������� �������� ����������
    //@param &reccount [out] - ������� ������� ���� ��������  
    //@return ������ ���������� ������������ �������
    static TList* getByRequestId(int requestId);

    //-- �������� ������ ���������� ��� �������� ������������ 
    //@param competitionId ������������� ������������, ��� ������� �������� ����������
    //@param &reccount [out] - ������� ������� ���� ��������
    //@return ������ ���������� ������������ �������
    static TList* getByCompetitionId(int competitionId);

    //-- �������� ������ ���������� c ������������ ������ ��� �������� ������������
    //@param competitionId ������������� ������������, ��� ������� �������� ����������
    //@param &reccount [out] - ������� ������� ���� ��������
    //@return ������ ���������� ������������ �������
    static TList* getExtendedByCompetitionId(int competitionId);

    //-- �������� ������ ���������� ������������ (�� ��������������), � ������������ ������
    // �� ��������� �� � ���� ��������� ���������
    //@param competitionId ������������� ������������, ��� ������� �������� ����������
    //@param &reccount [out] - ������� ������� ���� ��������
    //@return ������ ����������
    static TList* getExtendedUncategoryByCompetitionId(int competitionId, bool female);


    //-- �������� ������ ���������� �� ������, � ����������� ����� (�������� �������, ������ � ������� ����������)
    //@param requestId ������������� ������, ��� ������� �������� ����������
    //@param &reccount [out] - ������� ������� ���� ��������
    //@return ������ ���������� �� ������
    static TList* getExtendedByRequestId(int requestId);

    //-- �������� ������ ���������� � ���������, � ����������� �����
    //@param categoryId ������������� ���������,  ��� ������� �������� ����������
    //@param &reccount [out] - ������� ������� ���� ��������
    //@return ������ ���������� � ���������
    static TList* getExtendedByCategoryId(int categoryId);

    //-- ������� ������� ��� ������� ������
    static TCompetitor getCurrent(void);
    //-- ���������� ������ ��� ������� � �������
    void makeCurrent(void);

    //-- ������� ������� ��� ������� ������
    static TCompetitor getExtendedTableCurrent(void);
    //-- ���������� ������ ��� ������� � �������
    void makeExtendedTableCurrent(void);


    //-- ��������� ������ �� ���������
    //@param id ������������� ������, ������� ���������
    void getById(int id);

    //-- ������������� ������ ������ ��� ���������
    //@param ids - �������������� ������ ������
    void setFightVersion(int *ids, int count);
    //-- �������� ������ ������ ������ ��� ���������
    TList* getFightVersion(void);
    //-- �������� ������ ���������������� ������ ������ ��� ���������
    TList* getUncategoryFightVersion(void);
    //-- �������� ������ ����������� ��������� ������ ��������� 
    TList* getExtendedFightVersion(void);



    //-- ������� ������ ������ ��� ��������� �� ����
    void eraseFightVersion(void);

    //-- ����������, ��� �� ������ ��������
    bool isExtended(void){return extended;}

    //-- ������ ��������� � ���������� ������� �������
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    int getSkillId(void){return skillId;}
    void setSkillId(int inSkillId){skillId = inSkillId;}
    int getRequestId(void){return requestId;}
    void setRequestId(int inRequestId){requestId = inRequestId;}
    int getPersonId(void){return personId;}
    void setPersonId(int inPersonId){personId = inPersonId;}
    double getWeight(void){return weight;}
    void setWeight(double inWeight){weight = inWeight;}
    int getSortion(void){return sortion;}
    void setSortion(int inSortion){sortion = inSortion;}

    //������ ������ � ���������� ����������
    void loadResult(void);
    void storeResult(void);
    //������ ������ � ���������� ����������� � ��������� ��������� 
    void loadResult(int categoryId);
    void storeResult(int categoryId);

    //-- ������ ������������ ����������� ����
    TSkill getSkill(void){return skill;}
    TPerson  getPerson(void){return person;}
    TRequest getRequest(void){return request;}
    //-- ��������� ������ ������������
    void extend(TPerson inPerson, TSkill inSkill, TRequest inRequest);

     //��������� ������� ��������� ������ ��� ��������� ������
    static void setRecordMoveCallback(CallbackFunction cbf);    
};                                                                  





//---------------------------------------------------------------------------
#endif
