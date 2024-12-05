#pragma once
#ifndef PERSON_H
#define PERSON_H

using namespace ::std;

struct Group;

struct Person
{
  string name;   // ФИО
  string grades; // набор из 5 оценок
  int payment;   // стипендия
  Person *next;
  Person *prev;
  Person(string nm, string gr, int pmt, Person *n, Person *p)
  {
    name = nm;
    grades = gr;
    payment = pmt;
    next = n;
    prev = p;
  }
};

Person *initPerson();
Person *insertPerson(Person *item, string &name, string &grades, int payment);
Person *insertPersonTail(Group *Group, string &name, string &grades, int payment);
Person *searchPerson(Group *item, string &name);
void erasePerson(Group *item);
void deletPerson(Group *headGroup, string &name);

#endif