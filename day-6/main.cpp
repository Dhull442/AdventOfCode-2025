#include <algorithm>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
#define lli long long int
#define vi vector<lli>
#define pi pair<lli,lli>
int main(){
    ifstream file("input.txt");
    string line;
    // vector< vector<string> > nums;
    vector< vi > nums;
    // vector<char> ops;
    bool opsin = false;
    lli count = 0;
    while(getline(file,line)){
        int i=0;
        istringstream iss(line);
        string word;
        char begin = line[0];
        if(begin == '*' || begin == '+'){
            opsin = true;
        }
        while(iss >> word){
            if(opsin){
                lli val=0;
                if(word[0]=='*'){
                    val = 1;
                    for(lli num: nums[i]){
                        val*=num;
                    }
                } else {
                    val = 0;
                    for(lli num: nums[i]){
                        val+=num;
                    }
                }
                count+=val;
            } else {
                if(i<nums.size()){
                    nums[i].push_back(stoll(word));
                } else {
                    nums.push_back({stoll(word)});
                }
            }
            i++;
        }
    }
    cout << "ANSWER - " << count << endl;
}
