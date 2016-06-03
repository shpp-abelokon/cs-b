//
// Created by abelokon on 28.03.16.
// File: MyList.h
// Author abelokon
//

#ifndef A5_COLLECTIONS_MYLIST_H
#define A5_COLLECTIONS_MYLIST_H


template<typename T>
class MyList {
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

        /* Overload the operator increment ++ to iterator */
        iterator &operator++(int i) {
            nodePtr = nodePtr->next;
            return *this;
        }

        /* Overload the operator prefix increment ++ to iterator */
        iterator &operator++() {
            nodePtr = nodePtr->next;
            return *this;
        }

        /* Overload the operator decrement -- to iterator */
        iterator &operator--(int i) {
            nodePtr = nodePtr->prev;
            return *this;
        }

        /* Overload the operator prefix increment -- to iterator */
        iterator &operator--() {
            nodePtr = nodePtr->prev;
            return *this;
        }

        bool operator==(const iterator &ptr);

        bool operator!=(const iterator &ptr);

    };

    MyList();

    MyList(const MyList<T> &other);

    ~MyList();

    bool empty() const;

    void clear();

    void push_back(const T &value);

    void push_front(const T &value);

    void pop_back();

    void pop_front();

    void insert(iterator itr, const T &value);

    void erase(iterator itr);

    void swap(MyList &other);

    size_t size();

    T &front();

    T &back();

    /* Pointer to the start of the list */
    iterator begin() {
        iterator b(head);
        return b;
    }

    /* Pointer to the end of the list */
    iterator end() {
        iterator e(tail->next);
        return e;
    }

    void operator=(const T &other);


};

/* Constructor iterator */
template<typename T>
MyList<T>::iterator::iterator() {
    nodePtr = NULL;
}

/* Copy-constructor iterator*/
template<typename T>
MyList<T>::iterator::iterator(MyList<T>::Node *ptr) {
    nodePtr = ptr;
}

/* Overload the operator * to iterator */
template<typename T>
T &MyList<T>::iterator::operator*() {
    return nodePtr->data;
}

/* Overload the operator == to iterator */
template<typename T>
bool MyList<T>::iterator::operator==(const iterator &ptr) {
    return nodePtr == ptr.nodePtr;
}

/* Overload the operator != to iterator */
template<typename T>
bool MyList<T>::iterator::operator!=(const iterator &ptr) {
    return nodePtr != ptr.nodePtr;
}

/* Constructor */
template<typename T>
MyList<T>::MyList() {
    head = tail = NULL;
    count = 0;
}

/* Copy-constructor */
template<typename T>
MyList<T>::MyList(const MyList<T> &other) {
    if (!other.empty()) {
        head = tail = NULL;
        count = 0;
        for (Node *n = other.head; n != NULL; n = n->next) {
            push_back(n->data);
        }
    } else {
        std::cerr << "Error [copy constructor]. Try to copy empty list..." << std::endl;
    }
}

/* Destructor */
template<typename T>
MyList<T>::~MyList() {
    clear();
}

/* Check the list is empty */
template<typename T>
bool MyList<T>::empty() const {
    return (count == 0);
}

/* Delete all elements of the list */
template<typename T>
void MyList<T>::clear() {
    while (head) {
        head->prev = NULL;
        head = head->next;
    }
    count = 0;
}

/* Add element to the end of list */
template<typename T>
void MyList<T>::push_back(const T &value) {
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
        tail->data = n->data;
    }
    count++;
}

/* Add element to the start of list */
template<typename T>
void MyList<T>::push_front(const T &value) {
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

/* Delete the last element from the list */
template<typename T>
void MyList<T>::pop_back() {
    if (empty()) {
        std::cerr << "Error [pop_back]. The list is empty." << std::endl;
        exit(1);
    }
    tail = tail->prev;
    (tail == NULL) ? head = NULL : tail->next = NULL, count--;
}

/* Delete the first element from the list */
template<typename T>
void MyList<T>::pop_front() {
    if (empty()) {
        std::cerr << "Error [pop_front]. The list is empty." << std::endl;
        exit(1);
    }
    head = head->next;
    (head == NULL) ? tail = NULL : head->prev = NULL, count--;
}

/* Number of elements of the list */
template<typename T>
size_t MyList<T>::size() {
    return count;
}

/* The first element in the list */
template<typename T>
T &MyList<T>::front() {
    if (empty()) {
        std::cerr << "Error [front]. The list is empty." << std::endl;
        exit(1);
    }
    return head->data;
}

/* The last element in the list */
template<typename T>
T &MyList<T>::back() {
    if (empty()) {
        std::cerr << "Error[back]. The list is empty." << std::endl;
        exit(1);
    }
    return tail->data;
}

/* Insert element to the list in current position */
template<typename T>
void MyList<T>::insert(iterator itr, const T &value) {
    if (empty()) {
        std::cerr << "Error [insert]. The list is empty." << std::endl;
        exit(1);
    }
    if (itr == begin()) {
        push_front(value);
    }
    else if (itr == end()) {
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
        std::cerr << "Error [insert]. Iterator is out of range." << std::endl;
        exit(1);
    }
}

/* Delete element from the list from the current position */
template<typename T>
void MyList<T>::erase(iterator itr) {
    if (empty()) {
        std::cerr << "Error [erase]. The list is empty." << std::endl;
        exit(1);
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
        std::cerr << "Error [erase]. Iterator is out of rande." << std::endl;
    }
}

/* Overload operator = */
template<typename T>
void MyList<T>::operator=(const T &other) {
    if (head != other->head) {
        head = other->head;
        tail = other->tail;
        count = other->count;
    }
}

/* The exchange of content between two MyList */
template<typename T>
void MyList<T>::swap(MyList &other) {
    if (other.head != head && other.tail != tail) {
        Node *head_tmp = other.head;
        Node *tail_tmp = other.tail;
        size_t count_tmp = other.count;

        other.head = head;
        other.tail = tail;
        other.count = count;
        head = head_tmp;
        tail = tail_tmp;
        count = count_tmp;

    }
}


#endif //A5_COLLECTIONS_MYLIST_H
