#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

#define FILEPATH "/home/padwa/code-playground/Compiler-Design/Source_files/main.cpp"

void extract_lexemes(istream& input_stream, const string& OPERATOR_START_CHARS,
                        const vector<string>& TWO_CHAR_OPERATORS);

void extract_lexemes(istream& input_stream, const string& OPERATOR_START_CHARS,
                        const vector<string>& TWO_CHAR_OPERATORS) {
    char ch;
    vector<string> lexemes;

    while (input_stream.get(ch)){
        if (isspace(ch)) {
            continue;
        }

        if (ch == '#') {
            while (input_stream.get(ch) && ch != '\n'){}
            continue;
        }

        if (ch == '/') {
            if (input_stream.peek() == '/') {
                input_stream.get(); 
                while (input_stream.get(ch) && ch != '\n'){} 
                continue;
            }else if (input_stream.peek() == '*') {
                input_stream.get(); 
                char prev_ch = ' ';
                while (input_stream.get(ch)) {
                    if (prev_ch == '*' && ch == '/'){
                        break;
                    }
                    prev_ch = ch;
                }
                continue;
            }
        }
        
        string lexeme;
        if (isalpha(ch) || ch == '_'){
            lexeme += ch;

            while (input_stream.get(ch) && (isalnum(ch) || ch == '_')){
                lexeme += ch;
            }

            input_stream.unget();
            lexemes.push_back(lexeme);
            continue;
        }else if (isdigit(ch) || (ch == '.' && isdigit(input_stream.peek()))){
            lexeme += ch;

            while (input_stream.get(ch) && (isdigit(ch) || ch == '.')){
                lexeme += ch;
            }
            
            input_stream.unget();
            lexemes.push_back(lexeme);
            continue;
        }else if (OPERATOR_START_CHARS.find(ch) != string::npos){
            lexeme += ch;
            char next_ch = input_stream.peek();

            string potential_op;
            potential_op += ch;
            potential_op += next_ch;

            if (std::find(TWO_CHAR_OPERATORS.begin(), TWO_CHAR_OPERATORS.end(), potential_op) != TWO_CHAR_OPERATORS.end()){
                input_stream.get();
                lexeme = potential_op;
            }
            
            lexemes.push_back(lexeme);
            continue;
        }
    }
    cout << "--- Extracted Lexemes ---\n";
    cout << "Output: ";
    for (size_t i = 0; i < lexemes.size(); ++i){
        cout << lexemes[i];
        if (i < lexemes.size() - 1) {
            cout << ", ";
        }
    }
    cout << "\n-------------------------\n";
}


int main() {
    const string OPERATOR_START_CHARS = "+-*/%=!&|<>(){}[]:;,";

    const vector<string> TWO_CHAR_OPERATORS = {
        "==", "!=", "<=", ">=", "&&", "||", "<<", ">>", 
        "++", "--", "+=", "-=", "*=", "/=", "%="
    };

    ifstream file(FILEPATH);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file at " << FILEPATH << "!\n";
    } else {
        extract_lexemes(file, OPERATOR_START_CHARS, TWO_CHAR_OPERATORS);
        file.close();
    }

    return 0;
}