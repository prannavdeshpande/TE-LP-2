#include<iostream>
#include<vector>
using namespace std;

vector<vector<char>>grid;

void nQueen(int row,vector<bool>cols,vector<bool>ndiag,vector<bool>rdiag,int n){
    if(row == n){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<grid[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    for(int col = 0;col<n;col++){
        if(cols[col]==false && ndiag[row+col]==false && rdiag[row-col+n-1]==false){
            grid[row][col] = 'Q';
            cols[col]=true;
            ndiag[row+col] = true;
            rdiag[row-col+n-1] = true;

            nQueen(row+1,cols,ndiag,rdiag,n);

            grid[row][col] = '.';
            cols[col]=false;
            ndiag[row+col] = false;
            rdiag[row-col+n-1] = false;
        }
    }
}

int main(){
    int n;
    cout<<"Enter the size of chess board : ";
    cin>>n;
    grid.clear();
    grid.resize(n,vector<char>(n,'.'));
    vector<bool>cols(n,0);
    vector<bool>ndiag(2*n-1,0);
    vector<bool>rdiag(2*n-1,0);
    nQueen(0,cols,ndiag,rdiag,n);
}