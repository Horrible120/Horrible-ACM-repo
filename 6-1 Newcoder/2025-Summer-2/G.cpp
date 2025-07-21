#include<bits/stdc++.h>
#define double long double
using namespace std;
const int N = 5e6+5;
const double eps = 1e-12;
const double PI = acos(-1);
struct Point {
	double x, y;
	Point(double x=0, double y=0) : x(x), y(y) {}
	Point operator + (const Point &a) const { return Point(x+a.x, y+a.y);}
	Point operator - (const Point &a) const { return Point(x-a.x, y-a.y);}
	Point operator * (double a) const { return Point(x*a, y*a);}
	Point operator / (double a) const { return Point(x/a, y/a);}
	double operator * (const Point &a) const { return x*a.x + y*a.y;} // 点积
	double operator ^ (const Point &a) const { return x*a.y - y*a.x;}  // 叉积
	double len() const { return sqrt(x*x + y*y); }
}p[N];
int n;
Point P,a[N];
void work(){
	(cout<<fixed).precision(9);
	cin>>n>>P.x>>P.y;
	for(int i=1;i<=n;++i) cin>>p[i].x>>p[i].y;
	p[n+1]=p[1];
	bool f=1;
	for(int i=1;i<=n;++i)
		if(((P-p[i])^(p[i+1]-p[i])-eps)>0){
			f=0;
			break;
		}
	if(!f){//多边形外
		cout<<2*PI<<endl;
		return ;
	}
	double dis=0;
	int cnt=0;
	for(int i=1;i<=n;++i){
		Point tmp=p[i]-P;
		double d=tmp.len();
		if(fabs(d-dis)<eps) a[++cnt]=p[i]-P;
		else if(d>dis){
			dis=d;
			a[cnt=1]=p[i]-P;
		}
	}
	double maxang=0;
	for(int i=1;i<cnt;++i){
		Point p1=a[i],p2=a[i+1];
		double ang = acos((p1*p2)/p1.len()/p2.len());
		maxang=max(maxang,ang);
	}
	Point p1=a[1],p2=a[cnt];
	double ang = acos((p1*p2)/p1.len()/p2.len());
	if(((p1^p2)+eps)>0) maxang=max(maxang,2*PI-ang);
	else maxang=max(maxang,ang);
	cout<<maxang<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;cin>>T;while(T--)
		work();
	return 0;
}
