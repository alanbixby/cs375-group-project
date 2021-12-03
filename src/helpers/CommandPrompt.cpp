#include "CommandPrompt.h"

using namespace std;

vector<string> validCommands = getCommands();

Input* promptCommand(string executable, int length = 1, bool concat = false) {
  while (true) {
    cout << "[";
    for (int i = 0; i < (int)validCommands.size(); i++) {
      cout << "\"" << validCommands.at(i) << "\"";
      if (i != (int)validCommands.size() - 1) {
        cout << ", ";
      }
    }
    cout << "]\n " << executable << ": ";

    string input;
    getline(cin, input);

    Input* command = new Input(input, length, concat);
    string operation = command->getOperation();

    for (int i = 0; i < (int)validCommands.size(); i++) {
      if (operation == validCommands.at(i)) {
        return command;
      }
    }

    delete command;
    cout << "[X] Command not recognized. Please try again.\n\n";
  }
  return NULL;
}

bool compareFunction(string a, string b) { return a < b; }

vector<string> getCommands() {
  DIR* dir;
  struct dirent* dir_entry;
  vector<string> filenames;
  bool hasExit = false;
  bool hasDebug = false;
  if ((dir = opendir("./src/helpers/commands")) != nullptr) {
    while ((dir_entry = readdir(dir)) != nullptr) {
      if (string(dir_entry->d_name).find(".h") != string::npos) {
        string filename = dir_entry->d_name;
        filename = filename.substr(0, filename.length() - 2);  // remove .h
        filename[0] = tolower(filename[0]);                    // make lowercase
        if (filename == "exit") {
          hasExit = true;
        } else if (filename == "debug") {
          hasDebug = true;
        } else {
          filenames.push_back(filename);
        }
      }
    }
  }
  closedir(dir);
  sort(filenames.begin(), filenames.end(), compareFunction);
  if (hasDebug) filenames.push_back("debug");
  if (hasExit) filenames.push_back("exit");

  return filenames;
}