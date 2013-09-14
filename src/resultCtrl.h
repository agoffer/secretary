//---------------------------------------------------------------------------

#ifndef ResultCtrlH
#define ResultCtrlH

#include <vcl.h>

#include "utils.h"
#include <map.h>


//****************************************//
// ����� ������������� �������
// "��������� ���������"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 12.06.06
//****************************************//

class TResult{
private:
    //���������� �� �������� //

    //�����
    AnsiString crossTime;   //������ ������� H:MM:SS.dd
    //��������
    int shootScore;
    int shootRank;

    //���������� ��� ��� ��������� ������
    int fightWOKnifeScore;
    int fightWOKnifeRank;

    //����� ��������� ������������ ��� ��������� � ���������
    int commonRank;

    //��� ������, ����� ��������� ������� � ����������� �� ���������
    int categoryId;

    // ��������� ������� //
public:
    //-- �����������
    TResult(void){
        crossTime = "00:00.00";
        commonRank = 0;
        shootScore = -1;
        shootRank = 0;
        fightWOKnifeScore = -1;
        fightWOKnifeRank = 0;

        categoryId = 0;
    }
    //-- ����������
    ~TResult(void);
    //--�������� �������
    //@return true - ���� ������ ��������, false - ���� ������ �� ��������
    bool valid(AnsiString &errmess);

    //-- ������ ����������� ��� ��������� �� ���� ������
    void getResults(int competitorId);
    //-- ���������� ����������� � ���� ������
    void setResults(int competitorId);

    //-- ������ ����������� ��� ��������� �� ���� ������, �� ���������
    void getResults(int competitorId, int categoryId);
    //-- ���������� ����������� � ���� ������
    void setResults(int competitorId, int categoryId);

    //-- ������� ������� ��� ������� ���������� � ������������ ������
    static int getCurrentCompetitorId(void);
    static void setCurrentCompetitorById(int competitorId);

    //-- �������� ����� ����� ��� ������������.
    // disciplineId: 1 ���������� ���, 2 ��������
    static void getScoreRanking(map<int, int> & scoreRank, int competitionRank, int disciplineId);


    //�����
    AnsiString getCrossTime(void){return crossTime;}
    void setCrossTime(AnsiString inCrossTime){crossTime = inCrossTime;}
    //��������
    int getShootScore(void){return shootScore;}
    void setShootScore(int inShootScore){shootScore = inShootScore;}
    int getShootRank(void){return shootRank;}
    void setShootRank(int inShootRank){shootRank = inShootRank;}
    //���������� ��� ��� ��������� ������
    int getFightWOKnifeScore(void){return fightWOKnifeScore;}
    void setFightWOKnifeScore(int inFightWOKnifeScore){fightWOKnifeScore = inFightWOKnifeScore;}
    int getFightWOKnifeRank(void){return fightWOKnifeRank;}
    void setFightWOKnifeRank(int inFightWOKnifeRank){fightWOKnifeRank = inFightWOKnifeRank;}
    //�������� ���������, ��� ������� �������� ����������
    int getCategoryId(void){return categoryId;}

    //����� ��������� ������������, ��� ��������� � ���������
    int getCommonRank(void){return commonRank;}
    void setCommonRank(int inCommonRank){commonRank = inCommonRank;}

     //��������� ������� ��������� ������ ��� ��������� ������
    static void setRecordMoveCallback(CallbackFunction cbf);
};


//---------------------------------------------------------------------------
#endif
