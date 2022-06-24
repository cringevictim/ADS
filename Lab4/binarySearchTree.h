#pragma once
struct Data{
    std::string name;
    int gpa;
    bool motivation;
    int skippedLessons;
    Data();
    friend bool operator==(const Data& data1, const Data& data2){
        return data1.name == data2.name &&
                data1.gpa == data2.gpa &&
                data1.motivation == data2.motivation &&
                data1.skippedLessons == data2.skippedLessons;
    }
    friend bool operator<(const Data& data1, const Data& data2){
        if(data1.name != data2.name){
            return data1.name < data2.name;
        } else if(data1.gpa != data2.gpa){
            return data1.gpa < data2.gpa;
        } else if(data1.motivation != data2.motivation){
            return data1.motivation < data2.motivation;
        } else if(data1.skippedLessons != data2.skippedLessons){
            return data1.skippedLessons < data2.skippedLessons;
        }
        return false;
    }
    friend bool operator>(const Data& data1, const Data& data2){
        if(data1.name != data2.name){
            return data1.name > data2.name;
        } else if(data1.gpa != data2.gpa){
            return data1.gpa > data2.gpa;
        } else if(data1.motivation != data2.motivation){
            return data1.motivation > data2.motivation;
        } else if(data1.skippedLessons != data2.skippedLessons){
            return data1.skippedLessons > data2.skippedLessons;
        }
        return false;
    }
};

Data::Data(){
    int length = 15;
    for(int i = 0; i < length; i++){
        name.push_back(((char)(rand() % 26 + 65)));
    }
    gpa = rand() % 101;
    motivation = rand() % 2;
    skippedLessons = rand() % 101;
}

struct Node
{
    Data data;
    Node* leftChild;
    Node* rightChild;
    Node* parent;
    Node();
};

Node::Node(){
    leftChild = nullptr;
    rightChild = nullptr;
    parent = nullptr;
}

struct BinarySearchTree
{
    Node* root;
    int realSize;

    BinarySearchTree()
    {
        root = nullptr;
        realSize = 0;
    }

    void clr(Node* current)
    {
        if (current != nullptr) {
            clr(current->leftChild);
            clr(current->rightChild);
            delete current;
        }
        return;
    }

    void print(Node* current)
    {
        if (current != nullptr) {
            print(current->leftChild);
            print(current->rightChild);
            std::cout << "Name: " << current->data.name << "; GPA: " << current->data.gpa << "; Motivation: " << current->data.motivation << "; Skipped lessons: " << current->data.skippedLessons << ";" << std::endl;
        }
        return;
    }

    void print(){
        print(root);
    }

    bool find(Node* current, Data* toFind)
    {
        if (current == nullptr)
            return false;
        else if (current->data == *toFind)
            return true;
        else {
            if (*toFind < current->data)
                find(current->leftChild, toFind);
            else find(current->rightChild, toFind);
        }
    }

    bool find(Data toFind)
    {
        if (realSize > 0) {
            return find(root, &toFind);
        }
        else return false;
    }

    Node* minimum(Node* current)
    {
        if (current->leftChild == nullptr)
            return current;
        else return minimum(current->leftChild);
    }

    Node* maximum(Node* current)
    {
        if (current->rightChild == nullptr)
            return current;
        else return maximum(current->rightChild);
    }

    int size()
    {
        return realSize;
    }

    int height(Node* current)
    {
        if (current == nullptr)
            return 0;
        int left = height(current->leftChild);
        int right = height(current->rightChild);
        if (left > right)
            return left + 1;
        else return right + 1;
    }

    int height()
    {
        if (realSize > 0)
            return height(root);
        else
            return 0;
    }

    void insert(Node* current, Node* toInsert)
    {
        if (toInsert->data < current->data) {
            if (current->leftChild == nullptr) {
                toInsert->parent = current;
                current->leftChild = toInsert;
                realSize++;
            }
            else insert(current->leftChild, toInsert);
        }
        if (toInsert->data > current->data) {
            if (current->rightChild == nullptr) {
                toInsert->parent = current;
                current->rightChild = toInsert;
                realSize++;
            }
            else insert(current->rightChild, toInsert);
        }
        return;
    }

    void insert(Data toInsert)
    {
        Node* new_node = new Node();
        new_node->data = toInsert;
        if (realSize == 0) {
            root = new_node;
            realSize++;
        }
        else
            insert(root, new_node);
        return;
    }

    void erase(Node* current, Data* toErase)
    {
        if (current->data == *toErase)
            if ((current->leftChild == nullptr) && (current->rightChild == nullptr)) {
                if (*toErase < current->parent->data)
                    current->parent->leftChild = nullptr;
                else current->parent->rightChild = nullptr;
                realSize--;
            }
            else if (current->leftChild == nullptr) {
                if (*toErase < current->parent->data) {
                    current->rightChild->parent = current->parent;
                    current->parent->leftChild = current->rightChild;
                }
                else {
                    current->rightChild->parent = current->parent;
                    current->parent->rightChild = current->rightChild;
                }
                realSize--;
            }
            else if (current->rightChild == nullptr) {
                if (*toErase < current->parent->data) {
                    current->leftChild->parent = current->parent;
                    current->parent->leftChild = current->leftChild;
                }
                else {
                    current->leftChild->parent = current->parent;
                    current->parent->rightChild = current->leftChild;
                }
                realSize--;
            }
            else {
                Node* min = minimum(current->rightChild);
                current->data = min->data;
                erase(min, &min->data);
            }
        else {
            if ((*toErase < current->data) && (current->leftChild != nullptr))
                erase(current->leftChild, toErase);
            if ((*toErase > current->data) && (current->rightChild != nullptr))
                erase(current->rightChild, toErase);
        }
        return;
    }

    void erase(Data toErase)
    {
        if (root != nullptr) {
            if (root->data == toErase) {
                if ((root->leftChild == nullptr) && (root->rightChild == nullptr)) {
                    root = nullptr;
                    realSize--;
                }
                else if (root->leftChild == nullptr) {
                    root = root->rightChild;
                    root->parent = nullptr;
                    realSize--;
                }
                else if (root->rightChild == nullptr) {
                    root = root->leftChild;
                    root->parent = nullptr;
                    realSize--;
                }
                else {
                    Node* min = minimum(root->rightChild);
                    root->data = min->data;
                    erase(min, &min->data);
                }
            }
            else erase(root, &toErase);
        }
        return;
    }

    int findInRange(Node* current, Data* min, Data* max)
    {
        if (current == nullptr)
            return 0;
        else if (current->data < *min)
            return findInRange(current->rightChild, min, max);
        else if (current->data > *max)
            return findInRange(current->leftChild, min, max);
        else
            return findInRange(current->rightChild, min, max) + findInRange(current->leftChild, min, max) + 1;
    }

    int findInRange(Data min, Data max)
    {
        return findInRange(root, &min, &max);
    }

    ~BinarySearchTree()
    {
        clr(root);
    }
};

