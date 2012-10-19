//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "categoryTreeReportU.h"
#include "reportDataSourceDM.h"
#include "currentStateDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//Позиции элементов вывода для дерева на 16 участников
int Pos_16[16][2]=
{
{0, 20},    //1
{556, 20},  //2
{0, 323},   //3
{556, 323}, //4
{0, 171},   //5
{556, 171}, //6
{0, 474},   //7
{556, 474}, //8
{0, 116},   //9
{556, 116}, //10
{0, 264},   //11
{556, 264}, //12
{0, 411},   //13
{556, 411}, //14
{0, 562},   //15
{556, 562}  //16
};

//Позиции элементов вывода для дерева на 32 участников
int Pos_32[32][2]=
{
{0, 4},     //1
{572, 4},   //2
{0, 324},   //3
{572, 324}, //4
{0, 169},   //5
{572, 169}, //6
{0, 485},   //7
{572, 485}, //8
{0, 89},    //9
{572, 89},  //10
{0, 244},   //11
{572, 244}, //12
{0, 404},   //13
{572, 404}, //14
{0, 564},   //15
{572, 564}, //16
{0, 61},    //17
{572, 61},  //18
{0, 141},   //19
{572, 141}, //20
{0, 217},   //21
{572, 217}, //22
{0, 298},   //23
{572, 298}, //24
{0, 377},   //25
{572, 377}, //26
{0, 457},   //27
{572, 457}, //28
{0, 537},   //29
{572, 537}, //30
{0, 617},   //31
{572, 617}  //32
};



TfrmCategoryTreeReport *frmCategoryTreeReport;
//---------------------------------------------------------------------------
__fastcall TfrmCategoryTreeReport::TfrmCategoryTreeReport(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------


void TfrmCategoryTreeReport::PreviewFightTrees(TList *categories){
    //Установим выборку категорий для текущих соревнований
//    dmReportDataSource->setCategoriesToPrintByCompetition(dmCurrentState->getCompetition().getId());
    dmReportDataSource->setCategoriesFromList(categories);
    //Напечатать протоколы категорий
    qrTreeCategory->Preview();
}    




void __fastcall TfrmCategoryTreeReport::qrdbtFemalePrint(TObject *sender,
      AnsiString &Value)
{
  if(Value=="T"){
        Value  = "Ж";
        }
    else{
        Value = "";
        }
}
//---------------------------------------------------------------------------


void __fastcall TfrmCategoryTreeReport::qrbCategoryTreeBeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
    //Признак дереве на 32 участника
    bool is32tree = dmReportDataSource->ibqRepCompetitorDetail->RecordCount > 16;
    if(dmReportDataSource->ibqRepCompetitorDetail->RecordCount && !(dmReportDataSource->ibqRepCompetitorDetail->RecordCount > 32)){
        //Выбираем нужное дерево
        if(!is32tree){
            //Спозиционировать дерево
            qrimCategoryTree_16->Left = 0;
            qrimCategoryTree_16->Top = 50;
            qrimCategoryTree_16->Width = qrbCategoryTree->ClientWidth;
            qrimCategoryTree_16->Height = qrbCategoryTree->ClientHeight * 0.7;
            qrimAdditionTreeCategory_16->Left = 0;
            qrimAdditionTreeCategory_16->Top = qrbCategoryTree->ClientHeight * 0.7 + 50;
            qrimAdditionTreeCategory_16->Width = qrbCategoryTree->ClientWidth;
            qrimAdditionTreeCategory_16->Height = qrbCategoryTree->ClientHeight * 0.3 - 75;
            qrimCategoryTree_32->Enabled = false;
            qrimAdditionTreeCategory_32->Enabled = false;
            qrimCategoryTree_16->Enabled = true;
            qrimAdditionTreeCategory_16->Enabled = true;
            }
        else{
            //Спозиционировать дерево
            qrimCategoryTree_32->Left = 0;
            qrimCategoryTree_32->Top = 20;
            qrimCategoryTree_32->Width = qrbCategoryTree->ClientWidth;
            qrimCategoryTree_32->Height = qrbCategoryTree->ClientHeight * 0.8;

            qrimAdditionTreeCategory_32->Left = 0;
            qrimAdditionTreeCategory_32->Top = qrbCategoryTree->ClientHeight * 0.8 + 20;
            qrimAdditionTreeCategory_32->Width = qrbCategoryTree->ClientWidth;
            qrimAdditionTreeCategory_32->Height = qrbCategoryTree->ClientHeight * 0.2  - 40;
            qrimCategoryTree_16->Enabled = false;
            qrimAdditionTreeCategory_16->Enabled = false;
            qrimCategoryTree_32->Enabled = true;
            qrimAdditionTreeCategory_32->Enabled = true;
            }

        //Расставить на дереве участников текущей категории
        dmReportDataSource->ibqRepCompetitorDetail->First();
        int position = 1;
        while(!dmReportDataSource->ibqRepCompetitorDetail->Eof){



            //Получить атрибуты участника
            AnsiString skill = dmReportDataSource->ibqRepCompetitorDetail->FieldByName("shortdescription")->AsString;
            AnsiString ptr = dmReportDataSource->ibqRepCompetitorDetail->FieldByName("patronymic")->AsString.SubString(1,1);
            ptr += (ptr.Length()>0)? "." : " ";
            AnsiString snp = dmReportDataSource->ibqRepCompetitorDetail->FieldByName("surname")->AsString + " " +
                     dmReportDataSource->ibqRepCompetitorDetail->FieldByName("name")->AsString.SubString(1,1) + "." +
                     " " + ptr;
            AnsiString club = dmReportDataSource->ibqRepCompetitorDetail->FieldByName("shortName")->AsString;



             //Получить метку для фамилии имени отчества
             TQRLabel * qrlabel = (TQRLabel*)qrlSNF_1->Owner->FindComponent("qrlSNF_" + IntToStr(position));
             //установить элемент вывода на нужну позицию
             if(!is32tree){
                 qrlabel->Left = Pos_16[position - 1][0];
                 qrlabel->Top = Pos_16[position - 1][1];
                 qrlabel->Font->Size = 11;
                 }
             else{
                 qrlabel->Left = Pos_32[position - 1][0];
                 qrlabel->Top = Pos_32[position - 1][1];
                 qrlabel->Font->Size = 9;
                }
             qrlabel->Caption = snp ;
             qrlabel->Enabled = true ;
             //Получить метку для разряда
             qrlabel = (TQRLabel*)qrlSNF_1->Owner->FindComponent("qrlSkill_" + IntToStr(position));
             if(!is32tree){
                 qrlabel->Left = Pos_16[position - 1][0];
                 qrlabel->Top = Pos_16[position - 1][1] + 17;
                 qrlabel->Font->Size = 6;
                 qrlabel->Enabled = true ;
                }
             else{
                 qrlabel->Left = Pos_32[position - 1][0];
                 qrlabel->Top = Pos_32[position - 1][1] - 13;
                 qrlabel->Font->Size = 6;
                 qrlabel->Enabled = false;
                }
             qrlabel->Caption = skill ;

             //Получить метку для клуба
             qrlabel = (TQRLabel*)qrlSNF_1->Owner->FindComponent("qrlClub_"+ IntToStr(position));
             if(!is32tree){
                 qrlabel->Left = Pos_16[position - 1][0];
                 qrlabel->Top = Pos_16[position - 1][1] + 30;
                 qrlabel->Font->Size = 8;
                qrlabel->Enabled = true;
                }
             else{
                 qrlabel->Left = Pos_32[position - 1][0];
                 qrlabel->Top = Pos_32[position - 1][1] + 13;
                 qrlabel->Font->Size = 6;
                 qrlabel->Enabled = true;
                }
             qrlabel->Caption = club;


            //Перейти к следующей позиции
            position++;
            dmReportDataSource->ibqRepCompetitorDetail->Next();
            }

        //Остальные позиции обнуляем
        for(int i = 32; i >= position; i-- ){
             TQRLabel * qrlabel = (TQRLabel*)qrlSNF_1->Owner->FindComponent("qrlSNF_" + IntToStr(i));
             qrlabel->Enabled = false;
             //Получить метку для разряда
             qrlabel = (TQRLabel*)qrlSNF_1->Owner->FindComponent("qrlSkill_" + IntToStr(i));
             qrlabel->Enabled = false;
             //Получить метку для клуба
             qrlabel = (TQRLabel*)qrlSNF_1->Owner->FindComponent("qrlClub_"+ IntToStr(i));
             qrlabel->Enabled = false;
            }

        PrintBand=true;
        }
    else
        PrintBand = false;
}
//---------------------------------------------------------------------------



void __fastcall TfrmCategoryTreeReport::qrdbtCategoryStartWeightPrint(
      TObject *sender, AnsiString &Value)
{
    //Если печатается значение 0 - заменить его словом ДО
    if(StrToInt(Value) < 1){
        Value = "до";
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCategoryTreeReport::qrdbtCategoryEndWeightPrint(
      TObject *sender, AnsiString &Value)
{
    //Если указан большой вес, заменим на "и выше"
    if(StrToInt(Value) > 450){
        Value = "и выше"; 
        }
}
//---------------------------------------------------------------------------



