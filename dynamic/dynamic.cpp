#include "dynamic.h"

int main(int argc,char **argv) 
{
    ifstream fin;
    fstream fout;
    vector<ropeData> chainD; //vector sorted by Diameter
    vector<ropeData> chainT; //vector sorted by Tensile
    vector<ropeData> chainR;
    int x = 0, y = 0;
    //char dir[1000][1000];//vector<vector<char>> dir;
    //vector<vector<int>> cost;

    
    if (argc == 3) {

        int size = 1;
        fout.open("Times.csv", ios::out | ios::app);
        for (int w = 1; w < 101; w++) {
            
            chainR.clear();
            
            random(chainR, size++);
            vector<ropeData> chainRT = chainR;

            auto startR = chrono::steady_clock::now();
            sort(chainR.begin(), chainR.end(), sortDiameter); //sort by diameter
            sort(chainRT.begin(), chainRT.end(), sortTensile);  //sort by tensile strength

            int arrSize = chainR.size();
            int** dir = new int* [(int)arrSize];
            int** cost = new int* [(int)arrSize];

            for (int i = 0; i < arrSize; i++) {
                dir[i] = new int[arrSize];
            }

            for (int i = 0; i < arrSize; i++) {
                cost[i] = new int[arrSize];
            }

            for (int i = 0; i < arrSize - 1; i++) {
                for (int j = 0; j < arrSize - 1; j++) {
                    dir[i][j] = 0;
                }
            }

            LCS(chainR, chainRT, cost, dir);

            x = chainD.size() - 1;
            y = x;

            //cout << cost[chainD.size() - 1][chainD.size() - 1] << endl;
            //print(dir, chainD, x, y);
 
     
            auto endR = chrono::steady_clock::now();
            size_t timeR = chrono::duration_cast<chrono::nanoseconds>(endR - startR).count();

            fout << w << "," << timeR << endl;

            for (int i = 0; i < arrSize; i++) {
                delete dir[i];
                //    world[i] = 0;  // <- don't have to do this
            }
            delete dir;  // <- because they won't exist anymore after this
            dir = 0;

            for (int i = 0; i < arrSize; i++) {
                delete cost[i];
                //    world[i] = 0;  // <- don't have to do this
            }
            delete cost;  // <- because they won't exist anymore after this
            cost = 0;
            
        }
        
        fout.close();
        return 0;
    }
    
    //------------Read----------------------------------
    fin.open(argv[1]);
   
    if (!fin.is_open())
    {
        cout << "Unable to open input file: " << argv[1];
    }
    
    read(fin, chainD);
    fin.close();

    chainD.erase(unique(chainD.begin(),chainD.end(),compare),chainD.end());

    chainT = chainD;
    //-----------Sort-----------------------------------

    sort(chainD.begin(), chainD.end(), sortDiameter); //sort by diameter
    sort(chainT.begin(), chainT.end(), sortTensile);  //sort by tensile strength

    
    int arrSize = chainD.size();
    int** dir = new int *[arrSize];
    int** cost = new int* [arrSize];

    for (int i = 0; i < arrSize; i++) {
        dir[i] = new int[arrSize];
    }

    for (int i = 0; i < arrSize; i++) {
        cost[i] = new int[arrSize];
    }

    for (int i = 0; i < arrSize - 1; i++) {
        for (int j = 0; j < arrSize - 1; j++) {
            dir[i][j] = 0;
        }
    }

    LCS(chainD, chainT, cost, dir);

    x = chainD.size()-1; 
    y = x;

    cout << cost[chainD.size() - 1][chainD.size() - 1]<<endl;
    print( dir, chainD, x, y);

    for (int i = 0; i < arrSize; i++) {
        delete dir[i];
        
    }
    delete dir;
    dir = 0;

    for (int i = 0; i < arrSize; i++) {
        delete cost[i];
        
    }
    delete cost;
    cost = 0;
    return 0;
}

void read(ifstream& fin, vector<ropeData>& chain) {
    ropeData data;
    data.diameter = 0;
    data.tensile = 0;
    data.index = 0;
    chain.push_back(data);

    while (fin >> data.diameter)
    {
        //fin.ignore();
        data.index  += 1;
        fin >> data.tensile;
        chain.push_back(data);
    }
}

bool sortDiameter(ropeData rope1, ropeData rope2)
{
    if (rope1.diameter == rope2.diameter) {
        return rope1.tensile > rope2.tensile;
    }
    return rope1.diameter < rope2.diameter;
}

bool sortTensile(ropeData rope1, ropeData rope2)
{
    if (rope1.tensile == rope2.tensile)
    {
        return rope1.diameter > rope2.diameter;
    }
    return rope1.tensile < rope2.tensile;
}

//GRADING:REUSE
//GRADING:UPDATE
void LCS(vector<ropeData>& chainD, vector<ropeData>& chainT,
     int**& cost, int**&dir) { // vector<vector<int>>& cost, vector<vector<char>>& dir
    //char symbol;
    //vector<int> temp3;

    for (int x = 1; x < (int)chainT.size(); x++) { //chainD is A for alg            
        //temp3.push_back(0);
        cost[x][0] = 0;
    }
    //cost.push_back(temp3);

    for (int y = 0; y < (int)chainD.size(); y++) { //chainT is B for alg
        //cost.push_back(temp3);
        cost[0][y] = 0;
    }

    for (int x = 1; x < (int)chainD.size(); x++) {
       // vector<int> temp; //temp array 
        //vector<char> temp2;
        //int value;

        for (int y = 1; y < (int)chainT.size(); y++) {
            
            if (chainD[x].diameter == chainT[y].diameter && 
                chainD[x].tensile == chainT[y].tensile) {

                cost[x][y] = cost[x - 1][y - 1] + 1;
                dir[x][y] = 3; //dia
                //value = cost[x - 1][y - 1] + 1;
                //cost[x][y] = cost[x - 1][y - 1] + 1; //pushback
                //temp.push_back(value);
                //symbol = char("d"); //diagonal arrow
                //temp2.push_back(symbol);
                //dir[x][y] = symbol;   //pushback
            }
            else if (cost[x - 1][y] >= cost[x][y - 1]) {

                cost[x][y] = cost[x - 1][y];
                dir[x][y] = 1; //up
                //value = cost[x - 1][y];
                //cost[x][y] = cost[x - 1][y]; //pushback
                //temp.push_back(value);
                //symbol = char("^"); //up arrow
                //temp2.push_back(symbol);
                //dir[x][y] = symbol;//pushback
            }
            else {
                //value = cost[x][y - 1];
                cost[x][y] = cost[x][y - 1];//pushback
                //temp.push_back(value);
                //symbol = 2; //left arrow
                //temp2.push_back(symbol);
                dir[x][y] = 2;//pushback
            }
        }
        //cost.push_back(temp);
        //dir.push_back(temp2);
    }
}

int print(int** dir, vector<ropeData> chainD, int x, int y) {
    //char dia = char("d"); //diagonal arrow
    //char up = char("^"); //up arrow
    //char left = char("<"); //left arrow
    
    
    if (x == 0 || y == 0) {
        return 0;
    }
    if (dir[x][y] == 3) {
        print(dir, chainD, x - 1, y - 1);
        cout <<chainD[x].index <<" -> "<< chainD[x].diameter << " : " << chainD[x].tensile << endl;
    }
    else if (dir[x][y] == 1) {
        print(dir, chainD, x-1, y);
    }
    else {
        print(dir, chainD, x, y-1);
    }
}

void random(vector<ropeData>& input, int size)
{
    ropeData data;
    
    for (int i = 0; i < size; i++)
    {
        int z = 1+ rand() % 10000;
        data.diameter = z;
        int w = 1 + rand() % 10000;
        data.tensile = w;
        input.push_back(data);
    }

}

bool compare(ropeData x, ropeData y) 
{
    
    if (x.tensile == y.tensile && x.diameter == y.diameter) {
        return true;
    }
    else {
        return false;
    }
}