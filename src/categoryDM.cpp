//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "categoryDM.h"
#include "availCategoryCtrl.h"
#include "dataSourceDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmCategoryDAO *dmCategoryDAO;
//---------------------------------------------------------------------------
__fastcall TdmCategoryDAO::TdmCategoryDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------

void TdmCategoryDAO::initCategoryTable(void){
    if(ibqCategoryAll->Active){
        ibqCategoryAll->Close(); 
        }
    ibqCategoryAll->SQL->Clear();
    ibqCategoryAll->SQL->Add("select * from Category");
}


void TdmCategoryDAO::getById(int id, TCategory &obj){
AnsiString selectQuery =
"select id, availableCategoryId, fightVersionId, competitionId \
 from Category where id = :id";
    //Создать запрос для получения объектов из базы
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    ibqCategory->ParamByName("id")->AsInteger = id;
    //Получить записи из базы данных
    ibqCategory->Open();
    if(ibqCategory->RecordCount){
        obj.setId(id);
        obj.setAvailCategoryId(ibqCategory->FieldByName("availableCategoryId")->AsInteger);
        obj.setFightVersionId(ibqCategory->FieldByName("fightVersionId")->AsInteger);
        obj.setCompetitionId(ibqCategory->FieldByName("competitionId")->AsInteger);
        }
    //Записи не получены, вернуть null
    else{
        //Обнулить объект
        setmem(&obj, sizeof(obj), 0);
        }
    //Закрыть множество
    ibqCategory->Close(); 
}



void TdmCategoryDAO::store(TCategory &obj){
AnsiString updateQuery =
"update Category set availableCategoryId = :availableCategoryId,\
 fightVersionId = :fightVersionId, competitionId = :competitionId \
 where id = :id";
AnsiString insertQuery =
"insert into Category(availableCategoryId, fightVersionId, competitionId)\
 values(:availableCategoryId, :fightVersionId, :competitionId)";
AnsiString searchIdQuery =
"select id from Category where availableCategoryId=:availableCategoryId and \
 fightVersionId=:fightVersionId and competitionId=:competitionId";
    //Создать запрос для сохранения объекта в базе данных
    ibqCategory->SQL->Clear();
    if(obj.getId() > 0){
        //Обновить
        ibqCategory->SQL->Add(updateQuery);
        ibqCategory->ParamByName("id")->AsInteger = obj.getId();
        }
    else{
        //Добавить
        ibqCategory->SQL->Add(insertQuery);
        }
    ibqCategory->ParamByName("availableCategoryId")->AsInteger = obj.getAvailCategoryId();
    ibqCategory->ParamByName("fightVersionId")->AsInteger = obj.getFightVersionId();
    ibqCategory->ParamByName("competitionId")->AsInteger = obj.getCompetitionId();
    //выполнить запрос
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    ibqCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Выполнить сохранение данных
        dmDataSource->ibtrSecretaryDB->Commit();
        }    
    //Если была добавлена новая запись, узнать ее идентификатор
    if(!obj.getId()){
        //Получить из таблицы последнюю добавленную запись
        ibqCategory->SQL->Clear();
        ibqCategory->SQL->Add(searchIdQuery);                 
        ibqCategory->ParamByName("availableCategoryId")->AsInteger = obj.getAvailCategoryId();
        ibqCategory->ParamByName("fightVersionId")->AsInteger = obj.getFightVersionId();
        ibqCategory->ParamByName("competitionId")->AsInteger = obj.getCompetitionId();
        ibqCategory->Open();
        obj.setId(ibqCategory->FieldByName("id")->AsInteger);
        ibqCategory->Close();        
        }

}


void TdmCategoryDAO::erase(TCategory &obj){
AnsiString deleteQuery =
"delete from Category where id = :id";
    //Создать запрос для сохранения объекта в базе данных
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(deleteQuery);
    ibqCategory->ParamByName("id")->AsInteger = obj.getId();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //выполнить запрос
    ibqCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Выполнить сохранение данных
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}


void TdmCategoryDAO::deleteCategoriesByCompId(int compid){
AnsiString deleteQuery =
"delete from Category where competitionId = :competitionId";
    //Создать запрос для сохранения объекта в базе данных
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(deleteQuery);
    ibqCategory->ParamByName("competitionId")->AsInteger = compid;
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //выполнить запрос
    ibqCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Выполнить сохранение данных
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}


TCategory TdmCategoryDAO::getCurrent(void){
//Возвращаемый объект
TCategory result;
    result.setId(0);    //изначально запись не получена
    //Если таблица открыта, получить текущий объект
    if(ibqCategoryAll->State != dsInactive){
        result.setId(ibqCategoryAll->FieldByName("id")->AsInteger);
        result.setAvailCategoryId(ibqCategoryAll->FieldByName("availableCategoryId")->AsInteger);
        result.setFightVersionId(ibqCategoryAll->FieldByName("fightVersionId")->AsInteger);
        result.setCompetitionId(ibqCategoryAll->FieldByName("competitionId")->AsInteger);
        }
    //Вернуть результат
    return result;
}

void TdmCategoryDAO::makeCurrent(TCategory obj){
int res;
    //Если таблица открыта
    if(ibqCategoryAll->State != dsInactive){
        //Если передан не пустой объект
        if(obj.getId() > 0){
            ibqCategoryAll->Locate("id", obj.getId(), TLocateOptions());
            }
        }
}


TList * TdmCategoryDAO::getByCompetitionId(int competitionId){
AnsiString selectQuery =
"select id, availableCategoryId, fightVersionId \
 from Category where competitionId=:competitionId";
    //Создать запрос для получения объектов из базы
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    //Указать соревнование
    ibqCategory->ParamByName("competitionId")->AsInteger = competitionId;
    //Получить записи из базы данных
    ibqCategory->Open();
    //Создаем объекты по количеству полученных из базы данных
    TList* resultList = new TList();
    resultList->Clear();
    ibqCategory->First();
    for(int i = 0; i < ibqCategory->RecordCount; i++){
        TCategory *result = new TCategory();
        result->setId(ibqCategory->FieldByName("id")->AsInteger);
        result->setAvailCategoryId(ibqCategory->FieldByName("availableCategoryId")->AsInteger);
        result->setFightVersionId(ibqCategory->FieldByName("fightVersionId")->AsInteger);
        result->setCompetitionId(competitionId);
        //Добавить в список
        resultList->Add(result);
        //Перейдем к следующей записи
        ibqCategory->Next();
        }
    //Закрыть множество
    ibqCategory->Close();
    //вернем результирующее множество
    return resultList;
}


TList * TdmCategoryDAO::getExtendedByCompetitionId(int competitionId){
AnsiString selectQuery =
"select \
       cat.id, \
       avcat.id ac_id, \
       avcat.startAge ac_sa, \
       avcat.endAge ac_ea, \
       avcat.startWeight ac_sw, \
       avcat.endWeight ac_ew, \
       avcat.female ac_fem, \
       avcat.comments ac_com, \
       fver.id fv_id, \
       fver.code fv_code, \
       fver.description fv_des, \
       fver.comments fv_com , \
       comp.id c_id, \
       comp.beginDate c_bd, \
       comp.endDate c_ed, \
       comp.competitionRankId c_crid, \
       comp.comments c_com \
       from Category cat, AvailableCategory avcat, FightVersion fver, Competition comp where \
       avcat.id = cat.availableCategoryId and fver.id = cat.fightVersionId \
       and comp.id = cat.competitionId and cat.competitionId = :competitionId";
    //Создать запрос для получения объектов из базы
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    //Указать соревнование
    ibqCategory->ParamByName("competitionId")->AsInteger = competitionId;
    //Получить записи из базы данных
    ibqCategory->Open();

    //Создаем объекты по количеству полученных из базы данных
    TList* resultList = new TList();
    resultList->Clear(); 
    ibqCategory->First();
    //Создать расширенные поля
    TAvailCategory availCategory;
    TFightVersion fightVersion;
    TCompetition competition;
    for(int i = 0; i < ibqCategory->RecordCount; i++){
        //Заполнить структуру (доступные категории)

        availCategory.setId(ibqCategory->FieldByName("ac_id")->AsInteger);
        availCategory.setStartAge(ibqCategory->FieldByName("ac_sa")->AsInteger);
        availCategory.setEndAge(ibqCategory->FieldByName("ac_ea")->AsInteger);
        availCategory.setStartWeight(ibqCategory->FieldByName("ac_sw")->AsFloat);
        availCategory.setEndWeight(ibqCategory->FieldByName("ac_ew")->AsFloat);
        availCategory.setFemale(ibqCategory->FieldByName("ac_fem")->AsString =='T'?true:false);
        availCategory.setComments(ibqCategory->FieldByName("ac_com")->AsString);

        fightVersion.setId(ibqCategory->FieldByName("fv_id")->AsInteger);
        fightVersion.setCode(ibqCategory->FieldByName("fv_code")->AsString);
        fightVersion.setDescription(ibqCategory->FieldByName("fv_des")->AsString);
        fightVersion.setComments(ibqCategory->FieldByName("fv_com")->AsString);

        competition.setId(ibqCategory->FieldByName("id")->AsInteger);
        competition.setBeginDate(ibqCategory->FieldByName("c_bd")->AsDateTime);
        competition.setEndDate(ibqCategory->FieldByName("c_ed")->AsDateTime);
        competition.setCompetitionRankId(ibqCategory->FieldByName("c_crid")->AsInteger);
        competition.setComments(ibqCategory->FieldByName("c_com")->AsString);

        TCategory * result = new TCategory();

        result->setAvailCategoryId(ibqCategory->FieldByName("ac_id")->AsInteger);
        result->setFightVersionId(ibqCategory->FieldByName("fv_id")->AsInteger);
        result->setCompetitionId(competitionId);
        result->setId(ibqCategory->FieldByName("id")->AsInteger);
        //Установим дополнительные поля
        result->extend(availCategory, fightVersion, competition);
        //Добавить в список
        resultList->Add(result);

        //Перейдем к следующей записи
        ibqCategory->Next();
        }
    //Закрыть множество
    ibqCategory->Close();
    //вернем результирующее множество
    return resultList;
}


TList * TdmCategoryDAO::getExtendedByCompetitionIdSurname(int competitionId, AnsiString surname){
AnsiString selectQuery =
"select \
       cat.id, \
       avcat.id ac_id, \
       avcat.startAge ac_sa, \
       avcat.endAge ac_ea, \
       avcat.startWeight ac_sw, \
       avcat.endWeight ac_ew, \
       avcat.female ac_fem, \
       avcat.comments ac_com, \
       fver.id fv_id, \
       fver.code fv_code, \
       fver.description fv_des, \
       fver.comments fv_com , \
       comp.id c_id, \
       comp.beginDate c_bd, \
       comp.endDate c_ed, \
       comp.competitionRankId c_crid, \
       comp.comments c_com \
       from \
       Competitor comptr \
       left join CompetitorToCategory ctc on ctc.competitorId = comptr.id \
       left join Category cat on cat.id = ctc.categoryId \
       left join AvailableCategory avcat on avcat.id = cat.availableCategoryId \
       left join FightVersion fver on fver.id = cat.fightVersionId \
       left join Competition comp on comp.id = cat.competitionId \
       left join Person pers on pers.id = comptr.personId \
       where \
        cat.competitionId = :competitionId \
        and upper(pers.surname) like upper(:surname)";
    //Создать запрос для получения объектов из базы
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    //Указать соревнование
    ibqCategory->ParamByName("competitionId")->AsInteger = competitionId;
    //Фамилия участника
    ibqCategory->ParamByName("surname")->AsString = "%"+surname+"%";
    //Получить записи из базы данных
    ibqCategory->Open();

    //Создаем объекты по количеству полученных из базы данных
    TList* resultList = new TList();
    resultList->Clear();
    ibqCategory->First();
    //Создать расширенные поля
    TAvailCategory availCategory;
    TFightVersion fightVersion;
    TCompetition competition;
    for(int i = 0; i < ibqCategory->RecordCount; i++){
        //Заполнить структуру (доступные категории)

        availCategory.setId(ibqCategory->FieldByName("ac_id")->AsInteger);
        availCategory.setStartAge(ibqCategory->FieldByName("ac_sa")->AsInteger);
        availCategory.setEndAge(ibqCategory->FieldByName("ac_ea")->AsInteger);
        availCategory.setStartWeight(ibqCategory->FieldByName("ac_sw")->AsFloat);
        availCategory.setEndWeight(ibqCategory->FieldByName("ac_ew")->AsFloat);
        availCategory.setFemale(ibqCategory->FieldByName("ac_fem")->AsString =='T'?true:false);
        availCategory.setComments(ibqCategory->FieldByName("ac_com")->AsString);

        fightVersion.setId(ibqCategory->FieldByName("fv_id")->AsInteger);
        fightVersion.setCode(ibqCategory->FieldByName("fv_code")->AsString);
        fightVersion.setDescription(ibqCategory->FieldByName("fv_des")->AsString);
        fightVersion.setComments(ibqCategory->FieldByName("fv_com")->AsString);

        competition.setId(ibqCategory->FieldByName("id")->AsInteger);
        competition.setBeginDate(ibqCategory->FieldByName("c_bd")->AsDateTime);
        competition.setEndDate(ibqCategory->FieldByName("c_ed")->AsDateTime);
        competition.setCompetitionRankId(ibqCategory->FieldByName("c_crid")->AsInteger);
        competition.setComments(ibqCategory->FieldByName("c_com")->AsString);

        TCategory * result = new TCategory();

        result->setAvailCategoryId(ibqCategory->FieldByName("ac_id")->AsInteger);
        result->setFightVersionId(ibqCategory->FieldByName("fv_id")->AsInteger);
        result->setCompetitionId(competitionId);
        result->setId(ibqCategory->FieldByName("id")->AsInteger);
        //Установим дополнительные поля
        result->extend(availCategory, fightVersion, competition);
        //Добавить в список
        resultList->Add(result);

        //Перейдем к следующей записи
        ibqCategory->Next();
        }
    //Закрыть множество
    ibqCategory->Close();
    //вернем результирующее множество
    return resultList;
}

void TdmCategoryDAO::addFightVersionToCompetitor(int competitorId, int categoryId){
//Запрос, который добавляет участнику расширенную боевую версию
AnsiString insertFightVersionQuery =
 "insert into ExtendedFightVersion(competitorId, fightVersionId) \
 select distinct :competitorId, fightVersionId from CompetitorToFightVersion where \
 fightVersionId = (select fightVersionId from Category where id = :categoryId)";


    //Сформируем запрос для конкретного участника
    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(insertFightVersionQuery);    
    ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = competitorId;
    ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = categoryId;

    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //выполнить запрос
    ibqCompetitorToCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Выполнить сохранение данных
        dmDataSource->ibtrSecretaryDB->Commit();
        }

}


void TdmCategoryDAO::setCompetitors(int id, TList * ids){
    //Записать в таблицу связи участника и категории
AnsiString insertQuery =
"insert into CompetitorToCategory(categoryId, competitorId) \
 values(:categoryId, :competitorId)";

//Запрос для добавления признака распределения в боевой версии участника
AnsiString updateQuery =
"update CompetitorToFightVersion set destributed = 'T' where \
 competitorId = :competitorId and fightVersionId = (select fightVersionId from \
 Category where id = :categoryId)";

//Запрос, который добавляет участнику боевую версию, при добавлении в категорию
//с неопределенной для пользователя боевой версией
AnsiString insertFightVersionQuery_1 =
 "insert into CompetitorToFightVersion(competitorId, fightVersionId, destributed) \
 select distinct ";
AnsiString insertFightVersionQuery_2 =  ", fightVersionId, 'T' from CompetitorToFightVersion where \
 fightVersionId = (select fightVersionId from Category where id = "+ IntToStr(id) +")";
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    for(int i=0; i < ids->Count; i++){
        try{
            //Пытаемся добавить новую боевую версию участнику
            ibqCompetitorToCategory->SQL->Clear();
            //Сформируем запрос для конкретного участника
            ibqCompetitorToCategory->SQL->Add(insertFightVersionQuery_1 +
                                              IntToStr(((TCompetitor*)ids->Items[i])->getId()) +
                                              insertFightVersionQuery_2);

            try{
                ibqCompetitorToCategory->ExecSQL();
                //Если новая боевая версия была добавлена - сообщим об этом
                if(MessageDlg("Участник <" +((TCompetitor*)ids->Items[i])->getPerson().getSurname() + "> добавляется в категорию, с боевой версией, не указанной в заявке!\n"+
                        "Добавить в заявку новую боевую версию?" ,
                        mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0)==mrYes){
                    //Добавить участника и боевую версию в таблицу с добавленными версиями
                    addFightVersionToCompetitor(((TCompetitor*)ids->Items[i])->getId(), id);
                    //После добавления, открыть транзакцию заново 
                    if(!dmDataSource->ibtrSecretaryDB->Active){
                        dmDataSource->ibtrSecretaryDB->StartTransaction();
                        }
                    }
                else{
                    //"Откатить" результат вставки
                    if(dmDataSource->ibtrSecretaryDB->Active){
                        dmDataSource->ibtrSecretaryDB->Rollback();
                        }
                    dmDataSource->ibtrSecretaryDB->StartTransaction();
                    //Продолжить добавлять участников
                    continue;
                    }
                }
            catch(EIBInterBaseError *e){
                //Для участника определена боевая версия в заявке, обновить ее распределеение
                ibqCompetitorToCategory->SQL->Clear();
                ibqCompetitorToCategory->SQL->Add(updateQuery);
                //Установим значение идентификатора категории
                ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = id;
                //Добавить недостающий параметр и вставить запись
                ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = ((TCompetitor*)ids->Items[i])->getId();
                ibqCompetitorToCategory->ExecSQL();
                }

            ibqCompetitorToCategory->SQL->Clear();
            ibqCompetitorToCategory->SQL->Add(insertQuery);
            //Установим значение идентификатора категории
            ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = id;
            //Добавить недостающий параметр и вставить запись
            ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = ((TCompetitor*)ids->Items[i])->getId();
            ibqCompetitorToCategory->ExecSQL();
            }
        catch(EIBInterBaseError *e){
            //"Откатить" результат вставки
            if(dmDataSource->ibtrSecretaryDB->Active){
                dmDataSource->ibtrSecretaryDB->Rollback();
                }
            dmDataSource->ibtrSecretaryDB->StartTransaction();
            MessageDlg("Попытка передать участника в категорию, в которой он уже присутствует!\nПередача не выполнена!",
                        mtWarning, TMsgDlgButtons() << mbOK, 0);

            }
        }
    //Выполнить сохранение данных
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}


void TdmCategoryDAO::addCompetitor(int idCompetitor, int idCategory){
    //Записать в таблицу связи участника и категории
AnsiString insertQuery =
"insert into CompetitorToCategory(competitorId, categoryId) \
values(:competitorId, :categoryId)";
//Запрос для добавления признака распределения в боевой версии участника
AnsiString updateQuery =
"update CompetitorToFightVersion set destributed = 'T' where \
 competitorId = :competitorId and fightVersionId = (select fightVersionId from \
 Category where id = :categoryId)";


    //Добавить участника в категорию

    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }

    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(insertQuery);

    //Установить идентификатор участника
    ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = idCompetitor;
    //Установим значение идентификатора категории
    ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = idCategory;

    //выполнить запрос
    ibqCompetitorToCategory->ExecSQL();

    //Сделать отметку о том, что участника распределили
    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(updateQuery);

    //Установить идентификатор участника
    ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = idCompetitor;
    //Установим значение идентификатора категории
    ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = idCategory;
    //Добавить участника в категорию
    ibqCompetitorToCategory->ExecSQL();


    if(dmDataSource->ibtrSecretaryDB->Active){
        //Выполнить сохранение данных
        dmDataSource->ibtrSecretaryDB->Commit();
        }

}




TList* TdmCategoryDAO::getCompetitors(int id){
//Запрос на получение идентификаторов участников по категории
AnsiString selectQuery =
"select competitorId from CompetitorToCategory where \
 CategoryId = :CategoryId";

    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(selectQuery);

    //Установим значение идентификатора категории
    ibqCompetitorToCategory->ParamByName("CategoryId")->AsInteger = id;
    //Прочитаем список и определим сколько записей получено
    ibqCompetitorToCategory->Open();
    ibqCompetitorToCategory->First();

    TList *resultList = new TList();
    resultList->Clear();
    for(int i=0; i < ibqCompetitorToCategory->RecordCount; i++){
        TCompetitor *result = new TCompetitor();
        //Получить версию с заданным идентификатором
        result->getById(
                    ibqCompetitorToCategory->FieldByName("competitorId")->AsInteger);
        //Добавить в список
        resultList->Add(result);
        //К следующей записи
        ibqCompetitorToCategory->Next();
        }
    //Закрыть множество
    ibqCompetitorToCategory->Close();
    return resultList;
}


int TdmCategoryDAO::getCompetitorsAmount(int id){
int result = 0;
//Запрос на получение количества участников в категории
AnsiString selectQuery =
"select count(competitorId) from CompetitorToCategory where \
 CategoryId = :CategoryId";

    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(selectQuery);

    //Установим значение идентификатора категории
    ibqCompetitorToCategory->ParamByName("CategoryId")->AsInteger = id;
    //Прочитаем список и определим сколько записей получено
    ibqCompetitorToCategory->Open();
    ibqCompetitorToCategory->First();
    if(ibqCompetitorToCategory->RecordCount){
        result =  ibqCompetitorToCategory->FieldByName("count")->AsInteger;
        ibqCompetitorToCategory->Close();
        }
    return result;
}




void TdmCategoryDAO::eraseCompetitors(int id, TList *ids){

    //Получисть спосок удаляемых участников
    AnsiString idList;
    for(int i=0; i < ids->Count - 1; i++){
        idList+=IntToStr(((TCompetitor*)ids->Items[i])->getId()) + ",";
        }
    idList += IntToStr(((TCompetitor*)ids->Items[ids->Count-1])->getId());


//Запрос на удаление участников для категории
AnsiString deleteQuery =
"delete from CompetitorToCategory where \
 categoryId = :categoryId and competitorId in (" + idList + ")";

//Запрос для добавления признака распределения в боевой версии участника
AnsiString updateQuery =
"update CompetitorToFightVersion set destributed = 'F' where \
 competitorId in ("+ idList +") and fightVersionId = (select fightVersionId from \
 Category where id = :categoryId)";


    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(deleteQuery);

    //Установим значение идентификатора категории
    ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = id;
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //Выполняем запрос на удаление записей
    ibqCompetitorToCategory->ExecSQL();

    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(updateQuery);

    //Установим значение идентификатора категории
    ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = id;
    //Выполняем запрос на удаление записей
    ibqCompetitorToCategory->ExecSQL();
    //Выполнить сохранение данных
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}

bool TdmCategoryDAO::putCompetitor(double weight, int age, bool female,
                                    int fightVersionId, int competitionId, int competitorId){

bool added = false;

//Запрос на определение категории
AnsiString selectQuery =
"select cat.id from Category cat, AvailableCategory avcat where cat.availableCategoryId = avcat.id and \
 avcat.startWeight < :weight and avcat.endWeight >= :weight and avcat.startAge <= :age and \
 avcat.endAge >= :age and avcat.female = :female and cat.competitionId = :competitionId and \
 cat.fightVersionId = :fightVersionId";

    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    //Определить параметры
    ibqCategory->ParamByName("weight")->AsFloat = weight;
    ibqCategory->ParamByName("age")->AsInteger = age;
    ibqCategory->ParamByName("female")->AsString = (female?'T':'F');
    ibqCategory->ParamByName("competitionId")->AsInteger = competitionId;
    ibqCategory->ParamByName("fightVersionId")->AsInteger = fightVersionId;
    //Выполнить запрос
    ibqCategory->Open();
    ibqCategory->First();
    //Была ли получена категория
    if(ibqCategory->RecordCount){
        addCompetitor(competitorId, ibqCategory->FieldByName("id")->AsInteger);
        //Участник добавлен в категорию
        added = true;
        }
    ibqCategory->Close();
    //Не получили созданную категорию
    return added;
}


TList* TdmCategoryDAO::getSortionDataByCategory(int id){
//Результаты запроса
TList * resultList = new TList();
resultList->Clear();

//Запрос на получение данных для жеребьевки по категории
AnsiString selectQuery =
"select \
   ctc.competitorId, \
   sk.weight skillWeight, \
   req.clubId \
from \
   CompetitorToCategory ctc, \
   Competitor cpt, \
   Skill sk, \
   Request req \
where \
   cpt.id = ctc.competitorId and \
   sk.id = cpt.skillId and \
   req.id = cpt.requestId and \
   ctc.categoryId = :categoryId \
order by  req.clubId asc, sk.weight desc";

    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    //Определить параметры
    ibqCategory->ParamByName("categoryId")->AsInteger = id;
    //Выполнить запрос
    ibqCategory->Open();
    ibqCategory->First();
    //Была ли получены данные

    //Получим результирующее множество
    for(int i=0; i < ibqCategory->RecordCount ; i++){
        TSortionData* result = new TSortionData();
        result->competitorId = ibqCategory->FieldByName("competitorId")->AsInteger;
        result->skillWeight = ibqCategory->FieldByName("skillWeight")->AsInteger;
        result->clubId = ibqCategory->FieldByName("clubId")->AsInteger;

        //Добавить в список
        resultList->Add(result);

        //К следующей записи
        ibqCategory->Next();
        }
    //Закрыть множество
    ibqCategory->Close();
    //Вернуть полученные (или не полученные) данные
    return resultList;
}


void TdmCategoryDAO::storeSortionOrder(int id, int *sortionOrder, int amnt){
//Запрос на установку номеров жеребьевки
AnsiString updateQuery =
"update CompetitorToCategory ctc set sortion=:sortion where \
  ctc.competitorId=:competitorId and ctc.categoryId = :categoryId";

  //Сформируем запрос
  ibqCompetitorToCategory->SQL->Clear();
  ibqCompetitorToCategory->SQL->Add(updateQuery);
  //Зададим парамет - категория
  ibqCompetitorToCategory->ParamByName("categoryId")->AsInteger = id;

  //Проходимся по списку участников и присваиваем порядок жеребьевки
    //Выполнить установку номера
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
  for(int sn = 0; sn < amnt; sn++){
    //Выбираем участника
    ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = sortionOrder[sn];
    ibqCompetitorToCategory->ParamByName("sortion")->AsInteger = sn + 1;
    ibqCompetitorToCategory->ExecSQL();
    }
  //Выполнить сохранение данных
  if(dmDataSource->ibtrSecretaryDB->Active){
    dmDataSource->ibtrSecretaryDB->Commit();
    }
}


void TdmCategoryDAO::uncategory(int competitorId){
//Запрос на удаление участника из категорий
AnsiString deleteQuery =
"delete from CompetitorToCategory where \
 competitorId = :competitorId";

    ibqCompetitorToCategory->SQL->Clear();
    ibqCompetitorToCategory->SQL->Add(deleteQuery);

    //Установим значение идентификатора участника
    ibqCompetitorToCategory->ParamByName("competitorId")->AsInteger = competitorId;
    if(!dmDataSource->ibtrSecretaryDB->Active){
        //Запомнить в базе
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //Выполняем запрос на удаление записей
    ibqCompetitorToCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Запомнить в базе
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}


void TdmCategoryDAO::setDrawType(TCategory category, char drawType){
AnsiString updateQuery = "update category set drawtype=:drawType where id=:categoryId";
    //Создать запрос для сохранения объекта в базе данных
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(updateQuery);
    ibqCategory->ParamByName("categoryId")->AsInteger = category.getId();
    ibqCategory->ParamByName("drawType")->AsString = drawType;
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //выполнить запрос
    ibqCategory->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Выполнить сохранение данных
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}

char TdmCategoryDAO::getDrawType(TCategory category){
AnsiString selectQuery =
"select drawtype from Category where id = :id";
    //Создать запрос для получения объектов из базы
    ibqCategory->SQL->Clear();
    ibqCategory->SQL->Add(selectQuery);
    ibqCategory->ParamByName("id")->AsInteger = category.getId();
    //Получить записи из базы данных
    ibqCategory->Open();
    char result;
    if(ibqCategory->RecordCount){
        if(!ibqCategory->FieldByName("drawtype")->AsString.IsEmpty()){
            result = ibqCategory->FieldByName("drawtype")->AsString[1];
            }
        }
    //Закрыть множество
    ibqCategory->Close();

    return result;
}


