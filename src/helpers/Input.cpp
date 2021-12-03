#include "Input.h"

using namespace std;

/** Constructor for Parser; generates an array of args split by whitespace and can be used to validate inputs.
* 
*   @param input string split by whitespace to parse
*   @param numArgs expected number of arguments following the operator | default: 1
*   @param longLast last argument should concatenate remaining words (true) or ignore extra words (false) | default: false
*   @param stringValidators array of regex to validate args with | default: NULL
* 
*/
Input::Input(string _input, int _numArgs, bool _longLast) {
    input = _input;
    numArgs = _numArgs;

    trim_whitespace(input);
    stringstream is(input);

    // Fill basic array
    int i = 0;
    string word;
    while (is.good() && i <= numArgs) {
        string temp;
        is >> temp;
        args.push_back(temp);
        ++i;
    }

    operation = args.at(0);
    transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
    if ((is.good() && !_longLast) || (numArgs != i + 1)) {
        isValid = false;
    }

    string nextWord;
    while(is.good() && _longLast) {
        is >> nextWord;
        args.at(numArgs).append(" ").append(nextWord);
    }

    // TODO: Use Regex to validate inputs, update isValid on failure.
}

string Input::getArg(int i) {
    if (i > numArgs || i >= (int)args.size()) { 
        return ""; 
    }
    return args.at(i); 
};

const char *Input::WHITESPACE = " \t\n\r";