//---------------------------------------------------------------------------

#ifndef clubCtrlH
#define clubCtrlH

#include <vcl.h>


#include "utils.h"

//****************************************//
// ����� ������������� �������
// "����"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 26.11.05
//****************************************//

class TClub{
private:
    //�������������
    int id;
    //�������� �����
    AnsiString asName;
    //�������� �������� �������
    AnsiString asShortName;
    //����� �� �������� ����
    AnsiString asCity;
    //������ �� ������� ����
    AnsiString asCountry;
    //������������� ������������� �����
    int personId;
    //����������� � �������������� ����������
    AnsiString asComments;


// ��������� ������� //
public:


    //-- �����������
    //@param asName  - �������� �����
    //@param asCity - ����� �����
    //@param asCountry - ������ �����
    //@param personId - ������������� ������������� �����
    //@param asComments - �������������� ����������
    TClub(AnsiString asInName, AnsiString asInShortName, AnsiString asInCity,
            AnsiString asInCountry, int inPersonId,
            AnsiString asIComments);
    //-- ����������� �� ���������
    TClub(void){ asName = ""; asShortName = ""; asCity = ""; asCountry = "";
                    personId = 0; asComments = "";
                    id = 0;
                }
    //-- ����������
    ~TClub(void);

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
    static TClub getCurrent(void);
    //-- ���������� ������ ��� ������� � �������
    void makeCurrent(void);      
    

    //-- ��������� ������ �� ���������
    //@param id ������������� ������, ������� ���������
    static TClub getById(int id); 

    //-- ������ ��������� � ���������� ������� �������
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    AnsiString getName(void){return asName;}
    void setName(AnsiString asInName){asName = asInName;}
    AnsiString getShortName(void){return asShortName;}
    void setShortName(AnsiString asInShortName){asShortName = asInShortName;}
    AnsiString getCity(void){return asCity;}
    void setCity(AnsiString asInCity){asCity = asInCity;}
    AnsiString getCountry(void){return asCountry;}
    void setCountry(AnsiString asInCountry){asCountry = asInCountry;}
    int getPersonId(void){return personId;} 
    void setPersonId(int inPersonId){personId = inPersonId;}
    AnsiString getComments(void){return asComments;}
    void setComments(AnsiString asInComments){asComments = asInComments;}


    //��������� ������� ��������� ������ ��� ��������� ������
    static void setRecordMoveCallback(CallbackFunction cbf);
  
};



//---------------------------------------------------------------------------
#endif
