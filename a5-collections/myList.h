//
// Created by alex on 28.03.16.
//

#ifndef A5_COLLECTIONS_MYLIST_H
#define A5_COLLECTIONS_MYLIST_H
using namespace std;

template<typename T>
class myList {
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };
    size_t count;
    Node *head;
    Node *tail;
public:
    typedef T *iterator;

    myList();

    myList(const myList<T> &other);

    ~myList();

    bool empty() const;

    void clear();

    void push_back(const T &value);

    void push_front(const T &value);

    void pop_back();

    void pop_front();

    size_t size();

    T &front();

    T &back();

    iterator begin();

    iterator end();


};

/*Constructor*/
template<typename T>
myList<T>::myList() {
    head = tail = NULL;
    count = 0;
}

/*Copy-constructor*/
template<typename T>
myList<T>::myList(const myList<T> &other) {
    if (!other.empty()) {
        head = tail = NULL;
        count = 0;
        for (Node *n = other.head; n != NULL; n = n->next) {
            push_back(n->data);
        }
    } else {
        cerr << "Error [copy constructor]. Try to copy empty list..." << endl;
    }
}

/* Destructor */
template<typename T>
myList<T>::~myList() {
    clear();
}


/* Check the list is empty */
template<typename T>
bool myList<T>::empty() const {
    return (count == 0);
}


/* Delete all elements of the list */
template<typename T>
void myList<T>::clear() {
    while (head) {
        head->prev = NULL;
        head = head->next;
    }
    count = 0;
}

template<typename T>
void myList<T>::push_back(const T &value) {
    Node *n = new Node;
    n->data = value;
    n->prev = NULL;
    n->next = NULL;
    if (head == NULL) {
        head = n;
        tail = n;
    } else {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }
    count++;
}

template<typename T>
void myList<T>::push_front(const T &value) {
    Node *n = new Node;
    n->data = value;
    n->prev = NULL;
    n->next = NULL;
    if (head == NULL) {
        head = n;
        tail = n;
    } else {
        n->next = head;
        head->prev = n;
        head = n;
    }
    count++;

}

template<typename T>
void myList<T>::pop_back() {
    if (empty()) {
        cerr << "Error [pop_back]. The list is empty." << endl;
        exit(0);
    }
    tail = tail->prev;
    (tail == NULL) ? head = NULL : tail->next = NULL, count--;

//    if (tail==NULL){
//        head=NULL;
//    } else {
//        tail->next=NULL;
//        count--;
//    }
}

template<typename T>
void myList<T>::pop_front() {
    if (empty()) {
        cerr << "Error [pop_front]. The list is empty." << endl;
        exit(0);
    }
    head = head->next;
    (head == NULL) ? tail = NULL : head->prev = NULL, count--;
//    if(head==NULL){
//        tail=NULL;
//    } else{
//        head->prev=NULL;
//        count--;
//    }


}

template<typename T>
size_t myList<T>::size() {
    return count;
}

template<typename T>
T &myList<T>::front() {
    if (empty()) {
        cerr << "Error [front]. The list is empty." << endl;
        exit(0);
    }
    return head->data;
}

template<typename T>
T &myList<T>::back() {
    if (empty()) {
        cerr << "Error[back]. The list is empty." << endl;
        exit(0);
    }
    return tail->data;
}

template<typename T>
typename myList<T>::iterator myList<T>::begin() {
    return head;
}

template<typename T>
typename myList<T>::iterator myList<T>::end() {
    return tail;
}


#endif //A5_COLLECTIONS_MYLIST_H
