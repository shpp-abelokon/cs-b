#include <iostream>
#include <vector>
#include <list>
#include <stack>
//#include <queue>
#include "myVector.h"
#include "myList.h"
#include "myStack.h"
#include "myQueue.h"

#define space cout<<"------------------------"<<endl;
#define DEBUG_myVector false
#define DEBUG_myList false
#define DEBUG_myStack false
#define DEBUG_myQueue true
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    if (DEBUG_myQueue) {
        myQueue<int> a;
        a.push(10);
        a.push(20);
        cout<<"a.front(): "<<a.front()<<endl;
//
//        queue<int> b;

    }
    if (DEBUG_myStack) {
        cout << "Create a first 'a' stack and fill in {\"Java\",\"C++\"} " << endl;
        myStack<string> a;
        a.push("Java");
        a.push("C+");
        cout << "myStack a.size: " << a.size() << endl;
        cout << "myStack a.capacity: " << a.capacity() << endl;
        cout << "myStack a.top(): " << a.top() << endl;
        space
        cout << "The called method a.push(\"Ruby\");" << endl;
        a.push("Ruby");
        cout << "myStack a.size: " << a.size() << endl;
        cout << "myStack a.capacity: " << a.capacity() << endl;
        cout << "myStack a.top(): " << a.top() << endl;
        space
        cout << "The called method a.pop();" << endl;
        a.pop();
        cout << "myStack a.size: " << a.size() << endl;
        cout << "myStack a.capacity: " << a.capacity() << endl;
        cout << "myStack a.top(): " << a.top() << endl;
        space
        cout << "Create a second 'b' stack and fill in {\"rshmelev\",\"abelokon\",\"shpp\"}" << endl;
        myStack<string> b;
        a.push("rshmelev");
        a.push("abelokon");
        a.push("shpp");
        cout << "Compare the stack \"a==b\": " << boolalpha << (a == b) << endl;
        cout << "Compare the stack \"a!=b\": " << boolalpha << (a != b) << endl;
        space
        cout << "Assign the stack \"a=b\": " << endl;
        a = b;
        cout << "Compare the stack \"a==b\": " << boolalpha << (a == b) << endl;
        cout << "Compare the stack \"a!=b\": " << boolalpha << (a != b) << endl;
        cout << "The called method a.empty(): " << boolalpha << a.empty() << endl;
    }

    if (DEBUG_myList) {

        myList<string> b;
        b.push_back("Java");
        b.push_back("C++");
        myList<string>::iterator itr;
        myList<string>::iterator itr_end;
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "myList b [" << i << "] " << *itr << endl;
        }
        cout << "myList b.size: " << b.size() << endl;
        space
        cout << "The called method p.front(\"Ruby\");" << endl;
        b.push_front("Ruby");
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "myList b [" << i << "] " << *itr << endl;
        }
        cout << "myList b.size: " << b.size() << endl;
        space
        cout << "The called method b.insert(itr_end,\"C#\");" << endl;
        itr = b.begin();
        itr_end = b.end();
        b.insert(itr_end, "C#");
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "myList b [" << i << "] " << *itr << endl;
        }
        cout << "myList b.size: " << b.size() << endl;
        space
        cout << "Create a second 'a' list and fill in {\"rshmelev\",\"abelokon\",\"shpp\"} " << endl;
        myList<string> a;
        a.push_back("rshmelev");
        a.push_back("abelokon");
        a.push_back("shpp");
        cout << "The called method b.swap(a);" << endl;
        b.swap(a);
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "myList b [" << i << "] " << *itr << endl;
        }
        cout << "myList b.size: " << b.size() << endl;
        space
        cout << "Assign the list \"b=a\": " << endl;
        b = a;
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "myList b [" << i << "] " << *itr << endl;
        }
        cout << "myList b.size: " << b.size() << endl;
        space
        cout << "The called method b.erase(itr);" << endl;
        itr = b.begin();
        itr_end = b.end();
        b.erase(itr);
        itr = b.begin();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "myList b [" << i << "] " << *itr << endl;
        }
        cout << "myList b.size: " << b.size() << endl;
        space
        cout << "The called method b.front(); " << b.front() << endl;
        cout << "The called method b.back(); " << b.back() << endl;
        cout << "The called method b.pop_front();" << endl;
        b.pop_front();
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "myList b [" << i << "] " << *itr << endl;
        }
        cout << "myList b.size: " << b.size() << endl;
        space
        cout << "The called method b.pop_back();" << endl;
        b.pop_back();
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "myList b [" << i << "] " << *itr << endl;
        }
        cout << "myList b.size: " << b.size() << endl;
    }

    if (DEBUG_myVector) {
        myVector<string> p;
        p.push_back("10");
        p.push_back("20");
        p.push_back("30");
        for (int i = 0; i < p.size(); ++i) {
            cout << "myVector p [" << i << "] " << p[i] << endl;
        }
        cout << "The called method p.resize(6,\"40\");" << endl;
        p.resize(6, "40");
        for (int i = 0; i < p.size(); ++i) {
            cout << "myVector p [" << i << "] " << p[i] << endl;
        }
        space
        cout << "myVector p.front(): " << p.front() << endl;
        cout << "myVector p.back(): " << p.back() << endl;
        cout << "myVector p.at(1): " << p.at(1) << endl;
        cout << "myVector p.size: " << p.size() << endl;
        cout << "myVector p.capacity: " << p.capacity() << endl;
        space
        cout << "The called method p.resize(8);" << endl;
        p.resize(8);
        cout << "myVector p.capacity: " << p.capacity() << endl;
        space
        cout << "The called method p.resize(8,\"resize_value\");" << endl;
        p.resize(8, "resize_value");
        for (int i = 0; i < p.size(); ++i) {
            cout << "myVector p [" << i << "] " << p[i] << endl;
        }
        space
        cout << "The called method p.reserve(20);" << endl;
        p.reserve(20);
        cout << "myVector p.capacity: " << p.capacity() << endl;
        cout << "myVector p.size: " << p.size() << endl;
        space
        cout << "The called method p.emty();" << endl;
        cout << "myVector p.emty: " << boolalpha << (p.empty()) << endl;
        space
        cout << "Create a second 'a' vector and fill in {\"rshmelev\",\"abelokon\",\"shpp\"} " << endl;
        myVector<string> a;
        a.push_back("rshmelev");
        a.push_back("abelokon");
        a.push_back("shpp");
        cout << "Compare the vectors \"p==a\": " << boolalpha << (p == a) << endl;
        cout << "Compare the vectors \"p!=a\": " << boolalpha << (p != a) << endl;
        cout << "The called method p.swap(a); " << endl;
        p.swap(a);
        for (int j = 0; j < p.size(); ++j) {
            cout << "myVector p [" << j << "] " << p[j] << endl;
        }
        space
        cout << "The called method p.max_size(); " << p.max_size() << endl;
        cout << "Print contents of the vector \"p\" using iterators " << endl;
        myVector<string>::iterator itr = p.begin();
        myVector<string>::iterator itr_end = p.end();
        for (int j = 0; itr != itr_end; ++itr, ++j) {
            cout << "myVector p [" << j << "] " << *itr << endl;
        }
        space
        cout << "The called method p.erase(itr+1); " << endl;
        myVector<string>::iterator itr2 = p.begin();
        p.erase(itr2 + 1);
        for (int j = 0; j < p.size(); ++j) {
            cout << "myVector p [" << j << "] " << p[j] << endl;
        }
        space
        cout << "The called method p.insert(1,\"abelokon\"); " << endl;
        p.insert(1, "abelokon");
        for (int j = 0; j < p.size(); ++j) {
            cout << "myVector p [" << j << "] " << p[j] << endl;
        }
        space
        cout << "The called method p.swap(a); " << endl;
        for (int j = 0; j < p.size(); ++j) {
            cout << "myVector p [" << j << "] " << p[j] << endl;
        }
        cout << "Assign the vector \"p=a\": " << endl;
        p = a;
        for (int i = 0; i < p.size(); ++i) {
            cout << "myVector p [" << i << "] " << p[i] << endl;
        }
        space
        cout << "myVector p.capacity: " << p.capacity() << endl;
        cout << "myVector p.size: " << p.size() << endl;
        cout << "The called method p.shrink_to_fit(); " << endl;
        p.shrink_to_fit();
        cout << "myVector p.capacity: " << p.capacity() << endl;
        cout << "myVector p.size: " << p.size() << endl;
        space
        cout << "The called method p.clear(); " << endl;
        p.clear();
        for (int i = 0; i < p.size(); ++i) {
            cout << "myVector p [" << i << "] " << p[i] << endl;
        }
    }

    return 0;
}