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
//-- 1 человек
{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 2 человека
{1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 3 человека (есть свободные)
{1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 4 человека
{1, 3,  2, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 5 человек (есть свободные)
{1, 5,  2, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 6 человек (есть свободные)
{1, 5,  2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 7 человек (есть свободные)
{1, 5,  3, 7,  2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 8 человек
{1, 5,  3, 7,  2, 6,  4, 8, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 9 человек (есть свободные)
{1, 9,  3, 7,  2, 6,  4, 8, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 10 человек (есть свободные)
{1, 9,  3, 7,  2, 10, 4, 8, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 11 человек (есть свободные)
{1, 9,  5, 11,  3, 7,  2, 10, 4, 8, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 12 человек
{1, 9,  5, 11,  3, 7,  2, 10, 6, 12,  4, 8, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 13 человек (есть свободные)
{1, 9,  5, 11,  3, 13,  2, 10,  6, 12,  4, 8, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 14 человек (есть свободные)
{1, 9,  5, 11,  3, 13,  2, 10,  6, 12,  4, 14, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 15 человек (есть свободные)
{1, 9,  5, 11,  3, 13,  7, 15,  2, 10,  6, 12,  4, 14, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 16 человек
{1, 9,  5, 11,  3, 13,  7, 15,  2, 10,  6, 12,  4, 14,  8, 16,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 17 человек (есть свободные)
{1, 17,  5, 11,  3, 13,  7, 15,  2, 10,  6, 12,  4, 14,  8, 16,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 18 человек (есть свободные)
{1, 17,  5, 11,  3, 13,  7, 15,  2, 18,  6, 12,  4, 14,  8, 16,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 19 человек (есть свободные)
{1, 17,  9, 19,  5, 11,  3, 13,  7, 15,  2, 18,  6, 12,  4, 14,
 8, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 20 человек
{1, 17,  9, 19,  5, 11,  3, 13,  7, 15,  2, 18,  10, 20,  6, 12,
 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 21 человек (есть свободные)
{1, 17,  9, 19,  5, 21,  3, 13,  7, 15,  2, 18,  10, 20,  6, 12,
 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 22 человекa (есть свободные)
{1, 17,  9, 19,  5, 21,  3, 13,  7, 15,  2, 18,  10, 20,  6, 22,
 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 23 человекa (есть свободные)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 13,  7, 15,  2, 18,  10, 20,
 6, 22, 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 24 человекa
{1, 17,  9, 19,  5, 21,  11, 23,  3, 13,  7, 15,  2, 18,  10, 20,
 6, 22, 12, 24, 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 25 человек (есть свободные)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  7, 15,  2, 18,  10, 20,
 6, 22, 12, 24, 4, 14, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 26 человек (есть свободные)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  7, 15,  2, 18,  10, 20,
 6, 22, 12, 24, 4, 26, 8, 16, -1, -1, -1, -1, -1, -1, -1, -1},
//-- 27 человек (есть свободные)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 15,  2, 18,
 10, 20, 6, 22, 12, 24, 4, 26, 8, 16, -1, -1, -1, -1, -1, -1},
//-- 28 человек
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 15,  2, 18,
 10, 20, 6, 22, 12, 24, 4, 26, 14, 28, 8, 16, -1, -1, -1, -1},
//-- 29 человек (есть свободные)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 29,  2, 18,
 10, 20, 6, 22, 12, 24, 4, 26, 14, 28, 8, 16, -1, -1, -1, -1},
//-- 30 человек (есть свободные)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 29,  2, 18,
 10, 20, 6, 22, 12, 24, 4, 26, 14, 28, 8, 30, -1, -1, -1, -1},
//-- 31 человек (есть свободные)
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 29,  15, 31,
 2, 18, 10, 20, 6, 22, 12, 24, 4, 26, 14, 28, 8, 30, -1, -1},
//-- 32 человекa
{1, 17,  9, 19,  5, 21,  11, 23,  3, 25,  13, 27,  7, 29,  15, 31,
 2, 18, 10, 20, 6, 22, 12, 24, 4, 26, 14, 28, 8, 30, 16, 32}
};

int freePosition[32][2] =
{
{-1, -1}, //-- 1 человек
{-1, -1}, //-- 2 человека
{3, -1}, //-- 3 человека
{-1, -1}, //-- 4 человека
{3, -1}, //-- 5 человек
{3, 4}, //-- 6 человек
{4, -1}, //-- 7 человек
{-1, -1}, //-- 8 человек
{5, -1}, //-- 9 человек
{5, 6}, //-- 10 человек
{6, -1}, //-- 11 человек
{-1, -1}, //-- 12 человек
{7, -1}, //-- 13 человек
{7, 8}, //-- 14 человек
{8, -1}, //-- 15 человек
{-1, -1}, //-- 16 человек
{9, -1}, //-- 17 человек
{9, 10}, //-- 18 человек
{10, -1}, //-- 19 человек
{-1, -1}, //-- 20 человек
{11, -1}, //-- 21 человек
{11, 12}, //-- 22 человека
{12, -1}, //-- 23 человека
{-1, -1}, //-- 24 человека
{13, -1}, //-- 25 человек
{13, 14}, //-- 26 человек
{14, -1}, //-- 27 человек
{-1, -1}, //-- 28 человек
{15, -1}, //-- 29 человек
{15, 16}, //-- 30 человек
{16, -1}, //-- 31 человек
{-1, -1} //-- 32 человека
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
    //Устновить статус соревнований
    TCompetitionRank competitionRank;
    competitionRank.getById(dmCurrentState->getCompetition().getCompetitionRankId());
    //Установить статус соревнований
    qrlCompetitionRank->Caption = competitionRank.getDescription();
    //Установить дату проведения соревнований
    AnsiString competitionDate = dmCurrentState->getCompetition().getBeginDate().DateString() + " - " +
                                 dmCurrentState->getCompetition().getEndDate().DateString();
    qrlCompetitionDate->Caption = competitionDate;

    //Установим размеры области вывода
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
    //Сбросим счетчик пар
    pairCounter = 1;
    //Печать категорий, выбранных пользователем
    for(int c=0; c < lb->Count; c++){
        //Найдем категорию, которую будем выводить
        TCategory *curCategory = co[lb->Items->Strings[c]];
        //Проверить сколько участников в категории, если меньше двух не печатать
        if(curCategory->getCompetitorsAmount()< 2){
            continue;
            }
        //Установим свойства подписи категории
        out->Paragraph->Alignment = taCenter;
        out->SelAttributes->Height = 20;
        out->SelAttributes->Style = TFontStyles() << fsBold << fsUnderline;
        //Отобразим название категории
        out->Lines->Add(lb->Items->Strings[c]);
        insertBlankString(out, 5);
        //Перчатаем пары в категории
        writeCategoryPairs(out, curCategory);
        insertBlankString(out, 5);
        }
    reduceClubNameFont(out, 10); 
}


void TfrmCompetitorPairsReport::insertBlankString(TRichEdit *out, int height){
    //Сделать пропуск строки
    out->SelAttributes->Height = height;
    out->SelAttributes->Style = TFontStyles();
    out->Lines->Add("   ");
}


void TfrmCompetitorPairsReport::reduceClubNameFont(TRichEdit *out, int height){
int currentTextPos = 0;
int selStart = 0;
int selEnd = 0;
    while(currentTextPos < out->Text.Length()){
        //Найти названия клубов и уменьшить отображаемый шрифт
        selStart = out->Text.SubString(currentTextPos, out->Text.Length() - currentTextPos).Pos("[") ;
        //Если клуб не найден, выйти
        if(!selStart){
            break;
            }
        selStart += (currentTextPos - 2);
        selEnd = selStart + out->Text.SubString(selStart, out->Text.Length() - selStart).Pos("]");
        //Уменьшим размер шрифта по выделению
        out->SelStart = selStart;
        out->SelLength = selEnd - selStart; 
        out->SelAttributes->Height = height;
        //Передвинемся по тексту
        currentTextPos = selEnd;
        }



}



void TfrmCompetitorPairsReport::writeCategoryPairs(TRichEdit *out, TCategory *category){
    //Получить список участников, из которых формируем пары
    TList * competitors = TCompetitor::getExtendedByCategoryId(category->getId());
    //Отобразим список пар
    int pair = 0;
    int freeIndex = 0;
    int amnt = competitors->Count;
    while(pairsPosition[amnt - 1][pair] > 0){
        //Установим форматирование параграфа
        out->Paragraph->Alignment = taLeftJustify;
        out->SelAttributes->Height = 18;
        out->SelAttributes->Style = TFontStyles();
        //Получить номер по жеребьевки первого в паре
        int firstIndex = pairsPosition[amnt - 1][pair] - 1;
        //Получить номер второго по жеребьевке
        int secondIndex = pairsPosition[amnt - 1][pair + 1] - 1;

        //Получить фамилию имя отчество первого участника
        TCompetitor *firstCompetitor = (TCompetitor*)competitors->Items[firstIndex];
        AnsiString firstCompetitorSNP = firstCompetitor->getPerson().getSurname();
        AnsiString patronymic = firstCompetitor->getPerson().getPatronymic().SubString(1,1);
        patronymic += (patronymic.Length()>0)? "." : " ";
        AnsiString name = firstCompetitor->getPerson().getName().SubString(1,1) + ".";

        firstCompetitorSNP  +=  " " + name + " " + patronymic;

        //Получить клуб, из которого первый участник
        TRequest *firstRequest = dmCurrentState->getRequestById(firstCompetitor->getRequestId());
        AnsiString firstClubName = firstRequest->getClub().getShortName();
        //Добавить название клуба к фамилии участника
        firstCompetitorSNP += " [" + firstClubName + "] ";


        //Получить фамилию имя отчество второго участника
        TCompetitor *secondCompetitor = (TCompetitor*)competitors->Items[secondIndex];
        AnsiString secondCompetitorSNP = secondCompetitor->getPerson().getSurname();
        patronymic = secondCompetitor->getPerson().getPatronymic().SubString(1,1);
        patronymic += (patronymic.Length()>0)? "." : " ";
        name = secondCompetitor->getPerson().getName().SubString(1,1) + ".";
        secondCompetitorSNP  +=  " " + name + " " + patronymic;

        //Получить клуб, из которого второй участник
        TRequest *secondRequest = dmCurrentState->getRequestById(secondCompetitor->getRequestId());
        AnsiString secondClubName = secondRequest->getClub().getShortName();
        //Добавить название клуба к фамилии участника
        secondCompetitorSNP += " [" + secondClubName + "] ";

        //Отобразить пару
        AnsiString lineToOut = firstCompetitorSNP + " - " + secondCompetitorSNP;
        //Если есть свободные , выводим их в первых двух строках категории
        if((freeIndex < 2)){
            int index = freePosition[amnt - 1][freeIndex] - 1;
            if( index > 0){
                //Получить фамилию имя свободного участника
                TCompetitor *freeCompetitor = (TCompetitor*)competitors->Items[index];
                AnsiString freeCompetitorSNP = freeCompetitor->getPerson().getSurname();
                patronymic = freeCompetitor->getPerson().getPatronymic();
                name = freeCompetitor->getPerson().getName();
                freeCompetitorSNP  +=  " " +
                             AnsiString(name[1]) + ". " +
                             (patronymic!="" ? (AnsiString(patronymic[1]) + ".") : AnsiString(""));
                //Получить клуб, из которого свободный участник
                TRequest *freeRequest = dmCurrentState->getRequestById(freeCompetitor->getRequestId());
                AnsiString freeClubName = freeRequest->getClub().getShortName();
                //Добавить название клуба к фамилии участника
                freeCompetitorSNP += " [" + freeClubName + "] ";
                //Добавим свободного
                lineToOut+= "          (" + freeCompetitorSNP + " - своб.)";
                }
            //К следующему свободному
            freeIndex ++;
            }
        out->Lines->Add(IntToStr(pairCounter) + ". " + lineToOut);
        //Перейдем к следующей паре
        pair += 2;
        pairCounter++;
        }
    //Удалить список участников
    destroyList(competitors, etCOMPETITOR);
}
