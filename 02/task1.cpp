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

bool is_report_safe(vector<int> report) {
    int k = report[0];
    bool is_safe = true;
    if (k < report[1]) {
        for (int i = 0; i<report.size()-1; i++) {
            if (report[i] < report[i+1] && report[i]+3 >= report[i+1]) {
                is_safe = true;
            } else {
                return false;
            }
        }
    } else if (k > report[1]) {
        for (int i = 0; i<report.size()-1; i++) {
            if (report[i] > report[i+1] && report[i]-3 <= report[i+1]) {
                is_safe = true;
            } else {
                return false;
            }
        }
    } else {
        return false;
    }
    return is_safe;
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
    int safe = 0;
    string line;
    while (getline (Input, line)) {
        int start = 0, stop = 0;
        vector<int> report;
        for (int i = 0; i<line.size(); i++) {
            if (line[i] == ' ' || i == line.size()-1) {
                stop = i+1;
                int num = stoi(line.substr(start, stop - start));
                report.push_back(num);
                start = i+1;
            }
        }
        int k = report[0];
        bool is_safe = is_report_safe(report);
        if (is_safe) {
            safe++;
        }
    }
    Input.close();
    cout << "Result: " << safe << endl;
    assert_equal(expected, safe);
}

int main() {
    task1("02-sample", 2);
    task1("02", 549);
    return 0;
}