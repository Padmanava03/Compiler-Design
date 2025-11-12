#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

#define FILEPATH "/home/padwa/code-playground/Compiler-Design/Source_files/string_literal_code.cpp" 

void extract_string_literals(istream& input_stream);

void extract_string_literals(istream& input_stream){
    char ch;
    vector<string> literals;

    while (input_stream.get(ch)){
        if (isspace(ch)){
            continue;
        }

        if (ch == '"'){
            string literal;
            literal += ch;
            
            while (input_stream.get(ch)){
                literal += ch;
                if (ch == '\\'){
                    if (input_stream.get(ch)){
                        literal += ch;
                    }
                }else if (ch == '"'){
                    literals.push_back(literal);
                    break;
                }
            }
            continue;
        }
    }

    for (size_t i = 0; i < literals.size(); ++i){
        cout << literals[i];
        if (i < literals.size() - 1){
            cout << ", ";
        }
    }
    cout << "\n";
}


int main() {
    ifstream file(FILEPATH);
    
    if (!file.is_open()){
        cerr << "Error: Could not open file at " << FILEPATH << "!\n";
    }else{
        extract_string_literals(file);
        file.close();
    }

    return 0;
}