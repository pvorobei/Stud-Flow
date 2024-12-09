/*
    Персональное задание:
    Вывести (с разбивкой по группам) фамилии всех студентов, не получающих стипендии
    Hello, github!!
*/

#include "main.h"

const string file = "flow.txt"; // имя файла, с которым работаем

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Person *curentPerson; // указатель на студента
    string nameNew, nameSearch, groupTmp, grades;
    int payment, comand = 0; // payment - стипендия, comand - команда для меню
    cout << endl;
    cout << "Загрузка потока: " << endl;
    Group *headGroup = initGroup();            // инициализируем список групп (сохраняя голову)
    Group *curentGroup = headGroup;            // ставим указатель на текущую группу
    string runTitle = readBD(headGroup, file); // строка для хранения колонтитула

    do
    {
        BDPrint(headGroup, runTitle); // печатаем поток
        cout << endl;
        cout << setw(25) << left << "0 - выход без изменений";
        cout << setw(46) << left << "5 - Изменить имя группы" << endl;
        cout << setw(25) << left << "1 - добавить группу";
        cout << setw(46) << left << "6 - Изменить имя студента" << endl;
        cout << setw(25) << left << "2 - удалить группу";
        cout << setw(46) << left << "7 - Изменить набор оценок студента" << endl;
        cout << setw(25) << left << "3 - добавить студента";
        cout << setw(46) << left << "8 - Изменить стипендию студента" << endl;
        cout << setw(25) << left << "4 - удалить студента";
        cout << setw(46) << left << "9 - сохранить текущее состояние потока в файл" << endl;
        cout << endl;
        cout << "Введите команду: ";
        cin >> comand;
        switch (comand)
        {
        /*---добавление группы---*/
        case 1:
            cout << endl;
            cin.get(); // вычитываем из буфера \n
            cout << "Имя новой группы:" << endl;
            getline(cin, nameNew, '\n'); // читаем до следующего \n
            cout << "Добавить в начало - 0, Добавить в конец - 1, Добавить после - имя:" << endl;
            getline(cin, nameSearch, '\n');
            if (nameSearch == "0")
            {
                insertGroup(headGroup, nameNew); // если ввели 0, то вставляем элемент после головы
            }
            else if (nameSearch == "1")
            {
                insertGroupTail(headGroup, nameNew); // если ввели 1, то вставляем элемент перед хвостом
            }
            else
            {
                curentGroup = searchGroup(headGroup, nameSearch); // в противном случае ищем имя сущ-го студента
                if (curentGroup)
                    insertGroup(curentGroup, nameNew); // и вставляем нового после него
                else
                    break;
            }
            break;

        /*---Удаление группы---*/
        case 2:
            cout << "Имя удаляемой группы:" << endl;
            cin.get();
            getline(cin, nameSearch, '\n');
            deletGroup(headGroup, nameSearch);
            break;

        /*---Добавление нового студента---*/    
        case 3:
            cout << endl;
            cin.get();
            cout << "Полные ФИО нового студента:" << endl;
            getline(cin, nameNew, '\n');
            if (countChar(nameNew, ' ') != 2) // проверяем на правильность ввода(2 пробела)
            {
                cout << "Неверный формат Ф И О" << endl;
                system("pause");
                break;
            }
            cout << "Набор из пяти оценок(через запятую, без пробелов):" << endl;
            getline(cin, grades, '\n');
            if (countChar(grades, ' ') > 0) // проверяем на правильность ввода(без  пробелов)
            {
                cout << "Неверный формат Оценок" << endl;
                system("pause");
                break;
            }
            cout << "Размер стипендии:" << endl;
            cin >> payment;
            cout << "Имя группы, в которую нужно добавить студента:" << endl;
            cin >> groupTmp;
            cout << "Добавить в начало - 0, Добавить в конец - 1, Добавить после - имя:" << endl;
            cin >> nameSearch;
            curentGroup = searchGroup(headGroup, groupTmp);
            if (!curentGroup)
                break;
            else
            {
                if (nameSearch == "0")
                {
                    curentPerson = curentGroup->headPerson;
                    insertPerson(curentPerson, nameNew, grades, payment);
                }
                else if (nameSearch == "1")
                {
                    insertPersonTail(curentGroup, nameNew, grades, payment);
                }
                else
                {
                    curentPerson = searchPerson(curentGroup, nameSearch);
                    if (!curentPerson)
                        break;
                    else
                        insertPerson(curentPerson, nameNew, grades, payment);
                }
            }
            break;

        /*---Удаление студента из группы---*/    
        case 4:
            cout << endl;
            cin.get();
            cout << "Удалить из группы:" << endl;
            getline(cin, groupTmp, '\n');
            curentGroup = searchGroup(headGroup, groupTmp);
            cout << "Имя удаляемого студента:" << endl;
            getline(cin, nameSearch, '\n');
            deletPerson(curentGroup, nameSearch);
            break;

        /*---Изменение имени группы---*/    
        case 5:
            cout << endl;
            cout << "Предыдущее имя группы: ";
            cin >> groupTmp;
            curentGroup = searchGroup(headGroup, groupTmp);
            cout << "Новое имя группы: ";
            cin >> groupTmp;
            curentGroup->name = groupTmp;
            break;

        /*---Изменение имени студента---*/    
        case 6:
            cout << endl;
            cout << "Группа: ";
            cin >> groupTmp;
            curentGroup = searchGroup(headGroup, groupTmp);
            if (curentGroup)
            {
                cout << "Предыдущее имя: ";
                cin.get();
                getline(cin, nameSearch, '\n');
                curentPerson = searchPerson(curentGroup, nameSearch);
                if (curentPerson)
                {
                    cout << "Новое имя студента: ";
                    getline(cin, nameNew, '\n');
                    if (countChar(nameNew, ' ') != 2) // проверяем на правильность ввода(2 пробела)
                    {
                        cout << "Неверный формат Ф И О" << endl;
                        system("pause");
                        break;
                    }
                    curentPerson->name = nameNew;
                }
            }
            break;

        /*---Изменение оценок студента---*/     
        case 7:
            cout << endl;
            cout << "Группа: ";
            cin >> groupTmp;
            curentGroup = searchGroup(headGroup, groupTmp);
            if (curentGroup)
            {
                cout << "Имя студента: ";
                cin.get();
                getline(cin, nameSearch, '\n');
                curentPerson = searchPerson(curentGroup, nameSearch);
                if (curentPerson)
                {
                    cout << "Новый набор оценок(через запятую, без пробелов): ";
                    getline(cin, grades, '\n');
                    if (countChar(grades, ' ') > 0) // проверяем на правильность ввода(без  пробелов)
                    {
                        cout << "Неверный формат Оценок" << endl;
                        system("pause");
                        break;
                    }
                    curentPerson->grades = grades;
                }
            }
            break;

        /*---Изменение стипендии студента---*/     
        case 8:
            cout << endl;
            cout << "Группа: ";
            cin >> groupTmp;
            curentGroup = searchGroup(headGroup, groupTmp);
            if (curentGroup)
            {
                cout << "Имя студента: ";
                cin.get();
                getline(cin, nameSearch, '\n');
                curentPerson = searchPerson(curentGroup, nameSearch);
                if (curentPerson)
                {
                    cout << "Новая стипендия: ";
                    cin >> payment;
                    curentPerson->payment = payment;
                }
            }
            break;

        /*---Сохранение потока в файл---*/     
        case 9:
            cout << endl;
            writeBD(headGroup, file, runTitle);
            cout << "БД сохранена" << endl;
            system("pause");
            break;
        default:
            break;
        }
        system("CLS");
    } while (comand);

    system("CLS");
    cout << endl;
    cout << "Фамилии всех студентов, не получающих стипендии:" << endl;
    BDPrintNoPayment(headGroup); // персональное задание
    system("pause");
    return 0;
}

/*Вывод потока в консоль*/
void BDPrint(Group *head, string runTitle)
{
    cout << runTitle << endl;
    Group *curentGroup = head->next; // инициализируем текущую группу первым студентом
    Person *curentPerson;            // указатель на студента
    while (curentGroup->next)        // пока не дошли до последней группы
    {
        cout << curentGroup->name << ':' << endl;     
        curentPerson = curentGroup->headPerson->next; // ставим указатель на первого студента
        while (curentPerson->next)                    // пока не дошли до последнего студента indent - отступ
        {
            cout << setw(10) << left << "";
            cout << setw(35) << left << curentPerson->name;
            cout << setw(15) << left << curentPerson->grades;
            cout << setw(9) << right << curentPerson->payment << endl;
            curentPerson = curentPerson->next;
        }
        curentGroup = curentGroup->next;
    }
}

/*Вывод фамилий студентов без стипендии в консоль*/
void BDPrintNoPayment(Group *head)
{
    cout << "№ Группы__Фамилия" << endl;
    Group *curentGroup = head->next; // инициализируем текущую группу первым студентом
    Person *curentPerson;            // указатель на студента
    while (curentGroup->next)        // пока не дошли до последней группы
    {
        int groupTmp = 0;
        curentPerson = curentGroup->headPerson->next;
        while (curentPerson->next)
        {
            if (curentPerson->payment == 0)
                groupTmp++;
            curentPerson = curentPerson->next;
        }
        if (groupTmp)
        {
            cout << curentGroup->name << ':' << endl;
            curentPerson = curentGroup->headPerson->next; // ставим указатель напервого студента
            while (curentPerson->next)                    // пока не дошли до последнего студента
            {
                if (curentPerson->payment == 0)
                {
                    char *buf = new char[curentPerson->name.length() + 1];
                    curentPerson->name.copy(buf, curentPerson->name.length() + 1); // копируем строку в массив символов
                    int n = 0;
                    while (buf[n] != ' ') // Считаем кол символов до 1го пробела
                    {
                        n++;
                        if (buf[n] == '\0')
                            break;
                    }
                    string nameTmp = curentPerson->name.substr(0, n); // выделяем соответсвующую подстроку(Фамилию)
                    cout << setw(10) << left << "";
                    cout << setw(35) << left << nameTmp << endl;
                    delete[] buf;
                }
                curentPerson = curentPerson->next;
            }
        }
        curentGroup = curentGroup->next;
    }
}
// Какой-то комметарий
/*Подсчёт количества конкретных символов в указанной строке*/
int countChar(string &str, char ch)
{
    int count = 0;
    for (size_t i = 0; (i = str.find(ch, i)) != string::npos; i++)
    {
        count++;
    }
    return count;
}