#include<iostream>
#include<fstream>
using namespace std;
#define lli long long int
int maxJoltage(string line){
    string out = line.substr(line.size()-2);
    for(int i=line.size()-3;i>=0;i--){
        if(line[i]>=out[0]){
            if(out[0]>=out[1]){
                out[1] = out[0];
                out[0] = line[i];
            } else {
                out[0] = line[i];
            }
        }
    }
    cout << out << ", ";
    return stoi(out);
}
int main(){
    lli count = 0;
    ifstream file("input.txt");
    string line;
    while(file >> line){
        count += maxJoltage(line);
    }
    cout << "MAX JOLTAGE - " << count << endl;
}
