#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;

#define FILEPATH "/home/padwa/code-playground/Compiler-Design/Source_files/main.cpp"

void clean_source_code(istream& input_stream);

void clean_source_code(istream& input_stream){
    char ch;
    bool in_whitespace = true; 
    
    while (input_stream.get(ch)){
        if (ch == '\n') {
            if (!in_whitespace){
                cout << '\n';
                in_whitespace = true; 
            }
            continue;
        }

        if (isspace(ch)){
            in_whitespace = true;
            continue;
        }

        if (in_whitespace){
            cout << ' '; 
            in_whitespace = false;
        }
        
        if (ch == '/'){
            if (input_stream.peek() == '/'){
                input_stream.get();
                while (input_stream.get(ch) && ch != '\n'){}

                if (ch == '\n'){
                    cout << '\n';
                }
                in_whitespace = true;
                continue;
            }else if (input_stream.peek() == '*'){
                input_stream.get();
                char prev_ch = ' ';
                bool comment_end = false;

                while (input_stream.get(ch)){
                    if (ch == '\n') {
                        cout << '\n';
                    }
                    if (prev_ch == '*' && ch == '/'){
                        comment_end = true;
                        break;
                    }
                    prev_ch = ch;
                }
                in_whitespace = true;
                continue;
            }else {
                cout << ch;
                in_whitespace = false;
                continue;
            }
        }

        cout << ch;
        in_whitespace = false;
    }
}


int main() {
    ifstream file(FILEPATH);
    
    if (!file.is_open()){
        cerr << "Error: Could not open file at " << FILEPATH << "!\n";
    } else {
        cout << "--- Cleaned Source Code Output ---\n";
        clean_source_code(file);
        cout << "\n--------------------------------\n";
        file.close();
    }

    return 0;
}