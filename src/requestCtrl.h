//---------------------------------------------------------------------------

#ifndef requestCtrlH
#define requestCtrlH

#include <vcl.h>

#include "clubCtrl.h"
#include "personCtrl.h"


//****************************************//
// ����� ������������� �������
// "������"
// ���������� ������ ���������� ��������
// @author Andrey V. Goffer
// @create 30.11.05
//****************************************//

class TRequest{
private:
    //�������������
    int id;
    //������������� ������������ 
    int competitionId;
    //������������� �����, ��������� ������
    int clubId;
    //������������� ������������� ����� 
    int personId;
    //����������� � �������������� ����������
    AnsiString asComments;


    //--����������� ����
    bool extended; 
    TClub club;
    TPerson person; 

    
// ��������� ������� //
public:


    //-- �����������
    //@param competitionId - ������������� ������������ 
    //@param clubId - ������������� �����
    //@param personId - ������������� ������������� �����
    //@param asComments - �������������� ����������
    TRequest(int inCompetitionId, int inClubId,
             int inPersonId, AnsiString asIComments);
    //-- ����������� �� ���������
    TRequest(void){ competitionId = 0; clubId = 0;
                    personId = 0; asComments = "";
                    id = 0;
                }
    //-- ����������
    ~TRequest(void);

    //--�������� �������
    //@return true - ���� ������ ��������, false - ���� ������ �� ��������
    bool valid(AnsiString &errmess);

    //-- ���������� ������� � ���� ������
    void store(void);
    //-- ������ ���� �������� �� ���� ������
    //@return ������ ��������, ����������� �� ���� ������,
    //  ��� null, ���� �������� � ���� �� �������
    static TList* getAll(void);

    //--- �������
    static void deleteById(int requestId);


    //-- �������� ������ ������ �� ������� � ������������ �������������
    //@param competitionId ������������� ������������, ��� �������� �������� ������
    //@param &reccount [out] - ������� ������� ���� ��������  
    //@return ������ ������ �� ������� � �������������
    static TList* getByCompetitionId(int competitionId);


    //-- �������� ������ ������ �� ������������, � ����������� ����� (�������� �������������� � �����)
    //@param competitionId ������������� ������������, ��� �������� �������� ������
    //@param &reccount [out] - ������� ������� ���� ��������  
    //@return ������ ������ �� ������� � �������������
    static TList* getExtendedByCompetitionId(int competitionId);

    //-- ������� ������� ��� ������� ������
    static TRequest getCurrent(void);
    //-- ���������� ������ ��� ������� � �������
    void makeCurrent(void);


    //-- ��������� ������ �� ���������
    //@param id ������������� ������, ������� ���������
    void getById(int id);


    //-- ����������, ��� �� ������ ��������
    bool isExtended(void){return extended;}

    //-- ������ ��������� � ���������� ������� �������
    int getId(void){return id;}
    void setId(int inId){id = inId;}
    int getClubId(void){return clubId;}
    void setClubId(int inClubId){clubId = inClubId;}
    int getCompetitionId(void){return competitionId;}
    void setCompetitionId(int inCompetitionId){competitionId = inCompetitionId;}
    int getPersonId(void){return personId;}
    void setPersonId(int inPersonId){personId = inPersonId;}
    AnsiString getComments(void){return asComments;}
    void setComments(AnsiString asInComments){asComments = asInComments;}

    //-- ������ ������������ ����������� ����
    TClub getClub(void){return club;}
    TPerson  getPerson(void){return person;}
    //-- ��������� ������ ������������ 
    void extend(TPerson inPerson, TClub inClub);
};                                                                  




//---------------------------------------------------------------------------
#endif
