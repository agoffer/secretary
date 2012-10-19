//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "competitionSelectListU.h"
#include "competitionDM.h"
#include "currentStateDM.h"
#include "competitionCtrl.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCompetitionSelectList *frmCompetitionSelectList;
//---------------------------------------------------------------------------
__fastcall TfrmCompetitionSelectList::TfrmCompetitionSelectList(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCompetitionSelectList::FormShow(TObject *Sender)
{
    //-- ѕолучить минимальную и максимальную дату начала соревнований
    TDateTime max, min;
    TCompetition::getMinMaxBeginDate(min, max);

    dtpBeginDate->DateTime = min;
    dtpEndDate->DateTime = max;

    //¬ыбрать записи по заданному интервалу
    dmCompetitionDAO->selectRangeExtendedCompetitions(dtpBeginDate->DateTime,
                                                     dtpEndDate->DateTime);
}
//---------------------------------------------------------------------------


void __fastcall TfrmCompetitionSelectList::dtpDateChange(
      TObject *Sender)
{
    //ƒату изменили, перечитать таблицу
    //¬ыбрать записи по заданному интервалу
    dmCompetitionDAO->selectRangeExtendedCompetitions(dtpBeginDate->DateTime,
                                                     dtpEndDate->DateTime);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionSelectList::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //’отим получить соревнование
    if(ModalResult == mrOk){
        //”становить текущее соревнование, выбранное в таблице
        dmCurrentState->setCompetition(TCompetition::getExtendedCurrent());
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompetitionSelectList::bbtnDeleteCompetitionClick(
      TObject *Sender)
{
    if(MessageDlg("¬ы действительно хотите удалить выбранное соревнование?", mtConfirmation,
                TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo) {
                    return;
                }
    // ”далить выбранное соревнование
    dmCompetitionDAO->removeCurrent();
    // ќбновить данные в таблице с соревновани€ми
    dtpDateChange(NULL);
}
//---------------------------------------------------------------------------


