// Created by Julie, 7/5/2023
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <ctime>
#include <fstream>
#include "fileHandler.h"
#include "OpenAddressMap.h"
#include "SeparateChain.h"
using namespace std;

void printMenu(){
    cout << "Options:" << endl;
    cout << "-1: Quit" << endl;
    cout << "1: Input qualities searching for in a city, get recommendation" << endl;
    cout << "2: Top five cities depending on qualities like above" << endl;
    cout << "3: Top city w/o qualities ranked" << endl;
    cout << "4: Top 5 cities w/o qualities ranked?" << endl;
    // importance of each quality should be possible to weight by importance, but also to choose not to.
}

int main(){
    int option;
    cout << "hello" << endl;
    fileHandler handle;
    cout << "loading data, please wait." << endl;
    vector<pair<string, vector<string>>> data = handle.makeData();
    data = handle.avgToCity(data); // please work
    cout << "Data brought in from file." << endl;
    cout << "Now inserting data into open address hash map." << endl;
    // the file is big so you'll have to wait a couple seconds for it to load.
    OpenAddressMap<string, vector<string>> openAddressMap;
    clock_t t = clock();
    for(int i = 0; i < data.size(); i++){
        openAddressMap.insert(data.at(i).first, data.at(i).second);
    }
    t = clock() - t;
    cout << "Execution time to load data into open address hash map: " << t / 10000000.0 << "s" << endl;
    cout << "Now inserting data into separate chaining hash map." << endl;
    SeparateChain separateChain;
    t = clock();
    for(int i = 0; i < data.size(); i++){
        separateChain.Insert(data.at(i).first, data.at(i).second);
    }
    t = clock() - t;
    cout << "Execution time to load data into separate chaining hash map: " << t / 10000000.0 << "s" << endl;
    cin >> option;
    while(option != -1){
        printMenu();
        cin >> option;
        clock_t t = clock();
        // do stuff depending on option.
        if (option == 1){}
        if (option == 2){}
        if (option == 3){}
        if (option == 4){}
        if (option == 5){}
        t = clock() - t;
        cout << "Execution time: " << t / 10000000.0 << "s" << endl << endl;
    }
    return 0;
}