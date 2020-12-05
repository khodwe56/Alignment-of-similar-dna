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

int lenLcs(string &s,string &t,int i,int j,int ps,int subtractor){
    if(i >= ps or j >= t.size()){
        return 0;
    }
    if(dp[i-subtractor][j]!=-1)
        return dp[i-subtractor][j];
    if(s[i] == t[j])
        return dp[i-subtractor][j] = 1 + lenLcs(s,t,i+1,j+1,ps,subtractor);
    else{
        return dp[i-subtractor][j] = max(lenLcs(s,t,i+1,j,ps,subtractor),lenLcs(s,t,i,j+1,ps,subtractor));
    }
}

void getLCS(string &s,string &t,int length,vector<int> &indexing,int start,int subtractor){
//    string res;
    int i = start,j = 0;
    while(length > 0){
        if(s[i] == t[j]){
            indexing.push_back(i);
            i++;j++;length--;
        }else{
            if(dp[i-subtractor][j+1] > dp[i+1-subtractor][j]){
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
//    vector<pair<int,int> > nd1;
    int cnt = 0;
    nd.reserve(100000);
//    nd1.reserve(2000);
    for(int i = 0;i<orderings.size()-1;i++){
        //cout<<orderings[i]<<"\n";
        if(orderings.empty())
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
    indexed.reserve(100000);
    for(auto x:nd){
        if(x.second - x.first<= 1)
            continue;
        if(x.second - x.first >= 2900){
            int tmp = x.second;
            x.second = x.first + 2900;
            if(tmp < 99999995)
            nd.emplace_back(x.second + 1,tmp);
        }
//        nd1.emplace_back(x.first,x.second);
        memset(dp,-1,sizeof(dp));
        int length = lenLcs(a,b,x.first,0,x.second+1,x.first);
        //cout<<length<<"\n";
        getLCS(a,b,length,indexed,x.first,x.first);
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
//      for(int i = 0;i<a.size();i++){
//
//      }

    cout<<"\n";
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    unordered_map<int,int> mp;
    vector<int> orderings;
    orderings.reserve(10000000);
    mp.reserve(10000000);
    string a,b;
    a.reserve(100000000);
    b.reserve(100000000);
    a.clear();
    b.clear();
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