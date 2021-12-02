#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

class Input {
 public:
  /** Constructor for Command; generates an array of args split by whitespace
   * and can be used to validate inputs.
   *
   *   @param input string split by whitespace to parse
   *   @param numArgs=0 expected number of arguments following the operator
   *   @param longLast=false last argument should concatenate remaining words
   *   @param stringValidators=NULL array of regex to validate args with
   *
   */
  Input(string input, int numArgs = 0, bool longLast = false);
  ~Input() {};
  string getInput() { return input; };
  string getOperation() { return operation; };
  string getArg(int i);
  vector<string> getArgs() { return args; };
  int getNumArgs() { return numArgs; };
  static void trim_whitespace(string &str) {
    str.erase(0, str.find_first_not_of(WHITESPACE));
    str.erase(str.find_last_not_of(WHITESPACE) + 1);
  };

 private:
  static const char *WHITESPACE;
  bool isValid = true;
  string input;
  string operation;
  vector<string> args;
  int numArgs;
};

#endif