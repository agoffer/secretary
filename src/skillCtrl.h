//---------------------------------------------------------------------------

#ifndef skillCtrlH
#define skillCtrlH

#include<vcl.h>

//****************************************//
// ����� ������������� �������
// "������� ����������"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 4.12.05
//****************************************//


class TSkill{
private:
    //�������������
    int id;
    //�������� �������� ������
    AnsiString asShortDescription;
    //������ �������� ������
    AnsiString asFullDescription;
    //�����������
    AnsiString asComments;
    //������� ����������� ������
    int weight;
// ��������� ������� //
public:


    //-- �����������
    //@param asShortDescription - �������� �������� ������
    //@param asFullDescription - ������ ��������
    //@param asComments - �����������
    //@param weight - ������� ����������� ������
    TSkill(AnsiString asInShortDescription, AnsiString asInFullDescription, AnsiString asInComments,
            int inWeight);
    //-- ����������� �� ���������
    TSkill(void){asShortDescription=""; asFullDescription=""; asComments=""; weight=0; id=0;}
    //-- ����������
    ~TSkill(void);

    //--�������� �������
    //@return true - ���� ������ ��������, false - ���� ������ �� ��������
    bool valid(AnsiString &errmess); 

    //-- ���������� ������� � ���� ������
    void store(void);
    //-- ������ ���� �������� �� ���� ������
    //@return ������ ��������, ����������� �� ���� ������,
    //  ��� null, ���� �������� � ���� �� ������� 
    static TList* getAll(void);

    //-- �������� ������� ���������� �� ��������������
    //@param id ������������ ������, ������� ���� ��������
    void getById(int id); 

    //-- ������ ��������� � ���������� ������� �������
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    int getWeight(void){return weight;}
    void setWeight(int inWeight){weight = inWeight;}
    AnsiString getShortDescription(void){return asShortDescription;}
    void setShortDescription(AnsiString asInShortDescription){asShortDescription = asInShortDescription;}
    AnsiString getFullDescription(void){return asFullDescription;}
    void setFullDescription(AnsiString asInFullDescription){asFullDescription = asInFullDescription;}

    AnsiString getComments(void){return asComments;}
    void setComments(AnsiString asInComments){asComments = asInComments;}
};


//---------------------------------------------------------------------------
#endif
