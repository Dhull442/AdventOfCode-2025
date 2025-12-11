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
string operator^(const string& a, const string& b){
    string out = "";
    for(int i=0;i<a.size()&&i<b.size();i++){
        if(a[i]==b[i]){
            out += '0';
        } else {
            out += '1';
        }
    }
    return out;
}
class Query{
private:
    string output;
    vector<string> buttons;
    unordered_map<string,int> dp;
    string line;
    void setoutput(){
        int enPos = line.find(']');
        int stPos = 1;
        for(int i=stPos;i<enPos;i++){
            if(line[i]=='#'){
                output = output + "1";
            } else {
                output = output + "0";
            }
        }
    }
    string parseButton(int& st, int& en){
        string button(output.size(),'0');
        for(int i=st+1;i<en;i++){
            if(line[i]>='0' && line[i]<='9'){
                button[(int)(line[i]-'0')]='1';
            }
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
    void setJoltage(){

    }
public:
    Query(string input){
        line = input;
        output = "";
        buttons = {};
        setoutput();
        setbuttons();
        setJoltage();
    }

    int minPressesforOutput(){
        dp = {{string(output.size(),'0'),0}};
        unordered_map<string,int> nextdp = {};
        for(int i=0;i<buttons.size();i++){
            nextdp.clear();
            for(auto& p: dp){
                string nextNum = p.first^buttons[i];
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
        cout << "{" << output << "}, [";
        for(string& b: buttons){
            cout << "{" << b << "}, ";
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
