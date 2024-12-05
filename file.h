#pragma once
#ifndef FILE_H
#define FILE_H

using namespace ::std;

struct Person;
struct Group;

string readBD(Group *head, const string &file);
void writeBD(Group *head, const string &file, string runTitle);
void replaceChar(string &str, string a, string b);

#endif