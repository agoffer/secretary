//---------------------------------------------------------------------------

#pragma hdrstop

#include "categoryCtrl.h"
#include "categoryDM.h"
#include "currentStateDM.h"
#include "utils.h"

//Количество участников в дереве
const int COMPETITORS_IN_TREE = 32;

//Определяет порядок сортировки пар, на дереве 
bool desc = false;

int criticalPairs[32] = {0 /* не используется */, 0 /* не используется */,
//                 3    4    5    6    7    8    9   10   11   12   13   14   15   16
                   1,   2,   1,   2,   3,   4,   1,   2,   5,   6,   3,   4,   7,   8,
//                17   18   19   20   21   22   23   24   25   26   27   28   29   30
                   1,   2,   9,  10,   5,   6,  11,  12,   3,   4,  13,  14,   7,   8,
//                31   32
                  15,  16
                        };

void getCriticalPairsIndexes(int &bottomIndex, int &topIndex, int dataAmnt){
    //Выберем индексы в зависимости от количества участников
    switch(dataAmnt){
        case 32  :;
        case 31  :;
        case 30  :bottomIndex = 16; break;
        case 29  :bottomIndex = 15; break;
        case 28  :;
        case 27  :;
        case 26  : bottomIndex = 14; break;
        case 25  : bottomIndex = 13; break;
        case 24  :;
        case 23  :;
        case 22  : bottomIndex = 12; break;
        case 21  : bottomIndex = 11; break;
        case 20  :;
        case 19  :;
        case 18  : bottomIndex = 10; break;
        case 17  : bottomIndex = 9; break;
        case 16 :;
        case 15 :;
        case 14 : bottomIndex = 8; break;
        case 13 : bottomIndex = 7; break;
        case 12 : bottomIndex = 6; break;
        case 11 : bottomIndex = 5; break;
        case 10 : bottomIndex = 6; break;
        case 9  : bottomIndex = 5; break;
        case 8  :;
        case 7  :;
        case 6  : bottomIndex = 4; break;
        case 5  : bottomIndex = 3; break;
        case 4  : bottomIndex = 2; break;
        case 3  : bottomIndex = 2;
        }
    topIndex = dataAmnt - 1; 
}


//---------------------------------------------------------------------------


void TCategory::extend(void){
    //Получить расширенные поля 
    if(availCategoryId)
        availCategory.getById(availCategoryId);
    if(fightVersionId)
        fightVersion.getById(fightVersionId);
    if(competitionId)
        competition.getById(competitionId);
    //Установить признак расширения
    extended = true;
}

void TCategory::extend(TAvailCategory inAvailCategory, TFightVersion inFightVersion, TCompetition inCompetition){

    availCategory = inAvailCategory;
    availCategoryId = inAvailCategory.getId();

    fightVersion = inFightVersion;
    fightVersionId = inFightVersion.getId();


    competition.getById(competitionId);
    competitionId = inCompetition.getId();

    //Установить признак расширения
    extended = true;
}

TCategory::TCategory(int inAvailCategoryId, int inFightVersionId, int inCompetitionId){
    //Инициализируем объект
    availCategoryId = inAvailCategoryId;
    fightVersionId = inFightVersionId;
    competitionId = inCompetitionId;
    id = 0;
    //Изначально объект не расширен
    extended = false;
    availCategory.setId(0);
    fightVersion.setId(0);
    competition.setId(0);
}

TCategory::~TCategory(void){
}

bool TCategory::valid(AnsiString &errmess){
    //Проверим допустимость полей объекта
    //Все правильно
    return true;
}

void TCategory::store(void){
   dmCategoryDAO->store(*this);
}

TCategory TCategory::getCurrent(void){
    return dmCategoryDAO->getCurrent();
}


void TCategory::makeCurrent(void){
    return dmCategoryDAO->makeCurrent(*this);
}


TList* TCategory::getAll(void){

}

//-- Вернуть все категории (в расширенной форме), для текущих соревнований
TList * TCategory::getExtendedByCompetitionId(int competitionId){
    return dmCategoryDAO->getExtendedByCompetitionId(competitionId);
}

//-- Вернуть все категории (в расширенной форме), для текущих соревнований,
//-- в которых присутствует участник с фамилией : surname
TList * TCategory::getExtendedByCompetitionIdSurname(int competitionId, AnsiString surname){
    return dmCategoryDAO->getExtendedByCompetitionIdSurname(competitionId, surname);
}



void TCategory::getById(int id){
    dmCategoryDAO->getById(id, *this);
}

bool TCategory::checkForDistribution(TCompetition competition){
    int count = 0;
    TList* categories = dmCategoryDAO->getByCompetitionId(competition.getId());
    if(categories->Count!=0){
        count = categories->Count;
        destroyList(categories, etCATEGORY);
        }
    return (count != 0);
}

void TCategory::addCompetitor(TCompetitor inCompetitor){
    dmCategoryDAO->addCompetitor(inCompetitor.getId(), id);
}

void TCategory::setCompetitors(TList *ids){
    dmCategoryDAO->setCompetitors(id, ids);
}

void TCategory::eraseCompetitors(TList *ids){
    dmCategoryDAO->eraseCompetitors(id, ids); 
}


void TCategory::putInAvailCategory(TCompetitor competitor, TFightVersion fightVersion, TCompetition competition){
    //Проверяем, попадет ли участник в доступную категорию
    int checkAvailCategoryId = TAvailCategory::checkForAvailCategory(competitor);

    //Если участник попал в доступную категорию, создадим боевую категорию
    if(checkAvailCategoryId){
        //Создадим категорию
        this->availCategoryId = checkAvailCategoryId;
        this->fightVersionId = fightVersion.getId();
        this->competitionId = competition.getId();
        this->id = 0;
        //Сохраним категорию в базе данных
        this->store();
        //Поместить участника в категорию
        this->addCompetitor(competitor);
        }
    else{
        //Категория не создана
        id = 0;
        }
}


bool TCategory::putInCreatedCategory(TCompetitor competitor, TFightVersion fightVersion, TCompetition competition){
    //Проверяем, попадает ли участник в уже созданную категорию
    int age = YearsPassCalculator(competitor.getPerson().getDob());
    return  dmCategoryDAO->putCompetitor(competitor.getWeight(), age,
                        competitor.getPerson().getFemale(), fightVersion.getId(),
                        competition.getId(), competitor.getId());
}



void TCategory::destributeCompetitors(TRequest request, TCompetition competition){

    //Получисть список участников из заявки для соревнования
    TList* competitorsList = TCompetitor::getExtendedByRequestId(request.getId());
    int competitorCount = competitorsList->Count;

    // -- Для каждого участника, просматриваем его боевые версии и разносим по категориям

    for(int comp=0; comp < competitorCount; comp++){
        //Получить список боевых версий для текущего участника
        int fightVersionCount;
        TCompetitor *curCompetitor = (TCompetitor*)competitorsList->Items[comp];
        TList *fvids = curCompetitor->getFightVersion();

        //Проходимся по списку боевых версий - находим, куда мы можем добавить участника
        for(int fv = 0; fv < fvids->Count; fv++){

            //Можем ли мы добавить участника в существующие категории ?
            if(!putInCreatedCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition)){
                //Не смогли добавить в уже созданную категорию
                //Пробуем добавить в одну из доступных и формируем новую категорию
                TCategory newCategory;
                newCategory.putInAvailCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition);
                //Если была получена категория сохраним ее в списке созданных категорий,
                // в противном случае - сохраним в списке не попавших в категорию
                if(!newCategory.getId()){
                    //Участник не попадает в категорию
                    break;  //Проверяем его один раз
                    }
                }
            }
        }
    //Удалить список участников
    destroyList(competitorsList, etCOMPETITOR);
}



void TCategory::destributeCompetitors(TList *competitorsList, TCompetition competition){

    //Количество участников
    int competitorCount = competitorsList->Count;

    // -- Для каждого участника, просматриваем его боевые версии и разносим по категориям

    for(int comp=0; comp < competitorCount; comp++){
        //Получить список боевых версий для текущего участника
        int fightVersionCount;
        TCompetitor *curCompetitor = (TCompetitor*)competitorsList->Items[comp];
        TList *fvids = curCompetitor->getFightVersion();

        //Проходимся по списку боевых версий - находим, куда мы можем добавить участника
        for(int fv = 0; fv < fvids->Count; fv++){

            //Можем ли мы добавить участника в существующие категории ?
            if(!putInCreatedCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition)){
                //Не смогли добавить в уже созданную категорию
                //Пробуем добавить в одну из доступных и формируем новую категорию
                TCategory newCategory;
                newCategory.putInAvailCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition);
                //Если была получена категория сохраним ее в списке созданных категорий,
                // в противном случае - сохраним в списке не попавших в категорию
                if(!newCategory.getId()){
                    //Участник не попадает в категорию
                    break;  //Проверяем его один раз
                    }
                }
            }
        }
}



void TCategory::destributeCompetitor(TCompetitor competitor, TCompetition competition){

        //Получить список боевых версий для текущего участника
        TList *fvids = competitor.getFightVersion();

        //Проходимся по списку боевых версий - находим, куда мы можем добавить участника
        for(int fv = 0; fv < fvids->Count; fv++){
            //Можем ли мы добавить участника в существующие категории ?
            if(!putInCreatedCategory(competitor, *((TFightVersion*)fvids->Items[fv]), competition)){
                //Не смогли добавить в уже созданную категорию
                //Пробуем добавить в одну из доступных и формируем новую категорию
                TCategory newCategory;
                newCategory.putInAvailCategory(competitor, *((TFightVersion*)fvids->Items[fv]), competition);
                //Если была получена категория сохраним ее в списке созданных категорий,
                // в противном случае - сохраним в списке не попавших в категорию
                if(!newCategory.getId()){
                    //Участник не попадает в категорию
                    break;  //Проверяем его один раз
                    }
                }
            }
}





void TCategory::destributeCompetitors(TCompetition competition){

    //Получисть список участников для соревнования
    TList* competitorsList = TCompetitor::getExtendedByCompetitionId(competition.getId());
    int competitorCount = competitorsList->Count;

    // -- Для каждого участника, просматриваем его боевые версии и разносим по категориям

    for(int comp=0; comp < competitorCount; comp++){
        //Получить список боевых версий для текущего участника
        int fightVersionCount;
        TCompetitor *curCompetitor = (TCompetitor*)competitorsList->Items[comp];
        TList *fvids = curCompetitor->getFightVersion();

        //Проходимся по списку боевых версий - находим, куда мы можем добавить участника
        for(int fv = 0; fv < fvids->Count; fv++){

            //Можем ли мы добавить участника в существующие категории ?
            if(!putInCreatedCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition)){
                //Не смогли добавить в уже созданную категорию
                //Пробуем добавить в одну из доступных и формируем новую категорию
                TCategory newCategory;
                newCategory.putInAvailCategory(*curCompetitor, *((TFightVersion*)fvids->Items[fv]), competition);
                //Если была получена категория сохраним ее в списке созданных категорий,
                // в противном случае - сохраним в списке не попавших в категорию
                if(!newCategory.getId()){
                    //Участник не попадает в категорию
                    break;  //Проверяем его один раз
                    }
                }
            }
        }
    //Удалить список участников
    destroyList(competitorsList, etCOMPETITOR);
}



/*

int __fastcall sortionCompareClub(void *fstItem, void *secItem){
    if(((TSortionData *)fstItem)->clubId > ((TSortionData *)secItem)->clubId){
        //Первый клуб с большим идентификатором
        return 1;
        }
    else if(((TSortionData *)fstItem)->clubId < ((TSortionData *)secItem)->clubId){
            //Второй клуб с меньшим идентификатором
            return -1;
            }
         else{
            //Одинаковые клубы
            return 0;
            }
}

*/

int __fastcall sortionCompareSkill(void *fstItem, void *secItem){
    if(((TSortionData *)fstItem)->skillWeight > ((TSortionData *)secItem)->skillWeight){
        //Первый уровень больше
        return -1;
        }
    else if(((TSortionData *)fstItem)->skillWeight < ((TSortionData *)secItem)->skillWeight){
            //Второй уровень меньше
            return 1;
            }
         else{
            //Одинаковые уровни
            return 0;
            }
}

/*
int __fastcall sortionCompareClubSkill(void *fstItem, void *secItem){
    if(((TSortionData *)fstItem)->clubId > ((TSortionData *)secItem)->clubId){
//    if(((TSortionData *)fstItem)->skillWeight > ((TSortionData *)secItem)->skillWeight){
        //первое больше второго
        return -1;
        }
    else if(((TSortionData *)fstItem)->clubId < ((TSortionData *)secItem)->clubId){
//    else if(((TSortionData *)fstItem)->skillWeight < ((TSortionData *)secItem)->skillWeight){
            //Второе больше первого
            return 1;
            }
         else{
            //Одинаковые клубы проверяем уровни
//            if(((TSortionData *)fstItem)->skillWeight > ((TSortionData *)secItem)->skillWeight){
            if(((TSortionData *)fstItem)->clubId > ((TSortionData *)secItem)->clubId){
                //Первый уровень больше
                return -1;
                }
            else if(((TSortionData *)fstItem)->skillWeight < ((TSortionData *)secItem)->skillWeight){
//            else if(((TSortionData *)fstItem)->clubId < ((TSortionData *)secItem)->clubId){
                //Второй уровень меньше
                return 1;
                }
                else{
                    //Одинаковые уровни
                    return 0;
                    }
            }
}

*/


int __fastcall compareCategories(void *fstItem, void *secItem){
    TCategory * fst = (TCategory*)fstItem;
    TCategory * sec = (TCategory*)secItem;

    //Вначале сравниваем пол участников
    if(fst->getAvailCategory().getFemale() < sec->getAvailCategory().getFemale())
        //Первая категория женская
        return -1;
    else if(fst->getAvailCategory().getFemale() > sec->getAvailCategory().getFemale())
        //Вторая категория женская
        return 1;


    //Сравним боевую версию
    if(fst->getFightVersionId() < sec->getFightVersionId())
        return -1;
    else if(fst->getFightVersionId() > sec->getFightVersionId())
        return 1;

    //Сравниваем возраста
    if(fst->getAvailCategory().getStartAge() < sec->getAvailCategory().getStartAge())
        //Возраст первого больше
        return -1;
    else if(fst->getAvailCategory().getStartAge() > sec->getAvailCategory().getStartAge())
        //Возраст второго больше
        return 1;
    //Сравниваем веса
    if(fst->getAvailCategory().getStartWeight() < sec->getAvailCategory().getStartWeight())
        //Вес первого больше
        return -1;
    else if(fst->getAvailCategory().getStartWeight() > sec->getAvailCategory().getStartWeight())
        //Вес второго больше
        return 1;


    //Категории одинаковые
    return 0;
}



/*
void TCategory::sortitionCategory(void){

//Данные из категории отсортированные по мастерству и клубам
int skillOrderDataAmnt;
TSortionData * skillOrderData = dmCategoryDAO->getSortionDataByCategory(this->id,
                                                skillOrderDataAmnt);

//Левая "ветвь дерева"
TList *leftBranch = new TList();
//Правая "ветвь дерева"
TList *rightBranch = new TList();

    //Распределим участников по ветвям дерева
    for(int i=0; i < skillOrderDataAmnt; i++){
        //Распределяем четных и нечетных
        if(i % 2){
            //Четных на правую ветвь
            rightBranch->Add(&skillOrderData[i]);
            }
        else{
            //Нечетных на левую ветвь
            leftBranch->Add(&skillOrderData[i]);
            }
        }
    //Сортируем внутри ветви по клубам
//    leftBranch->Sort(sortionCompareClub);
//    leftBranch->Sort(sortionCompareSkill);
//    rightBranch->Sort(sortionCompareClub);
//     rightBranch->Sort(sortionCompareSkill);

//     leftBranch->Sort(sortionCompareClubSkill);
//     rightBranch->Sort(sortionCompareClubSkill);

    //Сформируем список участников в категории, в порядке проведенной жеребьевки
    int *sortionOrder = new int[skillOrderDataAmnt];

    //Переносим идентификаторы
    int r=0;
    int l=0; //Индексы элементов по ветвям
    for(int i = 0; i < skillOrderDataAmnt; i++){
        if(i % 2){
            //Если номер четный, переносим с правой ветви
            sortionOrder[i] = ((TSortionData *)rightBranch->Items[r])->competitorId;
            r++;
            }
        else{
            //Если номер нечетный, переносим с левой ветви
            sortionOrder[i] = ((TSortionData *)leftBranch->Items[l])->competitorId;
            l++;
            }
        }

    //Сохраняем порядок жеребьевки участников в категории
    dmCategoryDAO->storeSortionOrder(this->id, sortionOrder, skillOrderDataAmnt);

    //Удаляем все структуры, которые использовались
    delete []  skillOrderData;
    delete [] sortionOrder;
    delete leftBranch;
    delete rightBranch;
}
*/


int searchAnotherClub(TList * branch, int startpos){
//Индекс найденного участника
int foundIndex= -1; //Ничего не найдено
int tobeg = startpos - 1, toend = startpos + 1;
//Где проверяем в данный момент
int inUp = true;
    //Ищем от текущей позиции к началу и к концу, чередуем
    while((tobeg >= 0) || (toend < branch->Count)){
        //Проверяем выше
        if(inUp){
            //Проверяем, если индекс меньше начала продолжаем в другую сторону
            if(tobeg < 0){
                inUp = !inUp;
                continue;
                }
            if( (((TSortionData*)branch->Items[startpos])->clubId !=
                ((TSortionData*)branch->Items[tobeg])->clubId) &&
                (!((TSortionData*)branch->Items[tobeg])->onTree)){
                //Нашли подходящую запись
                foundIndex = tobeg;
                //Прерываем поиск
                break;
                }
            //Сдвигаемся к началу
            tobeg --;
            //Если есть еще куда двигаться к концу инвертируем условие поиска
            if(toend < branch->Count){
                //Инвертируем позицию проверки
                inUp = !inUp;
                }
            }
        //Проверяем ниже
        else{
            //Проверяем, если индекс больше кол-ва эл-ов продолжаем в другую сторону
            if(toend > (branch->Count - 1)){
                inUp = !inUp;
                continue;
                }
            if( (((TSortionData*)branch->Items[startpos])->clubId !=
                ((TSortionData*)branch->Items[toend])->clubId) &&
                (!((TSortionData*)branch->Items[toend])->onTree)){
                //Нашли подходящую запись
                foundIndex = toend;
                //Прерываем поиск
                break;
                }
            //Сдвигаемся к началу
            toend ++;
            //Если есть еще куда двигаться к началу инвертируем услвие поиска
            if(tobeg >=0){
                //Инвертируем позицию проверки
                inUp = !inUp;
                }
            }
        }
    //Вернуть результат поиска
    return foundIndex;
}


void TCategory::sortitionCategory(void){

    //Проверить, была ли выполнена жеребьевка над категорией раньше?
    char drawType = this->getDrawType();
    if((DT_AUTO == drawType) || (DT_MANUAL == drawType)){
        //Не надо проводить жеребьевку
        return;
        }

 

//Данные из категории отсортированные по мастерству и клубам
TList * skillClubOrderData = dmCategoryDAO->getSortionDataByCategory(this->id);
int dataAmnt = skillClubOrderData->Count;
    //Проверка на допустимое количество участников
    if(dataAmnt > COMPETITORS_IN_TREE){
        destroyList(skillClubOrderData, etSORTIONDATA);
        //Недопустимое число участников! Невозможно выполнить жеребьевоку
        throw "Число участников в \"дереве\" не может быть больше " + IntToStr(COMPETITORS_IN_TREE) + "!";
        }

//Левая "ветвь дерева"
TList *leftBranch = new TList();
    leftBranch->Clear();
//Правая "ветвь дерева"
TList *rightBranch = new TList();
    rightBranch->Clear();

    //Распределим участников по ветвям дерева
    for(int i=0; i < dataAmnt; i++){
        //Изначально, участник не находится в дереве
        ((TSortionData*)skillClubOrderData->Items[i])->onTree = false;
        //Распределяем четных и нечетных
        if(i % 2){
            //Четных на правую ветвь
            rightBranch->Add((TSortionData*)skillClubOrderData->Items[i]);
            }
        else{
            //Нечетных на левую ветвь
            leftBranch->Add((TSortionData*)skillClubOrderData->Items[i]);
            }
        }

    //Сформируем список участников в категории, в порядке проведенной жеребьевки
    int *sortionOrder = new int[dataAmnt];

    if(dataAmnt > 2){
        //Отсортировать по уровню мастерства
        leftBranch->Sort(sortionCompareSkill);
        rightBranch->Sort(sortionCompareSkill);


        //Определим в каком диапазоне расставлять пары
        int bottomIndex = -1; int topIndex = -1;
        getCriticalPairsIndexes(bottomIndex, topIndex, dataAmnt);

        bool beenSwap;

        //Проходимся по ветке, пока были перестановки
            do{
            //Перестановок не будет
            beenSwap = false;
            //Начинаем поиск с самого низа
            int begind = leftBranch->Count - 1;
            //Проходимся по ветке
            for(int i = leftBranch->Count; i > leftBranch->Count / 2; i--){
                //Для участника позиция в жеребьевке
                int sp = i * 2 - 1;
                //Нужно ли проверять этого участника
                if((sp < (bottomIndex + 1)) || (sp > (topIndex+1)))
                    //Нет, больше проверять не надо
                    break;
                //Проверяем, нормальная ли пара
                //Возьмем первого участника пары
                TSortionData * fst = (TSortionData *) leftBranch->Items[i - 1];
                //Если он уже распределен, пропускаем его
                if(fst->onTree)
                    continue;
                //Определим позицию и возьмем второго участника пары
                int secpos = criticalPairs[sp - 1] / 2;
                TSortionData * sec = (TSortionData *) leftBranch->Items[secpos];
                //Участники из одного клуба, будем искать перестановку
                if(fst->clubId == sec->clubId){
                    //Будет выполнена перестановка
                    beenSwap = true;
                    //Индекс участника в ветви, с которым будем делать перестановку
                    int swpind;
                    //Ищем участника из другого клуба
                    swpind = searchAnotherClub(leftBranch, secpos);
                    if(swpind >= 0){
                        //Если  нашли делаем перестановку в ветке
                        leftBranch->Exchange(secpos, swpind);
                        //Взять новые значения
                        fst = (TSortionData *) leftBranch->Items[i - 1];
                        sec = (TSortionData *) leftBranch->Items[secpos];
                        }
                        //Отметить, что пара распределена
                        fst->onTree = true;
                        sec->onTree = true;
    //                else{
    //                    //Отметить, что пара распределена
    //                    fst->onTree = true;
    //                    sec->onTree = true;
    //                    }
                    }
                }
            }while(beenSwap);

        //Теперь обрабатываем правую ветвь

        //Проходимся по ветке, пока были перестановки
            do{
            //Перестановок не будет
            beenSwap = false;
            //Начинаем поиск с самого низа
            int begind = rightBranch->Count - 1;
            //Проходимся по ветке
            for(int i = rightBranch->Count; i > rightBranch->Count / 2; i--){
                //Положение в предварительной жеребьевке
                int sp = i * 2;
                //Нужно ли проверять этого участника
                if((sp < (bottomIndex + 1)) || (sp > (topIndex+1)))
                    //Нет, больше проверять не надо
                    break;
                //Проверяем, нормальная ли пара
                //Возьмем первого участника пары
                TSortionData * fst = (TSortionData *) rightBranch->Items[i - 1];
                //Если он уже распределен, пропускаем его
                if(fst->onTree)
                    continue;
                //Определим позицию и возьмем второго участника пары
                int secpos = criticalPairs[sp - 1] / 2 - 1;
                TSortionData * sec = (TSortionData *) rightBranch->Items[secpos];
                //Участники из одного клуба, будем искать перестановку
                if(fst->clubId == sec->clubId){
                    //Будет выполнена перестановка
                    beenSwap = true;
                    //Индекс участника в ветви, с которым будем делать перестановку
                    int swpind;
                    //Ищем участника из другого клуба
                    swpind = searchAnotherClub(rightBranch, secpos);
                    if(swpind >= 0){
                        //Если  нашли делаем перестановку в ветке
                        rightBranch->Exchange(secpos, swpind);
                        //Взять новые значения
                        fst = (TSortionData *) rightBranch->Items[i - 1];
                        sec = (TSortionData *) rightBranch->Items[secpos];
                        }
                        //Отметить, что пара распределена
                        fst->onTree = true;
                        sec->onTree = true;
    //                else{
    //                    //Отметить, что пара распределена
    //                    fst->onTree = true;
    //                    sec->onTree = true;
    //                    }
                    }
                }
            }while(beenSwap);
        }


    //Расположим участников на дереве
    int lb=0; int rb=0;
    for(int i =0; i < dataAmnt; i++){
        if(i % 2){
            sortionOrder[i] = ((TSortionData *) rightBranch->Items[rb])->competitorId;
            rb++;
            }
        else{
            sortionOrder[i] = ((TSortionData *) leftBranch->Items[lb])->competitorId;
            lb++;
            }
        }




    //Сохраняем порядок жеребьевки участников в категории
    dmCategoryDAO->storeSortionOrder(this->id, sortionOrder, dataAmnt);

    //Удаляем все структуры, которые использовались
    destroyList(skillClubOrderData, etSORTIONDATA);
    delete [] sortionOrder;
    leftBranch->Clear();
    delete (TList*)leftBranch;
    rightBranch->Clear();
    delete (TList*)rightBranch;

    //Отметить категорию как отсортированную автоматически
    this->setDrawType(DT_AUTO);
}

int TCategory::getCompetitorsAmount(void){
    return dmCategoryDAO->getCompetitorsAmount(id);
}

void TCategory::uncategory(int competitorId){
    dmCategoryDAO->uncategory(competitorId);
}

void TCategory::deleteCategoriesByCompetition(TCompetition competition){
    dmCategoryDAO->deleteCategoriesByCompId(competition.getId());
}

void TCategory::setDrawType(char drawType){
    dmCategoryDAO->setDrawType(*this, drawType);
}

char TCategory::getDrawType(void){
    return dmCategoryDAO->getDrawType(*this);
}








#pragma package(smart_init)




