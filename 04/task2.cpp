#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <assert.h>
#include <tuple>

using namespace std;

void assert_equal(int expected, int actual) {
    if (expected != actual) {
        cerr << "Assert failed! Expected: " << expected << ", but got: " << actual << endl;
    }
}

void task2(string name, int expected) {
    cout << "Task 2" << endl;
    cout << "Input: " << name << endl;
    string fileame = name + ".txt";
    ifstream Input(fileame);
    if (!Input.is_open()) {
        cerr << "Error opening the file!";
        return;
    }
    int sum = 0;
    string line;
    vector<string> lines;
    while (getline (Input, line)) {
        lines.push_back(line);
    }
    int count = 0;
    for (int l = 1; l < lines.size()-1; l++) {
        for (int i = 1; i < lines[l].size()-1; i++) {
            /*          M M
            *  Check for A
            *           S S
            */
            if (lines[l][i] == 'A' && lines[l-1][i-1] == 'M' && lines[l+1][i+1] == 'S' && lines[l-1][i+1] == 'M' && lines[l+1][i-1] == 'S') {
                count++;
            }
            /*          S S
            *  Check for A
            *           M M
            */
            if (lines[l][i] == 'A' && lines[l-1][i-1] == 'S' && lines[l+1][i+1] == 'M' && lines[l-1][i+1] == 'S' && lines[l+1][i-1] == 'M') {
                count++;
            }
            /*          M S
            *  Check for A
            *           M S
            */
            if (lines[l][i] == 'A' && lines[l-1][i-1] == 'M' && lines[l+1][i+1] == 'S' && lines[l-1][i+1] == 'S' && lines[l+1][i-1] == 'M') {
                count++;
            }
            /*          S M
            *  Check for A
            *           S M
            */
            if (lines[l][i] == 'A' && lines[l-1][i-1] == 'S' && lines[l+1][i+1] == 'M' && lines[l-1][i+1] == 'M' && lines[l+1][i-1] == 'S') {
                count++;
            }
        }
    }
    Input.close();
    cout << "Result: " << count << endl;
    assert_equal(expected, count);
}

int main() {
    task2("04-sample", 9);
    task2("04", 2048);
    return 0;
}