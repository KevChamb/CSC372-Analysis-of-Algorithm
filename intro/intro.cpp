#include <chrono>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <stdlib.h>

using namespace std;

bool bubbleSort(vector <int>& input);
void heapSort(vector <int>& input);
void buildMaxHeap(vector <int>& input, size_t heapSize);
void maxHeapify(vector <int>& input, size_t i, size_t heapSize);
size_t Left(size_t i);
size_t Right(size_t i);
void swapNum(int& x, int& y);
void print(vector <int> input);
void random(vector <int>& input, int size);
void sorted(vector <int>& input, int size);

//--------ProtoTypes-----------------------------


int main(int argc,char* argv[])
{
    //TODO Error check
    srand(static_cast<unsigned int>(time(NULL)));
    fstream fout;
    vector <int> input;
    string sortType = argv[1];

    for (int i = 2; i < argc; i++){
        string temp = argv[i];
        int temp2 = stoi(temp);
        input.push_back(temp2);
    }

    //For testing
    /*list<int> ::iterator it;
    for (it = input.begin(); it != input.end(); ++it)
    {
        cout << '\t' << *it;
    }*/

    if (sortType == "b"){
        bubbleSort(input); //vector passed by reerence 
    }
    else if (sortType == "h"){
        heapSort(input); //vector passed by reference
    }
    else if (sortType == "t") {
        
        fout.open("Times.csv", ios::out | ios::app);
        vector <int> sHeap;
        vector <int> rHeap;
        vector <int> sBubble;
        vector <int> rBubble;
        
        //50 tests
        fout << "Size," << "Bubble Sorted," << "Heap Sorted," << "Bubble Rand," <<
            "Heap Rand" << endl;
        for (int j = 1; j < 100; j++) {

            //unsigned int time_ui = static_cast<unsigned int>(time(NULL));
            random(rHeap, j);
            rBubble = rHeap;
            sorted(sBubble, j);
            sHeap = sBubble;

            //Sorted
            auto startSB = chrono::steady_clock::now();
            bubbleSort(sBubble);
            auto endSB = chrono::steady_clock::now();

            auto startSH = chrono::steady_clock::now();
            heapSort(sHeap); 
            auto endSH = chrono::steady_clock::now();

            //Random
            auto startRB = chrono::steady_clock::now();
            bubbleSort(rBubble);
            auto endRB = chrono::steady_clock::now();

            auto startRH = chrono::steady_clock::now();
            heapSort(rHeap);
            auto endRH = chrono::steady_clock::now();
            
            size_t timeSB= chrono::duration_cast<chrono::nanoseconds>(endSB - startSB).count();
            size_t timeSH = chrono::duration_cast<chrono::nanoseconds>(endSH - startSH).count();
            size_t timeRB = chrono::duration_cast<chrono::nanoseconds>(endRB - startRB).count();
            size_t timeRH = chrono::duration_cast<chrono::nanoseconds>(endRH - startRH).count();

            fout << j << "," << timeSB <<"," <<timeSH <<","<<
                timeRB <<","<< timeRH << endl;

            //testing
            //print(input);
            //cout << endl;
           /* print(temp);
            cout << endl;
            print(sortedVec);
            cout << endl;
            print(temp2);
            //cout << endl << endl;*/
            input.clear();
            
        }
        fout.close();
    }
    else{
        cout << "Error: improper argument type. Only types 'b' and 'h' are excepted";
    }
    //size_t fucking_size =input.size();
    //cout << fucking_size << endl;
    //print(input);

    return 0;
}
void sorted(vector <int>& input,int size)
{
    int y = rand() % 100;
    for (int i = 0; i < size; i++)
    {
        int z = y * i;
        input.push_back(z);
    }
}
//HERE is broken
void random(vector <int>& input, int size)
{
    for (int i = 0; i < size; i++)
    {
        int z = rand() % 60000 + (-30000);
        input.push_back(z);
    }
    
}

bool bubbleSort(vector <int>& input) //GRADING:BUBBLE
{
    size_t n = input.size();
    int i = 1;
    bool sorted = false;
    while (i <= n && sorted == false){
        sorted = true;

        for (int j = 0; j < n - 1; j++){
            if (input[j] > input[j + 1]){
                swapNum(input[j], input[j + 1]);
                sorted = false;
            }
            
        }
     }

    return sorted;
}

void heapSort(vector <int> &input) //GRADING:HEAP
{
    size_t heapSize = input.size();
    buildMaxHeap(input, heapSize);

    for (size_t i = input.size()-1; i > 0; i--){
        swapNum(input[0], input[i]);
        heapSize = heapSize - 1;
        
        maxHeapify(input, 0, heapSize);
    }

}

void buildMaxHeap(vector <int> &input, size_t heapSize)
{
    size_t length = heapSize;
    for (size_t i = (length / 2); i > 1; i--){
        maxHeapify(input, 1, heapSize);
    }
 
}

void maxHeapify(vector <int> &input, size_t i, size_t heapSize)
{
    size_t l = Left(i);
    size_t r = Right(i);
    size_t largest;
    
    if (l < heapSize && input[l] > input[i]){
        largest = l;
    }
    else{
        largest = i;
    }

    if (r < heapSize && input[r] > input[largest]){
        largest = r;
    }

    if (largest != i) {
        swapNum(input[i], input[largest]);
        maxHeapify(input, largest, heapSize);
    }

}

size_t Left(size_t i)
{
    return 2*i;
}

size_t Right(size_t i)
{
    return 2 * i + 1;
}

void swapNum(int &x, int &y)
{
    int temp;
    temp = y;
    y = x;
    x = temp;

}
//------End GRADING:HEAP--------------
void print(vector <int> input)
{
    for (vector<int>::const_iterator i = input.begin(); i != input.end(); ++i)
    {
        cout << *i << ' ';
    }
}