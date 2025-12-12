#include <algorithm>
#include <bitset>
#include<iostream>
#include<fstream>
#include <limits>
#include <unordered_map>
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
    vector< vector<int> > buttonidx;
    unordered_map< int, vector<int> > bitSetButtons;
    vector<int> joltage;
    string line;
    void setOutput(){
        output = "";
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
    void parseButton(int& st, int& en){
        string button(output.size(),'0');
        buttonidx.push_back({});
        for(int i=st+1;i<en;i++){
            if(line[i]>='0' && line[i]<='9'){
                int idx = (int)(line[i]-'0');
                button[idx]='1';
                buttonidx.back().push_back(idx);
                if(bitSetButtons.find(idx)==bitSetButtons.end()){
                    bitSetButtons[idx] = {};
                }
                bitSetButtons[idx].push_back(buttonidx.size());
            }
        }
        buttons.push_back(button);
    }
    void setButtons(){
        buttons = {};
        buttonidx = {};
        bitSetButtons = {};
        int stPos = 0;
        int enPos = stPos;
        while(true){
            stPos = line.find('(', stPos);
            enPos = line.find(')', stPos);
            if(stPos == string::npos || enPos == string::npos){
                break;
            } else {
                parseButton(stPos, enPos);
                stPos=enPos+1;
            }
        }
        sort(buttonidx.begin(),buttonidx.end());
    }
    void setJoltage(){
        joltage={};
        int stPos = line.find('{')+1;
        int enPos = line.find('}');
        while(true){
            int nxtPos = line.find(',',stPos);
            if(nxtPos == string::npos){
                joltage.push_back(stoi(line.substr(stPos, enPos - stPos)));
                break;
            } else {
                joltage.push_back(stoi(line.substr(stPos,nxtPos - stPos)));
                stPos = nxtPos+1;
            }
        }
    }
public:
    Query(string input){
        line = input;
        setOutput();
        setButtons();
        setJoltage();
    }

    int minPressesforOutput(){
        unordered_map<string,int> dp = {{string(output.size(),'0'),0}};
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
    string vectorToStringHash(vector<int>& input){
        string hash = "";
        for(int i=0;i<input.size();i++){

            hash += to_string(input[i]);
            if(i<input.size()-1){
                hash += "#";
            }
        }
        return hash;
    }
    bool tryPressButtonForJoltage(int& i,vector<int>& currentJoltage){
        bool pos = true;
        vector<int>& button = buttonidx[i];
        for(int bi=0;bi<button.size();bi++){
            if(currentJoltage[button[bi]]==0){
                pos=false;
                break;
            }
        }
        if(!pos){
            return pos;
        } else {
            for(int bi=0;bi<button.size();bi++){
                currentJoltage[button[bi]]--;
            }
        }
        return pos;
    }
    bool tryUnpressButtonForJoltage(int& i, vector<int>& currentJoltage){
        bool pos = true;
        vector<int>& button = buttonidx[i];
        for(int bi=0;bi<button.size();bi++){
            currentJoltage[button[bi]]++;
        }
        return pos;
    }
    int minPressesforJoltage(int ii,vector<int>& target,unordered_map<string, int>& dp){
        string hash = vectorToStringHash(target);
        if(ii >= buttonidx.size()){
            return -1;
        }
        if(dp.find(hash)!=dp.end()){
            return dp[hash];
        }
        int bpress = minPressesforJoltage(ii+1,target,dp);
        int timePressed = 0;
        while(tryPressButtonForJoltage(ii,target)){
            timePressed++;
        }
        while(timePressed){
            int presses = minPressesforJoltage(ii+1,target, dp);
            if(presses!=-1){
                if(bpress == -1){
                    bpress = 1+presses;
                } else {
                    bpress = min(bpress,presses+1);
                }
            }
            tryUnpressButtonForJoltage(ii, target);
            timePressed--;
        }
        dp[hash]=bpress;
        // cout << hash << ": " << bpress << endl;
        return dp[hash];
    }
    int minPressesforJoltage(){
        vector<int> empJoltage(joltage.size(),0);
        unordered_map< string, int > dp={{vectorToStringHash(empJoltage),0}};
        return minPressesforJoltage(0, joltage,dp);
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
        cout << line << ": " << endl;
        int val = q.minPressesforJoltage();
        cout << "VAL: " << val << endl;
        count += val;
    }
    cout << "MIN COUNT - " << count << endl;
    return 0;
}
