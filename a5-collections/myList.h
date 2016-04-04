//
// Created by alex on 28.03.16.
//

#ifndef A5_COLLECTIONS_MYLIST_H
#define A5_COLLECTIONS_MYLIST_H
using namespace std;

template<typename T>
class myList {
private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };
    size_t count;
    Node *head;
    Node *tail;
public:

    class iterator {

    public:
        Node *nodePtr;

        iterator();

        iterator(Node *ptr);

        T &operator*();

        iterator &operator++(int i) {
            nodePtr = nodePtr->next;
            return *this;
        }

        iterator &operator++() {
            nodePtr = nodePtr->next;
            return *this;
        }

        iterator &operator--(int i) {
            nodePtr = nodePtr->prev;
            return *this;
        }

        iterator &operator--() {
            nodePtr = nodePtr->prev;
            return *this;
        }

        bool operator==(const iterator &ptr);

        bool operator!=(const iterator &ptr);

    };

    myList();

    myList(const myList<T> &other);

    ~myList();

    bool empty() const;

    void clear();

    void push_back(const T &value);

    void push_front(const T &value);

    void pop_back();

    void pop_front();

    void insert(iterator itr, const T &value);

    void erase(iterator itr);

    size_t size();

    T &front();

    T &back();

    iterator begin() {
        iterator b(head);
        return b;
    }

    iterator end() {
        iterator e(tail->next);
        return e;
    }
    void operator=(const T &other);
};

template<typename T>
myList<T>::iterator::iterator() {
    nodePtr = NULL;
}

template<typename T>
myList<T>::iterator::iterator(myList<T>::Node *ptr) {
    nodePtr = ptr;
}

template<typename T>
T &myList<T>::iterator::operator*() {
    return nodePtr->data;
}

template<typename T>
bool myList<T>::iterator::operator==(const iterator &ptr) {
    return nodePtr == ptr.nodePtr;
}

template<typename T>
bool myList<T>::iterator::operator!=(const iterator &ptr) {
    return nodePtr != ptr.nodePtr;
}




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
    if (!head) {
        head = new Node;
        head->data = value;
        head->prev = NULL;
        head->next = NULL;
        tail = head;
    } else {
        tail->next = new Node;
        tail->next->prev = tail;
        tail = tail->next;
        tail->next = NULL;
        tail->data = value;
    }

//    Node *n = new Node;
//    n->data = value;
//    n->prev = NULL;
//    n->next = NULL;
//    if (head == NULL) {
//        head = n;
//        tail = n;
//    } else {
//        n->prev = tail;
//        tail->next = n;
//        tail = n;
//        tail->data=n->data;
//    }
    count++;
}

template<typename T>
void myList<T>::push_front(const T &value) {
    Node *n = new Node;
    n->data = value;
    n->prev = NULL;
    n->next = NULL;
    if (head == NULL) {
        tail = head = n;
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
void myList<T>::insert(iterator itr, const T &value) {
    if (empty()) {
        cerr << "Error [insert]. The list is empty." << endl;
        exit(0);
    }
    if (itr == begin()) {
        push_front(value);
    }
    else if (itr == tail) {
        push_back(value);

    }
    else if (itr != NULL) {
        Node *n = new Node;
        n->data = value;
        n->next = itr.nodePtr;
        n->prev = itr.nodePtr->prev;
        itr.nodePtr->prev->next = n;
        itr.nodePtr->prev = n;
        count++;
    } else {
        cerr << "Error [insert]. Iterator is out of range." << endl;
        exit(0);
    }
}

template<typename T>
void myList<T>::erase(iterator itr) {
    if (empty()) {
        cerr << "Error [erase]. The list is empty." << endl;
        exit(0);
    }
    else if (itr == begin()) {
        pop_front();
    } else if (itr == tail) {
        pop_back();
    }
    else if (itr != NULL) {
        itr.nodePtr->prev->next = itr.nodePtr->next;
        itr.nodePtr->next->prev = itr.nodePtr->prev;
        count--;
    } else {
        cerr << "Error [erase]. Iterator is out of rande." << endl;
    }
}

template<typename T>
void myList<T>::operator=(const T &other) {
    if(head!=other->head){
        head=other->head;
        tail=other->tail;
        count=other->count;
    }
}


#endif //A5_COLLECTIONS_MYLIST_H
