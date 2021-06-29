/*
name: yasin küyük
id: 150170059
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point{
    int xCoordinate;
    int yCoordinate;
};

double distance(Point first,Point second){
    return sqrt(pow((first.xCoordinate - second.xCoordinate),2) + pow((first.yCoordinate - second.yCoordinate),2));
}

class PointSpace{
    int numberOfPoints;
    vector<Point> points;

public:
    void setNumberOfPoints(int n){
        numberOfPoints = n;
    }
    
    int getNumberOfPoints(){
        return numberOfPoints;
    }
    
    void addPoint(int x, int y){
        Point p = Point();
        p.xCoordinate = x;
        p.yCoordinate = y;
        
        points.push_back(p);
    }
    
    
    void printNumberOfPoints(){
        cout << "Total number of points: " << getNumberOfPoints() << endl;
    }
    
    void printAllPoints(){
        cout << "Points coordinates (x y): " << endl;
        
        for (std::vector<Point>::const_iterator i = points.begin(); i != points.end(); ++i){
            cout << i->xCoordinate << "\t" << i->yCoordinate << endl;
        }
    }
    
    double FindClosestPairDistance();

    pair<Point,Point> closest_pair_rec(vector<Point>,vector<Point>);

    pair<Point,Point> bruteForce(vector<Point>);
};

double PointSpace::FindClosestPairDistance(){
    vector<Point> x_sorted = points;
    vector<Point> y_sorted = points;

    sort(x_sorted.begin(), x_sorted.end(), [](const Point& first, const Point& second) {
        return first.xCoordinate < second.xCoordinate;
    });

    sort(y_sorted.begin(), y_sorted.end(), [](const Point& first, const Point& second) {
        return first.yCoordinate < second.yCoordinate;
    });

    pair<Point,Point> closest = closest_pair_rec(x_sorted,y_sorted);

    return distance(closest.first,closest.second);
}

pair<Point,Point> PointSpace::closest_pair_rec(vector<Point> sorted_X, vector<Point> sorted_Y){
    pair<Point,Point> closest;
    if(sorted_X.size() <= 3){
        closest = bruteForce(sorted_X);
        return closest;
    }
    else{
        vector<Point> q_X, r_X, q_Y, r_Y;
        int mid = sorted_X.size()/2;

        int i,j;
        for(i=0; i<mid; i++){
            q_X.push_back(sorted_X[i]);
            q_Y.push_back(sorted_Y[i]);
        }
        for(i=mid; i<sorted_X.size(); i++){
            r_X.push_back(sorted_X[i]);
            r_Y.push_back(sorted_Y[i]);
        }

        pair<Point,Point> left = closest_pair_rec(q_X,q_Y);
        pair<Point,Point> right = closest_pair_rec(r_X,r_Y);

        double sigma = min(distance(left.first,left.second),distance(right.first,right.second));
        int pointWith_x_maximum = q_X.back().xCoordinate;

        vector<Point> S;
        for(Point p:sorted_Y){
            if(abs(p.xCoordinate - pointWith_x_maximum)<=sigma){
                S.push_back(p);
            }
        }

        pair<Point,Point> temp  = bruteForce(S);

        if(distance(temp.first,temp.second) <= sigma){
            closest.first = temp.first;
            closest.second = temp.second;
        }
        else if(distance(left.first, left.second) < distance(right.first,right.second)){
            closest.first = left.first;
            closest.second = left.second;
        }
        else{
            closest.first = right.first;
            closest.second = left.second;
        }
   }
   return closest;
}

pair<Point,Point> PointSpace::bruteForce(vector<Point> p){
    double min = INFINITY;
    pair <Point,Point> closest;
    int count=0;
    for(int i=0; i<p.size(); i++){
        for(int j=i+1; j<p.size(); j++){
            if(distance(p[i],p[j]) < min && count<15){
                closest.first = p[i];
                closest.second = p[j];
                min = distance(p[i],p[j]);
            }
            count++;
        }
        count =0;
    }
    return closest;
}



int main(int argc, char* argv[]){
    //define a point space
    PointSpace pointSpace;

    //get file name
    string inputFileName = argv[1];
    
    string line;
    ifstream infile(inputFileName);

    //read the number of total points (first line)
    getline(infile, line);
    pointSpace.setNumberOfPoints(stoi(line));

    //read points' coordinates and assign each point to the space (second to last line)
    int x, y;
    while (infile >> x >> y){
       pointSpace.addPoint(x, y);
    }
    
    //print details of point space (not necessary for assignment evaluation: calico will not check this part)
    pointSpace.printAllPoints();
    pointSpace.printNumberOfPoints();
    
    //find and print the distance between closest pair of points (calico will check this part)
    double closestDistance = pointSpace.FindClosestPairDistance();
    cout << "Distance between the closest points: " << closestDistance << endl;
    
    return 0;
}



