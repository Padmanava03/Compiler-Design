#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

#define FILEPATH "/home/padwa/code-playground/Compiler-Design/Source_files/main.cpp" 

bool is_keyword(const string& token, const vector<string>& KEYWORDS);
void lex_analyze_file(istream& input_stream, map<string, int>& counts, const vector<string>& KEYWORDS,
                        const string& OPERATOR_START_CHARS, const string& SPECIAL_SYMBOLS,
                        const vector<string>& TWO_CHAR_OPERATORS);
void print_results(const map<string, int>& counts);

bool is_keyword(const string& token, const vector<string>& KEYWORDS) {
    return std::find(KEYWORDS.begin(), KEYWORDS.end(), token) != KEYWORDS.end();
}

void lex_analyze_file(istream& input_stream, map<string, int>& counts, const vector<string>& KEYWORDS,
                        const string& OPERATOR_START_CHARS, const string& SPECIAL_SYMBOLS,
                        const vector<string>& TWO_CHAR_OPERATORS){
    char ch;

    while (input_stream.get(ch)) {
        if (isspace(ch)) {
            continue;
        }

        if (ch == '#') {
            while (input_stream.get(ch) && ch != '\n') {}
            continue;
        }

        if (ch == '"' || ch == '\''){
            counts["Special Symbols"]++;
            char end_char = ch;
            
            while (input_stream.get(ch)){
                if (ch == '\\') {
                    if (input_stream.get(ch)) { continue; }
                } else if (ch == end_char) {
                    counts["Special Symbols"]++;
                    break; 
                }
            }
            continue;
        }

        if (isalpha(ch) || ch == '_'){
            string token;
            token += ch;

            while (input_stream.get(ch) && (isalnum(ch) || ch == '_')){
                token += ch;
            }

            input_stream.unget();
            
            if (is_keyword(token, KEYWORDS)){
                counts["Keywords"]++;
            } else {
                counts["Identifiers"]++;
            }
            continue;
        }else if (isdigit(ch) || (ch == '.' && isdigit(input_stream.peek()))){
            string token;
            token += ch;

            while (input_stream.get(ch) && (isdigit(ch) || ch == '.')){
                token += ch;
            }
            
            input_stream.unget();
            counts["Numbers"]++;
            continue;
        }else if (OPERATOR_START_CHARS.find(ch) != string::npos){

            char next_ch = input_stream.peek();
            string potential_op;
            potential_op += ch;
            potential_op += next_ch;

            if (find(TWO_CHAR_OPERATORS.begin(), TWO_CHAR_OPERATORS.end(),
                        potential_op) != TWO_CHAR_OPERATORS.end()){
                input_stream.get();
            }

            counts["Operators"]++;
            continue;
        }else if (SPECIAL_SYMBOLS.find(ch) != string::npos){
            counts["Special Symbols"]++;
            continue;
        }
    }
}

void print_results(const map<string, int>& counts){
    cout << "--- Lexical Analysis Results ---\n";
    cout << "Keywords:        " << counts.at("Keywords") << endl;
    cout << "Identifiers:     " << counts.at("Identifiers") << endl;
    cout << "Operators:       " << counts.at("Operators") << endl;
    cout << "Numbers:         " << counts.at("Numbers") << endl;
    cout << "Special Symbols: " << counts.at("Special Symbols") << endl;
    cout << "--------------------------------\n";
}


int main(){
    const vector<string> KEYWORDS = {
            "cout", "cin", "int", "float", "char", "for", "while", "if", "else", "break", 
            "endl", "return", "using", "namespace", "std", "vector"
        };

    const string OPERATOR_START_CHARS = "+-*/%=&|<>!";

    const string SPECIAL_SYMBOLS = "(){}[]:;,." ;

    const vector<string> TWO_CHAR_OPERATORS = {
        "==", "!=", "<=", ">=", "&&", "||", "<<", ">>", 
        "++", "--", "+=", "-=", "*=", "/=", "%=", "&=",
        "|=", "^=" 
    };

    map<string, int> counts = {
        {"Keywords", 0},
        {"Identifiers", 0},
        {"Operators", 0},
        {"Numbers", 0},
        {"Special Symbols", 0}
    };
    
    ifstream file(FILEPATH);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file at " << FILEPATH << "!\n";
    } else {
        lex_analyze_file(file, counts, KEYWORDS, OPERATOR_START_CHARS, SPECIAL_SYMBOLS, TWO_CHAR_OPERATORS);
        file.close();
    }
    
    print_results(counts);

    return 0;
}