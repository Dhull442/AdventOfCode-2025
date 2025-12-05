#include<iostream>
#include<fstream>
using namespace std;
#define lli long long int
int main(){
    ifstream file("input.txt");
    string line;
    vector<pair<lli,lli>> ranges;
    bool rangeInput = true;
    int count = 0;
    while(getline(file, line)){
        if(line.size()==0){
            rangeInput=false;
            sort(ranges.begin(), ranges.end());
            continue;
        }
        if(rangeInput){
            auto dashPos = line.find('-');
            lli start = stoll(line.substr(0, dashPos));
            lli end = stoll(line.substr(dashPos+1));
            ranges.push_back({start, end});
        } else {
            lli ing = stoll(line);
            // check code
            for(int i=0;i<ranges.size();i++){
                if(ranges[i].first <= ing && ing <= ranges[i].second){
                    count++;
                    break;
                }
            }
        }
    }
    cout << "FRESH - " << count << endl;
}
