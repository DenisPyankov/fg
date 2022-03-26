#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



struct Node {
    int data;
    Node* next = nullptr;
};

class EnclosedList {
private:
    Node* head = nullptr;
    Node* currentStone = nullptr;
public:
    EnclosedList(ifstream& readFrom);
    ~EnclosedList();

    void printList();
    vector<int> takeThreeStones();
    Node* findMaxStone();
    void putAfterFound(vector<int>&, Node* maxStone);
};



EnclosedList::EnclosedList(ifstream& readFrom) {
    Node* firstNode = new Node;
    this->head = firstNode;
    this->currentStone = firstNode;

    int data;
    readFrom >> data;
    firstNode->data = data;

    Node* tmp = firstNode;
    while (!readFrom.eof()) {
        Node* nextNode = new Node;
        readFrom >> data;
        nextNode->data = data;
        tmp->next = nextNode;
        tmp = nextNode;
    }
    tmp->next = this->head;
}

void EnclosedList::printList() {
    Node* tmp = this->head;
    cout << tmp->data << " ";
    tmp = tmp->next;
    while (tmp != this->head) {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
}

EnclosedList::~EnclosedList() {
    Node* tmp = this->head;
    tmp = tmp->next;
    while (tmp != this->head) {
        Node* tmp2 = tmp;
        tmp = tmp->next;
        delete tmp2;
    }
    delete tmp;
}

vector<int> EnclosedList::takeThreeStones() {
    Node* tmp = this->currentStone;
    vector<int> stones;
    tmp = tmp->next;
    for (int i = 0; i < 3; i++) {
        stones.push_back(tmp->data);
        Node* tmp2 = tmp;
        tmp = tmp->next;
        if (tmp2 == this->head)
            this->head = tmp;
        delete tmp2;
    }
    this->currentStone->next = tmp;
    return stones;
}

Node* EnclosedList::findMaxStone() {
    Node* tmp = this->currentStone->next;
    int currentStoneNumber = this->currentStone->data;
    int maxNumber = -1;
    Node* newMaxStone = nullptr;
    while (tmp != this->currentStone) {
        if (tmp->data > maxNumber && tmp->data < currentStoneNumber) {
            maxNumber = tmp->data;
            newMaxStone = tmp;
        }
        tmp = tmp->next;
    }
    if (maxNumber != -1)
        return newMaxStone;
    tmp = this->currentStone->next;
    while (tmp != this->currentStone) {
        if (tmp->data > maxNumber) {
            maxNumber = tmp->data;
            newMaxStone = tmp;
        }
        tmp = tmp->next;
    }
    return newMaxStone;
}

void EnclosedList::putAfterFound(vector<int>& stones, Node* maxStone) {
    Node* tmp = maxStone;
    Node* lastTie = maxStone->next;

    for (int i = 0; i < 3; i++) {
        Node* newNode = new Node;
        newNode->data = stones[i];
        if (i == 0)
            maxStone->next = newNode;
        if (i != 0)
            tmp->next = newNode;
        tmp = tmp->next;
    }
    tmp->next = lastTie;
    this->currentStone = lastTie;
}




int main()
{
    ifstream input("permutation.txt");
    EnclosedList list(input);
    cout << "Enter the amount of permutations" << endl;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        auto threeStones = list.takeThreeStones();
        auto maxStone = list.findMaxStone();
        list.putAfterFound(threeStones, maxStone);
    }
    list.printList();
    return 0;
}