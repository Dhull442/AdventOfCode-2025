#include <algorithm>
#include <functional>
#include<iostream>
#include<fstream>
#include<unordered_set>
#include<unordered_map>
using namespace std;
#define lli long long int
#define vi vector<lli>
#define pi pair<lli,lli>
ifstream file("input.txt");
struct Point{
    lli x,y,z;
    Point(lli x, lli y, lli z):x(x),y(y),z(z){}
    double dist(Point p){
        return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y)+(z-p.z)*(z-p.z));
    }
    bool operator<(const Point& p) const{
        return x < p.x || (x == p.x && y < p.y) || (x == p.x && y == p.y && z < p.z);
    }
};
int main(){
    string line;
    vector<Point> points;
    int limit;
    limit = 4872; // for second part;
    limit = 1000; // for first part;
    while(getline(file,line)){
        int ci = line.find(',');
        lli x = stoll(line.substr(0,ci));
        lli y = stoll(line.substr(ci+1,line.find(',',ci+1)-ci-1));
        lli z = stoll(line.substr(line.find(',',ci+1)+1));
        points.push_back(Point(x,y,z));
    }
    cout << "POINTS : " << points.size() << endl;
    sort(points.begin(),points.end());
    vector<int> grpid(1+points.size(),-1);
    unordered_map< int, vector<int> > group;
    priority_queue<pair<double,pi>,vector<pair<double,pi>>> pq;
    for(int i=0;i<points.size();i++){
        Point& pti = points[i];
        for(int j=i+1;j<points.size();j++){
            double dist = pti.dist(points[j]);
            pq.push({dist,{i,j}});
            if(pq.size()>limit){
                pq.pop();
            }
        }
    }
    cout << "PQ SIZE : " << pq.size() << endl;
    cout << "PART 2: " << points[pq.top().second.first].x * points[pq.top().second.second].x << endl;
    unordered_map< int, unordered_set<int> > adj;
    while(pq.size()>0){
        auto top = pq.top();pq.pop();
        int p1 = top.second.first;
        int p2 = top.second.second;
        if(adj.find(p1)!=adj.end()){
            adj[p1].insert(p2);
        } else {
            adj[p1] = {p2};
        }
        if(adj.find(p2)!=adj.end()){
            adj[p2].insert(p1);
        } else {
            adj[p2] = {p1};
        }
    }
    // int count = 0;
    vector<int> gpsize;
    unordered_set<int> vstd;
    for(auto& p: adj){
        if(vstd.find(p.first)==vstd.end()){
            int size = vstd.size();
            queue<int> dfs;
            dfs.push(p.first);
            vstd.insert(p.first);
            while(dfs.size()>0){
                int pt = dfs.front();dfs.pop();
                for(auto& n: adj[pt]){
                    if(vstd.find(n)==vstd.end()){
                        dfs.push(n);
                        vstd.insert(n);
                    }
                }
            }
            gpsize.push_back(vstd.size()-size);
        }
    }
    sort(gpsize.begin(),gpsize.end(), greater<>());
    cout << "GROUP " << gpsize.size() << " SIZEs - ";
    for(auto& gp: gpsize){
        cout << gp << ", ";
    }
    cout << endl;
    return 0;
}
