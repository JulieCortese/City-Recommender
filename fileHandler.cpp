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

vector<pair<string, vector<string>>> fileHandler::makeData() {
    //cout << "hi" << endl;
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
    /*
    unordered_map<string, vector<string>> fin;
    unordered_map<string, float> out; // I'm hoping that everything can be added.
    for(int i = 0; i < arr.size(); i++){
        if(fin.find(arr.at(i).first) == fin.end()){
            fin[arr.at(i).first] = arr.at(i).second;
        }else if(out.find(arr[i].first) == out.end()){
            // ok so we want to add the values in fin and store the number to divide by to get avg in out
            auto it = fin.find(arr[i].first);
            for(int j = 0; j < it->second.size(); j++){
                float value = stoi(arr[i].second.at(j));
                float val2 = stof(it->second.at(j));
                val2 += value;
                it->second.at(j) = to_string(val2);
            }
            out[it->first] = 2;
        }
        else{
            // this is if there's something in fin, but not out. add vals in fin and num to divide by is 2.
            auto it = fin.find(arr[i].first);
            for(int j = 0; j < it->second.size(); j++){
                float value = stoi(arr[i].second.at(j));
                float val2 = stof(it->second.at(j));
                val2 += value;
                it->second.at(j) = to_string(val2);
            }
            out[it->first] += 1;
        }
        // if there's already a key for the city, we want to add and then take avg.
    }
    for(auto it = out.begin(); it != out.end(); it++){
        auto it2 = fin.find(it->first);
        for(int m = 0; m < it2->second.size(); m++){
            float val = stof(it2->second.at(m));
            val /= it->second;
            it2->second.at(m) = to_string(val);
        }
    }
    return fin;
     */
    vector<pair<string, vector<string>>> out;
    cout << arr.size() << endl;
    for(int i = 0; i < arr.size(); i++){
        cout << "begin" << endl;
        bool found = false;
        for(int j = 0; j < out.size(); j++){
            if(out.at(j).first == arr.at(i).first){
               found = true;
               for(int m = 0; m < out.at(j).second.size(); m++){
                   float val = stof(arr.at(i).second.at(m));
                   val += stof(out.at(j).second.at(m));
                   out.at(j).second.at(m) = to_string(val);
               }
            }
        }
        if(!found){
            pair<string, vector<string>> temp;
            temp.first = arr.at(i).first;
            temp.second = arr.at(i).second;
            out.push_back(temp);
        }
    }
    return out;
}