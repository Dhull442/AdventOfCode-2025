#include <algorithm>
#include <climits>
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
    // vector< vi > nums;
    vector< string > lines;
    vector<char> ops;
    bool opsin = false;
    lli count = 0;
    int i=0;
    while(getline(file,line)){
        char begin = line[0];
        if(begin == '*' || begin == '+'){
            istringstream iss(line);
            char op;
            while(iss>>op){
                lli val = op=='*'?1:0;
                while(true){
                    string word = "";
                    for(int li=0;li<lines.size();li++){
                        if(i<lines[li].size() &&lines[li][i]!=' '){
                            word+=lines[li][i];
                        }
                    }
                    i++;
                    if(word.size()==0){
                        break;
                    } else {
                        if(op=='*')
                            val *= stoll(word);
                        else
                            val += stoll(word);
                    }
                }
                count += val;
            }
        } else {
            lines.push_back(line);
        }
    }



    cout << "ANSWER - " << count << endl;
}
