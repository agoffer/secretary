//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop



#include "reportDataSourceDM.h"

#include "excelApi.h"

#include "categoryCtrl.h"
#include "currentStateDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmReportDataSource *dmReportDataSource;
//---------------------------------------------------------------------------
__fastcall TdmReportDataSource::TdmReportDataSource(TComponent* Owner)
    : TDataModule(Owner)
{
    finalReport = false;
}
//---------------------------------------------------------------------------


void __fastcall TdmReportDataSource::ibqRepCategoryDetailAfterScroll(
      TDataSet *DataSet)
{
    //
    // ќбновить список участников в категории
    //

AnsiString selectQuery=
"select (Date 'now' - (Person.dob + 1)) / 365, \
 Person.id, \
       Person.surname, \
       Person.name, \
       Person.patronymic, \
       Person.dob, \
       Person.phone, \
       Person.female, \
       Person.additions, \
       Skill.id, \
       Skill.shortDescription, \
       Skill.fullDescription, \
       Skill.weight, \
       Skill.comments, \
       Request.id, \
       Request.personId, \
       Request.clubId, \
       Request.competitionId, \
       Request.comments, \
       Club.shortName,   \
       Competitor.id comp_id, \
       Competitor.weight, \
       CompetitorToCategory.sortion, \
       Result.shootscore, \
       Result.crosstime, \
       CompetitorToCategory.shootRank \
       from Competitor left outer join Result on Result.competitorId = Competitor.id, \
       Skill, Person, Request, Club, CompetitorToCategory where \
       Person.id = Competitor.personId and Skill.id = Competitor.skillId \
       and Club.id = Request.clubId and Request.id = Competitor.requestId and \
       Competitor.id = CompetitorToCategory.competitorId \
       and CompetitorToCategory.categoryId =  :categoryId order by CompetitorToCategory.sortion";

    // ѕосле перехода к другой записи
    // сформировать множество ”частников дл€ категории
    if(ibqRepCompetitorDetail->Active){
        ibqRepCompetitorDetail->Close();
        }
    ibqRepCompetitorDetail->SQL->Clear();
    ibqRepCompetitorDetail->SQL->Add(selectQuery);
    ibqRepCompetitorDetail->ParamByName("categoryId")->AsInteger = DataSet->FieldByName("id")->AsInteger;
    ibqRepCompetitorDetail->Open();
    ibqRepCompetitorDetail->Last();
    ibqRepCompetitorDetail->First();        
}
//---------------------------------------------------------------------------


void TdmReportDataSource::setCategoriesToPrintByCompetition(int compId){

AnsiString selectQuery =
"select \
  ct.id, \
  cr.description, \
  ac.female, \
  ac.startweight, \
  ac.endweight, \
  ac.startage, \
  ac.endage, \
  cpt.begindate, \
  cpt.enddate, \
  fv.code \
from \
  competitionrank cr, \
  availablecategory ac, \
  competition cpt, \
  fightversion fv, \
  category ct \
where \
  cr.id = cpt.competitionrankid and \
  ac.id = ct.availablecategoryid and \
  fv.id = ct.fightversionid and \
  ct.competitionid = competition.id and competition.id = :competitionId \
  order  by fv.code, ac.female, ac.startage, \
  ac.startweight";

    // сформировать множество категорий дл€ соревновани€
    if(ibqRepCategoryDetail->Active){
        ibqRepCategoryDetail->Close();
        }
    ibqRepCategoryDetail->SQL->Clear();
    ibqRepCategoryDetail->SQL->Add(selectQuery);
    ibqRepCategoryDetail->ParamByName("competitionId")->AsInteger = compId;
    ibqRepCategoryDetail->Open();
}


void TdmReportDataSource::setCategoriesFromList(TList* categories){
AnsiString selectQuery_1 =
"select \
  ct.id, \
  cr.description, \
  ac.female, \
  ac.startweight, \
  ac.endweight, \
  ac.startage, \
  ac.endage, \
  cpt.begindate, \
  cpt.enddate, \
  fv.code \
from \
  competitionrank cr, \
  availablecategory ac, \
  competition cpt, \
  fightversion fv, \
  category ct \
where \
  cr.id = cpt.competitionrankid and \
  ac.id = ct.availablecategoryid and \
  fv.id = ct.fightversionid and \
  cpt.id = ct.competitionid and ct.id in (";
AnsiString selectQuery_2 =  ")\
  order  by fv.code, ac.female, ac.startage, \
  ac.startweight";

//»тоговый запрос
AnsiString selectQuery;

    //—формируем список категорий
    for(int cl = 0; cl < (categories->Count - 1); cl ++){
        selectQuery_1 += IntToStr(((TCategory*)categories->Items[cl])->getId()) + ", ";
        }
    selectQuery_1 += IntToStr(((TCategory*)categories->Items[categories->Count - 1])->getId());

    //ѕолученный запрос
    selectQuery = selectQuery_1 + selectQuery_2;

    // сформировать множество категорий дл€ соревновани€
    if(ibqRepCategoryDetail->Active){
        ibqRepCategoryDetail->Close();
        }
    ibqRepCategoryDetail->SQL->Clear();
    ibqRepCategoryDetail->SQL->Add(selectQuery);
    ibqRepCategoryDetail->Open();
}



void TdmReportDataSource::setCategoryToPrintById(int prCat){
AnsiString selectQuery =
"select \
  ct.id, \
  cr.description, \
  ac.female, \
  ac.startweight, \
  ac.endweight, \
  ac.startage, \
  ac.endage, \
  cpt.begindate, \
  cpt.enddate, \
  fv.code \
from \
  competitionrank cr, \
  availablecategory ac, \
  competition cpt, \
  fightversion fv, \
  category ct \
where \
  cr.id = cpt.competitionrankid and \
  cpt.id = ct.competitionid and \
  ac.id = ct.availablecategoryid and \
  fv.id = ct.fightversionid and \
  ct.id = :categoryId order  by ac.female, ac.startage, \
  ac.startweight, fv.code";

    // сформировать множество категорий дл€ соревновани€
    if(ibqRepCategoryDetail->Active){
        ibqRepCategoryDetail->Close();
        }
    ibqRepCategoryDetail->SQL->Clear();
    ibqRepCategoryDetail->SQL->Add(selectQuery);
    ibqRepCategoryDetail->ParamByName("categoryId")->AsInteger = prCat;
    ibqRepCategoryDetail->Open();
}



void TdmReportDataSource::setUncategoryListQueryByCompetitionId(int competitionId){
AnsiString selectQuery =
"select \
       Person.surname, \
       Person.name, \
       Person.patronymic, \
       Club.shortName, \
       Competitor.id \
 from Competitor, Person, Request, Club \
 where Person.id = Competitor.personId \
       and Request.id = Competitor.requestId \
       and Request.competitionId = :competitionId and \
       Club.id = Request.clubId and Competitor.id  in \
       (select distinct competitorId from CompetitorToFightVersion, Competitor, \
        Request where CompetitorToFightVersion.destributed = 'F' and \
        CompetitorToFightVersion.competitorId  = Competitor.id and \
        Competitor.requestId = Request.id and \
        Request.competitionId = :competitionId) \
        order by Club.shortName, Person.female, Person.surname";


    // сформировать список участников, у которых не распределены или добавлены категории
    if(ibqRepUncategoryListDetail->Active){
        ibqRepUncategoryListDetail->Close();
        }
    ibqRepUncategoryListDetail->SQL->Clear();
    ibqRepUncategoryListDetail->SQL->Add(selectQuery);
    ibqRepUncategoryListDetail->ParamByName("competitionId")->AsInteger = competitionId;
    ibqRepUncategoryListDetail->Open();
}


void TdmReportDataSource::setRequestClubListByCompetitionId(int competitionId){
AnsiString selectQuery =
"select \
club.name, \
person.surname, \
person.name, \
person.patronymic, \
person.phone \
from \
club, person, request, competition \
where \
club.id = request.clubid and person.id = request.personid and \
request.competitionid = competition.id \
and competition.id = :competitionId order by club.name";


    // сформировать список участников, у которых не распределены или добавлены категории
    if(ibqRepRequestClubListDetail->Active){
        ibqRepRequestClubListDetail->Close();
        }
    ibqRepRequestClubListDetail->SQL->Clear();
    ibqRepRequestClubListDetail->SQL->Add(selectQuery);
    ibqRepRequestClubListDetail->ParamByName("competitionId")->AsInteger = competitionId;
    ibqRepRequestClubListDetail->Open();
}



void __fastcall TdmReportDataSource::CategoryDetailAfterScroll(
      TDataSet *DataSet)
{
    //ѕерешли к категории , обновить соответствующий список участников

    if(!finalReport){
        ibqRepCategoryDetailAfterScroll(DataSet);
        }
    else{
        ibqRepCategoryFinalCompetitorDetailAfterScroll(DataSet);
        }
}



void __fastcall TdmReportDataSource::ibqRepCategoryFinalCompetitorDetailAfterScroll(
      TDataSet *DataSet)
{
    //
    // ќбновить список участников в категории
    //

AnsiString selectQuery=
/*
"select \
       Person.surname, \
       Person.name, \
       Person.patronymic, \
       CompetitorToCategory.shootRank, \
       CompetitorToCategory.fightWOKnifeRank, \
       CompetitorToCategory.fightWKnifeRank, \
       CompetitorToCategory.commonRank \
       from Competitor, Person, CompetitorToCategory where \
       Person.id = Competitor.personId and \
       Competitor.id = CompetitorToCategory.competitorId \
       and CompetitorToCategory.categoryId = :categoryId order by \
       CompetitorToCategory.commonRank";
*/

"select \
  pers.surname, \
  pers.name, \
  pers.patronymic, \
  compToCat.shootrank, \
  compToCat.fightWOKnifeRank, \
  compToCat.commonRank , clb.shortname \
from \
  CompetitorToCategory compToCat \
join \
  Competitor comp on comp.id=compToCat.competitorid \
join \
  Person pers on pers.id=comp.personid \
join \
  Request req on req.id=comp.requestid \
join \
  Club clb on clb.id=req.clubid \
where \
  compToCat.categoryid= :categoryId order by compToCat.commonRank";


    // ѕосле перехода к другой записи
    // сформировать множество ”частников дл€ категории
    if(ibqRepCategoryFinalCompetitorDetail->Active){
        ibqRepCategoryFinalCompetitorDetail->Close();
        }
    ibqRepCategoryFinalCompetitorDetail->SQL->Clear();
    ibqRepCategoryFinalCompetitorDetail->SQL->Add(selectQuery);
    ibqRepCategoryFinalCompetitorDetail->ParamByName("categoryId")->AsInteger = DataSet->FieldByName("id")->AsInteger;
    ibqRepCategoryFinalCompetitorDetail->Open();

}
//---------------------------------------------------------------------------

void TdmReportDataSource::summaryProtocolExport(int competitionId){
    //ѕолучить данные по соревнованию, и создать файл сводного протокола
    AnsiString appPath = ExtractFilePath(Application->ExeName);
    TExcelApp *myExcel = new TExcelApp(appPath+"database\\summary.xlt",
                                       appPath + "database\\myreport.xls");

    // ѕосчитать количество строк, которые будут добавлены в протокол //
    int protocolRows = getCompetitorsAmount(competitionId);

    //ƒобавить строки в протокол
    myExcel->InsertRows("tablebegin", protocolRows - 1);

    //ќтображаем данные по мужским категори€м
    TIBQuery* dsCompetitorsDetail = getSummaryReportData(competitionId, false);
    //‘ормируем сторки дл€ протокола и заполн€ем его
    int competitorInCategoryAmntMale = dsCompetitorsDetail->RecordCount;
    Variant categoryArray = myExcel->createVariantArray(competitorInCategoryAmntMale, 18);
    //ѕолучить массив данных дл€ мужских категорий
    fillSummaryReportArray(0, competitorInCategoryAmntMale,
                           dsCompetitorsDetail, categoryArray);
    dsCompetitorsDetail->Close();
    myExcel->toExcelArrayToRange(categoryArray, "order", 18, competitorInCategoryAmntMale);

    //ќтображаем данные по женским категори€м
    dsCompetitorsDetail = getSummaryReportData(competitionId, true);
    //‘ормируем сторки дл€ протокола и заполн€ем его
    int competitorInCategoryAmntFemale = dsCompetitorsDetail->RecordCount;
    categoryArray = myExcel->createVariantArray(competitorInCategoryAmntFemale, 18);
    //ѕолучить массив данных дл€ мужских категорий
    fillSummaryReportArray(competitorInCategoryAmntMale,
                           competitorInCategoryAmntFemale,
                           dsCompetitorsDetail, categoryArray);
    dsCompetitorsDetail->Close();
    myExcel->toExcelArrayToRange(categoryArray, "order", competitorInCategoryAmntMale, 18, competitorInCategoryAmntFemale);

    delete myExcel;
}


void TdmReportDataSource::fillSummaryReportArray(int orderNum, int competitorInCategoryAmnt,
                                                TIBQuery* dsCompetitorsDetail,
                                                Variant & categoryArray){

    int currentCategoryId = -1;
    for(int i=0; i < competitorInCategoryAmnt; i++){

        int nextCategoryId = dsCompetitorsDetail->FieldByName("id")->AsInteger;
        bool printCategoryAttr = nextCategoryId != currentCategoryId;
        currentCategoryId = nextCategoryId;


        //ѕолучим данные дл€ записи
        String fightVersion =
            printCategoryAttr ? dsCompetitorsDetail->FieldByName("fightversion")->AsString : AnsiString("");

        int startAge = dsCompetitorsDetail->FieldByName("startage")->AsInteger;
        int endAge = dsCompetitorsDetail->FieldByName("endage")->AsInteger;

        AnsiString ages = printCategoryAttr ? IntToStr(startAge) + " - " + IntToStr(endAge) : AnsiString("");
        double startWeight = dsCompetitorsDetail->FieldByName("startweight")->AsFloat;
        double endWeight = dsCompetitorsDetail->FieldByName("endweight")->AsFloat;

        AnsiString weight = "";
        if(printCategoryAttr){
            if(endWeight > 450){
                weight = "више " + FloatToStr(startWeight);
                }
            else{
                weight = "до " + FloatToStr(endWeight);
                }
            }
        AnsiString surname = dsCompetitorsDetail->FieldByName("comp_surname")->AsString;
        // 10.10.12 ‘амили€ формируетс€ с инициалами полностью
        AnsiString name = dsCompetitorsDetail->FieldByName("comp_name")->AsString; // .SubString(1,1) + ".";
        AnsiString patronymic = dsCompetitorsDetail->FieldByName("comp_patronymic")->AsString; // .SubString(1,1);
        // patronymic += (patronymic.Length()>0)? "." : " ";
        AnsiString snp = surname + " " + name + " " +patronymic;

        AnsiString city = dsCompetitorsDetail->FieldByName("city")->AsString;

        AnsiString skill = dsCompetitorsDetail->FieldByName("skill")->AsString;

        AnsiString dob = dsCompetitorsDetail->FieldByName("comp_dob")->AsString;

        AnsiString commonScore;
        int shootRank = dsCompetitorsDetail->FieldByName("shootrank")->AsInteger;
        int fightWOKnifeRank = dsCompetitorsDetail->FieldByName("fightwokniferank")->AsInteger;

        int shootScore = dmCurrentState->getScoreForRank(shootRank, 0);
        int fightWOKnifeScore = dmCurrentState->getScoreForRank(fightWOKnifeRank, 1);

        int score = shootScore + fightWOKnifeScore;
        //commonScore = IntToStr();

        AnsiString commonRank = dsCompetitorsDetail->FieldByName("commonrank")->AsString;

        AnsiString representer = dsCompetitorsDetail->FieldByName("repr_surname")->AsString;

        categoryArray.PutElement((orderNum++) + 1, i, 0);        //1
        categoryArray.PutElement(fightVersion, i, 1);            //2
        categoryArray.PutElement(ages, i, 2);                    //3
        categoryArray.PutElement(weight, i, 3);                  //4
        categoryArray.PutElement(snp, i, 4);                     //5
        categoryArray.PutElement(dob, i, 5);                     //6
        categoryArray.PutElement(city, i, 6);                    //7
        categoryArray.PutElement(skill, i, 7);                   //8

        categoryArray.PutElement(shootRank, i, 8);               //9
        categoryArray.PutElement(shootScore, i, 9);              //10
        categoryArray.PutElement(fightWOKnifeRank, i, 10);       //11
        categoryArray.PutElement(fightWOKnifeScore, i, 11);      //12
        //categoryArray.PutElement(fightWKnifeRank, i, 12);        //13
        //categoryArray.PutElement(fightWKnifeScore, i, 13);       //14


        categoryArray.PutElement(/*commonScore*/ score, i, 14);             //15
        categoryArray.PutElement(commonRank, i, 15);              //16
         categoryArray.PutElement("", i, 16);                     //17
        categoryArray.PutElement(representer, i, 17);             //18

        dsCompetitorsDetail->Next();
        }
}




int TdmReportDataSource::getCompetitorsAmount(int competitionId){
    //
    // ќбновить список участников в категории
    //

AnsiString selectQuery=
    "select count(competitortocategory.competitorid) as compAmnt \
    from competitortocategory, category \
    where competitortocategory.categoryid = category.id \
    and category.competitionid = :competitionId";

    if(ibqSummaryReport->Active){
        ibqSummaryReport->Close();
        }
    ibqSummaryReport->SQL->Clear();
    ibqSummaryReport->SQL->Add(selectQuery);
    ibqSummaryReport->ParamByName("competitionId")->AsInteger = competitionId;
    ibqSummaryReport->Open();

    int amount = 0;
    if(ibqSummaryReport->RecordCount){
        amount = ibqSummaryReport->FieldByName("compAmnt")->AsInteger;
        }
    ibqSummaryReport->Close();
    return amount;
}

TIBQuery* TdmReportDataSource::getSummaryReportData(int competitionId, bool female){
AnsiString selectQuery=
    "select \
    cat.id, fv.code as fightversion, \
    avcat.startage, avcat.endage, \
    avcat.startweight, avcat.endweight, \
    comp_pers.surname as comp_surname, comp_pers.name as comp_name, \
    comp_pers.patronymic as comp_patronymic, \
    comp_pers.dob as comp_dob, \
    cl.city, sk.shortdescription as skill, \
    ctc.commonrank, \
    ctc.shootrank, \
    ctc.fightwokniferank, \
    req_pers.surname||' '||req_pers.name||' '||req_pers.patronymic as repr_surname\
    from \
     competitor comp \
     join person comp_pers on comp_pers.id = comp.personid \
     join request req on req.id = comp.requestid \
     join person req_pers on req_pers.id = req.personid \
     join competitortocategory ctc on ctc.competitorid = comp.id \
     join club  cl on cl.id = req.clubid \
     join skill sk on sk.id = comp.skillid \
     join category cat on cat.id = ctc.categoryid \
     join fightversion fv on fv.id = cat.fightversionid \
     join availablecategory avcat on avcat.id = cat.availablecategoryid \
    where \
     cat.competitionId = :competitionId and avcat.female = :female \
    order by fv.code, avcat.startage, avcat.endage, avcat.startweight, \
    avcat.endweight, ctc.commonrank, cat.id";

    if(ibqSummaryReport->Active){
        ibqSummaryReport->Close();
        }
    ibqSummaryReport->SQL->Clear();
    ibqSummaryReport->SQL->Add(selectQuery);
    ibqSummaryReport->ParamByName("competitionId")->AsInteger = competitionId;
    ibqSummaryReport->ParamByName("female")->AsString = female?'T' : 'F';
    ibqSummaryReport->Open();
    ibqSummaryReport->Last();
    ibqSummaryReport->First();
    return ibqSummaryReport;
}
