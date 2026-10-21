#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>   // 用hash
#include<ext/pb_ds/trie_policy.hpp>   // 用trie
#include<ext/pb_ds/priority_queue.hpp>// 用priority_queue
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using ordered_set = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

		ordered_set<int> s;
		s.insert(114514);
		s.insert(114514);
		s.insert(114514);
		s.insert(114514);
		cout<<s.order_of_key(114514)<<s.order_of_key(114515)<<endl;
		
	cout.flush();

	return 0;
}
