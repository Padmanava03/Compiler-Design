#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void process_input_line(istream& input_stream, const vector<string>& KEYWORDS, const string& ALL_DELIMITER_CHARS);

void process_input_line(istream& input_stream, const vector<string>& KEYWORDS, const string& ALL_DELIMITER_CHARS) {
    char ch;
    cout << "--- Lexeme Classification Results ---\n";
    cout << "Lexeme\t\tType\n";
    cout << "-------------------------------------\n";

    while (input_stream.get(ch)) {
        if (isspace(ch)) {
            continue;
        }

        string lexeme = "";
        
        if (isalpha(ch) || ch == '_') {
            lexeme += ch;

            while (input_stream.get(ch) && (isalnum(ch) || ch == '_')) {
                lexeme += ch;
            }

            input_stream.unget();

            if (std::find(KEYWORDS.begin(), KEYWORDS.end(), lexeme) != KEYWORDS.end()) {
                cout << lexeme << "\t\tKEYWORD\n";
            } else {
                cout << lexeme << "\t\tIDENTIFIER\n";
            }
            continue;
        }
        
        else if (isdigit(ch) || (ch == '.' && isdigit(input_stream.peek()))) {
            lexeme += ch;

            while (input_stream.get(ch) && (isdigit(ch) || ch == '.')) {
                lexeme += ch;
            }
            
            input_stream.unget();
            cout << lexeme << "\t\tCONSTANT\n";
            continue;
        }

        else{}
    }
    cout << "-------------------------------------\n";
}


int main() {
    const vector<string> KEYWORDS = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", 
        "double", "else", "enum", "extern", "float", "for", "goto", "if", 
        "inline", "int", "long", "main", "namespace", "private", "public", 
        "register", "return", "short", "signed", "sizeof", "static", "struct", 
        "switch", "typedef", "union", "unsigned", "using", "void", "volatile", 
        "while", "cout", "cin", "endl", "vector"
    };

    const string ALL_DELIMITER_CHARS = "+-*/%=!&|<>(){}[]:;,." ; 

    cout << "Enter a single line of C++ code to analyze (e.g., int result = val1 + 10;): \n";
    string input_line;
    
    if (!getline(cin, input_line) || input_line.empty()) {
        cerr << "No input provided. Using default example line.\n";
    }

    istringstream ss(input_line);

    process_input_line(ss, KEYWORDS, ALL_DELIMITER_CHARS);

    return 0;
}