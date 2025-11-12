#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

void process_input_line(istream& input_stream);

void process_input_line(istream& input_stream){
    char ch;
    vector<string> integers;
    vector<string> floats;
    vector<string> characters;

    while (input_stream.get(ch)){
        if (isspace(ch) || isalpha(ch) || ch == '_' || string("=+-*/").find(ch) != string::npos){
            continue;
        }

        if (ch == '\'') {
            string constant;
            constant += ch;
            
            while (input_stream.get(ch)){
                constant += ch;
                if (ch == '\\') {
                    if (input_stream.get(ch)) {
                        constant += ch;
                    }
                }else if (ch == '\'') {
                    // Closing quote
                    characters.push_back(constant);
                    break;
                }
            }
            continue;
        }

        else if (isdigit(ch) || (ch == '.' && isdigit(input_stream.peek()))){
            string constant;
            constant += ch;
            bool is_float = (ch == '.');

            while (input_stream.get(ch) && (isdigit(ch) || ch == '.')){
                if (ch == '.') {
                    is_float = true;
                }
                constant += ch;
            }
            
            input_stream.unget();

            if (constant.length() > 0 && (isdigit(constant[0]) || constant.find('.') != string::npos)){
                if (is_float){
                    floats.push_back(constant);
                } else {
                    integers.push_back(constant);
                }
            }
            continue;
        }
    }

    cout << "Integer: ";
    for (size_t i = 0; i < integers.size(); ++i){
        cout << integers[i];
        if (i < integers.size() - 1) cout << ", ";
    }
    cout << "\n";

    cout << "Float: ";
    for (size_t i = 0; i < floats.size(); ++i) {
        cout << floats[i];
        if (i < floats.size() - 1) cout << ", ";
    }
    cout << "\n";

    cout << "Character: ";
    for (size_t i = 0; i < characters.size(); ++i) {
        string char_val = characters[i].substr(1, characters[i].length() - 2); 
        cout << "'" << char_val << "'";
        if (i < characters.size() - 1) cout << ", ";
    }
    cout << "\n";
}


int main() {
    cout << "Enter a single line of C++ code to analyze (e.g., int x = 45; float y = 4.5; char c = 'a';): \n";
    string input_line;

    if (!getline(cin, input_line) || input_line.empty()) {
        cerr << "No input provided. Using default example line.\n";
    }

    istringstream ss(input_line);

    process_input_line(ss);

    return 0;
}