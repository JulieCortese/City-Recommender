//
// Created by julie on 8/2/2023.
//
#include "fileHandler.h"
#include <fstream>
#include <iostream>
#include <direct.h>
#include<limits.h>
#include<sstream>
using namespace std;

void directory_check(){
    char buff[PATH_MAX];
    _getcwd( buff, PATH_MAX );
    string current_working_dir(buff);
    //cout << current_working_dir << endl;
}

vector<pair<string, vector<string>>>& fileHandler::makeData() {
    cout << "hi" << endl;
    directory_check();
    vector<pair<string, vector<string>>> temp;
    vector<pair<string, vector<string>>> out;
    ifstream data("..\\EPA_SmartLocationDatabase_V3_Jan_2021_Final(1).csv");
    //using absolute path works
     /*I found the directory. My computer (Julie's) particularly likes to build the .exe file in cmake-build-debug
      * so I always have to account for that. */
    if(data.is_open()) {
        string line;
            //cout << line << endl;
            string arr[117]; // I used the program to check how many columns there were. It's 117.
            while(getline(data, line)) {
                istringstream stream1(line);
                int index = 0;
                string piece;
                pair<string, vector<string>> temporary;
                while (getline(stream1, piece, ',')) {
                    if (index >= 117) {
                        break;
                    }
                    if (piece == "" or piece == " ") {
                        //cout << index; (was helpful test code, now unnecessary)
                        break;
                    }
                    arr[index] = piece;
                    if (index == 8) {
                        temporary.first = arr[index];
                    } else if (index == 18 or index == 19 or index == 20 or index == 23 or index == 39 or index == 40) {
                        temporary.second.push_back(arr[index]);
                    } else if ((40 < index and index < 47) or index == 51 or index == 83 or index == 86 or
                               index == 92) {
                        temporary.second.push_back(arr[index]);
                    } else if (index == 99 or index == 101 or index == 114) {
                        temporary.second.push_back(arr[index]);
                    }
                    index += 1;
                }
                out.push_back(temporary);
                /* (Is helpful test code but not in use at the moment.)
                for(int i = 0; i < 117; i++){
                    cout << arr[i] << " at " << i << endl;
                }
                 */
            }
        //}
    }
    return out;
}

void fileHandler::avgToCity(vector<pair<string, vector<string>>>& arr){
    unordered_map<string, vector<string>> fin;
    for(int i = 0; i < arr.size(); i++){
        if(fin.find(arr.at(i).first) == fin.end()){
            fin[arr.at(i).first] = arr.at(i).second;
        }
        // if there's already a key for the city, we want to add and then take avg.
    }
}
