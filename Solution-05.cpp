#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void process_input_line(istream& input_stream, const string& ARITHMETIC_SINGLE_OPS,
                        const string& MULTI_CHAR_START, const string& ALL_OPERATOR_CHARS);


void process_input_line(istream& input_stream, const string& ARITHMETIC_SINGLE_OPS,
                        const string& MULTI_CHAR_START, const string& ALL_OPERATOR_CHARS) {
    char ch;
    cout << "--- Operator Classification Results ---\n";
    cout << "Lexeme\t\tType\n";
    cout << "-------------------------------------\n";

    while (input_stream.get(ch)) {
        
        if (isspace(ch)) {
            continue;
        }

        string lexeme = "";
        
        if (ALL_OPERATOR_CHARS.find(ch) != string::npos) {
            lexeme += ch;
            char next_ch = input_stream.peek();
            string category = "";

            if (MULTI_CHAR_START.find(ch) != string::npos && !input_stream.eof()) {
                string potential_op;
                potential_op += ch;
                potential_op += next_ch;

                if (potential_op == "==" || potential_op == "!=" || potential_op == "<=" || potential_op == ">=") {
                    category = "RELATIONAL OPERATOR";
                } 
                else if (potential_op == "&&" || potential_op == "||") {
                    category = "LOGICAL OPERATOR";
                }
                
                if (!category.empty()) {
                    input_stream.get(); 
                    lexeme = potential_op;
                    cout << lexeme << "\t\t" << category << "\n";
                    continue;
                }
            } 
            

            if (ARITHMETIC_SINGLE_OPS.find(ch) != string::npos) {
                category = "ARITHMETIC OPERATOR";
            } 

            else if (ch == '<' || ch == '>') {
                category = "RELATIONAL OPERATOR";
            }

            else if (ch == '!') {
                category = "LOGICAL OPERATOR";
            }

            if (!category.empty()) {
                cout << lexeme << "\t\t" << category << "\n";
            }
            continue;
        }

        else {}
    }
    cout << "-------------------------------------\n";
}


int main() {
    const string ARITHMETIC_SINGLE_OPS = "+-*/%";
    const string MULTI_CHAR_START = "=&|<>!";
    const string ALL_OPERATOR_CHARS = "+-*/%=&|<>!"; 

    cout << "Enter a single line of C++ code to analyze (e.g., if (a <= b && c != 0) { x = y * 5; }): \n";
    string input_line;
    
    if (!getline(cin, input_line) || input_line.empty()) {
        cerr << "No input provided. Using default example line.\n";
        input_line = "if (a <= b && !c) { result = x / 10 + 5 % 2; }";
    }

    istringstream ss(input_line);
    
    process_input_line(ss, ARITHMETIC_SINGLE_OPS, MULTI_CHAR_START, ALL_OPERATOR_CHARS);

    return 0;
}