#include<iostream>
#include<climits>
#include<vector>
#include <cstring>
#include <unordered_map>

#define int long long

#define HIT_SCORE 2
#define MISSED_SCORE -2

using namespace std;

int dc_align_same(string a,string b,int as,int ae,int bs,int be){
    if(as >= ae or bs >= be){
        return 0;
    }
    int cnt = 0;
    int mid1 = (as + ae)/2;
    int mid2 = (bs + be)/2;
    int left = dc_align_same(a,b,as,mid1,bs,mid2);
    if(a[mid1] == b[mid2]){
        cnt = left + HIT_SCORE;
    }else{
        cnt = left + MISSED_SCORE;
    }
    int right = dc_align_same(a,b,mid1 + 1,ae,mid2+1,be);
    cnt += right;
    return cnt;
}

void dc_align_output(string a,string b,int as,int ae,int bs,int be,unordered_map<int,int>&mp){
    if(as >= ae or bs >= be){
        return;
    }
    int mid1 = (as + ae)/2;
    int mid2 = (bs + be)/2;
    dc_align_output(a,b,as,mid1,bs,mid2,mp);
    if(a[mid1] == b[mid2] or mp.find(mid1) != mp.end()){
        cout<<a[mid1]<<"";
    }else{
        cout<<"_";
    }
    dc_align_output(a,b,mid1 + 1,ae,mid2+1,be,mp);
}

void dc_align_ordering(string a,string b,int as,int ae,int bs,int be,vector<int> &ordering){
    if(as >= ae or bs >= be){
        return;
    }
    int mid1 = (as + ae)/2;
    int mid2 = (bs + be)/2;
    dc_align_ordering(a,b,as,mid1,bs,mid2,ordering);

    if(a[mid1] == b[mid2]){
        int flag = 1;
    }else{
        ordering.push_back(mid1);
    }
    dc_align_ordering(a,b,mid1 + 1,ae,mid2+1,be,ordering);
}

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

void dc_align_multiple(string a,string b,int as,int ae,int bs,int be){
    if(a.size() < b.size()){
        swap(a,b);
    }
    int lengthDiff = a.size() - b.size();
//    cout<<lengthDiff<<endl;
    int ans = INT_MIN;
    int index = -1;
    for(int i = 0;i < lengthDiff + 1;i++){
        int val = dc_align_same(a,b,bs + i,be + i,bs,be);
        ans = max(ans,val);
        if(ans == val){
            index = i;
        }
    }
//    cout<<index<<endl;
    vector<int> ordering;
    ordering.reserve(5 * 1000000);
    dc_align_ordering(a,b,as+index,ae+index,bs,be,ordering);
//    Use longest consecutive subarray problem.
//    for(auto q:ordering){
//        cout<<q<<endl;
//    }
    vector<pair<int,int>> nd;
    nd.reserve(1000);
    int indexer = -1;
    int cnt = 0;
    vector<int>indexed;
    indexed.reserve(1000);
    for(int i = 0;i<ordering.size()-1;i++){
        cout<<ordering[i]<<endl;
        if(ordering[i] == ordering[i+1] - 1){
            cnt++;
            cout<<cnt<<endl;
            if(i == ordering.size()-2){
                cnt++;
                nd.emplace_back(ordering[i+1]-cnt,ordering[i]);
            }
        }
        else{
            nd.emplace_back(ordering[i]-cnt,ordering[i]);
            cnt = 0;
        }
    }
    cout<<"nd "<<nd.size()<<endl;
    for(auto x:nd){
        if(x.second - x.first<= 1)
            continue;
        memset(dp,-1,sizeof(dp));
        int length = lenLcs(a,b,x.first,0,x.second+1);
        cout<<length<<endl;
        getLCS(a,b,length,indexed,x.first);
    }

    unordered_map<int,int> mp;
    for(auto x : indexed){
        cout<<x<<endl;
        mp[x] = 1;
    }
    dc_align_output(a,b,bs+index,be+index,bs,be,mp);
}

int32_t main(){
    string a = "XTATGCTATDHAGDHAGFCDISGDIGVCDXT";
    string b = "XTATGCTATHAGDDHAGFCDISGDIGVCDXT";
    dc_align_multiple(a,b,0,a.size(),0,b.size());
    return 0;
}