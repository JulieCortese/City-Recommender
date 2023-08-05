// Created by Lorraine, 8/2/2023
//#pragma once
#include <functional> //for std::hash
#include <vector>
#include <iostream>
#include <stdexcept>

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
    //std::vector<Iter> iterators = {};

    int _size = 0;
    int _capacity = 16; //this is arbitrary
    float maxLoadFactor = 0.8;

    void reHash(){
        std::cout << "c:" << _capacity << "\n";
        std::vector<entry> temp = std::vector<entry>(_capacity);
        for (int j = 0; j < _capacity; j++){
            temp[j] = container[j];
        }
        std::cout << "{";
        for (int j = 0; j < _capacity; j++){
            std::cout << container[j].key << ", ";
        }
        std::cout << "}\n";
        std::cout << "{";
        for (int j = 0; j < _capacity; j++){
            std::cout << temp[j].key << ", ";
        }
        std::cout << "}\n";
        int i = 0;

        //empties container
        for (; i < container.capacity(); i++){
            std::cout << i << "a\n";
            container[i] = entry();
        }

        //expands container
        while (_size >= container.capacity() * maxLoadFactor){
            std::cout << i << "b\n";
            container.push_back(entry());
            i++;
        }

        //initializes the rest of container
        for(; i < container.capacity(); i++){
            std::cout << i << "c\n";
            container[i] = entry();
        }

        _capacity = container.capacity();
        _size = 0;


        //reinserts entries
        for(entry e : temp){
            std::cout << e.key << "\n";
            if(!e.empty)
                insert(e.key, e.value);
        }

    }



public:

    /*
    void insert(Key, Value); //inserts value at key
    bool erase(Key);         //removes element at key, returns if an element was removed
    bool contains(Key);      //returns if an element is present at key
    Value& operator[](Key);  //returns value at key

    int size();
    int capacity();
    bool empty();
    int count(Key);
    */

    OpenAddressMap(){
        for (int i = 0; i < _capacity; i++){
            container.push_back(entry());
        }
        _capacity = container.capacity();
    }
    /*
    class Iter{
    private:
        int index;
        int direction;
        
    public:
        Iter(int i, int d){
        
        }
        int getIndex(){
            return index;
        }
        void operator++(){
            do{
                index += direction;
            }while(container[index].empty);
        }
        Value& operator*(){
            return container[index].value;
        }
        bool operator==(Iter lhs){
            return index == lhs.getIndex();
        }
        bool operator<(Iter lhs){
            return direction * index < direction * lhs.getIndex();
        }
        bool operator>(Iter lhs){
            return direction * index > direction * lhs.getIndex();
        }
    }
    */
    
    void insert(Key k, Value v){
        unsigned int h = std::hash<Key>{}(k);
        int i = 0;
        for(; i < _capacity; i++){
            if(container[(i + h) % _capacity].empty || container[(i + h) % _capacity].key == k){
                if(container[(i + h) % _capacity].empty)
                    _size++;
                container[(i + h) % _capacity].fresh = false;
                container[(i + h) % _capacity].empty = false;
                container[(i + h) % _capacity].key = k;
                container[(i + h) % _capacity].value = v;
                break;
            }
        }
        std::cout << k << " " << h << " " << i << " " << _size << " " << _capacity * maxLoadFactor << "\n";
        if(_size >= _capacity * maxLoadFactor)
            reHash();
    }


    bool erase(Key k){
        unsigned int h = std::hash<Key>{}(k);
        for(int i = 0; i < _capacity; i++){
            if(container[(i + h) % _capacity].key == k){
                container[(i + h) % _capacity].empty = true;
                return true;
            }
            if(container[(i + h) % _capacity].fresh)
                return false;
        }
        return false;
    }




    bool contains(Key k){
        unsigned int h = std::hash<Key>{}(k);
        for(int i = 0; i < _capacity; i++){
            if(container[(i + h) % _capacity].key == k && !container[(i + h) % _capacity].empty)
                return true;
            if(container[(i + h) % _capacity].fresh)
                return false;
        }
        return false;
    }

    Value& operator[](Key k){
        unsigned int h = std::hash<Key>{}(k);
        int bookmark = -1;

        for(int i = 0; i < _capacity; i++){
            if(container[(i + h) % _capacity].key == k)
                return container[(i + h) % _capacity].value;

            //bookmarks the first empty slot
            if(container[(i + h) % _capacity].empty && bookmark == -1)
                bookmark = (i + h) % _capacity;

            if(container[(i + h) % _capacity].fresh)
                break;
        }

        //inserts an entry at bookmark
        container[bookmark].fresh = false;
        container[bookmark].empty = false;
        container[bookmark].key = k;
        return container[bookmark].value;
    }

    Value find(Key k){
        unsigned int h = std::hash<Key>{}(k);
        for(int i = 0; i < _capacity; i++){
            if(container[(i + h) % _capacity].key == k && !container[(i + h) % _capacity].empty)
                return container[(i + h) % _capacity].value;
            if(container[(i + h) % _capacity].fresh)
                throw std::runtime_error("Key is not present in map.");
        }
        throw std::runtime_error("Key is not present in map.");
    }

    int size(){
        return _size;
    }

    int capacity(){
        return _capacity;
    }

    bool empty(){
        return _size == 0;
    }

    int count(Key k){
        if(contains(k))
            return 1;
        return 0;
    }
/*
    Iter begin(){
        Iter it = new Iter();
        
    }
*/
};