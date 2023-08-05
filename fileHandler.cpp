//
// Created by julie on 8/2/2023.
//
#include "fileHandler.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include<sstream>
using namespace std;


vector<pair<string, vector<string>>> fileHandler::makeData() {
    vector<pair<string, vector<string>>> temp;
    vector<pair<string, vector<string>>> out;
    ifstream data("..\\EPA_SmartLocationDatabase_V3_Jan_2021_Final(1).csv");
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
            //need to check temporary to make sure it's ok. If not ok, function should continue rather than pushing back.
            if(temporary.first == "" or temporary.first == " "){
                continue;
            }
            if(temporary.second.size() != 19){
                continue;
            }
            for(int a = 0; a < temporary.second.size(); a++){
                if(temporary.second.at(a).find_first_not_of("0123456789.") != -1){
                    continue;
                }
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
    for(int i = 0; i < out.size(); i++){
        if(out.at(i).first != "" and out.at(i).first != " "){
            if(out.at(i).first.at(0) == '"') {
                string temp = out.at(i).first.substr(1, out.at(i).first.size() - 1);
                out.at(i).first = temp;
            }
        }
    }
    return out;
}

vector<pair<string, vector<string>>> fileHandler::avgToCity(vector<pair<string, vector<string>>>& arr){
    vector<pair<string, vector<string>>> out;
    unordered_map<string, int> divideBy;
    for(int i = 0; i < arr.size(); i++){
        bool found = false;
        for(int j = 0; j < out.size(); j++){
            if(out.at(j).first == arr.at(i).first){
                found = true;
                for(int m = 0; m < out.at(j).second.size(); m++){
                    float val = stof(arr.at(i).second.at(m));
                    val += stof(out.at(j).second.at(m));
                    out.at(j).second.at(m) = to_string(val);
                }
                divideBy[out.at(j).first] = divideBy[out.at(j).first] + 1;
            }
        }
        if(!found){
            pair<string, vector<string>> temp;
            temp.first = arr.at(i).first;
            temp.second = arr.at(i).second;
            out.push_back(temp);
            divideBy[temp.first] = 1;
        }
    }
    for(int b = 1; b < out.size() - 1; b++){
        int divider = divideBy[out.at(b).first];
        for(int k = 0; k < out.at(b).second.size(); k++){
            float val = stof(out.at(b).second.at(k));
            val /= (float)divider;
            if(val < 0){
                val = -val;
            }
            out.at(b).second.at(k) = to_string(val);
        }
    }
    // the 3 lines about the last city in the vector are to manually fix a weirdly specific error in which that one number refused to be positive.
    string sub = out.at(175).second.at(16).substr(1, out.at(175).second.at(16).size() - 1);
    out.at(175).second.at(16) = sub;
    out.erase(out.begin());
    return out;
}

/*
void fileHandler::printAll(vector<pair<string, vector<string>>> &arr) {
    for(int i = 0; i < arr.size(); i++){
        cout << i << ": " << arr.at(i).first << endl;
        for(int j = 0; j < arr.at(i).second.size(); j++){
            cout << arr.at(i).second.at(j) << ", ";
        }
        cout << endl;
    }
}
 */
