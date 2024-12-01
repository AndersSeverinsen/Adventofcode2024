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

int num_of_digits(vector<int> right, int l) {
    int count = 0;
    for (int i = 0; i<right.size(); i++) {
        if (right[i] == l) {
            count++;
        }
    }
    return count;
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
    int sim = 0;
    for (int j = 0; j<left.size(); j++) {
        sim += left[j] * num_of_digits(right, left[j]);
    }
    cout << "Result: " << sim << endl;
    assert_equal(expected, sim);
}

int main() {
    task2("01-sample", 31);
    task2("01", 20520794);
    return 0;
}