//
// Created by julie on 8/2/2023.
//

#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class fileHandler{
public:
    vector<unordered_map<string, vector<string>>> makeData();
};
