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
    cout << current_working_dir << endl;
}

vector<unordered_map<string, vector<string>>> fileHandler::makeData() {
    cout << "hi" << endl;
    directory_check();
    vector<unordered_map<string, vector<string>>> temp;
    ifstream data("..\\EPA_SmartLocationDatabase_V3_Jan_2021_Final(1).csv");
    //using absolute path works
     /*I found the directory. My computer (Julie's) particularly likes to build the .exe file in cmake-build-debug
      * so I always have to account for that. */
    if(data.is_open()){
        string line;
        getline(data, line);
        string arr[117]; // I used the program to check how many columns there were. It's 117.
        istringstream stream1(line);
        int index = 0;
        string piece;
        while(getline(stream1, piece, ',')){
            if(index >= 117){
                break;
            }
            if(piece == "" or piece == " "){
                //cout << index; (was helpful test code, now unnecessary)
                break;
            }
            arr[index] = piece;
            index += 1;
        }
        /* (Is helpful test code but not in use at the moment.)
        for(int i = 0; i < 117; i++){
            cout << arr[i] << " at " << i << endl;
        }
         */
    }
    cout << "are we here?" << endl;
    return temp;
}