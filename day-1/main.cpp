#include<iostream>
#include<fstream>
using namespace std;
int main(){
    int count = 0;
    int num = 50;
    ifstream file("input.txt");
    string c;
    while(getline(file, c)){
        int rot = stoi(c.substr(1));
        if(c[0] == 'R'){
            count+= ((num+rot)/100);
            num = (num+rot)%100;
        } else{
            if(num - rot <= 0){
                count += (abs(num - rot)/100);
                if(num > 0){
                    count ++;
                }
            }
            num = (num-rot)%100;
            if(num < 0){
                num += 100;
            }
        }
        // cout << c << ": " << rot << ": " <<num << ", " <<count << endl;
    }
    cout << "COUNT - " << count << endl;
}
