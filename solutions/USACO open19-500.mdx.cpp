---
id: usaco-946
title: USACO Open 2019 Gold - I Would Walk 500 Miles
author: Benjamin Qi
---

Two iterations of counting sort passes in 1966 ms ...

```cpp
const int a = 2019201997-2019201913;
const int b = 2019201997-2019201949;

int N,K;

pi rhsh(int x) { return {x>>16,x&((1<<16)-1)}; }
int wei(int x) { return (x>>16)*a+(x&((1<<16)-1))*b; }

/**
 * Description: Disjoint Set Union with path compression
 	* and union by size. Add edges and test connectivity. 
 	* Use for Kruskal's or Boruvka's minimum spanning tree.
 * Time: O(\alpha(N))
 * Source: CSAcademy, KACTL
 * Verification: *
 */

struct DSU {
	vi e; void init(int N) { e = vi(N,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};

/**template<class T> T kruskal(int N, vector<pair<T,pi>> ed) {
	sort(all(ed));
	T ans = 0; DSU D; D.init(N); // edges that unite are in MST
	trav(a,ed) if (D.unite(a.s.f,a.s.s)) ans += a.f; 
	return ans;
}*/

const int SZ = 28121250;
int ed[SZ], res[SZ];
DSU D;

int cnt[1<<16];

int main() {
	setIO("walk"); 
	clock_t beg = clock();
	re(N,K); D.init(N+1);
	dbg((db)(clock()-beg)/CLOCKS_PER_SEC);
	{
		FOR(i,1,N+1) FOR(j,i+1,N+1) cnt[(a*i+b*j)&((1<<16)-1)] ++;
		int sum = 0; R0F(i,1<<16) swap(sum,cnt[i]), sum += cnt[i];
		FOR(i,1,N+1) FOR(j,i+1,N+1) res[cnt[(a*i+b*j)&((1<<16)-1)]++] = (i<<16)+j;
	}
	dbg((db)(clock()-beg)/CLOCKS_PER_SEC);
	{
		F0R(i,1<<16) cnt[i] = 0;
		FOR(i,1,N+1) FOR(j,i+1,N+1) cnt[(a*i+b*j)>>16] ++;
		int sum = 0; R0F(i,1<<16) swap(sum,cnt[i]), sum += cnt[i];
		F0R(i,N*(N-1)/2) ed[cnt[wei(res[i])>>16]++] = res[i];
	}
	dbg((db)(clock()-beg)/CLOCKS_PER_SEC);
	vi ans;
	F0R(i,N*(N-1)/2) {
		int t = ed[i];
		pi p = rhsh(t);
		if (D.unite(p.f,p.s)) ans.pb(2019201997-wei(t));
	}
	ps(ans[N-K]);
	dbg((db)(clock()-beg)/CLOCKS_PER_SEC);
}
```