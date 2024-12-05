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

void task1(string name, int expected) {
    cout << "Task 1" << endl;
    cout << "Input: " << name << endl;
    string fileame = name + ".txt";
    ifstream Input(fileame);
    if (!Input.is_open()) {
        cerr << "Error opening the file!";
        return;
    }
    string line;
    vector<int> orders_left;
    vector<int> orders_right;
    vector<vector<int> > updates;
    bool isOrders = true;
    while (getline (Input, line)) {
        if (line.empty()) {
            isOrders = false;
            continue;
        }
        if (isOrders) {
            int num1 = stoi(line.substr(0, 2));
            int num2 = stoi(line.substr(3, 4));
            orders_left.push_back(num1);
            orders_right.push_back(num2);
        } else {
            vector<int> update;
            for (int i = 0; i < line.size(); i+=3) {
                int num = stoi(line.substr(i, i+2));
                update.push_back(num);
            }
            updates.push_back(update);
        }
    }
    int sum = 0;
    for (vector<int> update: updates) {
        vector<int> before;
        bool isBroken = false;
        for (int value: update) {
            vector<int> rules = find_all_rules(orders_left.begin(), orders_left.end(), value, orders_right);
            if (rules.size() != 0) {
                for (int r: rules) {
                    if (find(before.begin(), before.end(), r) != before.end()) {
                        isBroken = true;
                        break;
                    }
                }
                if (isBroken) {
                    break;
                }
            }
            before.push_back(value);
        }
        if (isBroken) {
            //cout << "Broken rules, skipping" << endl;
            continue;
        }
        int middle = update[update.size() / 2];
        //cout << "No broken rules, adding " << middle << " to sum" << endl;
        sum += middle;
    }
    Input.close();
    cout << "Result: " << sum << endl;
    assert_equal(expected, sum);
}

int main() {
    task1("05-sample", 143);
    task1("05", 4790);
    return 0;
}