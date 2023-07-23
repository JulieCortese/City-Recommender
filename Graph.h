//
// Created by julie on 7/5/2023.
//

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;


class Node{
    string cityName;
};


class Graph{
private:
    unordered_map<Node*, vector<Node*>>
public:
    void addNode(string name, string otherData);
};