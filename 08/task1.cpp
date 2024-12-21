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

int count_antinodes(vector<vector<char >>* map, int x0, int y0, vector<vector<char >>* antimap) {
    int count = 0;
    char c = (*map)[y0][x0];
    for (int y = 0; y < (*map).size(); y++) {
        for (int x = 0; x < (*map)[y].size(); x++) {
            if ((*map)[y][x] == c) {
                int distance = abs(x0 - x) + abs(y0 - y);
                int nx = x0 + (x0 - x);
                int ny = y0 + (y0 - y);
                if (nx >= 0 && nx < (*map)[y].size() && ny >= 0 && ny < (*map).size() && distance != 0 && (*map)[ny][nx] != '#' && (*antimap)[ny][nx] != '#') {
                    if ((*map)[ny][nx] == '.') {
                        (*map)[ny][nx] = '#';
                    }
                    (*antimap)[ny][nx] = '#';
                    count++;
                }
            }
        }
    }
    return count;
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
    vector<vector<char >> map;
    vector<vector<char >> antimap;
    while (getline (Input, line)) {
        vector<char> row;
        vector<char> antimap_row;
        for (int i = 0; i < line.size(); i++) {
            row.push_back(line[i]);
            antimap_row.push_back('.');
        }
        map.push_back(row);
        antimap.push_back(antimap_row);
    }
    Input.close();
    int count = 0;
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            if (map[y][x] != '.' && map[y][x] != '#') {
                count += count_antinodes(&map, x, y, &antimap);
            }
        }
    }
    cout << "Result: " << count << endl;
    assert_equal(expected, count);
}

int main() {
    task1("08-sample", 14);
    task1("08", 359);
    return 0;
}
