#include <algorithm>
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
        cout << "ADDING " << fromNode << " -> " << toNode << endl;
        if(edges.find(fromNode)!=edges.end()){
            edges[fromNode].push_back(toNode);
        } else {
            edges[fromNode] = {toNode};
        }
        indegrees[toNode] = indegrees[toNode]+1;
    }
    void addEdges(string line){
        cout << "PROCESSING " << line << endl;
        string par = line.substr(0,3);
        nodes.insert(par);
        int stPos = 5;
        while(stPos+3 <= line.size()){
            addEdge(par,line.substr(stPos,3));
            stPos+=4;
        }
    }
    int computeWays(string fromNode, string toNode){
        // unordered_map<string,int> ways = {{fromNode,1}};
        int ways = 0;
        // unordered_map<string, int> idg = indegrees;
        queue< string > nxt;
        nxt.push(fromNode);
        while(nxt.size()>0){
            string node = nxt.front();nxt.pop();
            for(string& child: edges[node]){
                if(child == toNode){
                    ways++;
                } else {
                    nxt.push(child);
                }
            }
        }
        return ways;
    }
};
int main(){
    string line;
    Graph graph;
    while(getline(file,line)){
        graph.addEdges(line);
    }
    cout << "WAYS - " << graph.computeWays("you","out") << endl;
}
