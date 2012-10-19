//---------------------------------------------------------------------------

#ifndef competitorPairsReportUH
#define competitorPairsReportUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
#include <ComCtrls.hpp>

#include <map.h>

#include "categoryCtrl.h"
//---------------------------------------------------------------------------
class TfrmCompetitorPairsReport : public TForm
{
__published:	// IDE-managed Components
    TQuickRep *qrCompetitorPairs;
    TQRBand *qdbCompetitorPairsList;
    TQRRichText *qrtCompetitorPairsList;
    TRichEdit *reCompetitorsPairList;
    TQRBand *qbListHeader;
    TQRLabel *qrlTitle;
    TQRLabel *qrlCompetitionDate;
    TQRLabel *qrlCompetitionRank;
    void __fastcall qrCompetitorPairsBeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
private:	// User declarations
    int pairCounter;     //Счетчик пар
    //-- вывод списка пар участников
    void writeCompetitorPairsList(TRichEdit *out, map<AnsiString, TCategory*> co,
                                  TListBox *lb);
    //-- вывод списка пар участников для категории
    void writeCategoryPairs(TRichEdit *out, TCategory* category);
    //-- Вставить пустую строчку в список
    void insertBlankString(TRichEdit *out, int height);

    //-- Уменьшить шрифт в названии
    void reduceClubNameFont(TRichEdit *out, int height);
public:		// User declarations
    __fastcall TfrmCompetitorPairsReport(TComponent* Owner);

    //-- Предварительный просмотр и печатьпар участников
    //@param lb - listbox со списком категорий, которые печатаются
    //@param co - колекция категорий, списки пар для которых печатаем
    void PreviewPairsOrder(map<AnsiString, TCategory*> co, TListBox *lb);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCompetitorPairsReport *frmCompetitorPairsReport;
//---------------------------------------------------------------------------
#endif
