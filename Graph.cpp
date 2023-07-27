//
// Created by julie on 7/5/2023.
//
/*
 More specifically this will be an adjacency list since I like adjacency lists and I don't think either of you will
 object to the idea.
 */
#include "Graph.h"

void Graph::addNode(string name, string otherData, string name2, string other2) {
    list[new Node(name, otherData)].push_back(new Node(name2, other2));
}

Node::Node(string name, string rest) {
    this->cityName = name;
    this->other = rest;
}
