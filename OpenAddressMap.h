// Created by Lorraine, 8/2/2023

#include <functional>
#include <vector>

template<typename Key, typename Value>
class OpenAddressMap{
private:
    int capacity;
    int size;
    float maxLoadFactor = 0.8;

    struct entry{
        Key key;
        Value value;
        bool fresh = true;
    };


    std::vector<entry> container;


public:
    OpenAddressMap(){}

    bool find(Key k){

        int h = std::hash<Key>{}(k);
        for (int i = 0; i < capacity; i++){
            if (container[(i + h) % capacity].key == k)
                return true;
            if (container[(i + h) % capacity].fresh)
                return false;
        }
        return false;
    }

    Value operator[](Key k){
        int h = std::hash<Key>{}(k);
        for (int i = 0; i < capacity; i++){
            if (container[(i + h) % capacity].key == k)
                return container[(i + h) % capacity].value;
            if (container[(i + h) % capacity].fresh)
                {}//throw error
        }

        //throw error
    }

};