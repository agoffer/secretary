//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "requestCompetitorsListEditU.h"
#include "mainFormU.h"
#include "currentStateDM.h"
#include "skillEditU.h"
#include "fightVersionEditU.h"
#include "categoryCtrl.h"

#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmRequestCompetitorsListEdit *frmRequestCompetitorsListEdit;
//---------------------------------------------------------------------------
__fastcall TfrmRequestCompetitorsListEdit::TfrmRequestCompetitorsListEdit(TComponent* Owner)
    : TForm(Owner)
{
    competitorsList = new TList();

}

//---------------------------------------------------------------------------


void __fastcall TfrmRequestCompetitorsListEdit::FormCreate(TObject *Sender)
{
    //Создать заголовки списка участников из заявки
    setCompetitorTableHeader(strgrdCompetitorsList);
}
//---------------------------------------------------------------------------
void __fastcall TfrmRequestCompetitorsListEdit::FormShow(TObject *Sender)
{
    //Установить начальное значение полей (при добавлении)
    InitFields();
}
//---------------------------------------------------------------------------


void TfrmRequestCompetitorsListEdit::InitFields(void){

    //Изменяем заголовки
    AnsiString clubName =dmCurrentState->getRequest().getClub().getName();
    frmRequestCompetitorsListEdit->Caption = "Список участников '" +
             clubName + "'";
    grboxCompetitorsList->Caption = "Участники '" + clubName + "'";


    //Создать список боевых версий
    createFightVersionList();

    //Создать список уровней мастерства
    createSkillList();

    //Очистить список участников
    strgrdCompetitorsList->RowCount = 2;
    strgrdCompetitorsList->Rows[1]->Clear();
    //Очистить все поля
    clearFields();
    //Если это загруженная заявка, сформируем список участников
    competitorsList = createCompetitorsList(dmCurrentState->getRequest().getId(),
                                                 strgrdCompetitorsList);
}


void TfrmRequestCompetitorsListEdit::clearFields(void){
    //Обнулить структуру персона
    dmCurrentState->getPerson().setId(0);
    lbledtSurname->Clear();
    lbledtName->Clear();
    lbledtPatronymic->Clear();
    dtpDOB->Date = Now();
    medtWeight->Clear();
    chboxFemale->Checked = false;
    //Очистить поле отображения возраста
    sttxtFullAge->Caption = "";

    //Сбросить поля боевой версии и уровня мастерства
    for(int i=0; i < chlstboxFightVersion->Count; i++){
        chlstboxFightVersion->Checked[i] = false;
        }
    cmboxSkill->ItemIndex = 0;
    //Поместить фокус на поле ввода фамилии
    lbledtSurname->SetFocus();
}



//---------------------------------------------------------------------------


void TfrmRequestCompetitorsListEdit::createFightVersionList(void){

    //Сформировать список
    chlstboxFightVersion->Items->Clear();
    for(int i=0; i < dmCurrentState->getFightVersionList()->Count; i++){
        chlstboxFightVersion->Items->Add(((TFightVersion*)dmCurrentState->getFightVersionList()->Items[i])->getCode());
        }
}

void TfrmRequestCompetitorsListEdit::destroyFightVersionList(void){
    //Очистим листбокс
    chlstboxFightVersion->Items->Clear();
}



void TfrmRequestCompetitorsListEdit::createSkillList(void){

    //Сформировать список
    cmboxSkill->Items->Clear();
    for(int i=0; i < dmCurrentState->getSkillList()->Count; i++){
        cmboxSkill->Items->Add(((TSkill*)dmCurrentState->getSkillList()->Items[i])->getShortDescription());
        }
    if(cmboxSkill->Items->Count){
        //Выберем первое значение по умолчанию
        cmboxSkill->Text = cmboxSkill->Items->Strings[0];
        cmboxSkill->ItemIndex = 0;
        }
    else{
        cmboxSkill->ItemIndex = -1;
        }
}

void TfrmRequestCompetitorsListEdit::destroySkillList(void){
    //Очистим листбокс
    cmboxSkill->Items->Clear();
}


void __fastcall TfrmRequestCompetitorsListEdit::btnAddSkillClick(
      TObject *Sender)
{
    //Добавить уровень мастерства
    frmSkillEdit->ShowModal();
    //Если добавили запись, обновить список
    if(frmSkillEdit->ModalResult == mrOk){
        //Уничтожить список уровней мастерства
        destroySkillList();
        //Создать список соревнований заново
        createSkillList();
        //Установить добавленную запись, как текущую
        cmboxSkill->Text =
            frmSkillEdit->lbledtShortDescription->Text;
            cmboxSkill->ItemIndex =cmboxSkill->Items->Count - 1;
        }


}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::btnAddFightVersionClick(
      TObject *Sender)
{
    //Добавить боевую версию
    frmFightVersionEdit->ShowModal();
    //Если добавили запись, обновить список
    if(frmFightVersionEdit->ModalResult == mrOk){
        //Уничтожить список статусов соревнований
        destroyFightVersionList();
        //Создать список соревнований заново
        createFightVersionList();
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::FormHide(TObject *Sender)
{
    //Удалить списки уровней мастерства и боевых версий
    destroySkillList();
    destroyFightVersionList();
    //Уничтожаем список участников
    destroyList(competitorsList, etCOMPETITOR);
}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::lbledtSurnameChange(
      TObject *Sender)
{
    //Применить фильтр отбора фамилий
    changePersonSearchTableState();
}
//---------------------------------------------------------------------------


void TfrmRequestCompetitorsListEdit::changePersonSearchTableState(void){
    dbgrdPersonList->DataSource  = NULL;
    //Применить фильтр отбора фамилий
    dmPersonDAO->setFilterCondition(lbledtSurname->Text);
    dmPersonDAO->filterByField(ptfSurname);
    dbgrdPersonList->DataSource =  dmPersonDAO->dsPersonTable;
}


void __fastcall TfrmRequestCompetitorsListEdit::bbtnToEditBoxClick(
      TObject *Sender)
{
    //Передать выбранного субъекта для участника
    fillCompetitorPerson();

}
//---------------------------------------------------------------------------


void TfrmRequestCompetitorsListEdit::fillCompetitorPerson(void){
    //Получить текущую персону
    dmCurrentState->setPerson(TPerson::getCurrent());
    //Установить поля, в соответствии с полученными значениями
    lbledtSurname->Text = dmCurrentState->getPerson().getSurname();
    lbledtName->Text = dmCurrentState->getPerson().getName();
    lbledtPatronymic->Text = dmCurrentState->getPerson().getPatronymic();
    dtpDOB->DateTime = dmCurrentState->getPerson().getDob();
    chboxFemale->Checked = dmCurrentState->getPerson().getFemale();
    //Установить фокус на следуюем вводимом поле
    medtWeight->SetFocus();
    TfrmRequestCompetitorsListEdit::dtpDOBChange(NULL);
}

void __fastcall TfrmRequestCompetitorsListEdit::dtpDOBChange(
      TObject *Sender)
{
    //Отобразить на форме ввода команды полных лет участника
    sttxtFullAge->Caption = IntToStr(YearsPassCalculator(dtpDOB->DateTime));
}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::bbtnAddCompetitorClick(
      TObject *Sender)
{
    //Перосна, которую будем сохранять
    TPerson personToStore;
    //Будем сохранять субъект из полей на форме
    personToStore.setId(0);
    personToStore.setSurname(lbledtSurname->Text.Trim());
    personToStore.setName(lbledtName->Text.Trim());
    personToStore.setPatronymic(lbledtPatronymic->Text.Trim());
    //Если в базе есть такой субъект, получить его идентификатор
    personToStore.likeAs();

    //Создать нового участника
    TCompetitor *newCompetitor = new TCompetitor();

    //Передать участника с формы, в базу данных
    if(CompetitorIntoDatabase(personToStore, newCompetitor)){
        //Добавить участника в список
        competitorsList->Add(newCompetitor);
        //Определить участника в категорию
        TCategory::destributeCompetitor(*newCompetitor, dmCurrentState->getCompetition()); 
        //Доавить участника в конец string grid
        addToCompetitorStringGrid(*newCompetitor, competitorsList->Count, strgrdCompetitorsList);
        //Увеличить количество строк
        strgrdCompetitorsList->RowCount = competitorsList->Count+1;
        //Очистить поля, для ввода нового участника
        clearFields();
        //Установить персону как текущую
        dmCurrentState->setPerson(personToStore); 
        }
}


bool TfrmRequestCompetitorsListEdit::CompetitorIntoDatabase(TPerson& obj, TCompetitor *newCompetitor){
//Признак ошибки
bool invalid = false;
//Сообщение об ошибке
AnsiString errmess;

    //Дата будет обязательно установлена
    obj.setDob(dtpDOB->DateTime);
    //Пол будет обязательно установлен 
    obj.setFemale(chboxFemale->Checked);    
    //Проверям корректное задание личности участника
    invalid = !obj.valid(errmess);
    //Выполняем дополнительную проверку на возраст участника
    int age = YearsPassCalculator(dtpDOB->DateTime);
    if(age > 80){
        //Проверка возраста в большую сторону
        errmess = "Участник слишком стар!";
        invalid = true;
        }
    if(age < 5){
        //Проверка возраста в меньшую сторону
        errmess = "Участник слишком молод!";
        invalid = true;
        }

    //Связать участника с боевыми версиями
    int idCount;
    int *fvids = createFightVersionIdList(idCount);
    if(!fvids){
        //Ошибка, должна быть указана хоть одна категория
        errmess = "Не задана ни одна боевая версия!";
        invalid = true;
        }

    //Проверяем, задан ли уровень мастрества (Факт задания уровня)
    if(cmboxSkill->ItemIndex == -1){
        //Не задан уровень мастерства
        errmess = "Укажите уровень мастерства!";
        invalid = true;
        }


    //Проверяем, задан ли вес участника (факт задания, не величина)
    if(medtWeight->Text.Trim()==","){
        //Вес не задан
        errmess = "Не задан вес участника!";
        invalid = true;
        }


    //Проверяем корректность введенных данных, если все нормально сохраняем
    if(invalid){
        //Отобразить сообщение об ошибке
        MessageDlg(errmess,
                    mtError, TMsgDlgButtons() << mbOK, 0);
        //Выходим для исправления данных
        return false;
        }

    //Сохранить личность в базе данных
    obj.store();

    //Созать участника и сохранить его в базе данных, поместить его в список
    int skillId =((TSkill*)dmCurrentState->getSkillList()->Items[cmboxSkill->ItemIndex])->getId();
    newCompetitor->setPersonId(obj.getId());
    newCompetitor->setSkillId(skillId);
    newCompetitor->setRequestId(dmCurrentState->getRequest().getId());
    newCompetitor->setWeight(StrToFloat(medtWeight->Text));

    //Сохранить участника в базе данных
    newCompetitor->store();
    //Установить боевые версии для участника
    newCompetitor->setFightVersion(fvids, idCount);
    delete[] fvids;

    //Расширить объект участника
    newCompetitor->extend(obj, *(TSkill*)dmCurrentState->getSkillList()->Items[cmboxSkill->ItemIndex],
                            dmCurrentState->getRequest());

    //Участник успешно добавлен 
    return true;
}




int *TfrmRequestCompetitorsListEdit::createFightVersionIdList(int &count){
    //Создаем список для всех объектов
    int *ids = new int[chlstboxFightVersion->Count];
    count=0;
    //Просматриваем все версии и находим id отмеченных версий
    for(int i=0; i < chlstboxFightVersion->Count; i++){
        if(chlstboxFightVersion->Checked[i]){
            ids[count++] = ((TFightVersion*)dmCurrentState->getFightVersionList()->Items[i])->getId();
            }
        }
    if(count){
        //Переопределить множество
        return (int *)realloc(ids, sizeof(int) * count);
        }
    else{
        return 0;
        }

}


//---------------------------------------------------------------------------


void __fastcall TfrmRequestCompetitorsListEdit::medtWeightExit(
      TObject *Sender)
{
    //Выровнять текст

    medtWeight->Text = FormatFloatValueText(medtWeight->Text);
}
//---------------------------------------------------------------------------



void __fastcall TfrmRequestCompetitorsListEdit::bbtnDeleteClick(
      TObject *Sender)
{
    //-- Удалить участника из списка
    if(MessageDlg("Удалить участника из заявки?", mtConfirmation,
    TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)return;
    //Удалить из списка участников в базе данных
    ((TCompetitor*)competitorsList->Items[strgrdCompetitorsList->Row -1])->erase();
    //Удалить из списка участников в памяти
    competitorsList->Delete(strgrdCompetitorsList->Row-1);
    //Удалить из StringGrid
    deleteFromCompetitorStringGrid(strgrdCompetitorsList->Row, strgrdCompetitorsList);
    //Переоткрыть таблицу с персонами 
    changePersonSearchTableState();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::bbtnEditClick(
      TObject *Sender)
{
    //-- Изменить выбранного пользователя
    //перейти в режим редактирования
    setEditMode();

    TCompetitor* edited = (TCompetitor*)(competitorsList->Items[strgrdCompetitorsList->Row - 1]);

    //Текущая персоналия
    dmCurrentState->setPerson(edited->getPerson()); 

    //Скопировать данные из таблицы в поля ввода
    lbledtSurname->Text = edited->getPerson().getSurname();
    lbledtName->Text = edited->getPerson().getName();
    lbledtPatronymic->Text = edited->getPerson().getPatronymic();
    dtpDOB->DateTime = edited->getPerson().getDob();
    chboxFemale->Checked = edited->getPerson().getFemale();
    medtWeight->Text = edited->getWeight();
    selectSkillById(edited->getSkill().getId());
    //Изменить значение возраста в поле его отображения
    dtpDOBChange(NULL);

    TList * fvids = edited->getFightVersion();
    //Пройтись по списку и расставить чекбоксы
    checkedFightVersion(fvids);
    destroyList(fvids, etFIGHTVERSION);
}


void TfrmRequestCompetitorsListEdit::selectSkillById(int id){
    //Проходимся по списку
    for(int i = 0; i < cmboxSkill->Items->Count; i++){
        //Когда идентификаторы совпадут, сделать текущим этот уровень мастерства
        if(((TSkill*)dmCurrentState->getSkillList()->Items[i])->getId() == id){
            cmboxSkill->Text = ((TSkill*)dmCurrentState->getSkillList()->Items[i])->getShortDescription();
            cmboxSkill->ItemIndex = i;
            //Прервать поиск
            break;  
            }
        }
}


void TfrmRequestCompetitorsListEdit::checkedFightVersion(TList *tocheck){
    //Проходимся по списку для поиска отмечаемых
    for(int i = 0; i < chlstboxFightVersion->Count; i++){
        //Сбрасываем отметку 
        chlstboxFightVersion->Checked[i] = false;
        //Проходимся по списку установленных для участника
        for(int j = 0; j < tocheck->Count; j++){
            if(((TFightVersion*)dmCurrentState->getFightVersionList()->Items[i])->getId() ==
               ((TFightVersion*)tocheck->Items[j])->getId()){
                //Отмечаем
                chlstboxFightVersion->Checked[i] = true;
                }
            }
        }
}



void TfrmRequestCompetitorsListEdit::setEditMode(void){
    //Изменить пиктограмму и подпись
    bbtnAddCompetitor->Visible = false;
    bbtnCloseList->Visible = false;
    bbtnUpdateCompetitor->Visible = true;
    bbtnCancelCompetitor->Visible = true;
    //Запретить изменение строки в таблице участников
    strgrdCompetitorsList->Enabled = false;       

}


void TfrmRequestCompetitorsListEdit::closeEditMode(void){
    //Изменить пиктограмму и подпись кнопок
    bbtnAddCompetitor->Visible = true;
    bbtnCloseList->Visible = true;
    bbtnUpdateCompetitor->Visible = false;
    bbtnCancelCompetitor->Visible = false;
    //Разрешить изменение строки в таблице
    strgrdCompetitorsList->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::bbtnUpdateCompetitorClick(
      TObject *Sender)
{

    TPerson personToStore = dmCurrentState->getPerson();

    TCompetitor *competitor =(TCompetitor*)competitorsList->Items[strgrdCompetitorsList->Row -1];

    //Изменить его основные атрибуты, в соответствии с данными формы
    personToStore.setSurname(lbledtSurname->Text.Trim());
    personToStore.setName(lbledtName->Text.Trim());
    personToStore.setPatronymic(lbledtPatronymic->Text.Trim());


    //Убрать из базы данных боевые версии для участника
    competitor->eraseFightVersion();
    //Убрать участника из категорий
    TCategory::uncategory(competitor->getId()); 

    //Заносим измения в базу данных
    if(CompetitorIntoDatabase(personToStore, competitor)){
        //Определить участника в категорию
        TCategory::destributeCompetitor(*competitor, dmCurrentState->getCompetition());
        //изменить пиктограмму и подпись кнопок
        closeEditMode();
        //Очистить поля
        clearFields();
        //Изменить значения в таблице
        addToCompetitorStringGrid(*competitor, strgrdCompetitorsList->Row, strgrdCompetitorsList);
        dmCurrentState->setPerson(personToStore);
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmRequestCompetitorsListEdit::bbtnCancelCompetitorClick(
      TObject *Sender)
{
    if(MessageDlg("Отменить изменения данных?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes){
        //-- отменить измения участника
        clearFields();
        closeEditMode();
        }


}
//---------------------------------------------------------------------------




void setCompetitorTableHeader(TStringGrid *grid){
    grid->ColCount = 5; grid->FixedCols = 0;
    grid->RowCount = 2; grid->FixedRows = 1; 
    grid->Cells[0][0] = "Ф.И.О";
    grid->Cells[1][0] = "Полных лет";
    grid->Cells[2][0] = "Вес";
    grid->Cells[3][0] = "Уровень мастерства";
    grid->Cells[4][0] = "Участвует в версиях";
}



void deleteFromCompetitorStringGrid(int delIndex, TStringGrid *grid){
    // Удаляем строчку с заданным индексом //

    //Если удаляется единственный участник
    if(grid->RowCount == 2){
        grid->Rows[1]->Clear();
        return;
        }

    //Если это не последняя строка
    if(delIndex != (grid->RowCount - 1)){
        //Смещаем все строки, которые находятся ниже на ее место
        for(int i = delIndex+1; i < grid->RowCount; i++){
            grid->Rows[i - 1] = grid->Rows[i];
            }
        }
    //Удаляем последнюю строчку
    grid->Rows[grid->RowCount - 1]->Clear();
    grid->RowCount--;
}

void clearStrGrid(TStringGrid *grid){
//    for(int i=1; i < grid->RowCount; i++){
//        grid->Rows[i]->Clear();
//        }

    grid->RowCount = 2;
    grid->Rows[1]->Clear();

}



void addToCompetitorStringGrid(TCompetitor competitor, int addIndex, TStringGrid *grid){
    //Ф.И.О.
    AnsiString surname = competitor.getPerson().getSurname();
    AnsiString name = competitor.getPerson().getName().SubString(1,1) + ".";
    AnsiString patronymic = competitor.getPerson().getPatronymic().SubString(1,1);
    patronymic += (patronymic.Length()>0)? "." : " ";
    AnsiString female = competitor.getPerson().getFemale()?"(Ж) " : " ";
    AnsiString snp = female + surname + " " + name + " " +patronymic;
    //Боевые версии

    TList *fvlist = competitor.getFightVersion();
    AnsiString fvstr = "";
    for(int i = 0; i < (fvlist->Count - 1); i++){
        fvstr += ((TFightVersion*)fvlist->Items[i])->getCode() + ", ";
        }
    if(fvlist->Count > 0){
        fvstr+= ((TFightVersion*)fvlist->Items[fvlist->Count - 1])->getCode();
        }
    destroyList(fvlist, etFIGHTVERSION);

    //Добавить участника в таблицу

    //Добавить ФИО
    grid->Cells[0][addIndex] = snp;
    //Добавить полных лет
    grid->Cells[1][addIndex] = IntToStr(YearsPassCalculator(
                                                        competitor.getPerson().getDob()
                                                        ));
    //Вес участника
    grid->Cells[2][addIndex] = FloatToStrF(competitor.getWeight(),
                                                            ffFixed, 4, 1);

    //Уровень мастерства
    grid->Cells[3][addIndex] = competitor.getSkill().getShortDescription();
    //Боевые версии, в кторых участвует участник
    grid->Cells[4][addIndex] = fvstr;
}



TList* createCompetitorsList(int requestId, TStringGrid *grid){
    //Получить список участников из базы данных
    TList* list = TCompetitor::getExtendedByRequestId(requestId);


    if(grid==NULL) return list;
    //Отобразить данные в таблице
    if(list->Count)
        grid->RowCount = list->Count + 1;
    else
        grid->RowCount = list->Count + 2;
    for(int i=0; i < list->Count; i++){
        addToCompetitorStringGrid(*((TCompetitor*)list->Items[i]), i + 1,
                                  grid);
        }

    //Вернуть результат (количество можно получить из строковой таблицы)
    return list;
}



void __fastcall TfrmRequestCompetitorsListEdit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //Отобразить сообщение об закрытии формы

    if(MessageDlg("Закончить заполнения списка участников?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo){
        Action = caNone;
        }
    else{
       dbgrdPersonList->DataSource = NULL;
    }
}
//---------------------------------------------------------------------------




