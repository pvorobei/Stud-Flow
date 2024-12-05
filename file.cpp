#include "main.h"
#include "file.h"

/*пропуск всех следующих пробелов до любого другого знака*/
#define skip_(x)            \
	while (x.peek() == ' ') \
	x.get()

/*Считывание базы из файла*/
string readBD(Group *head, const string &file) // возвращает колонтитул
{
	ifstream fin(file);
	if (!fin.is_open())
		cout << endl
			 << "Файл не открыт. Проверьте наличие файла в каталоге." << endl;
	Group *curentGroup = head;			 // инициализируем текущую группу (сначала головой)
	Person *curentPerson;				 // указатель на студента
	string runTitle;					 // строка для хранения колонтитула
	getline(fin, runTitle, '\n');		 // считываем колонтитул
	string nameGroup, namePerson, grades; // Временные переменные
	int payment;						 // временная переменная для стипендии
	while (1)
	{
		if (fin.peek() != ' ') // если строка начинаеится не с пробела(строка с именем группы)
		{
			getline(fin, nameGroup, ':');
			fin.get(); // считываем \n
			curentGroup = insertGroup(curentGroup, nameGroup);
			curentPerson = curentGroup->headPerson;
		}
		while (fin.peek() == ' ')
		{
			skip_(fin);
			getline(fin, namePerson, ' ');	   // считываем из файла текущие ФИО
			replaceChar(namePerson, "_", " "); // заменяем в имени все '_' на пробелы
			skip_(fin);
			getline(fin, grades, ' ');
			skip_(fin);
			string tmp;
			getline(fin, tmp, '\n');
			payment = atoi(tmp.c_str());
			curentPerson = insertPerson(curentPerson, namePerson, grades, payment);
		}
		if (fin.eof())
		{
			fin.close();
			break;
		}
	}
	return runTitle;
}
#undef skip_

/*Запись базы в файл*/
void writeBD(Group *head, const string &file, string runTitle)
{
	ofstream fout;
	fout.open(file, ios::out | ios::trunc);
	fout << runTitle << endl;
	Group *curentGroup = head->next; // инициализируем текущую группу первым студентом
	Person *curentPerson;		   // указатель на студента
	string namePerson;			   // Врем переменная имени студента
	while (curentGroup->next)	   // пока не дошли до последней группы
	{
		fout << curentGroup->name << ':' << endl;	 // 
		curentPerson = curentGroup->headPerson->next; // ставим указатель на первого студента
		while (curentPerson->next)					 // пока не дошли до последнего студента
		{
			namePerson = curentPerson->name;
			replaceChar(namePerson, " ", "_"); // заменяем в имени все пробелы на '_'
			fout << "          ";			   
			fout << setw(35) << left << namePerson;
			fout << setw(15) << left << curentPerson->grades;
			fout << setw(9) << right << curentPerson->payment << endl;
			curentPerson = curentPerson->next;
		}
		curentGroup = curentGroup->next;
	}
	fout.close();
}

/*Замена всех символов (а) на (b) в указанной строке*/
void replaceChar(string &str, string a, string b)
{
	size_t pos;
	while ((pos = str.find(a)) != string::npos)
	{
		str.replace(pos, 1, b);
	}
}
