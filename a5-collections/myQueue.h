//
// Created by alex on 05.04.16.
//

#ifndef A5_COLLECTIONS_MYQUEUE_H
#define A5_COLLECTIONS_MYQUEUE_H


template <typename T>
class myQueue {
    struct Node {
        T data;
        Node * next;
    };
    size_t _capacity;
    size_t _size;
    Node* head;
    Node* tail;

public:
    myQueue();
    ~myQueue();
    void push(const T& value);
    T& front()const;
    bool empty() const;

};

template <typename T>
myQueue<T>::myQueue() {
    head=NULL;
    _size=0;
}

template <typename T>
myQueue<T>::~myQueue() {

}
template <typename T>
void myQueue<T>::push(const T &value) {
    Node * nodePtr =new Node;
    nodePtr->data=value;
    nodePtr->next=NULL;
    if(head==NULL){
        head=tail=nodePtr;
    } else {
        tail->next= nodePtr;
        tail=nodePtr;
    }
    _size++;
}

template <typename T>
T &myQueue<T>::front() const {
    if(empty()){
        std::cerr<<"Error [front]. queue is empty!"<<std::endl;
    }
    return head->data;
}
template <typename T>
bool myQueue<T>::empty() const {
    return _size==0;
}


#endif //A5_COLLECTIONS_MYQUEUE_H
