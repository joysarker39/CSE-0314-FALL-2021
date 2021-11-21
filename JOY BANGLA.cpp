#include<bits/stdc++.h>
using namespace std;
#define D(x) cerr << __LINE__ << #x << " -> " << x << endl

vector < vector < int > > vec;
string s;

int getVal(int &pos){
    int num = 0;
    while(s[pos] >='0' and s[pos] <= '9') num = num * 10 + (s[pos] - '0'), pos++;
    return num;
}

void xShift(int pos){
    for(int i = 0; i < vec.size(); i++){
        vec[i][0] += pos;
        vec[i][2] += pos;
    }
}

void yShift(int pos){
    for(int i = 0; i < vec.size(); i++){
        vec[i][1] += pos;
        vec[i][3] += pos;
    }
}

void f2hd(){
    /// NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin
    int oldmx = 1920;
    int newmx = 1080;
    for(int i = 0; i < vec.size(); i++){
        vec[i][0] = ((((vec[i][0]-0)*newmx)/oldmx) + 0);
        vec[i][2] = ((((vec[i][2]-0)*newmx)/oldmx) + 0);
    }
    oldmx = 1080;
    newmx = 720;
    for(int i = 0; i < vec.size(); i++){
        vec[i][1] = ((((vec[i][1]-0)*newmx)/oldmx) + 0);
        vec[i][3] = ((((vec[i][3]-0)*newmx)/oldmx) + 0);
    }
}

void WRITE(){
    for(auto X: vec){
        printf("drawLineDDA(%d,%d,%d,%d);\n",X[0],X[1],X[2],X[3]);
    }
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("out.txt","w",stdout);
    while(1){
        getline(cin,s);
        if(!s.size())break;
        int pos = find(s.begin(),s.end(),'(')-s.begin();
        string temp = "";
        vec.emplace_back();
        for(int i = 0; i < 4; i++) pos++, vec.back().push_back(getVal(pos));
    }
    xShift(300);
    f2hd();
    WRITE();
    return 0;
}

