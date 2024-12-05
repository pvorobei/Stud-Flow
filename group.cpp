#include "main.h"
#include "group.h"

/*������������� ������ �����*/
Group *initGroup()
{
    Group *head = new Group("", NULL, NULL, NULL);
    Group *tail = new Group("", NULL, NULL, NULL);
    head->next = tail;
    tail->prev = head;
    return head;
}

/*�������� ����� ������ ����� ���������*/
Group *insertGroup(Group *item, string &name)
{
    Person *newHeadPerson = initPerson();
    Group *newItem = new Group(name, item->next, item, newHeadPerson);
    item->next->prev = newItem;
    item->next = newItem;
    return newItem;
}

/*�������� ����� ������ � ����� ������*/
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

/*����� ������ �� �����*/
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
    cout << "������ �� �������" << endl;
    system("pause");
    return NULL;
}

/*������� ������ �� �����*/
void deletGroup(Group *headGroup, string &name)
{
    Group *item = searchGroup(headGroup, name); // ���� ��������� ������
    if (item)
    {
        erasePerson(item); // ������� ������ ���������
        item->next->prev = item->prev;
        item->prev->next = item->next;
        delete item;
    }
    else
        return;
}
