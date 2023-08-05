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

void printQualities(){
    cout << "Qualities:" << endl;
    cout << "1: High Population" << endl; //TotPop, data.second.at(0)
    cout << "2: Lots of housing available" << endl; //countHU, data.second.at(1)
    cout << "3: Lots of households in the area" << endl; // HH, data.second.at(2)
    cout << "4: Low necessity of car" << endl; // this will correspond to high number Pct_AO0, data.second.at(3)
    cout << "5: High density (crowded, lots of people)" << endl; //D1A I think, data.second.at(12)
    cout << "6: High amount of retail jobs" << endl; //E8_Ret, data.second.at(4)
    cout << "7: High amount of office jobs" << endl; //E8_off, data.second.at(5)
    cout << "8: High amount of industrial jobs" << endl; //data.second.at(6)
    cout << "9: High amount of service jobs" << endl; //data.second.at(7)
    cout << "10: High amount of entertainment jobs" << endl; //data.second.at(8)
    cout << "11: High amount of education jobs" << endl; //data.second.at(9)
    cout << "12: High amount of health care jobs" << endl; //data.second.at(10)
    cout << "13: High amount of public administration jobs" << endl; //data.second.at(11)
    cout << "14: Ability to use a car" << endl; //data.second.at(13)
    cout << "15: High street intersection density " << endl; //D3B, data.second.at(14)
    cout << "16: High transit stop accessibility" << endl; //D4A, data.second.at(15)
    cout << "17: Short car commutes between workplaces and homes" << endl; //D5AE, data.second.at(16)
    cout << "18: Short transit commutes between workplaces and homes" << endl; // D5BE, data.second.at(17)
    cout << "19: National Walkability index" << endl; //NatWalkInd, data.second.at(18)
    cout << "Please pick a top five and input them in order, first being most important and fifth being the least." << endl;
}

int main(){
    int option;
    cout << "hello" << endl;
    fileHandler handle;
    cout << "loading data, please wait." << endl;
    vector<pair<string, vector<string>>> data = handle.makeData();
    data = handle.avgToCity(data); // please work
    cout << "Data brought in from file." << endl;
    /*
    cout << "Now inserting data into open address hash map." << endl;
    // the file is big so you'll have to wait a couple seconds for it to load.
    OpenAddressMap<string, vector<string>> openAddressMap;
    clock_t t = clock();
    for(int i = 0; i < data.size(); i++){
        openAddressMap.insert(data.at(i).first, data.at(i).second);
    }
    t = clock() - t;
    cout << "Execution time to load data into open address hash map: " << t / 10000000.0 << "s" << endl;
    */
    cout << "Now inserting data into separate chaining hash map." << endl;
    SeparateChain separateChain;
    clock_t t = clock();
    for(int i = 0; i < data.size(); i++){
        separateChain.Insert(data.at(i).first, data.at(i).second);
    }
    t = clock() - t;
    cout << "Execution time to load data into separate chaining hash map: " << t / 10000000.0 << "s" << endl;
    printMenu();
    cin >> option;
    while(option != -1){
        // do stuff depending on option.
        if (option == 1){
            vector<string> inputs;
            string input;
            printQualities();
            bool fail = false;
            for(int i = 0; i < 5; i++){
                cin >> input;
                if(input.find_first_not_of("0123456789") != -1){
                    cout << "invalid input." << endl;
                    fail = true;
                    break;
                }
                if(stoi(input) > 19){
                    fail = true;
                    break;
                }
                for(int j = 0; j < inputs.size(); j++){
                    if(inputs.at(j) == input){
                        cout << "invalid input, you cannot repeat a number." << endl;
                        fail = true;
                        break;
                    }
                }
                if(fail){
                    break;
                }
                inputs.push_back(input);
            }
            if(fail){
                continue;
            }
            for(int i = 0; i < inputs.size(); i++){
                cout << inputs.at(i) << endl;
            }
            // should start the clock once we start searching the hash maps.
            // using address map and chain map, take the index of first most important, multiply by 5,
            // index 2nd most important, multiply by 4, 3rd multiplied by 3, 4th multiply by 2, 5th by itself, and add them all up
            // city with biggest sum is outputted.t = clock();
            t = clock();

        }
        if (option == 2){

            t = clock();
        }
        if (option == 3){

            t = clock();
            string top = separateChain.FindTop();
            cout << "The top city based on walkability is " << top << endl;
        }
        if (option == 4){

            t = clock();
        }
        t = clock() - t;
        cout << "Execution time: " << t / 10000000.0 << "s" << endl << endl;
        printMenu();
        cin >> option;
    }
    return 0;
}