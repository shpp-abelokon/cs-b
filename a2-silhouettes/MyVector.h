//
// Created by abelokon on 28.03.16.
// File: MyVector.h
// Author abelokon
//

#ifndef A5_COLLECTIONS_MYVECTOR_H
#define A5_COLLECTIONS_MYVECTOR_H

template<class T>
class MyVector {
private:
    T *vectorPtr; // reference to the region of allocated memory for the vector
    size_t maxSize; // the current size of the vector
    size_t vSize; // the number of elements in vector, 0 is the vector is empty

    bool equal(const MyVector<T> &other) const;

public:
    typedef T *iterator;

    MyVector(size_t s = 0);

    MyVector(const MyVector<T> &);

    MyVector(size_t, const T & = 0);

    ~MyVector();

    size_t size() const;

    void resize(size_t size);

    void resize(size_t size, T value);

    void push_back(const T &value);

    void pop_back();

    T &front();

    T &back();

    bool empty();

    size_t capacity();

    T &operator[](const size_t &_index);

    void operator=(const T &other);

    bool operator==(const MyVector<T> &other) const;

    bool operator!=(const MyVector<T> &other) const;

    iterator begin();

    iterator end();

    size_t max_size() const;

    void erase(iterator itr);

    void shrink_to_fit();

    void reserve(const size_t value);

    void clear();

    T &at(const size_t index);

    void insert(size_t index, const T &value);

    void swap(MyVector &other);

};

/* Constructor */
template<typename T>
MyVector<T>::MyVector(size_t s) {
    vSize = s;
    maxSize = (s != 0) ? s : 2;
    vectorPtr = new T[maxSize];
}

/* Copy constructor */
template<typename T>
MyVector<T>::MyVector(const MyVector<T> &other) {
    vSize = other.vSize;
    maxSize = other.maxSize;
    vectorPtr = new T[maxSize];
    for (size_t i = 0; i < vSize; i++) {
        vectorPtr[i] = other.vectorPtr[i];
    }
}

/* Secondary consrtuctor */
template<typename T>
MyVector<T>::MyVector(size_t newSize, const T &value) {
    vSize = newSize;
    maxSize = newSize;
    vectorPtr = new T[newSize];
    for (int i = 0; i < newSize; i++) {
        vectorPtr[i] = value;
    }
}

/* Destructor */
template<typename T>
MyVector<T>::~MyVector() {
    delete[] vectorPtr;
    vSize = 0;
}


/* The number of elements in the vector */
template<typename T>
size_t MyVector<T>::size() const { return vSize; }

/* Change the size of the current vector by the specified size */
template<typename T>
void MyVector<T>::resize(size_t size = 0) {
    if (size >= maxSize) {
        maxSize = (size > maxSize) ? size : maxSize * 2;
        T *tmpPtr = new T[maxSize];
        for (int i = 0; i < vSize; ++i) {
            tmpPtr[i] = vectorPtr[i];
        }
        T *tmp = vectorPtr;
        vectorPtr = tmpPtr;
        delete[]tmp;
    }
}

/* Change the size of the current vector to the specified size and fill the given value */
template<typename T>
void MyVector<T>::resize(size_t size, T value) {
    maxSize = size;
    T *tmpPtr = new T[maxSize];
    for (int i = 0; i < maxSize; ++i) {
        tmpPtr[i] = (i < vSize) ? vectorPtr[i] : value;
    }
    T *tmp = vectorPtr;
    vSize = maxSize;
    vectorPtr = tmpPtr;
    delete[]tmp;
}

/* Add element to the end of vector */
template<typename T>
void MyVector<T>::push_back(const T &value) {
    if (vSize == maxSize) {
        resize(maxSize);
    }
    vectorPtr[vSize] = value;
    vSize++;
}

/* Delete the last element from the vector */
template<typename T>
void MyVector<T>::pop_back() {
    if (vSize != 0) {
        vSize--;
    }
}

/* The first element of the vector */
template<typename T>
T &MyVector<T>::front() {
    return *begin();
}

/* The last element of the vector */
template<typename T>
T &MyVector<T>::back() {
    return *(end() - 1);
}

/* Check the vector is empty */
template<typename T>
bool MyVector<T>::empty() {
    return vSize == 0;
}

/* The capacity of the vector */
template<typename T>
size_t MyVector<T>::capacity() {
    return maxSize;
}

/* Overload operator [] */
template<typename T>
T &MyVector<T>::operator[](const size_t &_index) {
    return vectorPtr[_index];
}

/* Overload operator = */
template<typename T>
void MyVector<T>::operator=(const T &other) {
    if (vectorPtr != other.vectorPtr) {
        maxSize = other.maxSize;
        vSize = other.currentSize;
        delete[] vectorPtr;
        T *vector = new T[maxSize];
        for (size_t i = 0; i < maxSize; ++i) {
            vector[i] = other.vectorPtr[i];
        }
    }
}

/* Overload operator == */
template<typename T>
bool MyVector<T>::operator==(const MyVector<T> &other) const {
    return (vectorPtr == other.vectorPtr) ? true : (vSize != other.vSize) ? false : equal(other);
}

/* Overload operator != */
template<typename T>
bool MyVector<T>::operator!=(const MyVector<T> &other) const {
    return !((vectorPtr == other.vectorPtr) ? true : (vSize != other.vSize) ? false : equal(other));
}

/* Pointer to the start of the vector */
template<typename T>
typename MyVector<T>::iterator MyVector<T>::begin() {
    return vectorPtr;
}

/* Pointer to the end of the vector */
template<typename T>
typename MyVector<T>::iterator MyVector<T>::end() {
    return vectorPtr + (vSize);
}


/* A comparison of two objects */
template<typename T>
bool MyVector<T>::equal(const MyVector<T> &other) const {
    if (this->vSize != other.vSize) {
        return false;
    } else {
        size_t i = 0;
        for (; i < other.vSize; ++i) {
            if (other.vectorPtr[i] != vectorPtr[i]) {
                return false;
            }
        }
        return true;
    }
}

/* The max possible size of the vector */
template<typename T>
size_t MyVector<T>::max_size() const {
    return (size_t) (-1) / sizeof(size_t);
}

/* Delete element in current position with iterator */
template<typename T>
void MyVector<T>::erase(iterator itr) {
    if (itr != end()) {
        for (; itr != end(); ++itr) {
            *itr = *(itr + 1);
        }
        pop_back();
    } else {
        pop_back();
    }
}

/* Reduces the amount of used memory by freeing unused */
template<typename T>
void MyVector<T>::shrink_to_fit() {
    if (maxSize != vSize) {
        T *tmpPtr = new T[vSize];
        int i = 0;
        for (; i < vSize; ++i) {
            tmpPtr[i] = vectorPtr[i];
        }
        delete[] vectorPtr;
        vectorPtr = tmpPtr;
        maxSize = vSize;
    }
}

/* Reserve needed memory for currrent vector */
template<typename T>
void MyVector<T>::reserve(const size_t value) {
    if (vSize < value) {
        if (maxSize < value) {
            T *tmpPtr = new T[value];
            size_t i = 0;
            for (; i < vSize; ++i) {
                tmpPtr[i] = vectorPtr[i];
            }
            delete[] vectorPtr;
            vectorPtr = tmpPtr;
            maxSize = value;
        }
    }
}

/* Delete all elements of the vector */
template<typename T>
void MyVector<T>::clear() {
    vSize = 0;
}

/* Access element by index */
template<typename T>
T &MyVector<T>::at(const size_t index) {
    try {
        if (index >= maxSize) {
            throw 1;
        }
        return vectorPtr[index];
    } catch (int e) {
        std::cout << "Error at(" << index << "). Out of range." << std::endl;
        exit(1);
    }
}

/* Insert element to the vector in curent position */
template<typename T>
void MyVector<T>::insert(size_t index, const T &value) {
    if (index == vSize) {
        resize(maxSize + 1);
    }
    try {
        if (index < 0 || index > vSize) {
            throw 1;
        }
        T *tmpPtr = new T[maxSize];
        for (int i = 0, j = 0; i < vSize + 1; ++i, ++j) {
            if (i == index) {
                tmpPtr[i] = value;
                j -= 1;
            } else {
                tmpPtr[i] = vectorPtr[j];
            }
        }
        delete[] vectorPtr;
        vectorPtr = tmpPtr;
        vSize += 1;
    } catch (int e) {
        std::cout << "Error insert (" << index << "). Out of range." << std::endl;
        exit(1);
    }
}

/* Exchange contents of two vectors */
template<typename T>
void MyVector<T>::swap(MyVector &other) {
    if (vectorPtr != other.vectorPtr) {
        T *tmpPtr = vectorPtr;
        size_t tmpvSize = vSize;
        size_t tmpMaxSize = maxSize;
        vectorPtr = other.vectorPtr;
        vSize = other.vSize;
        maxSize = other.maxSize;
        other.vectorPtr = tmpPtr;
        other.vSize = tmpvSize;
        other.maxSize = tmpMaxSize;
    }
}


#endif //A5_COLLECTIONS_MYVECTOR_H
