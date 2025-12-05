#include <algorithm>
#include<iostream>
#include<fstream>
using namespace std;
#define lli long long int
vector<pair<lli,lli>> merge(vector<pair<lli,lli>>& ints) {
      if(ints.size()==1)
         return ints;
      vector< pair<lli,lli> > ans;
      lli f=ints.front().first,s=ints.front().second;
      for(int i=0;i<ints.size()-1;i++)
      {
          pair<lli,lli> a;
          if(s>=ints[i+1].first)
          {
              s=max(s,ints[i+1].second);
          }
          else
          {
              a.first=f;
              a.second=s;
              f=ints[i+1].first;
              s=ints[i+1].second;
              ans.push_back(a);
          }
      }
      int n=ints.size();
      ans.push_back({f,s});
      return ans;
}
int main(){
    ifstream file("input.txt");
    string line;
    vector<pair<lli,lli>> ranges;
    bool rangeInput = true;
    lli count = 0;
    while(getline(file, line)){
        if(line.size()==0){
            rangeInput=false;
            sort(ranges.begin(), ranges.end());
            break;
        }
        if(rangeInput){
            auto dashPos = line.find('-');
            lli start = stoll(line.substr(0, dashPos));
            lli end = stoll(line.substr(dashPos+1));
            ranges.push_back({start, end});
        }
    }
    vector<pair<lli,lli>> mergedRanges = merge(ranges);
    for(int i=0;i<mergedRanges.size();i++){
        count += (mergedRanges[i].second - mergedRanges[i].first + 1);
    }
    cout << "FRESH - " << count << endl;
}
