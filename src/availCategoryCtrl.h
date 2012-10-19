//---------------------------------------------------------------------------

#ifndef availCategoryCtrlH
#define availCategoryCtrlH

#include<vcl.h>

#include "competitionCtrl.h"
#include "competitorCtrl.h"
#include "fightVersionCtrl.h"



//****************************************//
// ����� ������������� �������
// "��������� ���������"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 5.01.06
//****************************************//



class TAvailCategory{
private:
    //�������������
    int id;
    //��������� ������ � ���������
    int startAge;
    //�������� ������� � ���������
    int endAge;
    //��������� ��� � ���������
    double startWeight;
    //�������� ��� � ���������
    double endWeight;
    //��� ���������
    bool female;  
    //�����������
    AnsiString asComments;

// ��������� ������� //
public:


    //-- �����������
    //@param startAge - ��������� �������
    //@param endAge - �������� �������
    //@param startWeight - ��������� ���
    //@param endWeight - �������� ���
    //@param female - ���
    //@param asComments - �����������
    TAvailCategory(int inStartAge, int inEndAge, double inStartWeight, double inEndWeight,
                    bool inFemale, AnsiString asInComments);
    //-- ����������� �� ���������
    TAvailCategory(void){startAge = 0; endAge = 100; startWeight = 0;
                         endWeight = 500.0; female = false; asComments = ""; id =0;}
    //-- ����������
    ~TAvailCategory(void);

    //--�������� �������
    //@return true - ���� ������ ��������, false - ���� ������ �� ��������
    bool valid(AnsiString &errmess);

    //-- ���������� ������� � ���� ������
    void store(void);

    //-- �������� ������� � ���� ������
    void remove(void);

    //-- ������ ���� �������� �� ���� ������
    //@return ������ ��������, ����������� �� ���� ������,
    //  ��� null, ���� �������� � ���� �� �������
    static TList* getAll(void);

    //-- �������� ������� ���������� �� ��������������
    //@param id ������������ ������, ������� ���� ��������
    void getById(int id);

    //-- �������� ������� ��������� ��������� � �������
    static TAvailCategory getCurrent(void);
    //-- ���������� ������� ��������� 
    void TAvailCategory::makeCurrent(void);



    // ������� ��������� ��������� �������������� ��������� ���������� ����������
    // @param competitor - ��������
    // @param fightVersion - ������ � ������� ����� ����������� ��������
    // @return ��������� � ������� ����� ��������. null - ���� ��� ��������� ������
    // ������� ���������
    static int checkForAvailCategory(TCompetitor competitor);
    static int checkForAvailCategory(int age, double weight, bool female);      

    //-- ������ ��������� � ���������� ������� �������
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    int getStartAge(void){return startAge;}
    void setStartAge(int inStartAge){startAge = inStartAge;}
    int getStartWeight(void){return startWeight;}
    void setStartWeight(int inStartWeight){startWeight = inStartWeight;}
    int getEndAge(void){return endAge;}
    void setEndAge(int inEndAge){endAge = inEndAge;}
    int getEndWeight(void){return endWeight;}
    void setEndWeight(int inEndWeight){endWeight = inEndWeight;}
    bool getFemale(void){return female;}
    void setFemale(bool inFemale){female = inFemale;}
    AnsiString getComments(void){return asComments;}
    void setComments(AnsiString asInComments){asComments = asInComments;}
};


//---------------------------------------------------------------------------
#endif
