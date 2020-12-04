//
// Created by omkarkh1 on 03/12/20.
//

#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstring>
#include<climits>
#include<chrono>

#define int long long

#define HIT_SCORE 2
#define MISSED_SCORE -2

using namespace std;
using namespace chrono;

int dp[3001][3001];

int lenLcs(string &s,string &t,int i,int j,int ps){
    if(i >= ps or j >= t.size()){
        return 0;
    }
    if(dp[i][j]!=-1)
        return dp[i][j];
    if(s[i] == t[j])
        return dp[i][j] = 1 + lenLcs(s,t,i+1,j+1,ps);
    else{
        return dp[i][j] = max(lenLcs(s,t,i+1,j,ps),lenLcs(s,t,i,j+1,ps));
    }
}

void getLCS(string &s,string &t,int length,vector<int> &indexing,int start){
//    string res;
    int i = start,j = 0;
    while(length > 0){
        if(s[i] == t[j]){
            indexing.push_back(i);
            i++;j++;length--;
        }else{
            if(dp[i][j+1] > dp[i+1][j]){
                j++;
            }
            else{
                i++;
            }
        }
    }
}

int getLcsScore(string &a,string &b,int asize,int bsize,int idiff){
    int score = 0;
    for(int i = 0;i<bsize;i++){
        if(b[i] == a[i + idiff])
            score += HIT_SCORE;
        else
            score += MISSED_SCORE;
    }
    return score;
}

void getLcsIndex(string &a,string &b,int asize,int bsize,int idiff,vector<int> &orderings){

    for(int i = 0;i<bsize;i++){
        if(b[i] == a[i + idiff])
            continue;
        else
            orderings.push_back(i+idiff);
    }
}

void solve(string &a,string &b,unordered_map<int,int> &mp,vector<int> &orderings){
    int val = INT_MIN;
    int asize = a.size();
    int bsize = b.size();
    int lengthDIff = asize - bsize;
    int indexer = 0;
    for(int i = 0;i<lengthDIff+1;i++){
        int ans = getLcsScore(a,b,asize,bsize,i);
        val = max(val,ans);
        if(val == ans)
            indexer = i;
    }
    getLcsIndex(a,b,asize,bsize,indexer,orderings);
    vector<pair<int,int> > nd;
    int cnt = 0;
    nd.reserve(1000);
    for(int i = 0;i<orderings.size()-1;i++){
        //cout<<orderings[i]<<"\n";
        if(orderings.size() == 0)
            break;
        if(orderings[i] == orderings[i+1] - 1){
            cnt++;
            if(i == orderings.size()-2){
                cnt++;
                nd.emplace_back(orderings[i+1]-cnt,orderings[i]);
            }
        }
        else{
            nd.emplace_back(orderings[i]-cnt,orderings[i]);
            cnt = 0;
        }
    }
    vector<int>indexed;
    indexed.reserve(1000);
    for(auto x:nd){
        if(x.second - x.first<= 1)
            continue;
        memset(dp,-1,sizeof(dp));
        int length = lenLcs(a,b,x.first,0,x.second+1);
        //cout<<length<<"\n";
        getLCS(a,b,length,indexed,x.first);
    }

//    unordered_map<int,int> mp;
    for(auto x : indexed){
        //cout<<x<<"\n";
        mp[x] = 1;
    }

    for(int i = 0;i<b.size();i++){
        if(a[i + indexer] == b[i] or mp.find(i+indexer) != mp.end())
            cout<<b[i];
        else{
            cout<<"_";
        }
    }
    cout<<"\n";
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    unordered_map<int,int> mp;
    vector<int> orderings;
    orderings.reserve(1000000);
    mp.reserve(1000000);
    string a,b;
    a.reserve(100000000);
    b.reserve(100000000);
    cin >> a >> b;
//    a = "cool";
//    b = "cool";

    srand(time(0));
    auto start = high_resolution_clock::now();
    solve(a,b,mp,orderings);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout<<a.size()<<"\n";
    cout<<b.size()<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout << duration.count() << "\n";
//    cout << end - start<<"\n";
    return 0;
}