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
    string other;
public:
    Node(string name, string rest);
};


class Graph{
private:
    unordered_map<Node*, vector<Node*>> list;
public:
    void addNode(string name, string otherData, string name2, string other2);
};