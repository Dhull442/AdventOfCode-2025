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
    vector< vector<lli> > v,h;
    for(int i=0;i<points.size();i++){
        int j = i+1;
        if(i==points.size()-1){
            j=0;
        }
        if(points[i].f == points[j].f){
            v.push_back({points[i].f,min(points[i].s,points[j].s),max(points[i].s,points[j].s)});
        } else {
            h.push_back({points[i].s,min(points[i].f,points[j].f),max(points[i].f,points[j].f)});
        }
    }
    for(int i=0;i<points.size();i++){
        pi& pointi = points[i];
        for(int j=i+1;j < points.size();j++){
            lli xd = 1+abs(pointi.f-points[j].f);
            lli yd = 1+abs(pointi.s-points[j].s);
            lli area = xd*yd;
            if(area > maxArea){
                // verify if inside
                if(xd == 1 || yd==1){
                    maxArea = area;
                } else {
                    pi p4 = {max(pointi.f,points[j].f),max(pointi.s,points[j].s)};
                    pi p2 = {max(pointi.f,points[j].f),min(pointi.s,points[j].s)};
                    pi p3 = {min(pointi.f,points[j].f),min(pointi.s,points[j].s)};
                    pi p1 = {min(pointi.f,points[j].f),max(pointi.s,points[j].s)};
                    // cout << "CHECKING " << points[i].first << " " << points[i].second << " " << points[j].f << " " << points[j].s << endl;
                // check from x
                // p1 ---- p4
                // |       |
                // p3 ---- p2
                    lli count_up, count_down, count_p1, count_p3;
                    count_up = count_down = count_p1 = count_p3 = 0;
                    for(int k=0;k<v.size();k++){
                        if(p1.f>=v[k][0] && v[k][1]<=p1.s && v[k][2]>=p1.s){
                            count_p1++;
                        }
                        if(p1.f<v[k][0] && v[k][0]<p4.f && v[k][1]<p1.s && v[k][2]>=p1.s){
                            count_up++;
                        }
                        if(p3.f>=v[k][0] && v[k][1]<=p3.s && v[k][2]>=p3.s){
                            count_p3++;
                        }
                        if(p3.f<v[k][0] && v[k][0]<p2.f && v[k][1]<=p2.s && v[k][2]>p2.s){
                            count_down++;
                        }
                    }
                    // cout << "UP: " << count_up << ", DOWN: " << count_down << endl;
                    if(count_up==0 && count_down==0){
                        lli count_left, count_right, count_p2;
                        count_left = count_right = count_p2 = count_p3 = 0;
                        for(int k=0;k<h.size();k++){
                            if(h[k][0]<=p3.s && h[k][1]<=p3.f && h[k][2]>=p3.f){
                                count_p3++;
                            }
                            if(p3.s<h[k][0] && h[k][0]<p1.s && h[k][1]<=p1.f && h[k][2]>p1.f){
                                count_left++;
                            }
                            if(h[k][0]<=p2.s && h[k][1]<=p2.f && h[k][2]>=p2.f){
                                count_p2++;
                            }
                            if(p2.s<h[k][0] && h[k][0]<p4.s && h[k][1]<p2.f && h[k][2]>=p2.f){
                                count_right++;
                            }
                        }
                        // cout << "LEFT: " << count_left << ", RIGHT: " << count_right << endl;

                        if(count_left==0 && count_right==0){
                            maxArea = area;
                            cout << "MAXREA - "<<area << ": {" << p1.f << "," << p1.s << "}, {" << p4.f <<"," << p4.s << "}, {" << p2.f << ", " << p2.s << "}, {" << p3.f << ", " << p3.s << "}" << endl;
                        }
                    }
                    // check from y
                }
            }
        }
    }
    cout << "MAX AREA: " << maxArea <<endl;
}
