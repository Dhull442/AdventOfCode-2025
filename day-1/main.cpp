#include<iostream>
#include<fstream>
using namespace std;
int main(){
    int count = 0;
    int num = 50;
    ifstream file("input.txt");
    string c;
    while(getline(file, c)){
        if(c[0] == 'R'){
            num += stoi(c.substr(1));
        } else{
            num -= stoi(c.substr(1));
        }
        num = num % 100;
        if(num < 0){
            num += 100;
        }
        if(num == 0){
            count++;
        }
    }
    cout << "COUNT - " << count << endl;
}
