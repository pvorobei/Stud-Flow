#include "main.h"
#include "group.h"

/*Инициализация списка групп*/
Group *initGroup()
{
    Group *head = new Group("", NULL, NULL, NULL);
    Group *tail = new Group("", NULL, NULL, NULL);
    head->next = tail;
    tail->prev = head;
    return head;
}

/*Вставить новую группу после указанной*/
Group *insertGroup(Group *item, string &name)
{
    Person *newHeadPerson = initPerson();
    Group *newItem = new Group(name, item->next, item, newHeadPerson);
    item->next->prev = newItem;
    item->next = newItem;
    return newItem;
}

/*Вставить новую группу в конец списка*/
Group *insertGroupTail(Group *item, string &name)
{
    while (item->next->next)
    {
        item = item->next;
    }
    Person *newHeadPerson = initPerson();
    Group *newItem = new Group(name, item->next, item, newHeadPerson);
    item->next->prev = newItem;
    item->next = newItem;
    return newItem;
}

/*Поиск группы по имени*/
Group *searchGroup(Group *item, string &name)
{
    while (item->next)
    {
        if (item->name == name)
        {
            return item;
        }
        item = item->next;
    }
    cout << "Группа не найдена" << endl;
    system("pause");
    return NULL;
}

/*Удалить группу по имени*/
void deletGroup(Group *headGroup, string &name)
{
    Group *item = searchGroup(headGroup, name); // ищем указанную группу
    if (item)
    {
        erasePerson(item); // очищаем список студентов
        item->next->prev = item->prev;
        item->prev->next = item->next;
        delete item;
    }
    else
        return;
}
