#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <set>
#include <iterator>
#include <chrono>

using namespace std;
/*
struct SL {
    double x;
    double y;
    bool left; //1=left, 0=right
    int id;

    SL(double x, double y, bool left, int id) : x(x), y(y), left(left), id(id) {}

    bool operator < (const point& next) const {

        if (y == next.y) {
            return x < next.x;
        }
        else {
            return y < next.y;
        }
    }

};
*/

struct point {
    double x;
    double y;
    bool left; //1=left, 0=right
    int id;
    
    //point con(double x, double y, bool left, int id) : x(x), y(y), left(left), id(id) {}
    
    bool operator < (const point& next) const {

        if (y == next.y) {
            return x < next.x;
        }
        else {
            return y > next.y;
        }
    }
    
};

struct line {
    point pt1;
    point pt2;
    int id;
    
    
    

};

int readFile(fstream& fin, point& pt, line& lin, vector<point>& points,
    vector<line>& segments);
multiset<point>::iterator below(multiset<point>& rbt, multiset<point>::iterator it);
multiset<point>::iterator above(multiset<point>& rbt, multiset<point>::iterator it);
int ASI(vector<point> points, vector<line> segments);
bool segIntersect(point pt1, point pt2, point pt3, point pt4);
bool onSeg(point pt1, point pt2, point pt3);
int dir(point pt1, point pt2, point pt3);
bool compareX(point pt1, point& pt2);
bool sortComp(point pt1, point pt2);
void timetest(fstream& fout);
