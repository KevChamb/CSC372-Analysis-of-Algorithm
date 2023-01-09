#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>


using namespace std;

struct ropeData {
    int diameter;
    int tensile;
    int index;
};

bool compare(ropeData x, ropeData y);
void read(ifstream& fin, vector<ropeData>& chain);
bool sortDiameter(ropeData rope1, ropeData rope2);
bool sortTensile(ropeData rope1, ropeData rope2);
void LCS(vector<ropeData>& chainD, vector<ropeData>& chainT,
    int**& cost, int**& dir);
int print(int** dir, vector<ropeData> chainD, int x, int y);
void random(vector<ropeData>& input, int size);