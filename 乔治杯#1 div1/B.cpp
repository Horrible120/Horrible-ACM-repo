#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
#define OOO cout<<">>>>";	//调试标识

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
Mod = 1e9+7;

ll tt;

struct Student{
	string name;
	ll key,tri_times,flag=0;
	ll tot=0;
	
	bool operator< (const Student &a) const{
		if(flag!=a.flag) return flag>a.flag;
		else if(a.tot!=tot) return tot>a.tot;
		else if(a.tri_times!=tri_times) return tri_times>a.tri_times;
		else return key<a.key;
	}
	
};

vector<Student> stu;

//bool cmp(Student b,Student a){
//	if(b.flag!=a.flag) return b.flag>a.flag;
//	else if(a.tot!=b.tot) return b.tot>a.tot;
//	else if(a.tri_times!=tri_times) return tri_times>a.tot;
//	else return key<a.key;
//}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	ll n,cnt=0;
	
	cin >> n;
	ll times;
	for(ll i=1;i<=n;i++){
		Student it={};
		it.key=i;
		it.tot=0;
		it.tri_times=0;
		it.flag=0;
		cin>>it.name>>times;
		double r=0;
		for(ll j=1;j<=times;j++){
			cin>>r;
			if(r>=3) it.tri_times++;
			it.tot+=(r*100)+0.1;
		}
		if(it.tot>=15000||it.tri_times>=40){
			it.flag=1;
			cnt++;
		}
			
		stu.emplace_back(it);
	}
	
	if(stu.size()) sort(stu.begin(),stu.end());
	
	cout<<cnt<<endl;
	for(ll i=0;i<cnt;i++)
		cout<<stu[i].name<<endl;
	
	cout.flush();
	
	return 0;
}
