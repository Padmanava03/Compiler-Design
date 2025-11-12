#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(){
    int a = 10 + 1;
    int b = 20;
    int sum = a + b;

    cout << "Sum" << sum << endl;

    vector<int> numbers = {1, 2, 3, 4, 5};

    cout << "This is a string literal example." << endl;

    vector<string> stringLiterals = {
        "Hello, World!",
        "C++ is fun.",
        "String literals are enclosed in double quotes."
    };

    return 0;
}