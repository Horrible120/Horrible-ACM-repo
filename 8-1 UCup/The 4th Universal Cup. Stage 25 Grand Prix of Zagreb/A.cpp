#include <iostream>
#include<queue>
#include<vector>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;

typedef long long ll;

ll tt=1;
struct node{
	ll w,id;
	bool operator <(const node &b)const{
		return w<b.w;
	}
};
node a[400009];
void solve(){
	priority_queue<node> q;
	vector<ll> v;
	ll n;
	cin>>n;
	for(int i=1;i<=2*n;i++){
		cin>>a[i].w;
		a[i].id=i;
	}
	v.push_back(1);
	for(int i=2;i<=2*n;i+=2){
		if(i==2*n)break;
		q.push(a[i]);
		q.push(a[i+1]);
		v.push_back(q.top().id);
		q.pop();
	}
	sort(v.begin(),v.end());
	for(auto i:v){
		cout<<i<<' ';
	}
	cout<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
