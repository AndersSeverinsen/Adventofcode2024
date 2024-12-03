#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <assert.h>

using namespace std;

void assert_equal(int expected, int actual) {
    if (expected != actual) {
        cerr << "Assert failed! Expected: " << expected << ", but got: " << actual << endl;
    }
}

void task1(string name, int expected) {
    cout << "Task 1" << endl;
    cout << "Input: " << name << endl;
    string fileame = name + ".txt";
    ifstream Input(fileame);
    if (!Input.is_open()) {
        cerr << "Error opening the file!";
        return;
    }
    int sum = 0;
    string line;
    while (getline (Input, line)) {
        int start = 0, stop = 0;
        int startright, stopright;
        int num1, num2;
        bool mul, rightparen;
        for (int i = 0; i<line.size(); i++) {
            if (i >= line.size()-7) {
                break;
            }
            if (line[i] == 'm' && line[i+1] == 'u' && line[i+2] == 'l' && line[i+3] == '(') {
                mul = true;
                rightparen = false;
                start = i+4;
                i += 4;
                for (int j = i; j<line.size(); j++) {
                    i = j;
                    if (line[i] == ')') {
                        if (mul && rightparen) {
                            num1 = stoi(line.substr(start, stop - start));
                            num2 = stoi(line.substr(startright, i - startright));
                            sum += num1 * num2;
                        }
                        i = j;
                        mul = false;
                        break;
                    } else if (line[i] == ',') {
                        rightparen = true;
                        startright = i+1;
                    } else if (mul && !rightparen && (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7' || line[i] == '8' || line[i] == '9')) {
                        stop = i+1;
                    } else if (mul && rightparen && (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7' || line[i] == '8' || line[i] == '9')) {
                        stopright = i;
                    } else {
                        mul = false;
                        rightparen = false;
                        break;
                    }
                }
                mul = false;
            }
        }
    }
    Input.close();
    cout << "Result: " << sum << endl;
    assert_equal(expected, sum);
}

int main() {
    task1("03-sample", 161);
    task1("03", 174336360);
    return 0;
}