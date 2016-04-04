#include <iostream>
#include <vector>
#include <list>
#include "myVector.h"
#include "myList.h"

#define space cout<<"------------------------"<<endl;
#define DEBUG_myVector false
#define DEBUG_myList true
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    if(DEBUG_myList){

        myList<int> b;
        b.push_back(10);
        b.push_back(20);
        b.push_back(30);

        myList<int> f;
        f.push_back(90);
        f.push_back(80);
        f.push_back(70);
        f.push_back(60);
        b=f;
//        f.head=b.begin();

//        for (int i = 0; i <4 ; ++i, f.head=f.head->next) {
//
//            cout<<f.head->data<<endl;
////            f.head=b.head->next;
//        }

        myList<int>::iterator itr=b.begin();
        myList<int>::iterator itr_end=b.end();
        myList<int>::iterator itr_temp;
//        myList<int>::iterator itr_end;
//        b.insert(itr+2,55);
        itr_temp=b.begin();
        for (int i=0; itr != itr_end; ++itr,i++) {
            if(i==2){
                b.insert(itr,50);
            }

            cout<<*itr<<endl;
        }
        space
        itr=b.begin();
        itr_end=b.end();
        for (int i=0; itr != itr_end; itr++,i++) {
            cout<<*itr<<endl;
        }
        space
        itr=b.begin();
        itr_end=b.end();
//        b.erase(itr);
        cout<<"back(): "<<b.back()<<endl;
        for (int i=0; itr != itr_end; itr++,i++) {
            if(i==3){

//                b.pop_back();
                b.erase(itr);
                cout<<"itr равен: "<<*itr<<endl;
            }

        }
        space
        itr=b.begin();
        itr_end=b.end();
        for (int i=0; itr != itr_end; itr++,i++) {
            cout<<*itr<<endl;
        }
//        cout<<b.front()<<endl;
//        cout<<b.back()<<endl;
        space
//        itr=b.begin();
//        cout<<(itr+1)->data<<endl;
//        cout<<(itr+1)->data<<endl;
//        cout<<(itr+1)->data<<endl;
//        cout<<(itr+1)->data<<endl;
//        space
//        cout<<b.begin()<<endl;
//        cout<<b.end()<<endl;
        list<string> c;
        c.push_back("viktor");
        c.push_back("Bell");
        c.push_back("Alex");
        c.sort();
        list<string>::iterator itr2=c.begin();
        list<string>::iterator itr2_end=c.end();
        for (int j=0; itr2 !=itr2_end ; itr2++,j++) {
//            if (j==2){
//                c.erase(itr2);
                cout<<"["<<j<<"] "<<*itr2<<endl;
//            }
        }


    }

    if (DEBUG_myVector) {
        myVector<string> p;
        p.push_back("10");
        p.push_back("20");
        p.push_back("30");
        for (int i = 0; i < p.size(); ++i) {
            cout << "myVector p [" << i << "] " << p[i] << endl;
        }
        cout << "The called method p.resize(6,\"40\");"<<endl;
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
        p.insert(1,"abelokon");
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