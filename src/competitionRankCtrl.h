//---------------------------------------------------------------------------

#ifndef competitionRankCtrlH
#define competitionRankCtrlH

#include<vcl.h>

//****************************************//
// ����� ������������� �������
// "������ ����������"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 23.11.05
//****************************************//


class TCompetitionRank{
private:
    //�������������
    int id;
    //�������� ������� ������������
    AnsiString asDescription;
    //�����������
    AnsiString asComments;
// ��������� ������� //
public:


    //-- �����������
    //@param asDescription - �������� ������� ������������
    //@param asComments - �����������
    TCompetitionRank(AnsiString asInDescription, AnsiString asInComments);
    //-- ����������� �� ��������� 
    TCompetitionRank(void){asDescription=""; asComments=""; id=0;}
    //-- ����������
    ~TCompetitionRank(void);

    //--�������� �������
    //@return true - ���� ������ ��������, false - ���� ������ �� ��������
    bool valid(AnsiString &errmess); 

    //-- ���������� ������� � ���� ������
    void store(void);
    //-- ������ ���� �������� �� ���� ������
    //@return ������ ��������, ����������� �� ���� ������,
    //  ��� null, ���� �������� � ���� �� ������� 
    static TList* getAll(void);

    //-- �������� ������ ����������� �� ��������������
    //@param id ������������ �������, ������� ���� �������� 
    void getById(int id);

    //-- ������ ��������� � ���������� ������� �������
    int getId(void);
    void setId(int inId);
    AnsiString getDescription(void);
    void setDescription(AnsiString asInDescription);
    AnsiString getComments(void);
    void setComments(AnsiString asInComments);
};


//---------------------------------------------------------------------------
#endif
