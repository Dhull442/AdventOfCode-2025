#include <algorithm>
#include<iostream>
#include<fstream>
using namespace std;
#define lli long long int
#define vi vector<lli>
#define pi pair<lli,lli>
#define f first
#define s second
ifstream file("input.txt");
int main(){
    vector< pi > points;
    lli maxArea = 0;
    string line;
    while(getline(file,line)){
        int ci = line.find(',');
        points.push_back({stoll(line.substr(0,ci)),stoll(line.substr(ci+1))});
        // cout << line << endl;
    }
    // sort(points.begin(),points.end());
    for(int i=0;i<points.size();i++){
        pi& pointi = points[i];
        for(int j=i+2;j<i+4 && j < points.size();j++){
            lli xd = 1+abs(pointi.f-points[j].f);
            lli yd = 1+abs(pointi.s-points[j].s);
            lli area = xd*yd;
            maxArea = max(maxArea,area);
        }
    }
    cout << "MAX AREA: " << maxArea <<endl;
}
