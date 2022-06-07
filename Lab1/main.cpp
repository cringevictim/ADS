#include <iostream>
#include <cmath>
#include <ctime>

struct University
{
    char name;
    int students_amount;
    bool turnstile;
    University()
    {
        name = (char)(rand() % 26 + 65);
        students_amount = rand() % 100001;
        turnstile = rand() % 2;
    };
};

struct DynamicArray
{
    int volume;
    University* data;
    int size;
    const int alpha = 2;

    DynamicArray()
    {
        volume = 1;
        size = 0;
        data = new University[volume];
    }

    void Print()
    {
        for(int j = 0; j < size; j++)
            std::cout << data[j].name << " " << data[j].students_amount << " " << data[j].turnstile << std::endl;
    }

    void PushBack(University newRecord)
    {
        if (size == volume) {
            volume *= alpha;
            University* newArray = new University[volume];
            for(int j = 0; j < size; j++)
                newArray[j] = data[j];
            delete[] data;
            data = newArray;
        }
        data[size] = newRecord;
        size++;
    }

    void PushFront(University newRecord)
    {
        if (size == volume) {
            volume *= alpha;
            University* newArray = new University[volume];
            for(int j = 0; j < size; j++)
                newArray[j] = data[j];
            delete[] data;
            data = newArray;
        }
        for (int l = size; l > 0; l--)
            data[l] = data[l - 1];
        data[0] = newRecord;
        size++;
    }

    University PopBack()
    {
        if (size > 0) {
            size--;
            return data[size];
        }
    }

    University Get(int number)
    {
        return data[number];
    }

    int Size()
    {
        return size;
    }

    University PopFront()
    {
        if (size > 0) {
            University saveFirst = data[0];
            for (int j = 0; j < size; j++)
                data[j] = data[j + 1];
            size--;
            return saveFirst;
        }
    }
};

struct Node
{
    University data;
    Node* next;
};

struct LinkedList
{
    Node* head;
    Node* tail;
    int size;

    LinkedList()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    void Print()
    {
        Node* node = head;
        while (node->next != NULL) {
            std::cout << node->data.name << " " << node->data.students_amount << " " << node->data.turnstile << std::endl;
            node = node->next;
        }
        std::cout << node->data.name << " " << node->data.students_amount << " " << node->data.turnstile << std::endl;
    }

    void PushFront(University newRecord)
    {
        Node* newNode = new Node();
        newNode->data = newRecord;
        newNode->next = NULL;
        if (size == 0)
            tail = newNode;
        newNode->next = head;
        head = newNode;
        size++;
    }

    int Size()
    {
        return size;
    }

    void PushBack(University newRecord)
    {
        Node* newNode = new Node();
        newNode->data = newRecord;
        newNode->next = NULL;
        if (size == 0)
            head = newNode;
        else
            tail->next = newNode;
        tail = newNode;
        size++;
    }

    University Get(int number)
    {
        if (size > 0) {
            Node* newNode = head;
            for (int j = 2; j <= number; j++)
                newNode = newNode->next;
            return newNode->data;
        }
    }

    University PopFront()
    {
        if (size > 0) {
            University saveRecord = head->data;
            head = head->next;
            size--;
            return saveRecord;
        }
    }

    University PopBack()
    {
        if (size > 0) {
            University saveRecord = tail->data;
            Node* node = head;
            while (node->next != tail)
                node = node->next;
            tail = node;
            node->next = NULL;
            size--;
            return saveRecord;
        }
    }
};

template <typename T>
T test(T& data){
    clock_t startAll = clock();

    clock_t start1 = clock();
    for (int i = 0; i < 50000; i++) {
        University record;
        data.PushBack(record);
    }
    clock_t finish1 = clock();

    clock_t start2 = clock();
    for (int i = 0; i < 10000; i++) {
        University record;
        data.PushFront(record);
    }
    clock_t finish2 = clock();

    clock_t start3 = clock();
    for (int i = 0; i < 20000; i++) {
        if (data.size > 0) {
            int n = rand() % data.size + 1;
            University result = data.Get(n);
        }
    }
    clock_t finish3 = clock();

    clock_t start4 = clock();
    for (int i = 0; i < 5000; i++) {
        University result = data.PopBack();
    }
    clock_t finish4 = clock();

    clock_t start5 = clock();
    for (int i = 0; i < 5000; i++) {
        University dresult = data.PopFront();
    }
    clock_t finish5 = clock();

    clock_t finishAll = clock();

    float time1 = (float(finish1 - start1)) / CLOCKS_PER_SEC;
    float time2 = (float(finish2 - start2)) / CLOCKS_PER_SEC;
    float time3 = (float(finish3 - start3)) / CLOCKS_PER_SEC;
    float time4 = (float(finish4 - start4)) / CLOCKS_PER_SEC;
    float time5 = (float(finish5 - start5)) / CLOCKS_PER_SEC;

    float timeAll = (float(finishAll - startAll)) / CLOCKS_PER_SEC;
    std::cout << "PushBack time: " << time1 << "s" << std::endl;
    std::cout << "PushFront time: " << time2 << "s" << std::endl;
    std::cout << "Get time: " << time3 << "s" << std::endl;
    std::cout << "PopBack time: " << time4 << "s" << std::endl;
    std::cout << "PopFront time: " << time5 << "s" << std::endl;
    std::cout << "Summary: " << timeAll << "s\n" << std::endl;
}

int main()
{
    srand(time(NULL));

    DynamicArray array;
    LinkedList list;
    std::cout << "Dynamic array testing:" << std::endl;
    test(array);
    std::cout << "Linked list testing:" << std::endl;
    test(list);
    return 0;
}