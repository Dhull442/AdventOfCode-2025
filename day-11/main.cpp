#include <algorithm>
#include <queue>
#include <unordered_map>
#include<unordered_set>
#include<iostream>
#include<fstream>
using namespace std;
#define lli long long int
#define vi vector<lli>
#define pi pair<lli,lli>
ifstream file("input.txt");
class Graph{
private:
    unordered_set<string> nodes;
    unordered_map< string, vector<string> > edges;
    unordered_map< string, int> indegrees;
    void build(){
        nodes = {};
        edges={};
        indegrees = {};
    }
public:
    Graph(){
        nodes = {};
        edges={};
    }
    void addEdge(string fromNode, string toNode){
        // cout << "ADDING " << fromNode << " -> " << toNode << endl;
        if(edges.find(fromNode)!=edges.end()){
            edges[fromNode].push_back(toNode);
        } else {
            edges[fromNode] = {toNode};
        }
        if(indegrees.find(fromNode)==indegrees.end()){
            indegrees[fromNode]=0;
        }
        indegrees[toNode] = indegrees[toNode]+1;
    }
    void addEdges(string line){
        string par = line.substr(0,3);
        nodes.insert(par);
        int stPos = 5;
        while(stPos+3 <= line.size()){
            addEdge(par,line.substr(stPos,3));
            stPos+=4;
        }
    }
    lli computeWays(string fromNode, string toNode){
        unordered_map<string,lli> ways;
        unordered_map<string, int> idg = indegrees;
        queue<string> nxt;
        for(auto& p: indegrees){
            if(p.second == 0){
                nxt.push(p.first);
                ways[p.first] = 0;
            }
        }
        if(ways.find(fromNode)==ways.end()){
            nxt.push(fromNode);
        }
        ways[fromNode]=1;
        lli count = 0;
        while(nxt.size()>0){
            string node = nxt.front();nxt.pop();
            cout << node << ": " << ways[node] << endl;
            count++;
            if(node == toNode){
                break;
            }
            for(string& child: edges[node]){
                ways[child]=ways[child]+ways[node];
                idg[child]--;
                if(idg[child]==0){
                    if(child == fromNode){
                        continue;
                    }
                    nxt.push(child);
                }
            }
        }
        cout << indegrees.size() << " " << ways.size() << " " << count<< endl;
        return ways[toNode];
    }
};
int main(){
    string line;
    Graph graph;
    while(getline(file,line)){
        graph.addEdges(line);
    }
    // lli svr2dac = graph.computeWays("svr","dac");
    lli svr2fft = graph.computeWays("svr","fft");
    // lli fft2out = graph.computeWays("fft","out");
    lli dac2out = graph.computeWays("dac","out");
    lli fft2dac = graph.computeWays("fft","dac");
    // lli dac2fft = graph.computeWays("dac","fft");
    // cout << "SVR -> DAC: " << svr2dac << endl;
    cout << "SVR -> FFT: " << svr2fft << endl;
    // cout << "FFT -> OUT: " << fft2out << endl;
    cout << "DAC -> OUT: " << dac2out << endl;
    cout << "FFT -> DAC: " << fft2dac << endl;
    // cout << "DAC -> FFT: " << dac2fft << endl;
    cout << svr2fft * fft2dac * dac2out << endl;

}
