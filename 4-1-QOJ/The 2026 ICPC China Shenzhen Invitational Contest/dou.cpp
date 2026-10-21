#include <bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
ll tt=1;
const ll N=300098;
string ss1,ss2;
ll c;
ll n;
set<ll> s1,s2,s3,s4;
ll siz1,siz2;
void clear(){
	s1.clear();
	s2.clear();
	s3.clear();
	s4.clear();
	siz1=siz2=0;
}
bool pd1(){
	for(int i=1;i<=n;i++){
		if(ss1[i-1]=='2')s3.insert(i);
		if(ss2[i-1]=='2')s4.insert(i);
		if(i<c){
			if(ss1[i-1]=='1')siz1++;
			if(ss2[i-1]=='1')siz2++;
		}
		else{
			if(ss1[i-1]=='1')s1.insert(i);
			if(ss2[i-1]=='1')s2.insert(i);
		}
	}
	ll cnt1=0;
	while(1){
		if(s2.empty())break;
		auto it=s1.upper_bound(*s2.begin());
		if(it!=s1.end()){
			s1.erase(it);
			s2.erase(s2.begin());
			cnt1++;
		}
		else break;
	}
	ll cnt2=0;
	while(1){
		
		auto it=s3.upper_bound(*s4.begin());
		if(it!=s3.end()){
			s3.erase(it);
			s4.erase(s4.begin());
			cnt2++;
		}
		else break;
	}
	if(siz1-1<=min((ll)s2.size(),cnt2)+cnt1){
		return 1;
	}
	else return 0;
}
bool pd2(){
	for(int i=1;i<=n;i++){
		if(ss1[i-1]=='2')s3.insert(i);
		if(ss2[i-1]=='2')s4.insert(i);
		if(i<c){
			if(ss1[i-1]=='1')siz1++;
			if(ss2[i-1]=='1')siz2++;
		}
		else{
			if(ss1[i-1]=='1')s1.insert(i);
			if(ss2[i-1]=='1')s2.insert(i);
		}
	}
	if(siz2>1)return 0;
	if(s2.upper_bound(*s1.begin())!=s2.end()||s4.upper_bound(*s3.begin())!=s4.end()){
		return 1;
	}
	else return 0;
	
}
void solve(){
	cin>>n;
	cin>>ss1>>ss2;
	cin>>c;
	if(pd1()||pd2())cout<<"Yes\n";
	else cout<<"No\n";
}

int main() {
	cin >> tt;    //非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		clear();
		solve();
//        cout.flush();
	}
	cout.flush();
	
	return 0;
}

