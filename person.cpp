#include "main.h"
#include "person.h"

/*Инициализация списка студентов группы*/
Person *initPerson()
{
	Person *head = new Person("", "", 0, NULL, NULL);
	Person *tail = new Person("", "", 0, NULL, NULL);
	head->next = tail;
	tail->prev = head;
	return head;
}

/*Добавить нового студента после указанного*/
Person *insertPerson(Person *item, string &name, string &grades, int payment)
{
	Person *newItem = new Person(name, grades, payment, item->next, item);
	item->next->prev = newItem;
	item->next = newItem;
	return newItem;
}

/*Добавить нового студента в конец списка*/
Person *insertPersonTail(Group *group, string &name, string &grades, int payment)
{
	Person *tmp = group->headPerson;
	while (tmp->next->next)
	{
		tmp = tmp->next;
	}
	Person *newItem = new Person(name, grades, payment, tmp->next, tmp);
	tmp->next->prev = newItem;
	tmp->next = newItem;
	return newItem;
}

/*Поиск студента по имени в указанной группе*/
Person *searchPerson(Group *group, string &name)
{
	Person *tmp = group->headPerson->next;
	while (tmp->next)
	{
		if (tmp->name == name)
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	cout << "студент не найден" << endl;
	system("pause");
	return NULL;
};

/*Очистить список студентов указанной группы*/
void erasePerson(Group *itemGroup)
{
	Person *tmp;
	Person *item = itemGroup->headPerson; // ставим указатель на голову
	while (item)						 // удаляем вместе с головой и хвостом
	{
		tmp = item;
		item = item->next;
		delete tmp;
	}
}

/*Удалить студента по имени*/
void deletPerson(Group *group, string &name)
{
	Person *item = searchPerson(group, name); // ищем студента
	if (item)
	{
		item->next->prev = item->prev;
		item->prev->next = item->next;
		delete item;
	}
	else return;
}