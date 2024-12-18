#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <assert.h>
#include <tuple>
#include <cmath>
#include <string>

using namespace std;

void assert_equal(long expected, long actual) {
    if (expected != actual) {
        cerr << "Assert failed! Expected: " << expected << ", but got: " << actual << endl;
    }
}

template <typename T>
vector<T> find_all_rules(typename vector<T>::iterator begin, typename vector<T>::iterator end, T value, vector<T> orders_right) {
    vector<T> rules;
    for (typename vector<T>::iterator it = begin; it != end; it++) {
        if (*it == value) {
            int i = distance(begin, it);
            rules.push_back(orders_right[i]);
        }
    }
    return rules;
}

bool equation_possible(vector<long> numbers, long test_value, int index, long acc) {
    bool concat_branch = false;
    if (index >= numbers.size()) {
        return acc == test_value;
    }
    bool plus_branch = equation_possible(numbers, test_value, index+1, acc + numbers[index]);
    bool mul_branch = equation_possible(numbers, test_value, index+1, acc * numbers[index]);
    int potens = to_string(numbers[index]).size();
    long concat = acc * pow(10, potens) + numbers[index]; 
    concat_branch = equation_possible(numbers, test_value, index+1, concat);
    return plus_branch || mul_branch || concat_branch;
}

void task2(string name, long expected) {
    cout << "Task 2" << endl;
    cout << "Input: " << name << endl;
    string fileame = name + ".txt";
    ifstream Input(fileame);
    if (!Input.is_open()) {
        cerr << "Error opening the file!";
        return;
    }
    string line;
    long long sum = 0;
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
    task2("07-sample", 11387);
    task2("07", 162987117690649);
    return 0;
}