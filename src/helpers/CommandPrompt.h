#ifndef COMMAND_PROMPT_H
#define COMMAND_PROMPT_H

#include <dirent.h>

#include <iostream>
#include <vector>

#include "Input.h"

using namespace std;

Input* promptCommand(string, int, bool);
bool compareFunction(string, string);
vector<string> getCommands();

#endif