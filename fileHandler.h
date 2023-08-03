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
    vector<pair<string, vector<string>>>& makeData();
    void avgToCity(vector<pair<string, vector<string>>>& arr);
};
