#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <assert.h>
#include <tuple>

using namespace std;

void assert_equal(long expected, long actual) {
    if (expected != actual) {
        cerr << "Assert failed! Expected: " << expected << ", but got: " << actual << endl;
    }
}

bool equation_possible(vector<long> numbers, long test_value, int index, long acc) {
    if (index == numbers.size()) {
        return acc == test_value;
    }
    bool plus_branch = equation_possible(numbers, test_value, index+1, acc + numbers[index]);
    bool mul_branch = equation_possible(numbers, test_value, index+1, acc * numbers[index]);
    return plus_branch || mul_branch;
}

void task1(string name, long expected) {
    cout << "Task 1" << endl;
    cout << "Input: " << name << endl;
    string fileame = name + ".txt";
    ifstream Input(fileame);
    if (!Input.is_open()) {
        cerr << "Error opening the file!";
        return;
    }
    string line;
    long sum = 0;
    while (getline (Input, line)) {
        long test_value = 0;
        bool after_colon = false;
        vector<long> numbers;
        int start_index = 0;
        for (int i = 0; i < line.size(); i++) {
            if (after_colon) {
                if (line[i] == ' ' || i == line.size()-1) {
                    long num = stol(line.substr(start_index, i));
                    numbers.push_back(num);
                    start_index = i+1;
                }
            } else {
                if (line[i] == ':') {
                    test_value = stol(line.substr(0, i));
                    start_index = i+2;
                    i += 2;
                    after_colon = true;
                }
            }
        }
        if (equation_possible(numbers, test_value, 0, 0)) {
            sum += test_value;
        }
    }
    Input.close();
    cout << "Result: " << sum << endl;
    assert_equal(expected, sum);
}

int main() {
    task1("07-sample", 3749);
    task1("07", 2437272016585);
    return 0;
}