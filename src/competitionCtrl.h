//---------------------------------------------------------------------------
#ifndef competitionCtrlH
#define competitionCtrlH

#include "competitionRankCtrl.h"

#include <vcl.h>

//****************************************//
// ����� ������������� �������
// "������������"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 24.11.05
//****************************************//

class TCompetition{
private:
    //�������������
    int id;
    //���� ������ ������������
    TDate beginDate;
    //���� ��������� ������������
    TDate endDate;  
    //�����������
    AnsiString asComments;
    //������������� ������� ������������
    int competitionRankId;

    //���� ����������
    bool extended; 
    TCompetitionRank competitionRank; 
    
// ��������� ������� //
public:


    //-- �����������
    //@param inBeginDate - ���� ������ ���������� ������������
    //@param inEndDate - ���� ��������� ���������� ������������
    //@param inCompetitionRankId - �����. ������� ������������
    //@param asInComments - �����������  
    TCompetition(TDate inBeginDate, TDate inEndDate,
                int inCompetitionRankId, AnsiString asInComments);
    //-- ����������� �� ���������
    TCompetition(void){ beginDate = Now();
                            endDate = Now();
                            competitionRankId = 0;
                            asComments = "";
                            id = 0;
                            extended = false; 
                            }
    //-- ����������
    ~TCompetition(void);

    //--�������� �������
    //@return true - ���� ������ ��������, false - ���� ������ �� ��������
    bool valid(AnsiString &errmess);

    //-- ���������� ������� � ���� ������
    void store(void);
    //-- ������ ���� �������� �� ���� ������
    //@return ������ ��������, ����������� �� ���� ������,
    //  ��� null, ���� �������� � ���� �� �������
    static TList* getAll(void);

    //-- ��������� ������ �� ���������
    //@param id ������������� ������, ������� ���������
    void getById(int id);

    //-- �������� ������� ������������ �� ����������� �������
    static TCompetition getExtendedCurrent(void);  

    

    //-- �������� ������������ � ����������� ���� ������ ������������
    //@param minBeginDate - ����������� ���� ������ ������������
    //@param maxBeginDate - ������������ ���� ������ ������������
    static void getMinMaxBeginDate(TDateTime &minBeginDate, TDateTime &maxBeginDate);

    //-- �������� ������������ � ����������� ���� ��������� ������������
    //@param minEndDate - ����������� ���� ��������� ������������
    //@param maxEndDate - ������������ ���� ��������� ������������
    static void getMinMaxEndDate(TDateTime &minBeginDate, TDateTime &maxBeginDate);

    //-- ������ ��������� � ���������� ������� �������
    int getId(void);
    void setId(int inId);
    TDate getBeginDate(void);
    void setBeginDate(TDate inBeginDate);
    TDate getEndDate(void);
    void setEndDate(TDate inEndDate);
    int getCompetitionRankId(void);
    void setCompetitionRankId(int inCompetitionRankId);
    AnsiString getComments(void);
    void setComments(AnsiString asInComments);

    //-- ����������, ��� �� ������ ��������
    bool isExtended(void){return extended;}
    //-- ������ ������������ ����������� ����
    TCompetitionRank getCompetitionRank(void){return competitionRank;}
    //-- ��������� ������ ������������
    void extend(TCompetitionRank inCompetitionRank){competitionRank = inCompetitionRank; extended = true;};
};



//---------------------------------------------------------------------------
#endif
