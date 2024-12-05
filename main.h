#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <string>

#include "person.h"
#include "group.h"
#include "file.h"

using namespace ::std;

void BDPrint(Group *head, string runTitle);
void BDPrintNoPayment(Group *head);
int countChar(string &str, char ch);

#endif