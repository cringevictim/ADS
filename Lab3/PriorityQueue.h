#pragma once
#include <iostream>
#include <vector>
#include <ctime>

struct Data{
    int hp, damage, resistance;
    Data(){
        hp = rand()%101;
        damage = rand()%501;
        resistance = rand()%100;
    };

    Data(int code){
        hp = -1;
        damage = -1;
        resistance = -1;
    }

    bool operator<(const Data& data2) const{
        if(hp != data2.hp){
            return hp < data2.hp;
        } else if(damage != data2.damage){
            return damage < data2.damage;
        }
        return resistance < data2.resistance;
    }

    bool operator==(const Data& data2) const{
        return hp == data2.hp && damage == data2.damage && resistance == data2.resistance;
    }
};

struct PriorityQueue
{
    int capacity;
    Data* enemy;
    int heapSize;
    const int alpha = 2;

    PriorityQueue()
    {
        capacity = 16;
        heapSize = 0;
        enemy = new Data[capacity];
    }

    int parent(int i)
    {
        if(i > 0)
            return (i - 1) / 2;
        return 0;
    }

    int left(int i)
    {
        return i * 2 + 1;
    }

    int right(int i)
    {
        return i * 2 + 2;
    }

    void siftDown(int i)
    {
        while (left(i) < heapSize) {
            int j = left(i);
            if ((right(i) < heapSize) && (enemy[j] < enemy[right(i)]))
                j = right(i);
            if (enemy[j] < enemy[i] || enemy[j] == enemy[i])
                break;
            std::swap(enemy[i], enemy[j]);
            i = j;
        }
    }

    void siftUp(int i)
    {
        while (enemy[parent(i)] < enemy[i]) {
            std::swap(enemy[i], enemy[parent(i)]);
            i = parent(i);
        }
    }

    void push(Data new_record)
    {
        if (heapSize == capacity) {
            capacity *= alpha;
            Data* new_array = new Data[capacity];
            for (int j = 0; j < heapSize; j++)
                new_array[j] = enemy[j];
            delete[] enemy;
            enemy = new_array;
        }
        heapSize++;
        enemy[heapSize - 1] = new_record;
        siftUp(heapSize - 1);
    }

    Data top()
    {
        if (heapSize > 0)
            return enemy[0];
        Data empty(-1);
        return empty;
    }

    Data pop()
    {
        if (heapSize > 0) {
            std::swap(enemy[0], enemy[heapSize - 1]);
            heapSize--;
            siftDown(0);
            return enemy[heapSize];
        }
        Data empty(-1);
        return empty;
    }

    int size()
    {
        return heapSize;
    }

    ~PriorityQueue()
    {
        delete[] enemy;
    }
};