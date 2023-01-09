/*
Kevin Chamberlain
CSC372
Project 2
*/
#include "dynamic.h"

int main(int argc, char* argv[])
{
    fstream fin;
    fstream fout;
    point pt;
    line lin;
    int count = 0;

    vector<point> points;
    vector<line> segments; //polies for Full, segments for B
    string fileName = argv[1];
    fin.open(fileName);


    if (!fin.is_open()) {
        cout << "Unable to open file: " << argv[1];
        return -1;
    }
    else { //For degbugging Make sure to remove before submission
        cout << "Successfully opened file: " << argv[1] << endl;
    }


    readFile(fin, pt, lin, points, segments);
    sort(points.begin(), points.end(), compareX);
    count = ASI(points, segments);
    cout << count;
    timetest(fout);

    fin.close();
    return 0;
}

int readFile(fstream& fin, point& pt, line& lin, vector<point>& points,
    vector<line>& segments) {
    int i = 0; //for setting id

    while (!fin.eof()) {

        fin >> pt.x >> pt.y; //Read in x,y coordinates for a point

        char x = fin.peek(); //check to see it next entry is a point

        if (x == '\n' || x == EOF) {

            lin.pt2 = pt;
            lin.pt2.id = i;

            if (lin.pt1.x < lin.pt2.x) {
                lin.pt1.left = 1; //sets bool as left
                lin.pt2.left = 0; //sets bool as right
            }
            else {
                lin.pt1.left = 0; //sets bool as right
                lin.pt2.left = 1; //sets bool as left
            }
            lin.id = i;

            segments.push_back(lin);
            points.push_back(lin.pt1);
            points.push_back(lin.pt2);
            i++;

        }
        else {
            lin.pt1 = pt;
            lin.pt1.id = i;
        }

    }
    return 1;
}

bool sortComp(point pt1, point pt2) {
    if (pt1.y == pt2.y) {
        return pt1.x < pt2.x;
    }

    return pt1.y < pt2.y;
}

bool compareX(point pt1, point& pt2)
{
  
    if (pt1.x == pt2.x) {
        return pt1.y < pt2.y;
    }

    return pt1.x < pt2.x;
}

//from slides
int dir(point pt1, point pt2, point pt3) {

    double ret = (((pt3.x - pt1.x) * (pt2.y - pt1.y)) - ((pt2.x - pt1.x) * (pt3.y - pt1.y)));

    if (ret == 0) {
        return 0;
    }

    return (ret > 0) ? 1 : 2; //True return 1 else 2

}

//from slides
bool onSeg(point pt1, point pt2, point pt3) {
    if (min(pt1.x, pt2.x) <= pt3.x && pt3.x <= max(pt1.x, pt2.x)) {
        if (min(pt1.y, pt2.y) <= pt3.y && pt3.y <= max(pt1.y, pt2.y)) {
            return true;
        }
    }

    return false;
}

bool segIntersect(point pt1, point pt2, point pt3, point pt4) {

    int d1 = dir(pt3, pt4, pt1);
    int d2 = dir(pt3, pt4, pt2);
    int d3 = dir(pt1, pt2, pt3);
    int d4 = dir(pt1, pt2, pt4);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 >0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4>0))) {
        return true;
    }
    else if (d1 == 0 && onSeg(pt3, pt4, pt1)) { return true; }
    else if (d2 == 0 && onSeg(pt3, pt4, pt2)) { return true; }
    else if (d3 == 0 && onSeg(pt1, pt2, pt3)) { return true; }
    else if (d4 == 0 && onSeg(pt1, pt2, pt4)) { return true; }
    else { return false; }

}

int ASI(vector<point> points, vector<line> segments) {

    multiset<point> rbt;
    int count = 0;
    int i = 0;
    point curr1;
    point curr2;
    point below1;
    point below2;
    point above1;
    point above2;

    for (int j = 0; j < points.size(); j++) {

        if (points.size() == 2) {
            break;
        }
        //GRADING : SWEEP
        curr1 = segments[points[j].id].pt1;
        curr2 = segments[points[j].id].pt2;

        if (j != points.size() - 1) {
            below1 = segments[points[j + 1].id].pt1;
            below2 = segments[points[j + 1].id].pt2;
        }


        if (j >= 1) {
            above1 = segments[points[j - 1].id].pt1;
            above2 = segments[points[j - 1].id].pt2;
        }

        if (points[j].left == 1) {

            //GRADING: ACTIVE
            rbt.insert(points[j]);
            auto curr = rbt.lower_bound(points[j]);
            auto prev = above(rbt, curr);
            auto next = rbt.upper_bound(points[j]);
            

            //GRADING: INTERSECT
            //GRADING : CHECK
            if (prev != rbt.end() && segIntersect(above1, above2, curr1, curr2)) 
            {
                count++;
            }//GRADING : CHECK
            else if (next != rbt.end() && segIntersect(below1, below2, curr1, curr2))
            {
                count++;
            }

        }
        else {

            //This will get input over, just here to make compiler happy
            auto curr = rbt.lower_bound(segments[points[j].id].pt1);
            auto prev = above(rbt, curr);
            auto next = rbt.upper_bound(segments[points[j].id].pt1);

            if (segments[points[j].id].pt1.left == 1) {
                auto curr = rbt.lower_bound(segments[points[j].id].pt1);
                auto prev = above(rbt, curr);
                auto next = rbt.upper_bound(segments[points[j].id].pt1);
                //auto it = rbt.find(segments[points[j].id].pt1);
            }
            else
            {
                auto curr = rbt.lower_bound(segments[points[j].id].pt2);
                auto prev = above(rbt, curr);
                auto next = rbt.upper_bound(segments[points[j].id].pt2);
                //auto it = rbt.find(segments[points[j].id].pt2);
            }



            if (prev != rbt.end() && next != rbt.end())//both above and below exist && above intersects below
            {//GRADING : CHECK
                if (segIntersect(above1, above2, below1, below2)) {
                    count++;
                }

            }

            if (segments[points[j].id].pt1.x == segments[points[j].id].pt2.x) {
                for (point r : rbt)
                {
                    //GRADING : CHECK
                    if (segIntersect(segments[r.id].pt1, segments[r.id].pt2, segments[points[j].id].pt1, segments[points[j].id].pt2)) {
                        count++;
                    }
                }
            }
            //GRADING : INACTIVE
            rbt.erase(points[j]);
        }


    }


    return count;
}

multiset<point>::iterator above(multiset<point>& rbt, multiset<point>::iterator it) {
    return it == rbt.begin() ? rbt.end() : --it;
}

multiset<point>::iterator below(multiset<point>& rbt, multiset<point>::iterator it) {
    return it++;
}

//------------------ Algorithm testing
void random(vector <point>& points, int size, line& lin, vector<line>& segments)
{
    point pt;
    point pt2;
    line ln;
    int id = 0;

    //int x = rand() % 100;
    for (int i = 0; i < size + 1; i++)
    {
        pt.x = rand() % 100;
        pt.y = rand() % 100;
        pt2.x = rand() % 100;
        pt2.y = rand() % 100;
        if (pt.x < pt2.x) {
            pt.left = 1;
            pt2.left = 0;
        }
        else {
            pt.left = 0;
            pt2.left = 1;
        }

        pt.id = id;
        pt2.id = id;
        ln.pt1 = pt;
        ln.pt2 = pt2;
        ln.id = id;
        segments.push_back(ln);
        points.push_back(pt);
        points.push_back(pt2);
    }

}

//int readFile(fstream& fin, point& pt, line& lin, vector<point>& points,
//    vector<line>& segments)
void timetest(fstream& fout)
{
    fout.open("Times.csv", ios::out | ios::app);
    line lin;
    vector <point> points;
    vector<line> segments;

    for (int j = 1; j < 100; j++) {

        //unsigned int time_ui = static_cast<unsigned int>(time(NULL));
        random(points, j, lin, segments);
        sort(points.begin(), points.end(), compareX);

        //Sorted
        auto start = chrono::steady_clock::now();
        ASI(points, segments);
        auto end = chrono::steady_clock::now();

        size_t time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        fout << j << "," << time << endl;


        points.clear();
        segments.clear();

    }
    fout.close();
}