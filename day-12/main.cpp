#include <algorithm>
#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;
#define lli long long int
#define vi vector<lli>
#define pi pair<lli,lli>
struct Block{
    vector<string> format;
    int setcount;
    Block(){
        format = {};
        setcount = 0;
    }
    Block(vector<string> input){
        format = input;
        setcount = 0;
        for(int i=0;i<format.size();i++){
            for(int j=0;j<format[i].size();j++){
                if(format[i][j]=='#'){
                    setcount++;
                }
            }
        }
    }
    Block rotateClock(){
        Block nxt;
        nxt.setcount = setcount;
        vector<string>& f = nxt.format;
        int m = format.size();
        int n = format.front().size();
        f = vector<string>(n, string(m,'.'));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                f[j][(m-i)-1] =  format[i][j];
            }
        }
        return nxt;
    }
    Block flipHorizontal(){
        Block nxt;
        nxt.setcount = setcount;
        vector<string>& f = nxt.format;
        int m = format.size();
        int n = format.front().size();
        f = vector<string>(m, string(n,'.'));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                f[i][(n-j)-1] =  format[i][j];
            }
        }
        return nxt;
    }
    Block flipVertical(){
        Block nxt;
        nxt.setcount = setcount;
        vector<string>& f = nxt.format;
        int m = format.size();
        int n = format.front().size();
        f = vector<string>(m, string(n,'.'));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                f[m-i-1][j] =  format[i][j];
            }
        }
        return nxt;
    }
    bool operator==(Block& other){
        if(other.format.size() == format.size()){
            if(other.format.front().size() == format.front().size()){
                for(int i=0;i<format.size();i++){
                    if(other.format[i]!=format[i]){
                        return false;
                    }
                }
                return true;
            }
        }
        return false;
    }
    void print(){
        cout << endl;
        for(int i=0;i<format.size();i++){
            cout << format[i] << endl;
        }
        cout << endl;
    }
};
class BlockBasket{
public:
    vector< vector<Block> > blocks;
    void addBlock(vector<string> block){
        Block start(block);
        vector<Block> variations = {start};
        for(int i=0;i<3;i++){
            Block rot = variations.back().rotateClock();
            bool found = false;
            for(auto& b: variations){
                if(rot==b){
                    found = true;
                    break;
                }
            }
            if(!found){
                variations.push_back(rot);
            } else {
                break;
            }
        }
        Block fstart = start.flipHorizontal();
        bool found = false;
        for(auto& b: variations){
            if(b==fstart){
                found = true;
                break;
            }
        }
        if(!found){
            variations.push_back(fstart);
            for(int i=0;i<3;i++){
                Block rot = variations.back().rotateClock();
                bool found = false;
                for(auto& b: variations){
                    if(rot==b){
                        found = true;
                        break;
                    }
                }
                if(!found){
                    variations.push_back(rot);
                } else {
                    break;
                }
            }
        }
        blocks.push_back(variations);
        cout << "ADDED " << variations.size() << " variations!" << endl;
    }
    bool canFitGrid(vector<int>& nums, int h, int w){
        int size = h*w;
        int totalset = 0;
        for(int i=0;i<nums.size();i++){
            totalset+= (nums[i]*blocks[i].front().setcount);
        }
        if(totalset<=size){
            return true;
        } else {
            return false;
        }
    }
};
ifstream file("input.txt");
int main(){
    string line;
    BlockBasket bb;
    vector<string> bblock = {};
    lli count = 0;
    while(getline(file,line)){
        if(line.find('x')!=string::npos){
            if(bblock.size()>0){
                bb.addBlock(bblock);
                bblock={};
            }
            cout << line << " >>> ";
            int xPos = line.find('x');
            int cPos = line.find(':');
            int h = stoi(line.substr(0,xPos));
            int w = stoi(line.substr(xPos+1,cPos-xPos));
            istringstream iss(line.substr(cPos+1));
            vector<int> nums;
            int numBlock;
            while(iss >> numBlock){
                nums.push_back(numBlock);
            }
            if(bb.canFitGrid(nums, h, w)){
                cout << "valid!" << endl;
                count++;
            } else {
                cout << "invalid!" << endl;
            }
        } else if(line.size()>0) {
            if(line[1]==':'){
                if(bblock.size()){
                    bb.addBlock(bblock);
                }
                bblock = {};
            } else {
                bblock.push_back(line);
            }
        }
    }
    cout << "COUNT - " << count << endl;
}
