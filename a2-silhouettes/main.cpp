//
// Created by abelokon on 12.04.16.
// Author abelokon
//
#include<QtGui/QImage>
#include<QtGui/QColor>
#include<iostream>
#include"myVector.h"
#include<queue>
#include<vector>

#define DEBUG true

using namespace std;

/* The structure of the data object parameters */
struct Silhouette {
    Silhouette() {
        width = 0;
        height = 0;
    }

    int width; // the width of the object
    int height;// the height of the object
};

bool **createMatrix(QImage *_img, int _rows, int _cols);

string countSilhouettes(string &_filename);

void calcNumObjInRows(bool **ptrImage, int _rows, int _columns, vector<int> &ptrObjH);

void calcNumOfPxInColumns(bool **ptrImage, int _rows, int _columns, vector<int> &ptrOfpxObjV);

vector<Silhouette> findingAllSeparatedObjects(bool **ptrImage, int rows, int columns, int &averageHeight);

void recursionFillObject(int _rows, int _columns, int i, int j, bool **ptrIMG, vector<int> &charactXOfObj,
                         vector<int> &charactYOfObj);

Silhouette createObject(vector<int> &charactXOfObj, vector<int> &charactYOfObj);

void calcHeightAndWidthOfObj(vector<int> &charactXOfObj, vector<int> &charactYOfObj, int &width, int &height);

void deleteBinaryImage(bool **pBoolean, int rows);

int calcApproximateNumOfObj(vector<Silhouette> &separatedObjects, int averageHeight);


int main() {
    string filename;
    cout << "Enter the file with the silhouettes: ";
    if (DEBUG) {
        filename = "sport-silhouettes-vector-free-27120.png";
    }
    if (!DEBUG) {
        getline(cin, filename);
    }
    cout << endl<< "The number of silhouettes: " << countSilhouettes(filename) << endl;

    return 0;
}


/*
 *  Count the silhouettes in the image
 *  @return - result - the approximate number of silhouettes of people
 */
string countSilhouettes(string &_filename) {
    QImage *img = new QImage(_filename.c_str());
    int rows = img->height(); // the number of rows in the image
    int columns = img->width(); // the number of columns in the image

    bool **binaryImage = createMatrix(img, rows, columns); // Creates binary image

    vector<int> numOfObjH(rows); // the number of objects in each row
    calcNumObjInRows(binaryImage, rows, columns, numOfObjH); // сount the number of objects in each row


    vector<int> numOfpxObjV(columns); // the number of pixels in each column
    calcNumOfPxInColumns(binaryImage, rows, columns, numOfpxObjV); // count the number of pixels in each column

    int averageHeight = 0; // The average height of all objects
    vector<Silhouette> separatedObjects = findingAllSeparatedObjects(binaryImage, rows, columns, averageHeight);

    deleteBinaryImage(binaryImage, rows); // Delete binary image

    int approximateNumObj = calcApproximateNumOfObj(separatedObjects, averageHeight);

    string result = "Approximate number of persons = " + to_string(approximateNumObj);

    return result;
}

/*  Discard is not the appropriate objects
 *  @return - int approximateNumObj - Approximate number of person in the image
 */
int calcApproximateNumOfObj(vector<Silhouette> &separatedObjects, int averageHeight) {
    int approximateNumObj = 0;
    for (int i = 0; i < separatedObjects.size(); ++i) {
        Silhouette dataObj = separatedObjects[i];
        if (dataObj.height > averageHeight / 2) { // discard all the objects height
            // Compare the proportions of body width with its height
            if ((dataObj.width <= dataObj.height / 2, 7) && (dataObj.width >= dataObj.height / 4, 7)) {
                approximateNumObj++;
            }
        }
    }
    return approximateNumObj;
}

/* Delete binary image */
void deleteBinaryImage(bool **pBoolean, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete pBoolean[i];
    }
    delete pBoolean;
}

/* find the width and height of the object */
void calcHeightAndWidthOfObj(vector<int> &charactXOfObj, vector<int> &charactYOfObj, int &width, int &height) {

    for (int i = 0; i < charactXOfObj.size(); ++i) {
        if (charactXOfObj[i] > height) {
            height = charactXOfObj[i]; // find max height of object
        }
    }
    for (int i = 0; i < charactYOfObj.size(); ++i) {
        if (charactYOfObj[i] > width) {
            width = charactYOfObj[i]; // find max width of object
        }
    }
}

/*  Create an object
 *  @return -  Silhouette dataObj - Filled objects
 */
Silhouette createObject(vector<int> &charactXOfObj, vector<int> &charactYOfObj) {
    Silhouette dataObj;
    int heightOfObj = 0; // the width of the object
    int widthOfObj = 0; // the height of the object
    calcHeightAndWidthOfObj(charactXOfObj, charactYOfObj, widthOfObj, heightOfObj); // Определяем высоту объекта и шрину

    dataObj.width = widthOfObj; // The width assigned to the current object
    dataObj.height = heightOfObj; // The height assigned to the current object

    return dataObj;
}

/* Recursively select the object from a binary image */
void recursionFillObject(int _rows, int _columns, int i, int j, bool **ptrIMG, vector<int> &charactXOfObj,
                         vector<int> &charactYOfObj) {
    if (ptrIMG[i][j] == 0) return;
    else {
        ptrIMG[i][j] = 0; // note the coordinate of the object on which
        charactXOfObj[j]++; // count the number of pixels in each column of object
        charactYOfObj[i]++; // count the number of pixels in each row of object
        if (j + 1 < _columns) {
            recursionFillObject(_rows, _columns, i, j + 1, ptrIMG, charactXOfObj, charactYOfObj);
        }
        if (i - 1 > 0) {
            recursionFillObject(_rows, _columns, i - 1, j, ptrIMG, charactXOfObj, charactYOfObj);
        }
        if (i + 1 < _rows) {
            recursionFillObject(_rows, _columns, i + 1, j, ptrIMG, charactXOfObj, charactYOfObj);
        }
        if (j - 1 > 0) {
            recursionFillObject(_rows, _columns, i, j - 1, ptrIMG, charactXOfObj, charactYOfObj);
        }
    }
}

/*
 *  Find all silhouettes and create from them objects
 *  @return - vector<Silhouette> separatedObjects - the vector of separated objects
 */
vector<Silhouette> findingAllSeparatedObjects(bool **ptrImage, int _rows, int _columns, int &averageHeight) {
    int heightOfObjects = 0; // the total height of the objects
    vector<Silhouette> separatedObjects; // the vector of separated objects
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _columns; ++j) {
            if (ptrImage[i][j] == 1) {
                vector<int> charactXOfObj(_columns, 0);
                vector<int> charactYOfObj(_rows, 0);
                recursionFillObject(_rows, _columns, i, j, ptrImage, charactXOfObj, charactYOfObj);// Select the object
                Silhouette dataObj = createObject(charactXOfObj, charactYOfObj); // create an object
                heightOfObjects += dataObj.height; // add the height of the objects
                separatedObjects.push_back(dataObj); // Put the object into the vector
            }
        }
    }
    if (!separatedObjects.empty())
        averageHeight = (int) (heightOfObjects / separatedObjects.size());// calculate the average height of the object
    return separatedObjects;
}

/* Count the number of pixels in each column */
void calcNumOfPxInColumns(bool **ptrImage, int _rows, int _columns, vector<int> &ptrOfpxObjV) {
    for (int j = 0; j < _columns; ++j) {
        for (int i = 0; i < _rows; ++i) {
            if (ptrImage[i][j] == 1) {
                ptrOfpxObjV[j]++;
            }
        }
    }
}

/* сount the number of objects in each row */
void calcNumObjInRows(bool **ptrImage, int _rows, int _columns, vector<int> &ptrObjH) {
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _columns; ++j) {
            if (ptrImage[i][j] == 1) {
                ptrObjH[i]++;
                while (ptrImage[i][j] == 1) {
                    j++;
                }
            }
        }
    }
}

/* Creates binary image */
bool **createMatrix(QImage *_img, int _rows, int _columns) {

    bool **matrix = new bool *[_rows];
    for (int i = 0; i < _rows; ++i) {
        matrix[i] = new bool[_columns];
    }
    for (int y = 0; y < _rows; y++) {
        for (int x = 0; x < _columns; x++) {
            matrix[y][x] = (QColor(_img->pixel(x, y)).lightness() < 128) ? 1 : 0;
//                cout<<((QColor(_img->pixel(x,y)).lightness() < 128) ? 1 : 0)<<" ";
        }
//            cout<<endl;
    }

    return matrix;
}
