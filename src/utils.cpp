//---------------------------------------------------------------------------


#pragma hdrstop

#include "utils.h"

#include "competitorCtrl.h"
#include "categoryCtrl.h"
#include "availCategoryCtrl.h"
#include "fightVersionCtrl.h"
#include "skillCtrl.h"
#include "requestCtrl.h"



//---------------------------------------------------------------------------

#pragma package(smart_init)


int YearsPassCalculator(TDateTime date){
//���������� ���
TDateTime pass = Now() - date;
    //������� ���������� ���
return static_cast<double>(pass) / 365;
}

AnsiString FormatFloatValueText(AnsiString value){
   //��������� �����
    AnsiString txt = value;
    while(int i = txt.Pos(" ,")){
        txt.Delete(i, 1);
        }
    return txt;
}


void clearCompetitorList(TList *list){
    if(list==NULL) return; //��� ������ ��� �������
    //���������� ���������� ������
    for(int i=0; i < list->Count; i++){
        try{
        delete(TCompetitor*)list->Items[i];
        }catch(Exception *e){};
        }
    list->Clear();
}

void clearCategoryList(TList *list){
    if(list==NULL) return; //��� ������ ��� �������
    //���������� ���������� ������
    for(int i=0; i < list->Count; i++){
        try{
        delete (TCategory*)list->Items[i];
        }catch(Exception *e){}; 
        }
    list->Clear();
}

void clearAvailCategoryList(TList *list){
    if(list==NULL) return; //��� ������ ��� �������
    //���������� ���������� ������
    for(int i=0; i < list->Count; i++){
        try{
        delete (TAvailCategory*)list->Items[i];
        }catch(Exception *e){};
        }
    list->Clear();
}

void clearRequestList(TList *list){
    if(list==NULL) return; //��� ������ ��� �������
    //���������� ���������� ������
    for(int i=0; i < list->Count; i++){
        try{
        delete (TRequest*)list->Items[i];
        }catch(Exception *e){};
        }
    list->Clear();
}

void clearFightVersionList(TList *list){
    if(list==NULL) return; //��� ������ ��� �������
    //���������� ���������� ������
    for(int i=0; i < list->Count; i++){
        try{
        delete (TFightVersion*)list->Items[i];
        }catch(Exception *e){};
        }
    list->Clear();
}

void clearSkillList(TList *list){
    if(list==NULL) return; //��� ������ ��� �������
    //���������� ���������� ������
    for(int i=0; i < list->Count; i++){
        try{
        delete (TSkill*)list->Items[i];
        }catch(Exception *e){};
        }
    list->Clear();
}

void clearCompetitionRankList(TList *list){
    if(list==NULL) return; //��� ������ ��� �������
    //���������� ���������� ������
    for(int i=0; i < list->Count; i++){
        try{
        delete (TCompetitionRank*)list->Items[i];
        }catch(Exception *e){};
        }
    list->Clear();
}

void clearSortionDataList(TList *list){
    if(list==NULL) return; //��� ������ ��� �������
    //���������� ���������� ������
    for(int i=0; i < list->Count; i++){
        try{
        delete (TSortionData*)list->Items[i];
        }catch(Exception *e){}; 
        }
    list->Clear();
}

void destroyList(TList *list, TEntityType listtype){
    if(list==NULL) return; //��� ������ ��� ��������
    //� ����������� �� ���� ������ �������
    switch(listtype){
        case etCOMPETITOR:
            clearCompetitorList(list);
            break;
        case etCATEGORY:
            clearCategoryList(list);
            break;
        case etAVAILCATEGORY:
            clearAvailCategoryList(list);
            break;
        case etREQUEST:
            clearRequestList(list);
            break;
        case etFIGHTVERSION:
            clearFightVersionList(list);
            break;
        case etSKILL:
            clearSkillList(list);
            break;
        case etCOMPETITIONRANK:
            clearCompetitionRankList(list);
            break;
        case etSORTIONDATA:
            clearSortionDataList(list);
        }
    try{delete (TList*)list; }catch(Exception *e){};
}
