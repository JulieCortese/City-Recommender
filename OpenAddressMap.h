// Created by Lorraine, 8/2/2023

#include <functional> //for std::hash
#include <vector>

template<typename Key, typename Value>
class OpenAddressMap{
private:


    struct entry{
        Key key;
        Value value;
        bool fresh = true;
        bool empty = true;
    };


    std::vector<entry> container;
    int capacity = container.capacity();
    int size = 0;
    float maxLoadFactor = 0.8;

    void reHash(){
        std::vector<entry> temp = container;
        int i = 0;
        while ((float)size / container.capacity() >= maxLoadFactor){
            container[i] = entry();
            i++;
        }
        for(; i < container.capacity(); i++){
            container[i] = entry();
        }
        capacity = container.capacity();
        for (entry e : temp){
            insert(e.key, e.value);
        }
    }


public:
    OpenAddressMap(){}


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
            }
        }
        if((float)size / capacity >= maxLoadFactor)
            reHash();
    }


    void remove(Key k){
        int h = std::hash<Key>{}(k);
        for(int i = 0; i < capacity; i++){
            if(container[(i + h) % capacity].key == k)
                container[(i + h) % capacity].empty = true;
            if(container[(i + h) % capacity].fresh)
                return;
        }
    }




    bool find(Key k){

        int h = std::hash<Key>{}(k);
        for(int i = 0; i < capacity; i++){
            if(container[(i + h) % capacity].key == k && !container[(i + h) % capacity].empty)
                return true;
            if(container[(i + h) % capacity].fresh)
                return false;
        }
        return false;
    }

    Value operator[](Key k){
        int h = std::hash<Key>{}(k);
        for(int i = 0; i < capacity; i++){
            if(container[(i + h) % capacity].key == k)
                return container[(i + h) % capacity].value;
            if(container[(i + h) % capacity].fresh)
                {}//throw error
        }

        //throw error
    }

};