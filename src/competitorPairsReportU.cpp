//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "competitorPairsReportU.h"
#include "competitionRankCtrl.h"
#include "currentStateDM.h"

#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCompetitorPairsReport *frmCompetitorPairsReport;


int pairsPosition[32][32] =
{
//-- 1 �������
{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 2 ��������
{1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 3 �������� (���� ���������)
{1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 4 ��������
{1, 3,  2, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 5 ������� (���� ���������)
{1, 5,  2, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 6 ������� (���� ���������)
{1, 5,  2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 7 ������� (���� ���������)
{1, 5,  3, 7,  2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 8 �������
{1, 5,  3, 7,  2, 6,  4, 8, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 9 ������� (���� ���������)
{1, 9,  3, 7,  2, 6,  4, 8, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 10 ������� (���� ���������)
{1, 9,  3, 7,  2, 10, 4, 8, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 11 ������� (���� ���������)
{1, 9,  5, 11,  3, 7,  2, 10, 4, 8, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 12 �������
{1, 9,  5, 11,  3, 7,  2, 10, 6, 12,  4, 8, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 13 ������� (���� ���������)
{1, 9,  5, 11,  3, 13,  2, 10,  6, 12,  4, 8, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 14 ������� (���� ���������)
{1, 9,  5, 11,  3, 13,  2, 10,  6, 12,  4, 14, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 15 ������� (���� ���������)
{1, 9,  5, 11,  3, 13,  7, 15,  2, 10,  6, 12,  4, 14, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 16 �������
{1, 9,  5, 11,  3, 13,  7, 15,  2, 10,  6, 12,  4, 14,  8, 16,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 17 ������� (���� ���������)
{1, 17,  5, 11,  3, 13,  7, 15,  2, 10,  6, 12,  4, 14,  8, 16,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 18 ������� (���� ���������)
{1, 17,  5, 11,  3, 13,  7, 15,  2, 18,  6, 12,  4, 14,  8, 16,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 19 ������� (���� ���������)
{1, 17,  9, 19,  5, 11,  3, 13,  7, 15,  2, 18,  6, 12,  4, 14,
 8, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 20 �������
{1, 17,  9, 19,  5, 11,  3, 13,  7, 15,  2, 18,  10, 20,  6, 12,
 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 21 ������� (���� ���������)
{1, 17,  9, 19,  5, 21,  3, 13,  7, 15,  2, 18,  10, 20,  6, 12,
 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 22 �������a (���� ���������)
{1, 17,  9, 19,  5, 21,  3, 13,  7, 15,  2, 18,  10, 20,  6, 22,
 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 23 �������a (���� ���������)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 13,  7, 15,  2, 18,  10, 20,
 6, 22, 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 24 �������a
{1, 17,  9, 19,  5, 21,  11, 23,  3, 13,  7, 15,  2, 18,  10, 20,
 6, 22, 12, 24, 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 25 ������� (���� ���������)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  7, 15,  2, 18,  10, 20,
 6, 22, 12, 24, 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 26 ������� (���� ���������)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  7, 15,  2, 18,  10, 20,
 6, 22, 12, 24, 4, 26, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 27 ������� (���� ���������)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 15,  2, 18,
 10, 20, 6, 22, 12, 24, 4, 26, 8, 16, -1, -1, -1, -1, -1, -1},
//-- 28 �������
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 15,  2, 18,
 10, 20, 6, 22, 12, 24, 4, 26, 14, 28, 8, 16, -1, -1, -1, -1},
//-- 29 ������� (���� ���������)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 29,  2, 18,
 10, 20, 6, 22, 12, 24, 4, 26, 14, 28, 8, 16, -1, -1, -1, -1},
//-- 30 ������� (���� ���������)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 29,  2, 18,
 10, 20, 6, 22, 12, 24, 4, 26, 14, 28, 8, 30, -1, -1, -1, -1},
//-- 31 ������� (���� ���������)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 29,  15, 31,
 2, 18, 10, 20, 6, 22, 12, 24, 4, 26, 14, 28, 8, 30, -1, -1},
//-- 32 �������a
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 29,  15, 31,
 2, 18, 10, 20, 6, 22, 12, 24, 4, 26, 14, 28, 8, 30, 16, 32}
};

int freePosition[32][2] =
{
{-1, -1}, //-- 1 �������
{-1, -1}, //-- 2 ��������
{3, -1}, //-- 3 ��������
{-1, -1}, //-- 4 ��������
{3, -1}, //-- 5 �������
{3, 4}, //-- 6 �������
{4, -1}, //-- 7 �������
{-1, -1}, //-- 8 �������
{5, -1}, //-- 9 �������
{5, 6}, //-- 10 �������
{6, -1}, //-- 11 �������
{-1, -1}, //-- 12 �������
{7, -1}, //-- 13 �������
{7, 8}, //-- 14 �������
{8, -1}, //-- 15 �������
{-1, -1}, //-- 16 �������
{9, -1}, //-- 17 �������
{9, 10}, //-- 18 �������
{10, -1}, //-- 19 �������
{-1, -1}, //-- 20 �������
{11, -1}, //-- 21 �������
{11, 12}, //-- 22 ��������
{12, -1}, //-- 23 ��������
{-1, -1}, //-- 24 ��������
{13, -1}, //-- 25 �������
{13, 14}, //-- 26 �������
{14, -1}, //-- 27 �������
{-1, -1}, //-- 28 �������
{15, -1}, //-- 29 �������
{15, 16}, //-- 30 �������
{16, -1}, //-- 31 �������
{-1, -1} //-- 32 ��������
};



//---------------------------------------------------------------------------
__fastcall TfrmCompetitorPairsReport::TfrmCompetitorPairsReport(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCompetitorPairsReport::qrCompetitorPairsBeforePrint(
      TCustomQuickRep *Sender, bool &PrintReport)
{
    //��������� ������ ������������
    TCompetitionRank competitionRank;
    competitionRank.getById(dmCurrentState->getCompetition().getCompetitionRankId());
    //���������� ������ ������������
    qrlCompetitionRank->Caption = competitionRank.getDescription();
    //���������� ���� ���������� ������������
    AnsiString competitionDate = dmCurrentState->getCompetition().getBeginDate().DateString() + " - " +
                                 dmCurrentState->getCompetition().getEndDate().DateString();
    qrlCompetitionDate->Caption = competitionDate;

    //��������� ������� ������� ������
    qrtCompetitorPairsList->Top = 0;
    qrtCompetitorPairsList->Left = 0;
    qrtCompetitorPairsList->Height = qdbCompetitorPairsList->Height;
    qrtCompetitorPairsList->Width = qdbCompetitorPairsList->Width;
}
//---------------------------------------------------------------------------


void TfrmCompetitorPairsReport::PreviewPairsOrder(map<AnsiString, TCategory*> co, TListBox *lb){
    reCompetitorsPairList->Lines->Clear();
    writeCompetitorPairsList(reCompetitorsPairList, co, lb);
    qrCompetitorPairs->Preview();
}



void TfrmCompetitorPairsReport::writeCompetitorPairsList(TRichEdit *out,
                                                         map<AnsiString, TCategory*> co,
                                                         TListBox *lb){
    //������� ������� ���
    pairCounter = 1;
    //������ ���������, ��������� �������������
    for(int c=0; c < lb->Count; c++){
        //������ ���������, ������� ����� ��������
        TCategory *curCategory = co[lb->Items->Strings[c]];
        //��������� ������� ���������� � ���������, ���� ������ ���� �� ��������
        if(curCategory->getCompetitorsAmount()< 2){
            continue;
            }
        //��������� �������� ������� ���������
        out->Paragraph->Alignment = taCenter;
        out->SelAttributes->Height = 20;
        out->SelAttributes->Style = TFontStyles() << fsBold << fsUnderline;
        //��������� �������� ���������
        out->Lines->Add(lb->Items->Strings[c]);
        insertBlankString(out, 5);
        //��������� ���� � ���������
        writeCategoryPairs(out, curCategory);
        insertBlankString(out, 5);
        }
    reduceClubNameFont(out, 10); 
}


void TfrmCompetitorPairsReport::insertBlankString(TRichEdit *out, int height){
    //������� ������� ������
    out->SelAttributes->Height = height;
    out->SelAttributes->Style = TFontStyles();
    out->Lines->Add("   ");
}


void TfrmCompetitorPairsReport::reduceClubNameFont(TRichEdit *out, int height){
int currentTextPos = 0;
int selStart = 0;
int selEnd = 0;
    while(currentTextPos < out->Text.Length()){
        //����� �������� ������ � ��������� ������������ �����
        selStart = out->Text.SubString(currentTextPos, out->Text.Length() - currentTextPos).Pos("[") ;
        //���� ���� �� ������, �����
        if(!selStart){
            break;
            }
        selStart += (currentTextPos - 2);
        selEnd = selStart + out->Text.SubString(selStart, out->Text.Length() - selStart).Pos("]");
        //�������� ������ ������ �� ���������
        out->SelStart = selStart;
        out->SelLength = selEnd - selStart; 
        out->SelAttributes->Height = height;
        //������������ �� ������
        currentTextPos = selEnd;
        }



}



void TfrmCompetitorPairsReport::writeCategoryPairs(TRichEdit *out, TCategory *category){
    //�������� ������ ����������, �� ������� ��������� ����
    TList * competitors = TCompetitor::getExtendedByCategoryId(category->getId());
    //��������� ������ ���
    int pair = 0;
    int freeIndex = 0;
    int amnt = competitors->Count;
    while(pairsPosition[amnt - 1][pair] > 0){
        //��������� �������������� ���������
        out->Paragraph->Alignment = taLeftJustify;
        out->SelAttributes->Height = 18;
        out->SelAttributes->Style = TFontStyles();
        //�������� ����� �� ���������� ������� � ����
        int firstIndex = pairsPosition[amnt - 1][pair] - 1;
        //�������� ����� ������� �� ����������
        int secondIndex = pairsPosition[amnt - 1][pair + 1] - 1;

        //�������� ������� ��� �������� ������� ���������
        TCompetitor *firstCompetitor = (TCompetitor*)competitors->Items[firstIndex];
        AnsiString firstCompetitorSNP = firstCompetitor->getPerson().getSurname();
        AnsiString patronymic = firstCompetitor->getPerson().getPatronymic().SubString(1,1);
        patronymic += (patronymic.Length()>0)? "." : " ";
        AnsiString name = firstCompetitor->getPerson().getName().SubString(1,1) + ".";

        firstCompetitorSNP  +=  " " + name + " " + patronymic;

        //�������� ����, �� �������� ������ ��������
        TRequest *firstRequest = dmCurrentState->getRequestById(firstCompetitor->getRequestId());
        AnsiString firstClubName = firstRequest->getClub().getShortName();
        //�������� �������� ����� � ������� ���������
        firstCompetitorSNP += " [" + firstClubName + "] ";


        //�������� ������� ��� �������� ������� ���������
        TCompetitor *secondCompetitor = (TCompetitor*)competitors->Items[secondIndex];
        AnsiString secondCompetitorSNP = secondCompetitor->getPerson().getSurname();
        patronymic = secondCompetitor->getPerson().getPatronymic().SubString(1,1);
        patronymic += (patronymic.Length()>0)? "." : " ";
        name = secondCompetitor->getPerson().getName().SubString(1,1) + ".";
        secondCompetitorSNP  +=  " " + name + " " + patronymic;

        //�������� ����, �� �������� ������ ��������
        TRequest *secondRequest = dmCurrentState->getRequestById(secondCompetitor->getRequestId());
        AnsiString secondClubName = secondRequest->getClub().getShortName();
        //�������� �������� ����� � ������� ���������
        secondCompetitorSNP += " [" + secondClubName + "] ";

        //���������� ����
        AnsiString lineToOut = firstCompetitorSNP + " - " + secondCompetitorSNP;
        //���� ���� ��������� , ������� �� � ������ ���� ������� ���������
        if((freeIndex < 2)){
            int index = freePosition[amnt - 1][freeIndex] - 1;
            if( index > 0){
                //�������� ������� ��� ���������� ���������
                TCompetitor *freeCompetitor = (TCompetitor*)competitors->Items[index];
                AnsiString freeCompetitorSNP = freeCompetitor->getPerson().getSurname();
                patronymic = freeCompetitor->getPerson().getPatronymic();
                name = freeCompetitor->getPerson().getName();
                freeCompetitorSNP  +=  " " +
                             AnsiString(name[1]) + ". " +
                             (patronymic!="" ? (AnsiString(patronymic[1]) + ".") : AnsiString(""));
                //�������� ����, �� �������� ��������� ��������
                TRequest *freeRequest = dmCurrentState->getRequestById(freeCompetitor->getRequestId());
                AnsiString freeClubName = freeRequest->getClub().getShortName();
                //�������� �������� ����� � ������� ���������
                freeCompetitorSNP += " [" + freeClubName + "] ";
                //������� ����������
                lineToOut+= "          (" + freeCompetitorSNP + " - ����.)";
                }
            //� ���������� ����������
            freeIndex ++;
            }
        out->Lines->Add(IntToStr(pairCounter) + ". " + lineToOut);
        //�������� � ��������� ����
        pair += 2;
        pairCounter++;
        }
    //������� ������ ����������
    destroyList(competitors, etCOMPETITOR);
}
