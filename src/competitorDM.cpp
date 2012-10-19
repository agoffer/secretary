//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dataSourceDM.h"
#include "competitorDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmCompetitorDAO *dmCompetitorDAO;

//Функция обратного вызова - скроллинг по таблице
CallbackFunction CompetitorScrollCallback;

//---------------------------------------------------------------------------
__fastcall TdmCompetitorDAO::TdmCompetitorDAO(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------


void TdmCompetitorDAO::initCompetitorTable(void){
    if(ibqCompetitorAll->Active){
        ibqCompetitorAll->Close();
        }
    ibqCompetitorAll->SQL->Clear();
    ibqCompetitorAll->SQL->Add("select * from Competitor");
}

void TdmCompetitorDAO::initExtendedCompetitorTable(void){
    if(ibqCompetitorExtendedTable->Active){
        ibqCompetitorExtendedTable->Close();
        }
AnsiString selectQuery =
"select (Date 'now' - Person.dob) / 365 age, \
       Person.id pers_id, \
       Person.surname, \
       Person.name pers_name, \
       Person.patronymic, \
       Person.female, \
       Skill.id skill_id, \
       Skill.shortDescription, \
       Club.shortName, \
       Competitor.id comp_id, \
       Competitor.weight \
from \
       Competitor, Skill, Person, Request, Club, Competition \
where \
       Person.id = Competitor.personId and Skill.id = Competitor.skillId \
       and Club.id = Request.clubId and Competitor.requestId = Request.id and \
       Request.competitionId = Competition.id";
    ibqCompetitorExtendedTable->SQL->Clear();
    ibqCompetitorExtendedTable->SQL->Add(selectQuery);
}


void TdmCompetitorDAO::selectFromCompetitorTable(AnsiString filter){
    //Формируем обычный запрос
    initExtendedCompetitorTable();
    //Добавим условия выборки и сортировки
    if(filter.Trim()!="")
        ibqCompetitorExtendedTable->SQL->Add("and " + filter);
    //Выполнить выборку с установленными условиями
    ibqCompetitorExtendedTable->Open();
}


AnsiString TdmCompetitorDAO::getFieldName(CompetitorTableField field){
    switch(field){
        case ctfSurname : return "Person.surname";
        case ctfClub_Name : return "Club.name";
        //Не определно поле
        default: return "";
        }
}


void TdmCompetitorDAO::filterByField(int competitionId, CompetitorTableField field_1,
                                     CompetitorTableField field_2){
    //Получим строковое представление поля
    AnsiString asField_1 = getFieldName(field_1);
    AnsiString asField_2 = getFieldName(field_2);
    AnsiString condition = "Competition.id = " + IntToStr(competitionId);
    if(asField_1.Trim()!=""){
        //Формируем строку с условием
        condition += " and "  + asField_1 + " like '%" + filterCondition_1 + "%'";
        }
    if(asField_2.Trim()!=""){
        //Формируем строку с условием
        condition += " and " + asField_2 + " like '%" + filterCondition_2 + "%'";
        }
    condition += "order by shortName";
    //Выполнить выборку с установленным условием
    selectFromCompetitorTable(condition);
    //Сбросить условие фильтрации
    filterCondition_1 = "";
    filterCondition_2 = "";
    //Запомним, по какому поля выполнялась фильтрация
    filteredField_1 = field_1;
    filteredField_2 = field_2;
}



void TdmCompetitorDAO::store(TCompetitor &obj){
AnsiString updateQuery =
"update Competitor set requestId = :requestId,\
 skillId = :skillId, personId = :personId, weight = :weight\
 where id = :id";
AnsiString insertQuery =
"insert into Competitor(requestId, skillId, personId, weight)\
 values(:requestId, :skillId, :personId, :weight)";
AnsiString searchIdQuery =
"select id from Competitor where requestId=:requestId and skillId=:skillId and \
 personId=:personId and weight=:weight";

 AnsiString blankResultQuery = "insert into result(competitorId, competitionentryid, rank) \
 values(:competitorId, 1, 0)"; 

    //Создать запрос для сохранения объекта в базе данных
    ibqCompetitor->SQL->Clear();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    if(obj.getId() > 0){
        //Обновить
        ibqCompetitor->SQL->Add(updateQuery);
        ibqCompetitor->ParamByName("id")->AsInteger = obj.getId();
        }
    else{
        //Добавить
        ibqCompetitor->SQL->Add(insertQuery);
        }
    ibqCompetitor->ParamByName("requestId")->AsInteger = obj.getRequestId();
    ibqCompetitor->ParamByName("skillId")->AsInteger = obj.getSkillId();
    ibqCompetitor->ParamByName("personId")->AsInteger = obj.getPersonId();
    ibqCompetitor->ParamByName("weight")->AsFloat = obj.getWeight();
    //выполнить запрос
    ibqCompetitor->ExecSQL();
    //Сохранить данные
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
    //Если была добавлена новая запись, узнать ее идентификатор
    if(!obj.getId()){
        //Получить из таблицы последнюю добавленную запись
        ibqCompetitor->SQL->Clear();
        ibqCompetitor->SQL->Add(searchIdQuery);
        ibqCompetitor->ParamByName("requestId")->AsInteger = obj.getRequestId();
        ibqCompetitor->ParamByName("skillId")->AsInteger = obj.getSkillId();
        ibqCompetitor->ParamByName("personId")->AsInteger = obj.getPersonId();
        ibqCompetitor->ParamByName("weight")->AsFloat = obj.getWeight();
        ibqCompetitor->Open();
        obj.setId(ibqCompetitor->FieldByName("id")->AsInteger);
        ibqCompetitor->Close();
        //Установить пустой результат для участника
        ibqCompetitor->SQL->Clear();
//        ibqCompetitor->SQL->Add(blankResultQuery);
//        ibqCompetitor->ParamByName("competitorId")->AsInteger = obj.getId();
//        if(!dmDataSource->ibtrSecretaryDB->Active){
//            dmDataSource->ibtrSecretaryDB->StartTransaction();
//            }
//        ibqCompetitor->ExecSQL();
        //Сохранить данные
//        if(dmDataSource->ibtrSecretaryDB->Active){
//            dmDataSource->ibtrSecretaryDB->Commit();
//            }
        }
}


void TdmCompetitorDAO::erase(TCompetitor &obj){
    //Удалить список боевыех версий, для участника
    eraseFightVersion(obj.getId());

AnsiString deleteQuery =
"delete from Competitor where id = :id";
    //Создать запрос для сохранения объекта в базе данных
    ibqCompetitor->SQL->Clear();
    ibqCompetitor->SQL->Add(deleteQuery);
    ibqCompetitor->ParamByName("id")->AsInteger = obj.getId();
    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //выполнить запрос
    ibqCompetitor->ExecSQL();
    //Сохранить данные
    if(dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}




TCompetitor TdmCompetitorDAO::getCurrent(void){
//Возвращаемый объект
TCompetitor result;
    result.setId(0);    //изначально запись не получена
    //Если таблица открыта, получить текущий объект
    if(ibqCompetitorAll->State != dsInactive){
        result.setId(ibqCompetitorAll->FieldByName("id")->AsInteger);
        result.setRequestId(ibqCompetitorAll->FieldByName("requestId")->AsInteger);
        result.setSkillId(ibqCompetitorAll->FieldByName("skillId")->AsInteger);
        result.setPersonId(ibqCompetitorAll->FieldByName("personId")->AsInteger);
        result.setWeight(ibqCompetitorAll->FieldByName("weight")->AsFloat);
        }
    //Вернуть результат
    return result;
}

void TdmCompetitorDAO::makeCurrent(TCompetitor obj){
int res;
    if(ibqCompetitorAll->Active){
        //Если передан не пустой объект
        if(obj.getId() > 0){
            ibqCompetitorAll->Locate("id", obj.getId(), TLocateOptions());
            }
        }
}


TCompetitor TdmCompetitorDAO::getExtendedTableCurrent(void){
//Возвращаемый объект
TCompetitor result;
    result.setId(0);    //изначально запись не получена
    //Если таблица открыта, получить текущий объект
    if(ibqCompetitorExtendedTable->State != dsInactive){
        result.setId(ibqCompetitorExtendedTable->FieldByName("comp_id")->AsInteger);
//        result.setRequestId(ibqCompetitorExtendedTable->FieldByName("requestId")->AsInteger);
        result.setSkillId(ibqCompetitorExtendedTable->FieldByName("skill_id")->AsInteger);
        result.setPersonId(ibqCompetitorExtendedTable->FieldByName("pers_id")->AsInteger);
        result.setWeight(ibqCompetitorExtendedTable->FieldByName("weight")->AsFloat);
        }
    //Вернуть результат
    return result;
}

void TdmCompetitorDAO::makeExtendedTableCurrent(TCompetitor obj){
int res;
    if(ibqCompetitorExtendedTable->Active){
        //Если передан не пустой объект
        if(obj.getId() > 0){
            ibqCompetitorExtendedTable->Locate("comp_id", obj.getId(), TLocateOptions());
            }
        }
}





TList * TdmCompetitorDAO::getByRequestId(int requestId){
AnsiString selectQuery =
"select id, skillId, personId,weight\
 from Competitor where requestId=:requestId";
    //Создать запрос для получения объектов из базы
    ibqCompetitor->SQL->Clear();
    ibqCompetitor->SQL->Add(selectQuery);
    //Указать соревнование
    ibqCompetitor->ParamByName("requestId")->AsInteger;
    //Получить записи из базы данных
    ibqCompetitor->Open();
    //Создаем объекты по количеству полученных из базы данных
    TList* resultList = new TList();
    resultList->Clear(); 
    ibqCompetitor->First();
    for(int i = 0; i < ibqCompetitor->RecordCount; i++){
        TCompetitor *result= new TCompetitor();
        result->setId(ibqCompetitor->FieldByName("id")->AsInteger);
        result->setSkillId(ibqCompetitor->FieldByName("skillId")->AsInteger);
        result->setPersonId(ibqCompetitor->FieldByName("personId")->AsInteger);
        result->setWeight(ibqCompetitor->FieldByName("weight")->AsFloat);
        result->setRequestId(requestId);
        //Добавить в список
        resultList->Add(result);
        //Перейдем к следующей записи
        ibqCompetitor->Next();
        }
    //Закрыть множество
    ibqCompetitor->Close();
    //вернем результирующее множество
    return resultList;
}

TList * TdmCompetitorDAO::getByCompetitionId(int competitionId){
AnsiString selectQuery =
"select comp.id, comp.skillId, comp.personId, comp.requestId, comp.weight\
 from Competitor comp,Request req where comp.requestId=req.id and req.competitionId = :competitionId";
    //Создать запрос для получения объектов из базы
    ibqCompetitor->SQL->Clear();
    ibqCompetitor->SQL->Add(selectQuery);
    //Указать соревнование
    ibqCompetitor->ParamByName("competitionId")->AsInteger = competitionId;
    //Получить записи из базы данных
    ibqCompetitor->Open();
    //Создаем объекты по количеству полученных из базы данных
    TList* resultList = new TList();
    resultList->Clear(); 
    ibqCompetitor->First();
    for(int i = 0; i < ibqCompetitor->RecordCount; i++){
        TCompetitor *result = new TCompetitor();
        result->setId(ibqCompetitor->FieldByName("id")->AsInteger);
        result->setSkillId(ibqCompetitor->FieldByName("skillId")->AsInteger);
        result->setPersonId(ibqCompetitor->FieldByName("personId")->AsInteger);
        result->setWeight(ibqCompetitor->FieldByName("weight")->AsFloat);
        result->setRequestId(ibqCompetitor->FieldByName("requestId")->AsInteger);
        //Добавить в список
        resultList->Add(result);
        //Перейдем к следующей записи
        ibqCompetitor->Next();
        }
    //Закрыть множество
    ibqCompetitor->Close();
    //вернем результирующее множество
    return resultList;
}



void TdmCompetitorDAO::formTableByRequestId(int requestId){
    if(ibqCompetitorExtendedTable->Active){
        ibqCompetitorExtendedTable->Close();
        }
    //Определить параметр,
    ibqCompetitorExtendedTable->ParamByName("requestId")->AsInteger;
    //Получить таблицу
    ibqCompetitorExtendedTable->Open();
}


TList * TdmCompetitorDAO::getExtendedByCompetitionId(int competitionId){
AnsiString selectQuery =
"select \
       Skill.id, \
       Skill.shortDescription, \
       Skill.fullDescription, \
       Skill.weight, \
       Skill.comments, \
       Person.id, \
       Person.surname, \
       Person.name, \
       Person.patronymic, \
       Person.dob, \
       Person.phone, \
       Person.female, \
       Person.additions, \
       Request.id, \
       Request.personId, \
       Request.clubId, \
       Request.competitionId, \
       Request.comments, \
       Competitor.id, \
       Competitor.weight \
       from Competitor, Skill, Person, Request where \
       Person.id = Competitor.personId and Skill.id = Competitor.skillId \
       and Request.id = Competitor.requestId and Competitor.requestId = Request.id \
       and Request.competitionId = :competitionId";
    //Создать запрос для получения объектов из базы
    ibqCompetitor->SQL->Clear();
    ibqCompetitor->SQL->Add(selectQuery);
    //Указать соревнование
    ibqCompetitor->ParamByName("competitionId")->AsInteger = competitionId;
    //Получить записи из базы данных
    ibqCompetitor->Open();

    //Создаем объекты по количеству полученных из базы данных
    TList* resultList = new TList();
    resultList->Clear();
    ibqCompetitor->First();
    //Создать расширенные поля
    TPerson person;
    TSkill skill;
    TRequest request;
    for(int i = 0; i < ibqCompetitor->RecordCount; i++){
        //Заполнить структуру
        person.setId(ibqCompetitor->FieldByName("id1")->AsInteger);
        person.setSurname(ibqCompetitor->FieldByName("surname")->AsString);
        person.setName(ibqCompetitor->FieldByName("name")->AsString);
        person.setPatronymic(ibqCompetitor->FieldByName("patronymic")->AsString);
        person.setDob(ibqCompetitor->FieldByName("dob")->AsDateTime);
        person.setPhone(ibqCompetitor->FieldByName("phone")->AsString);
        person.setFemale(ibqCompetitor->FieldByName("female")->AsString=='T'?true:false);
        person.setAdditions(ibqCompetitor->FieldByName("additions")->AsString);

        skill.setId(ibqCompetitor->FieldByName("id")->AsInteger);
        skill.setShortDescription(ibqCompetitor->FieldByName("shortDescription")->AsString);
        skill.setFullDescription(ibqCompetitor->FieldByName("fullDescription")->AsString);
        skill.setComments(ibqCompetitor->FieldByName("comments")->AsString);
        skill.setWeight(ibqCompetitor->FieldByName("weight")->AsInteger);

        request.setId(ibqCompetitor->FieldByName("id2")->AsInteger);
        request.setCompetitionId(ibqCompetitor->FieldByName("competitionId")->AsInteger);
        request.setPersonId(ibqCompetitor->FieldByName("personId")->AsInteger);
        request.setClubId(ibqCompetitor->FieldByName("clubId")->AsInteger);
        request.setComments(ibqCompetitor->FieldByName("comments1")->AsString);

        TCompetitor *result = new TCompetitor();
        result->setSkillId(ibqCompetitor->FieldByName("id")->AsInteger);
        result->setPersonId(ibqCompetitor->FieldByName("id1")->AsInteger);
        result->setRequestId(ibqCompetitor->FieldByName("id2")->AsInteger);
        result->setWeight(ibqCompetitor->FieldByName("Weight1")->AsFloat);
        result->setId(ibqCompetitor->FieldByName("id3")->AsInteger);
        //Установим дополнительные поля
        result->extend(person, skill, request);
        //Добавить в список
        resultList->Add(result);
        //Перейдем к следующей записи
        ibqCompetitor->Next();
        }
    //Закроем множество
    ibqCompetitor->Close();
    //вернем результирующее множество
    return resultList;
}

TList * TdmCompetitorDAO::getExtendedUncategoryByCompetitionId(int competitionId,
                                                                    bool female){
AnsiString selectQuery =
"select \
       Skill.id, \
       Skill.shortDescription, \
       Skill.fullDescription, \
       Skill.weight, \
       Skill.comments, \
       Person.id, \
       Person.surname, \
       Person.name, \
       Person.patronymic, \
       Person.dob, \
       Person.phone, \
       Person.female, \
       Person.additions, \
       Request.id, \
       Request.personId, \
       Request.clubId, \
       Request.competitionId, \
       Request.comments, \
       Competitor.id, \
       Competitor.weight \
       from Competitor, Skill, Person, Request where \
       Person.id = Competitor.personId and Skill.id = Competitor.skillId \
       and Request.id = Competitor.requestId and Competitor.requestId = Request.id \
       and Request.competitionId = :competitionId and Competitor.id  in \
       (select distinct competitorId from CompetitorToFightVersion, Competitor, \
        Request where CompetitorToFightVersion.destributed = 'F' and \
        CompetitorToFightVersion.competitorId  = Competitor.id and \
        Competitor.requestId = Request.id and \
        Request.competitionId = :competitionId) and Person.female=:female \
        order by Person.female, Person.dob desc, Competitor.weight desc";


    //Создать запрос для получения объектов из базы
    ibqCompetitor->SQL->Clear();
    ibqCompetitor->SQL->Add(selectQuery);
    //Указать соревнование
    ibqCompetitor->ParamByName("competitionId")->AsInteger = competitionId;
    ibqCompetitor->ParamByName("female")->AsString = female?"T" : "F";    
    //Получить записи из базы данных
    ibqCompetitor->Open();

    //Создаем объекты по количеству полученных из базы данных
    TList* resultList = new TList();
    resultList->Clear();
    ibqCompetitor->First();
    //Создать расширенные поля
    TPerson person;
    TSkill skill;
    TRequest request;
    for(int i = 0; i < ibqCompetitor->RecordCount; i++){
        //Заполнить структуру

        person.setId(ibqCompetitor->FieldByName("id1")->AsInteger);
        person.setSurname(ibqCompetitor->FieldByName("surname")->AsString);
        person.setName(ibqCompetitor->FieldByName("name")->AsString);
        person.setPatronymic(ibqCompetitor->FieldByName("patronymic")->AsString);
        person.setDob(ibqCompetitor->FieldByName("dob")->AsDateTime);
        person.setPhone(ibqCompetitor->FieldByName("phone")->AsString);
        person.setFemale(ibqCompetitor->FieldByName("female")->AsString=='T'?true:false);
        person.setAdditions(ibqCompetitor->FieldByName("additions")->AsString);

        skill.setId(ibqCompetitor->FieldByName("id")->AsInteger);
        skill.setShortDescription(ibqCompetitor->FieldByName("shortDescription")->AsString);
        skill.setFullDescription(ibqCompetitor->FieldByName("fullDescription")->AsString);
        skill.setComments(ibqCompetitor->FieldByName("comments")->AsString);
        skill.setWeight(ibqCompetitor->FieldByName("weight")->AsInteger);

        request.setId(ibqCompetitor->FieldByName("id2")->AsInteger);
        request.setCompetitionId(ibqCompetitor->FieldByName("competitionId")->AsInteger);
        request.setPersonId(ibqCompetitor->FieldByName("personId")->AsInteger);
        request.setClubId(ibqCompetitor->FieldByName("clubId")->AsInteger);
        request.setComments(ibqCompetitor->FieldByName("comments1")->AsString);

        TCompetitor * result = new TCompetitor();

        result->setSkillId(ibqCompetitor->FieldByName("id")->AsInteger);
        result->setPersonId(ibqCompetitor->FieldByName("id1")->AsInteger);
        result->setRequestId(ibqCompetitor->FieldByName("id2")->AsInteger);
        result->setWeight(ibqCompetitor->FieldByName("Weight1")->AsFloat);
        result->setId(ibqCompetitor->FieldByName("id3")->AsInteger);
        //Установим дополнительные поля
        result->extend(person, skill, request);

        //Добавить в список
        resultList->Add(result);
        //Перейдем к следующей записи
        ibqCompetitor->Next();
        }
    //Закроем множество
    ibqCompetitor->Close();
    //вернем результирующее множество
    return resultList;
}



TList * TdmCompetitorDAO::getExtendedByRequestId(int requestId){
AnsiString selectQuery =
"select \
       Skill.id, \
       Skill.shortDescription, \
       Skill.fullDescription, \
       Skill.weight, \
       Skill.comments, \
       Person.id, \
       Person.surname, \
       Person.name, \
       Person.patronymic, \
       Person.dob, \
       Person.phone, \
       Person.female, \
       Person.additions, \
       Request.id, \
       Request.personId, \
       Request.clubId, \
       Request.competitionId, \
       Request.comments, \
       Competitor.id, \
       Competitor.weight \
       from Competitor, Skill, Person, Request where \
       Person.id = Competitor.personId and Skill.id = Competitor.skillId \
       and Request.id = Competitor.requestId and Competitor.requestId = :requestId";
    //Создать запрос для получения объектов из базы
    ibqCompetitor->SQL->Clear();
    ibqCompetitor->SQL->Add(selectQuery);
    //Указать соревнование
    ibqCompetitor->ParamByName("requestId")->AsInteger = requestId;
    //Получить записи из базы данных
    ibqCompetitor->Open();

    //Создаем объекты по количеству полученных из базы данных
        TList* resultList = new TList();
        resultList->Clear();
        ibqCompetitor->First();
        //Создать расширенные поля
        TPerson person;
        TSkill skill;
        TRequest request;
        for(int i = 0; i < ibqCompetitor->RecordCount; i++){
            //Заполнить структуру

            person.setId(ibqCompetitor->FieldByName("id1")->AsInteger);
            person.setSurname(ibqCompetitor->FieldByName("surname")->AsString);
            person.setName(ibqCompetitor->FieldByName("name")->AsString);
            person.setPatronymic(ibqCompetitor->FieldByName("patronymic")->AsString);
            person.setDob(ibqCompetitor->FieldByName("dob")->AsDateTime);
            person.setPhone(ibqCompetitor->FieldByName("phone")->AsString);
            person.setFemale(ibqCompetitor->FieldByName("female")->AsString=='T'?true:false);
            person.setAdditions(ibqCompetitor->FieldByName("additions")->AsString);

            skill.setId(ibqCompetitor->FieldByName("id")->AsInteger);
            skill.setShortDescription(ibqCompetitor->FieldByName("shortDescription")->AsString);
            skill.setFullDescription(ibqCompetitor->FieldByName("fullDescription")->AsString);
            skill.setComments(ibqCompetitor->FieldByName("comments")->AsString);
            skill.setWeight(ibqCompetitor->FieldByName("weight")->AsInteger);

            request.setId(ibqCompetitor->FieldByName("id2")->AsInteger);
            request.setCompetitionId(ibqCompetitor->FieldByName("competitionId")->AsInteger);
            request.setPersonId(ibqCompetitor->FieldByName("personId")->AsInteger);
            request.setClubId(ibqCompetitor->FieldByName("clubId")->AsInteger);
            request.setComments(ibqCompetitor->FieldByName("comments1")->AsString);

            TCompetitor *result = new TCompetitor();

            result->setSkillId(ibqCompetitor->FieldByName("id")->AsInteger);
            result->setPersonId(ibqCompetitor->FieldByName("id1")->AsInteger);
            result->setRequestId(requestId);
            result->setWeight(ibqCompetitor->FieldByName("Weight1")->AsFloat);
            result->setId(ibqCompetitor->FieldByName("id3")->AsInteger);
            //Установим дополнительные поля
            result->extend(person, skill, request);

            //Добавим в список
            resultList->Add(result);
            //Перейдем к следующей записи
            ibqCompetitor->Next();
            }
        //Закроем множество
        ibqCompetitor->Close();
        //вернем результирующее множество
        return resultList;
}


TList * TdmCompetitorDAO::getExtendedByCategoryId(int categoryId){
AnsiString selectQuery =
"select \
       CompetitorToCategory.sortion, \
       Skill.id, \
       Skill.shortDescription, \
       Skill.fullDescription, \
       Skill.weight, \
       Skill.comments, \
       Person.id, \
       Person.surname, \
       Person.name, \
       Person.patronymic, \
       Person.dob, \
       Person.phone, \
       Person.additions, \
       Request.id, \
       Request.personId, \
       Request.clubId, \
       Request.competitionId, \
       Request.comments, \
       Competitor.id, \
       Competitor.weight \
       from Competitor, Skill, Person, Request, CompetitorToCategory where \
       Person.id = Competitor.personId and Skill.id = Competitor.skillId \
       and Request.id = Competitor.requestId and \
       Competitor.id = CompetitorToCategory.competitorId and \
       CompetitorToCategory.categoryId = :categoryId order by \
       CompetitorToCategory.sortion";
    //Создать запрос для получения объектов из базы
    ibqCompetitor->SQL->Clear();
    ibqCompetitor->SQL->Add(selectQuery);
    //Указать соревнование
    ibqCompetitor->ParamByName("categoryId")->AsInteger = categoryId;
    //Получить записи из базы данных
    ibqCompetitor->Open();

        //Создаем объекты по количеству полученных из базы данных
        TList* resultList = new TList();
        resultList->Clear(); 
        ibqCompetitor->First();
        //Создать расширенные поля
        TPerson person;
        TSkill skill;
        TRequest request;
        while(!ibqCompetitor->Eof){
            //Заполнить структуру

            person.setId(ibqCompetitor->FieldByName("id1")->AsInteger);
            person.setSurname(ibqCompetitor->FieldByName("surname")->AsString);
            person.setName(ibqCompetitor->FieldByName("name")->AsString);
            person.setPatronymic(ibqCompetitor->FieldByName("patronymic")->AsString);
            person.setDob(ibqCompetitor->FieldByName("dob")->AsDateTime);
            person.setPhone(ibqCompetitor->FieldByName("phone")->AsString);
            person.setAdditions(ibqCompetitor->FieldByName("additions")->AsString);

            skill.setId(ibqCompetitor->FieldByName("id")->AsInteger);
            skill.setShortDescription(ibqCompetitor->FieldByName("shortDescription")->AsString);
            skill.setFullDescription(ibqCompetitor->FieldByName("fullDescription")->AsString);
            skill.setComments(ibqCompetitor->FieldByName("comments")->AsString);
            skill.setWeight(ibqCompetitor->FieldByName("weight")->AsInteger);

            request.setId(ibqCompetitor->FieldByName("id2")->AsInteger);
            request.setCompetitionId(ibqCompetitor->FieldByName("competitionId")->AsInteger);
            request.setPersonId(ibqCompetitor->FieldByName("personId")->AsInteger);
            request.setClubId(ibqCompetitor->FieldByName("clubId")->AsInteger);
            request.setComments(ibqCompetitor->FieldByName("comments1")->AsString);

            TCompetitor *result = new TCompetitor(); 

            result->setSkillId(ibqCompetitor->FieldByName("id")->AsInteger);
            result->setPersonId(ibqCompetitor->FieldByName("id1")->AsInteger);
            result->setRequestId(ibqCompetitor->FieldByName("id2")->AsInteger);
            result->setWeight(ibqCompetitor->FieldByName("Weight1")->AsFloat);
            result->setId(ibqCompetitor->FieldByName("id3")->AsInteger);
            result->setSortion(ibqCompetitor->FieldByName("sortion")->AsInteger);
            //Установим дополнительные поля
            result->extend(person, skill, request);

            //Добавить в список
            resultList->Add(result); 
            //Перейдем к следующей записи
            ibqCompetitor->Next();
            }
        //Закроем множество
        ibqCompetitor->Close();
        //вернем результирующее множество
        return resultList;
}



void TdmCompetitorDAO::setFightVersion(int id, int * ids, int count){
    //Записать в таблицу связи участника и б. версии
AnsiString insertQuery =
"insert into CompetitorToFightVersion(competitorId, fightVersionId) \
 values(:competitorId, :fightVersionId)";

    ibqCompetitorToFightVersion->SQL->Clear();
    ibqCompetitorToFightVersion->SQL->Add(insertQuery);


    //Установим значение идентификатора пользователя
    ibqCompetitorToFightVersion->ParamByName("competitorId")->AsInteger = id;

    if(!dmDataSource->ibtrSecretaryDB->Active){
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    for(int i=0; i < count; i++){
        //Добавить недостающий параметр и вставить запись
        ibqCompetitorToFightVersion->ParamByName("fightVersionId")->AsInteger = ids[i];
        ibqCompetitorToFightVersion->ExecSQL();
        }
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Сохранить в базе
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}




TList* TdmCompetitorDAO::getFightVersion(int id){
//Запрос на получение идентификаторов боевых версий
AnsiString selectQuery =
"select fightVersionId from CompetitorToFightVersion where \
 competitorId = :competitorId";

    ibqCompetitorToFightVersion->SQL->Clear();
    ibqCompetitorToFightVersion->SQL->Add(selectQuery);

    //Установим значение идентификатора участника
    ibqCompetitorToFightVersion->ParamByName("competitorId")->AsInteger = id;
    //Прочитаем список и определим сколько записей получено
    ibqCompetitorToFightVersion->Open();
    ibqCompetitorToFightVersion->First();

    TList *resultList = new TList();
    resultList->Clear(); 

    for(int i=0; i < ibqCompetitorToFightVersion->RecordCount; i++){
        TFightVersion * result = new TFightVersion(); 
        //Получить версию с заданным идентификатором
        result->getById(
                    ibqCompetitorToFightVersion->FieldByName("fightVersionId")->AsInteger);
        //Добавить в список
        resultList->Add(result);         
        //К следующей записи
        ibqCompetitorToFightVersion->Next();
        }

    //Закрыть множество
    ibqCompetitorToFightVersion->Close(); 
    return resultList;
}


TList* TdmCompetitorDAO::getUncategoryFightVersion(int id){
//Запрос на получение идентификаторов боевых версий
AnsiString selectQuery =
"select fightVersionId from CompetitorToFightVersion where \
 competitorId = :competitorId and destributed='F'";

    ibqCompetitorToFightVersion->SQL->Clear();
    ibqCompetitorToFightVersion->SQL->Add(selectQuery);

    //Установим значение идентификатора участника
    ibqCompetitorToFightVersion->ParamByName("competitorId")->AsInteger = id;
    //Прочитаем список и определим сколько записей получено
    ibqCompetitorToFightVersion->Open();
    ibqCompetitorToFightVersion->First();

    TList *resultList = new TList();
    resultList->Clear(); 

    for(int i=0; i < ibqCompetitorToFightVersion->RecordCount; i++){
        TFightVersion * result = new TFightVersion(); 
        //Получить версию с заданным идентификатором
        result->getById(
                    ibqCompetitorToFightVersion->FieldByName("fightVersionId")->AsInteger);
        //Добавить в список
        resultList->Add(result);
        //К следующей записи
        ibqCompetitorToFightVersion->Next();
        }
    //Закрыть множество
    ibqCompetitorToFightVersion->Close(); 
    //Вернуть список
    return resultList;
}


TList* TdmCompetitorDAO::getExtendedFightVersion(int id){
//Запрос на получение идентификаторов боевых версий
AnsiString selectQuery =
"select fightVersionId from ExtendedFightVersion where \
 competitorId = :competitorId";

    ibqCompetitorToFightVersion->SQL->Clear();
    ibqCompetitorToFightVersion->SQL->Add(selectQuery);

    //Установим значение идентификатора участника
    ibqCompetitorToFightVersion->ParamByName("competitorId")->AsInteger = id;
    //Прочитаем список и определим сколько записей получено
    ibqCompetitorToFightVersion->Open();
    ibqCompetitorToFightVersion->First();

    TList *resultList = new TList();
    resultList->Clear(); 

    for(int i=0; i < ibqCompetitorToFightVersion->RecordCount; i++){
        TFightVersion *result = new TFightVersion(); 
        //Получить версию с заданным идентификатором
        result->getById(
                    ibqCompetitorToFightVersion->FieldByName("fightVersionId")->AsInteger);
        //Добавить в список
        resultList->Add(result);
        //К следующей записи
        ibqCompetitorToFightVersion->Next();
        }
    //Закрыть множество
    ibqCompetitorToFightVersion->Close();
    //Вернуть список
    return resultList;
}



void TdmCompetitorDAO::eraseFightVersion(int id){
//Запрос на удаление боевых версий для участника
AnsiString deleteQuery =
"delete from CompetitorToFightVersion where \
 competitorId = :competitorId";

    ibqCompetitorToFightVersion->SQL->Clear();
    ibqCompetitorToFightVersion->SQL->Add(deleteQuery);

    //Установим значение идентификатора участника
    ibqCompetitorToFightVersion->ParamByName("competitorId")->AsInteger = id;
    if(!dmDataSource->ibtrSecretaryDB->Active){
        //Запомнить в базе
        dmDataSource->ibtrSecretaryDB->StartTransaction();
        }
    //Выполняем запрос на удаление записей
    ibqCompetitorToFightVersion->ExecSQL();
    if(dmDataSource->ibtrSecretaryDB->Active){
        //Запомнить в базе
        dmDataSource->ibtrSecretaryDB->Commit();
        }
}





void TdmCompetitorDAO::setScrollCallback(CallbackFunction cbf){
    CompetitorScrollCallback = cbf;
}

void __fastcall TdmCompetitorDAO::ibqCompetitorExtendedTableAfterScroll(
      TDataSet *DataSet)
{
    //Если определена функция обратного вызова, вызываем ее
    if(CompetitorScrollCallback){
        CompetitorScrollCallback();
        }
}
//---------------------------------------------------------------------------


void TdmCompetitorDAO::getById(int id, TCompetitor &obj){
AnsiString selectQuery =
"select id, skillId, personId, requestId, weight\
 from Competitor where id = :id";
    //Создать запрос для получения объектов из базы
    ibqCompetitor->SQL->Clear();
    ibqCompetitor->SQL->Add(selectQuery);
    ibqCompetitor->ParamByName("id")->AsInteger = id;
    //Получить записи из базы данных
    ibqCompetitor->Open();
    if(ibqCompetitor->RecordCount){
        obj.setId(id);
        obj.setSkillId(ibqCompetitor->FieldByName("skillId")->AsInteger);
        obj.setPersonId(ibqCompetitor->FieldByName("personId")->AsInteger);
        obj.setRequestId(ibqCompetitor->FieldByName("requestId")->AsInteger);
        obj.setWeight(ibqCompetitor->FieldByName("weight")->AsFloat);        
        }
    //Записи не получены, вернуть null
    else{
        //Обнулить объект
        setmem(&obj, sizeof(obj), 0);
        }
    //Закрываем множество
    ibqCompetitor->Close();
}


