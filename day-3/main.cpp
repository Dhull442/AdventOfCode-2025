#include<iostream>
#include<fstream>
using namespace std;
#define lli long long int
lli maxJoltage(string line, int len){
    string out = line.substr(line.size()-len);
    for(int i=line.size()-(len+1);i>=0;i--){
        char carry = line[i];
        for(int j=0;j<out.size();j++){
            if(out[j]<=carry){
                char newcarry = out[j];
                out[j] = carry;
                carry = newcarry;
            } else {
                break;
            }
        }
    }
    cout << out << ", ";
    return stoll(out);
}
int main(){
    lli count = 0;
    ifstream file("input.txt");
    string line;
    while(file >> line){
        count += maxJoltage(line, 12);
    }
    cout << "MAX JOLTAGE - " << count << endl;
}
