//---------------------------------------------------------------------------

#ifndef personCtrlH
#define personCtrlH

#include <vcl.h>

#include "utils.h"

//****************************************//
// ����� ������������� �������
// "�������"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 26.11.05
//****************************************//

class TPerson{
private:
    //�������������
    int id;
    //������� ��������
    AnsiString asSurname;
    //��� ��������
    AnsiString asName;
    //�������� ��������
    AnsiString asPatronymic;    
    //���� �������� ��������
    TDate dob;
    //���������� ������� ��������
    AnsiString asPhone;
    //������� ����, ��� ������� �������� ����
    bool female; 
    //�������������� ���������� 
    AnsiString asAdditions;

    
// ��������� ������� //
public:


    //-- �����������
    //@param asSurname - ������� ��������
    //@param asName - ��� ��������
    //@param asPatronymic - �������� ��������
    //@param dob - ���� �������� ��������
    //@param asPhone - ������� ��������
    //@param asAdditions - �������������� ����������   
    TPerson(AnsiString asInSurname, AnsiString asInName,
            AnsiString asInPatronymic, TDateTime inDob,
            AnsiString asInPhone, bool inFemale, AnsiString asInAdditions);
    //-- ����������� �� ���������
    TPerson(void){ asSurname = ""; asName = ""; asPatronymic = "";
                    dob = Now(); asPhone = ""; asAdditions = "";
                    female = false;
                    id = 0;
                }
    //-- ����������
    ~TPerson(void);

    //--�������� �������
    //@return true - ���� ������ ��������, false - ���� ������ �� ��������
    bool valid(AnsiString &errmess);

    //-- ���������� ������� � ���� ������
    void store(void);
    //-- ������ ���� �������� �� ���� ������
    //@return ������ ��������, ����������� �� ���� ������,
    //  ��� null, ���� �������� � ���� �� �������
    static TPerson* getAll(int &reccount);

    //-- ������� ������� ��� ������� ������
    static TPerson getCurrent(void);

    //-- ������� ������� ������ � �������  
    static bool deleteCurrent(void);

    //-- ���������� ������ ��� ������� � �������
    void makeCurrent(void);
    static void makeCurrent(int id);      

    //-- ��������� ������ �� ���������
    //@param id ������������� ������, ������� ���������
    void getById(int id);

    //-- ���������, ���� �� ������� � �������� (�������, ��� ��������) � ����
    // �������� ����, ���� ���� ����� �������
    // @return true ���� ����� ������� �������
    bool likeAs(void);     

    //-- ������ ��������� � ���������� ������� �������
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    AnsiString getSurname(void){return asSurname;}
    void setSurname(AnsiString asInSurname){asSurname = asInSurname;}
    AnsiString getName(void){return asName;}
    void setName(AnsiString asInName){asName = asInName;}
    AnsiString getPatronymic(void){return asPatronymic;}
    void setPatronymic(AnsiString asInPatronymic){asPatronymic = asInPatronymic;}
    TDate getDob(void){return dob;}
    void setDob(TDate inDob){dob = inDob;}
    bool getFemale(void){return female;}
    void setFemale(bool inFemale){female = inFemale;} 
    AnsiString getAdditions(void){return asAdditions;}
    void setAdditions(AnsiString asInAdditions){asAdditions = asInAdditions;}
    AnsiString getPhone(void){return asPhone;}
    void setPhone(AnsiString asInPhone){asPhone = asInPhone;}


     //��������� ������� ��������� ������ ��� ��������� ������
    static void setRecordMoveCallback(CallbackFunction cbf);
     
};



//---------------------------------------------------------------------------
#endif
