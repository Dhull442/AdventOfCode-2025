#include <algorithm>
#include <bitset>
#include<iostream>
#include<fstream>
#include <limits>
using namespace std;
#define lli long long int
#define vi vector<lli>
#define pi pair<lli,lli>
ifstream file("input.txt");
class Query{
private:
    int output;
    int outputsize;
    vector<int> buttons;
    // vector<int> dp;
    unordered_map<int,int> dp;
    string line;
    void setoutput(){
        output = 0;
        int enPos = line.find(']');
        int stPos = 1;
        for(int i=stPos;i<enPos;i++){
            output = output << 1;
            if(line[i]=='#'){
                output += 1;
            }
        }
        outputsize = enPos - stPos;
    }
    int parseButton(int& st, int& en){
        int button = 0;
        vector<int> idx;
        for(int i=st+1;i<en;i++){
            if(line[i]>='0' && line[i]<='9'){
                idx.push_back((int)(line[i]-'0'));
            }
        }
        sort(idx.begin(),idx.end());
        int bsize = 0;
        for(int i=0;i<idx.size();i++){
            while(bsize<=idx[i]){
                if(button == 0){
                    bsize = idx[i]+1;
                    break;
                }
                button = button << 1;
                bsize++;
            }
            button += 1;
        }
        while(bsize<outputsize){
            button = button << 1;
            bsize++;
        }
        return button;
    }
    void setbuttons(){
        string bline = line;
        int stPos = 0;
        int enPos = stPos;
        while(true){
            stPos = bline.find('(', stPos);
            enPos = bline.find(')', stPos);
            if(stPos == string::npos || enPos == string::npos){
                break;
            } else {
                buttons.push_back(parseButton(stPos, enPos));
                stPos=enPos+1;
            }
        }
    }
public:
    Query(string input){
        line = input;
        output = 0;
        buttons = {};
        setoutput();
        setbuttons();
    }
    int minPressesforOutput(){
        dp = {{0,0}};
        unordered_map<int,int> nextdp = {};
        for(int i=0;i<buttons.size();i++){
            nextdp.clear();
            for(auto& p: dp){
                int nextNum = p.first^buttons[i];
                if(dp.find(nextNum)==dp.end() || dp[nextNum]>p.second+1){
                    nextdp.insert({nextNum,p.second+1});
                }
            }
            for(auto p: nextdp){
                dp[p.first] = p.second;
            }
        }
        return dp[output];
    }
    void print(){
        const int num_bits = 10;
        cout << line << endl;
        cout << "{" << bitset<num_bits>(output).to_string() << "}, [";
        for(int& b: buttons){
            cout << "{" << bitset<num_bits>(b).to_string() << "}, ";
        }
        cout << "] " << endl;
    }
};
int main(){
    string line;
    int count = 0;
    while(getline(file,line)){
        Query q(line);
        int val = q.minPressesforOutput();
        cout << line << ": " << val << endl;
        count += val;
    }
    cout << "MIN COUNT - " << count << endl;
    return 0;
}
