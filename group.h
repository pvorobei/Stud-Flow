#pragma once
#ifndef GROUP_H
#define GROUP_H

using namespace ::std;

struct Person;

struct Group
{
    string name;
    Group *next;
    Group *prev;
    Person *headPerson;
    Group(string nm, Group *n, Group *p, Person *hL)
    {
        name = nm;
        next = n;
        prev = p;
        headPerson = hL;
    }
};

Group *initGroup();
Group *insertGroup(Group *item, string &name);
Group *insertGroupTail(Group *item, string &name);
Group *searchGroup(Group *item, string &name);
void deletGroup(Group *headGroup, string &name);

#endif
