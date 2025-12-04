#include <csetjmp>
#include<iostream>
#include<fstream>
using namespace std;
#define lli long long int
int main(){
    ifstream file("input.txt");
    string line;
    vector< string > board;
    while(getline(file, line)){
        board.push_back(line);
    }
    int totalcount = 0;
    while(true){
        int count = 0;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j]=='@'){
                    int tot = 0;
                    if(i-1 >=0){
                        if(j-1 >=0 && board[i-1][j-1]=='@'){
                            tot++;
                        }
                        if(j+1<board[i].size() && board[i-1][j+1]=='@'){
                            tot++;
                        }
                        if(board[i-1][j]=='@'){
                            tot++;
                        }
                    }
                    if(j-1 >=0 && board[i][j-1]=='@'){
                        tot++;
                    }
                    if(j+1<board[i].size() && board[i][j+1]=='@'){
                        tot++;
                    }
                    if(i+1<board.size()){
                        if(j-1 >=0 && board[i+1][j-1]=='@'){
                            tot++;
                        }
                        if(j+1<board[i].size() && board[i+1][j+1]=='@'){
                            tot++;
                        }
                        if(board[i+1][j]=='@'){
                            tot++;
                        }
                    }
                    if(tot < 4){
                        board[i][j]='.';
                        count++;
                    }
                }
            }
        }
        if(count == 0){
            break;
        }
        totalcount += count;
    }
    cout << "TOTAL = " << totalcount << endl;
}
