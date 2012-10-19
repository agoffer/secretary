//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("mainFormU.cpp", frmMainForm);
USEFORM("dataSourceDM.cpp", dmDataSource); /* TDataModule: File Type */
USEFORM("competitionEditU.cpp", frmCompetitionEdit);
USEFORM("competitionRankEditU.cpp", frmCompetitionRankEdit);
USEFORM("competitionRankDM.cpp", dmCompetitionRankDAO); /* TDataModule: File Type */
USEFORM("competitionDM.cpp", dmCompetitionDAO); /* TDataModule: File Type */
USEFORM("requestEditU.cpp", frmRequestEdit);
USEFORM("requestDM.cpp", dmRequestDAO); /* TDataModule: File Type */
USEFORM("clubDM.cpp", dmClubDAO); /* TDataModule: File Type */
USEFORM("personEditU.cpp", frmPersonEdit);
USEFORM("personDM.cpp", dmPersonDAO); /* TDataModule: File Type */
USEFORM("clubEditU.cpp", frmClubEdit);
USEFORM("requestCompetitorsListEditU.cpp", frmRequestCompetitorsListEdit);
USEFORM("competitorDM.cpp", dmCompetitorDAO); /* TDataModule: File Type */
USEFORM("fightVersionDM.cpp", dmFightVersionDAO); /* TDataModule: File Type */
USEFORM("skillDM.cpp", dmSkillDAO); /* TDataModule: File Type */
USEFORM("fightVersionEditU.cpp", frmFightVersionEdit);
USEFORM("skillEditU.cpp", frmSkillEdit);
USEFORM("competitionSelectListU.cpp", frmCompetitionSelectList);
USEFORM("availCategoryEditU.cpp", frmAvailCategoryEdit);
USEFORM("availCategoryDM.cpp", dmAvailCategoryDAO); /* TDataModule: File Type */
USEFORM("categoryEditU.cpp", frmCategoryEdit);
USEFORM("categoryDM.cpp", dmCategoryDAO); /* TDataModule: File Type */
USEFORM("currentStateDM.cpp", dmCurrentState); /* TDataModule: File Type */
USEFORM("reportDataSourceDM.cpp", dmReportDataSource); /* TDataModule: File Type */
USEFORM("categoryReportU.cpp", frmCategoryReport);
USEFORM("categoryTreeReportU.cpp", frmCategoryTreeReport);
USEFORM("uncategoryListReportU.cpp", frmUncategoryListReport);
USEFORM("categoryToPrintSelectU.cpp", frmCategoryToPrintSelect);
USEFORM("competitorPairsReportU.cpp", frmCompetitorPairsReport);
USEFORM("manuallyAddCategoryEditU.cpp", frmManuallyAddCategoryEdit);
USEFORM("resultEnterEditU.cpp", frmResultEnterEdit);
USEFORM("requestClubReportU.cpp", frmRequestClubReport);
USEFORM("resultDM.cpp", dmResultDAO); /* TDataModule: File Type */
USEFORM("competitorCategoryResultEditU.cpp", frmCompetitorCategoryResultEdit);
USEFORM("categoryFinalReportU.cpp", frmCategoryFinalReport);
USEFORM("manualDrawEditU.cpp", frmManualDraw);
USEFORM("availCategoryFullEditU.cpp", frmAvailCategoryFullEdit);
USEFORM("personFullEditU.cpp", frmPersonFullEdit);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TfrmMainForm), &frmMainForm);
         Application->CreateForm(__classid(TdmDataSource), &dmDataSource);
         Application->CreateForm(__classid(TfrmCompetitionEdit), &frmCompetitionEdit);
         Application->CreateForm(__classid(TfrmCompetitionRankEdit), &frmCompetitionRankEdit);
         Application->CreateForm(__classid(TdmCompetitionRankDAO), &dmCompetitionRankDAO);
         Application->CreateForm(__classid(TdmCompetitionDAO), &dmCompetitionDAO);
         Application->CreateForm(__classid(TfrmRequestEdit), &frmRequestEdit);
         Application->CreateForm(__classid(TdmRequestDAO), &dmRequestDAO);
         Application->CreateForm(__classid(TdmClubDAO), &dmClubDAO);
         Application->CreateForm(__classid(TfrmPersonEdit), &frmPersonEdit);
         Application->CreateForm(__classid(TdmPersonDAO), &dmPersonDAO);
         Application->CreateForm(__classid(TfrmClubEdit), &frmClubEdit);
         Application->CreateForm(__classid(TfrmRequestCompetitorsListEdit), &frmRequestCompetitorsListEdit);
         Application->CreateForm(__classid(TdmCompetitorDAO), &dmCompetitorDAO);
         Application->CreateForm(__classid(TdmFightVersionDAO), &dmFightVersionDAO);
         Application->CreateForm(__classid(TdmSkillDAO), &dmSkillDAO);
         Application->CreateForm(__classid(TfrmFightVersionEdit), &frmFightVersionEdit);
         Application->CreateForm(__classid(TfrmSkillEdit), &frmSkillEdit);
         Application->CreateForm(__classid(TfrmCompetitionSelectList), &frmCompetitionSelectList);
         Application->CreateForm(__classid(TfrmAvailCategoryEdit), &frmAvailCategoryEdit);
         Application->CreateForm(__classid(TdmAvailCategoryDAO), &dmAvailCategoryDAO);
         Application->CreateForm(__classid(TfrmCategoryEdit), &frmCategoryEdit);
         Application->CreateForm(__classid(TdmCategoryDAO), &dmCategoryDAO);
         Application->CreateForm(__classid(TdmCurrentState), &dmCurrentState);
         Application->CreateForm(__classid(TdmReportDataSource), &dmReportDataSource);
         Application->CreateForm(__classid(TfrmCategoryReport), &frmCategoryReport);
         Application->CreateForm(__classid(TfrmCategoryTreeReport), &frmCategoryTreeReport);
         Application->CreateForm(__classid(TfrmUncategoryListReport), &frmUncategoryListReport);
         Application->CreateForm(__classid(TfrmCategoryToPrintSelect), &frmCategoryToPrintSelect);
         Application->CreateForm(__classid(TfrmCompetitorPairsReport), &frmCompetitorPairsReport);
         Application->CreateForm(__classid(TfrmManuallyAddCategoryEdit), &frmManuallyAddCategoryEdit);
         Application->CreateForm(__classid(TfrmResultEnterEdit), &frmResultEnterEdit);
         Application->CreateForm(__classid(TfrmRequestClubReport), &frmRequestClubReport);
         Application->CreateForm(__classid(TdmResultDAO), &dmResultDAO);
         Application->CreateForm(__classid(TfrmCompetitorCategoryResultEdit), &frmCompetitorCategoryResultEdit);
         Application->CreateForm(__classid(TfrmCategoryFinalReport), &frmCategoryFinalReport);
         Application->CreateForm(__classid(TfrmManualDraw), &frmManualDraw);
         Application->CreateForm(__classid(TfrmAvailCategoryFullEdit), &frmAvailCategoryFullEdit);
         Application->CreateForm(__classid(TfrmPersonFullEdit), &frmPersonFullEdit);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------







































