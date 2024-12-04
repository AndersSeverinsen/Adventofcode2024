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
    vector<string> lines;
    while (getline (Input, line)) {
        lines.push_back(line);
    }
    int count = 0;
    for (int l = 0; l < lines.size(); l++) {
        for (int i = 0; i < lines[l].size(); i++) {
            if (i <= lines[l].size()-3) {
                // Check for XMAS
                if (lines[l][i] == 'X' && lines[l][i+1] == 'M' && lines[l][i+2] == 'A' && lines[l][i+3] == 'S') {
                    count++;
                } 
                // Check for SAMX
                if (lines[l][i] == 'S' && lines[l][i+1] == 'A' && lines[l][i+2] == 'M' && lines[l][i+3] == 'X') {
                    count++;
                }
                /* Check for X
                *             M
                *              A
                *               S
                */
                if (lines[l][i] == 'X' && lines[l+1][i+1] == 'M' && lines[l+2][i+2] == 'A' && lines[l+3][i+3] == 'S') {
                    count++;
                }
                /* Check for S
                *             A
                *              M
                *               X
                */
                if (lines[l][i] == 'S' && lines[l+1][i+1] == 'A' && lines[l+2][i+2] == 'M' && lines[l+3][i+3] == 'X') {
                    count++;
                }
            }
            if (i >= 3 && l <= lines.size()-3) {
                /* Check for S
                *           A
                *          M
                *         X
                */
                if (lines[l][i] == 'S' && lines[l+1][i-1] == 'A' && lines[l+2][i-2] == 'M' && lines[l+3][i-3] == 'X') {
                    count++;
                }
                /* Check for X
                *           M
                *          A
                *         S
                */
                if (lines[l][i] == 'X' && lines[l+1][i-1] == 'M' && lines[l+2][i-2] == 'A' && lines[l+3][i-3] == 'S') {
                    count++;
                }
            }
            if (l <= lines.size()-3) {
                /* Check for X
                *            M
                *            A
                *            S
                */
                if (lines[l][i] == 'X' && lines[l+1][i] == 'M' && lines[l+2][i] == 'A' && lines[l+3][i] == 'S') {
                    count++;
                }
                /* Check for S
                *            A
                *            M
                *            X
                */
                if (lines[l][i] == 'S' && lines[l+1][i] == 'A' && lines[l+2][i] == 'M' && lines[l+3][i] == 'X') {
                    count++;
                }
            }
        }
    }
    Input.close();
    cout << "Result: " << count << endl;
    assert_equal(expected, count);
}

int main() {
    task1("04-sample", 18);
    task1("04", 2685);
    return 0;
}