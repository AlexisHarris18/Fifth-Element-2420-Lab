#pragma once
#include <memory>

//USE ONLY THE LIBRARIES THAT YOU NEED
using std::ostream;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

template<class Type>
struct Node {
    Type data;
    //Node<Type> *next; //RAW POINTER
    shared_ptr <Node<Type> > next; // SHARED POINTER (Not unique because it might have to be shared multiple times.)
};

template<class Type>
class LinkedList;

template<class Type>
ostream& operator<<(ostream& out, const LinkedList<Type>& list);

template<class Type>
class LinkedList {
public:
    LinkedList() : front(nullptr), back(nullptr), count(0) {}// Default constructor for the LinkedList.  Creates an empty list by setting front and back of the list to nulllptr
    //~LinkedList();           //Destructor for the LinkedList.  Creates an empty list by setting front and back of the list to nulllptr
    void insert(Type data);  //Adds to the back of the list
    Type peek(int ndx)const;//Looks at an element at the given ndx value
    void remove(int ndx);    //Removes an element at the given ndx position
    friend ostream& operator<< <>(ostream& out, const LinkedList<Type>& list);// Returns an output stream for displaying the LinkedList
protected:
    int count;
    shared_ptr <Node<Type> > front;
    shared_ptr <Node<Type> > back;
};

template <class Type>
void LinkedList<Type>::insert(Type data) {
    //auto temp = new Node<Type> RAW POINTER
    auto temp = make_shared <Node<Type>>();
    temp->data = data;
    temp->next = nullptr;
    if (!front) { // MEANS THAT FRONT = NULL, THERE IS NOTHING IN THE LIST
        front = temp;
        back = temp;
    }
    else {
        back->next = temp;
        back = temp;
    }
    count++;
}

template <class Type>
Type LinkedList<Type>:: peek(int ndx)const {
    if (ndx >= count || ndx < 0) {
        throw runtime_error("Out of Range");
    }
    int currNodeNum = 0;
    auto currentNode = front;
    while (currNodeNum < ndx) {
        currNodeNum++;
        currentNode = currentNode->next; // MOVING POINTER THROUGH THE LIST AND SETTING IT EQUAL TO THE NEXT VALUE (ITERATOR)
    }
    return currentNode->data; //RETURNS ONLY THE DATA THAT WE WANT AND NOT THE NEXT NODE
}

template<class Type>
void LinkedList<Type>::remove(int ndx) {
    if (ndx >= count || ndx < 0) {
        throw runtime_error("Out of Range");
    }
    //If removing the front
    if (ndx == 0) {
        auto toDelete = front;
        front = toDelete->next; // can just do front = front->next if using smart pointers
        //delete toDelete; only use for raw pointers
        return;
    }
    int currNodeNum = 0;
    auto currentNode = front;
    while (currNodeNum < ndx - 1) { //Modifying it so we're changing the pointer to what we are deleting
        currNodeNum++;
        currentNode = currentNode->next; // MOVING POINTER THROUGH THE LIST AND SETTING IT EQUAL TO THE NEXT VALUE (ITERATOR)
    }
    auto toDelete = currentNode->next;

    //Deleting from middle
    if (toDelete->next) { //if this exists it is a middle value
        currentNode->next = toDelete->next;
    }

    //Deleting End Node
    else {
        currentNode->next = nullptr;
        back = currentNode;
    }
    count--;
    //delete toDelete; //only use for raw pointers
}

template <class Type>
ostream& operator<<(ostream& out, const LinkedList<Type>& list) {
    auto curr = list.front;

    while (curr) {
        out << curr->data;
        if (curr->next) {
            out << " ";
        }
        curr = curr->next;
    }
    return out;
}



template<class Type>
class FifthElement : public LinkedList<Type> {
public:
    FifthElement() {}
    Type getFifthElement();
    void insertNewFifthElement(const Type value);
    void deleteFifthElement();
    void swapFourthAndFifthElement();
   
};


template<class Type>
Type FifthElement<Type>::getFifthElement() {
    auto current = this->front;
    int count = 0;
    while (current && count < 4) {
        count++;
        current = current->next;
    }
    if (current) {
        return current->data;
    }
    
    else {
        throw runtime_error("No Fifth Element Exists.");
    }
}

template <class Type>
void FifthElement<Type>::insertNewFifthElement(const Type value) {
    int count = 0;
    auto current = this->front;
    while(current && count < 4 ) {
        count++;
        current = current->next;
    }
    auto temp = make_shared<Node<Type>>();
    temp->data = value;

    if(!this->front) { //If there is no front value
        this->front = temp;
        this->back = temp;
        return;
    }

    if(count < 4) { //If the list doesn't have a fifth element
        this->back->next = temp;
        this->back = temp;
        temp->next = nullptr;
    }

    int currNodeNum = 0;
    auto currentNode = this->front;
    while(currNodeNum < 3 && currentNode->next) { //Finding the third node
        currNodeNum++;
        currentNode = currentNode->next;
    }
    if(currentNode && currentNode->next) { //Inserting a value between the 4th and 5th elements
        currentNode->next = temp;
        temp->next = currentNode->next;

    }

}

template <class Type>
void FifthElement<Type>::deleteFifthElement() {
    auto currentNode = this->front;
    int count = 0;
    while (currentNode && count < 3) {
        count++;
        currentNode = currentNode->next;
    }
    auto toDelete = currentNode->next;
    if (!toDelete->next) {
        currentNode->next = toDelete->next;
    }
    else {
        currentNode->next = nullptr;
        this->back = currentNode;
    }
}

template <class Type>
void FifthElement<Type>::swapFourthAndFifthElement() {
    auto currentNode = this->front;
    int count = 0;
    while (currentNode && count < 4) {
        count++;
        currentNode = currentNode->next;
    }
}