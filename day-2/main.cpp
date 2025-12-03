#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
#define lli long long int
#define pii pair<lli,lli>
#define pss pair<string,string>
#define vpii vector<pii>
pair<string,string> split(string range){
    auto it = range.find('-');
    return {range.substr(0,it),range.substr(it+1)};
}
vector<pss> tokenize(string line){
    vector<pss> ranges;
    while(line.size()>0){
        auto it = line.find(',');
        if(it == string::npos){
            pss range = split(line);
            ranges.push_back(range);
            break;
        } else {
            ranges.push_back(split(line.substr(0, it)));
            line = line.substr(it+1);
        }
    }
    return ranges;
}
long long int countInvalid(pss& range){
    if(range.first.size() == range.second.size() && range.first.size()%2 == 1){
        return 0;
    }
    lli f = stoll(range.first);
    lli xlen = (range.first.size()+1)/2;
    if(range.first.size()%2==1){
        f = (lli)pow(10, range.first.size());
    }
    lli s = stoll(range.second);
    if(range.second.size()%2==1){
        s = (lli)pow(10, range.second.size()-1)-1;
    }
    lli sum = 0;
    lli x = (lli)pow(10, xlen);
    cout << x << endl;
    while(f <= s){
        if(f/x == f%x){
            sum += f;
        }
        f++;
    }
    return sum;
}
int main(){
    ifstream file("input.txt");
    string line;
    file >> line;
    long long int count = 0;
    vector<pss> ranges = tokenize(line);
    for(pss& r: ranges){
        cout << "{ " << r.first << " - " << r.second << " }: ";
        lli sum = countInvalid(r);
        cout << sum << endl;
        count += sum;
    }
    cout << "COUNT - " << count << endl;
}
