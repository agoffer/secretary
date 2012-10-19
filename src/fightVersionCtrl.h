//---------------------------------------------------------------------------

#ifndef fightVersionCtrlH
#define fightVersionCtrlH

#include<vcl.h>

//****************************************//
// ����� ������������� �������
// "������ ������"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 4.12.05
//****************************************//


class TFightVersion{
private:
    //�������������
    int id;
    //��� ������ ������
    AnsiString asCode;
    //��������, ������ �������� ������ 
    AnsiString asDescription;
    //�����������
    AnsiString asComments;


    //��� ������������ ���������� ������ ������� ������������� � ��������� 
    bool destributed;

// ��������� ������� //
public:


    //-- �����������
    //@param asCode - ��� ������ ������ 
    //@param asDescription - �������� ������� ������������
    //@param asComments - �����������
    TFightVersion(AnsiString asCode, AnsiString asInDescription, AnsiString asInComments);
    //-- ����������� �� ��������� 
    TFightVersion(void){asCode=""; asDescription=""; asComments=""; id=0; destributed=false;}
    //-- ����������
    ~TFightVersion(void);

    //--�������� �������
    //@return true - ���� ������ ��������, false - ���� ������ �� ��������
    bool valid(AnsiString &errmess);

    //-- ���������� ������� � ���� ������
    void store(void);
    //-- ������ ���� �������� �� ���� ������
    //@return ������ ��������, ����������� �� ���� ������,
    //  ��� null, ���� �������� � ���� �� �������
    static TList* getAll(void);

    //-- �������� ������ ������  �� ��������������
    //@param id ������������ �������, ������� ���� ��������
    void getById(int id);

    //-- ������ ��������� � ���������� ������� �������
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    void setCode(AnsiString asInCode){asCode = asInCode;}
    AnsiString getCode(void){return asCode;}
    AnsiString getDescription(void){return asDescription;}
    void setDescription(AnsiString asInDescription){asDescription = asInDescription;}
    AnsiString getComments(void){return asComments;}
    void setComments(AnsiString asInComments){asComments = asInComments;}

    //-- ��� �������� ���������������� ������ � ���������
    bool getDestributed(void){return destributed;}
    void setDestributed(bool inDestributed){destributed = inDestributed;}
};




//---------------------------------------------------------------------------
#endif
