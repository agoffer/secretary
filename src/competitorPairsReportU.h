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
    int pairCounter;     //������� ���
    //-- ����� ������ ��� ����������
    void writeCompetitorPairsList(TRichEdit *out, map<AnsiString, TCategory*> co,
                                  TListBox *lb);
    //-- ����� ������ ��� ���������� ��� ���������
    void writeCategoryPairs(TRichEdit *out, TCategory* category);
    //-- �������� ������ ������� � ������
    void insertBlankString(TRichEdit *out, int height);

    //-- ��������� ����� � ��������
    void reduceClubNameFont(TRichEdit *out, int height);
public:		// User declarations
    __fastcall TfrmCompetitorPairsReport(TComponent* Owner);

    //-- ��������������� �������� � ��������� ����������
    //@param lb - listbox �� ������� ���������, ������� ����������
    //@param co - �������� ���������, ������ ��� ��� ������� ��������
    void PreviewPairsOrder(map<AnsiString, TCategory*> co, TListBox *lb);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCompetitorPairsReport *frmCompetitorPairsReport;
//---------------------------------------------------------------------------
#endif
