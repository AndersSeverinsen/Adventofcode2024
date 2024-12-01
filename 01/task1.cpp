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
    vector<int> left;
    vector<int> right;
    string line;
    while (getline (Input, line)) {
        int start, stop;
        bool space = false;
        for (int i = 0; i<line.size(); i++) {
            if (line[i] == ' ' && !space) {
                stop = i;
                space = true;
            } else if (line[i] == ' ' && space) {
                start = i;
                space = true;
            }
        }
        int l = stoi(line.substr(0, stop));
        int r = stoi(line.substr(start, line.size()+1));
        left.push_back(l);
        right.push_back(r);
    }
    Input.close();
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int sum = 0;
    for (int j = 0; j<left.size(); j++) {
        sum += abs(left[j] - right[j]);
    }
    cout << "Result: " << sum << endl;
    assert_equal(expected, sum);
}

int main() {
    task1("01-sample", 11);
    task1("01", 1765812);
    return 0;
}