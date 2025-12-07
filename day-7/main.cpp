#include <algorithm>
#include<iostream>
#include<fstream>
using namespace std;
#define lli long long int
#define vi vector<lli>
#define pi pair<lli,lli>
int main(){
    ifstream file("input.txt");
    string line;
    int m =0, n=0;
    vector<string> lines;
    while(getline(file,line)){
        lines.push_back(line);
    }
    m = lines.size();
    n = lines.front().size();
    queue< pi > pts;
    vector< vi > ways(m, vi(n,0));
    for(int i=0;i<lines[0].size();i++){
        if(lines[0][i]=='S'){
            pts.push({0,i});
            ways[0][i]=1;
        }
    }
    lli totalways = 0;
    while(pts.size()>0){
        pi pt = pts.front(); pts.pop();
        lli way = ways[pt.first][pt.second];
        if(pt.first+1 < lines.size()){
            char& nxt = lines[pt.first+1][pt.second];
            if(nxt == '^'){
                if(pt.second>0){
                    pi nxtpt = {pt.first+1,pt.second-1};
                    if(lines[nxtpt.first][nxtpt.second]!='|'){
                        lines[nxtpt.first][nxtpt.second] = '|';
                        pts.push(nxtpt);
                    }
                    ways[nxtpt.first][nxtpt.second]+=way;
                }
                if(pt.second+1<lines[pt.first+1].size()){
                    pi nxtpt = {pt.first+1,pt.second+1};
                    if(lines[nxtpt.first][nxtpt.second]!='|'){
                        lines[nxtpt.first][nxtpt.second] = '|';
                        pts.push(nxtpt);
                    }
                    ways[nxtpt.first][nxtpt.second]+=way;
                }
            } else {
                if(nxt=='.'){

                    nxt = '|';
                    pts.push({pt.first+1,pt.second});
                }
                ways[pt.first+1][pt.second] += way;
            }
        } else {
            totalways+=way;
        }
    }
    // lli count = 0;
    // for(int i=1;i<lines.size();i++){
    //     cout << lines[i] << endl;
    //     for(int j=0;j<lines[i].size();j++){
    //         if(lines[i][j]=='^' && lines[i-1][j]=='|'){
    //             count++;
    //         }
    //     }
    // }
    // cout << "ACTIVATED - " << count << endl;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(lines[i][j]=='.'){
                cout << "   ";
            } else {
                cout << ways[i][j] << "" << lines[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << "TOTAL WAYS - " << totalways << endl;
}
