#include <algorithm>
#include<iostream>
#include<fstream>
using namespace std;
#define lli long long int
#define vi vector<lli>
#define pi pair<lli,lli>
int main(){
    ifstream file("input.txt");
    string line;
    while(getline(file,line)){
        cout << line << endl;
    }
}
