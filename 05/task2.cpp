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

template <typename T>
vector<T> fix_ordering(vector<T> update, vector<T> orders_left, vector<T> orders_right) {
    vector<T> fixed_order;
    bool isFixed = true;
    for (T value: update) {
        bool isBroken = false;
        vector<T> rules = find_all_rules(orders_left.begin(), orders_left.end(), value, orders_right);
        if (rules.size() == 0) {
            fixed_order.push_back(value);
            continue;
        }
        for (T r: rules) {
            auto find_it = find(fixed_order.begin(), fixed_order.end(), r);
            if (find_it != fixed_order.end()) {
                int index = find_it - fixed_order.begin();
                T wrong = fixed_order[index];
                fixed_order[index] = value;
                fixed_order.push_back(wrong);
                isBroken = true;
                isFixed = false;
                break;
            }
        }
        if (!isBroken) {
            fixed_order.push_back(value);
        }
    }
    if (!isFixed) {
        return fix_ordering(fixed_order, orders_left, orders_right);
    }
    return fixed_order;
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
                    auto find_it = find(before.begin(), before.end(), r);
                    int index = find_it - before.begin();
                    if (find_it != before.end()) {
                        isBroken = true;
                        break;
                    }
                }
            }
            if (isBroken) {
                break;
            }
            before.push_back(value);
        }
        if (isBroken) {
            vector<int> fixed_order = fix_ordering(update, orders_left, orders_right);
            int middle = fixed_order[fixed_order.size() / 2];
            sum += middle;
            //cout << "Broken rules, adding " << middle << " to sum" << endl;
            continue;
        }
        //cout << "no broken rules, skipping" << endl;
    }
    Input.close();
    cout << "Result: " << sum << endl;
    assert_equal(expected, sum);
}

int main() {
    task2("05-sample", 123);
    task2("05", 6319);
    return 0;
}