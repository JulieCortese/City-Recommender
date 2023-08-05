// Created by Lorraine, 8/2/2023
//#pragma once
#include <functional> //for std::hash
#include <vector>
#include <stdexcept>
#include <iostream>

template<typename Key, typename Value>
class OpenAddressMap{
private:


    struct entry{
        Key key;
        Value value;
        bool fresh = true;
        bool empty = true;
    };


    std::vector<entry> container = {};

    int size = 0;
    int capacity = 16;
    float maxLoadFactor = 0.8;

    void reHash(){
        std::vector<entry> temp = container;
        int i = 0;

        //empties container
        for (; i < container.capacity(); i++){
            container[i] = entry();
        }

        //expands container
        while ((float)size / container.capacity() >= maxLoadFactor){
            container.push_back(entry());
            i++;
        }

        //initializes the rest of container
        for(; i < container.capacity(); i++){
            container[i] = entry();
        }

        capacity = container.capacity();

        //reinserts entries
        for (entry e : temp){
            insert(e.key, e.value);
        }

    }



public:

    /*
    void insert(Key, Value); //inserts value at key
    bool erase(Key);         //removes element at key, returns if an element was removed
    bool contains(Key);      //returns if an element is present at key
    Value operator[](Key);   //returns value at key
    */

    OpenAddressMap(){
        for (int i = 0; i < capacity; i++){
            container.push_back(entry());
        }
        capacity = container.capacity();
    }


    void insert(Key k, Value v){
        int h = std::hash<Key>{}(k);
        for(int i = 0; i < capacity; i++){
            if(container[(i + h) % capacity].empty || container[(i + h) % capacity].key == k){
                if(container[(i + h) % capacity].empty)
                    size++;
                container[(i + h) % capacity].fresh = false;
                container[(i + h) % capacity].empty = false;
                container[(i + h) % capacity].key = k;
                container[(i + h) % capacity].value = v;
                return;
            }
        }
        if((float)size / capacity >= maxLoadFactor)
            reHash();
    }


    bool erase(Key k){
        int h = std::hash<Key>{}(k);
        for(int i = 0; i < capacity; i++){
            if(container[(i + h) % capacity].key == k){
                container[(i + h) % capacity].empty = true;
                return true;
            }
            if(container[(i + h) % capacity].fresh)
                return false;
        }
        return false;
    }




    bool contains(Key k){

        int h = std::hash<Key>{}(k);
        for(int i = 0; i < capacity; i++){
            if(container[(i + h) % capacity].key == k && !container[(i + h) % capacity].empty)
                return true;
            if(container[(i + h) % capacity].fresh)
                return false;
        }
        return false;
    }

    Value& operator[](Key k){
        int h = std::hash<Key>{}(k);
        for(int i = 0; i < capacity; i++){
            if(container[(i + h) % capacity].key == k)
                return container[(i + h) % capacity].value;
            if(container[(i + h) % capacity].fresh)
                throw std::runtime_error("Key is not present in map.");
        }

        throw std::runtime_error("Key is not present in map.");
    }

};