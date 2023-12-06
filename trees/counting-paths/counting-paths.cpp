#include <bits/stdc++.h>
using namespace std;

template<typename... T>
void see(T&... args) { ((cin >> args), ...);}
template<typename... T>
void put(T&&... args) { ((cout << args << " "), ...);}
template<typename... T>
void putl(T&&... args) { ((cout << args << "\n"), ...);}
#define ll long long
#define ld long double
#define ii pair<int, int>
#define vi vector<int>
#define vii vector<ii>
#define vec vector
#define rep(i,a,b) for(int i = a; i < b; i++)
#define f0r(i,a) for(int i = 0; i < a; i++)
#define r0f(i,a) for(int i = a - 1; i >= 0; i--)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(v) (v).begin(), (v).end()
#define sz size
#define debug(x) cout << #x << ": " << x << endl;

class LowestCommonAncestor 
{
public:
    LowestCommonAncestor(const vec<vi>& _adj, const int& _num_nodes):
        num_nodes(_num_nodes), jump_table(LOG, vi(_num_nodes + 1)), depth(_num_nodes + 1)
    {
        __make_parent_depth(_adj, jump_table[0], depth, 1, 0, 0);
        rep(pow,1,LOG)
        {
            rep(i,1,_num_nodes + 1)
            {
                jump_table[pow][i] = jump_table[pow - 1][jump_table[pow-1][i]];
            }
        }
    }
    int operator()(int a, int b)
    {
        assert(1 <= min(a,b) && max(a,b) <= num_nodes);
        if(depth[a] < depth[b])
        {
            swap(a,b);
        }
        a = jump(a, depth[a] - depth[b]);
        if(a == b)
        {
            return a;
        }
        r0f(i,LOG - 1)
        {
            int aP = jump_table[i][a], bP = jump_table[i][b];
            if(aP != bP)
            {
                a = aP;
                b = bP;
            }
        }
        return jump_table[0][a];
    }
private:
    static constexpr int LOG = 25;
    int num_nodes;
    vi depth;
    vec<vi> jump_table;
    int jump(const int start_node, const int steps)
    {
        int cur = start_node;
        f0r(i,LOG)
        {
            if((1<<i) & steps)
            {
                cur = jump_table[i][cur];
            }
        }
        return cur;
    }
    void __make_parent_depth(const vec<vi>& adj, vi& parent, vi& depth, const int curr, const int prev, int curr_depth)
    {
        parent[curr] = prev;
        depth[curr] = curr_depth;
        for(const int next : adj[curr])
        {
            __make_parent_depth(adj, parent, depth, next, curr, curr_depth + 1);
        }
    }
};
class Euler
{
public:
    Euler(const vec<vi>& adj, const int _num_nodes):
        num_nodes(_num_nodes), tour_start(num_nodes + 1), tour_end(num_nodes + 1), cur_tour_len(0)
    {
        _dfs(adj, 1, 0);
    }
    int get_start(int node)
    {
        return tour_start[node];
    }
    int get_end(int node)
    {
        return tour_end[node];
    }
private:
    void _dfs(const vec<vi>& adj, int cur, int prev)
    {
        cur_tour_len++;
        tour_start[cur] = cur_tour_len - 1;
        for(int next : adj[cur])
        {
            if(next == prev)
            {
                continue;
            }
            _dfs(adj, next, cur);
        }
        tour_end[cur] = cur_tour_len - 1;
    }
    int num_nodes;
    int cur_tour_len;
    vi tour_start;
    vi tour_end;
};
void solve()
{
    int n,m;
    see(n,m);
    vec<vi> adj(n + 1);
    f0r(_,n-1)
    {
        int s,t;
        see(s,t);
        adj[s].pb(t);
        adj[t].pb(s);
    }
    LowestCommonAncestor lca(adj, n);
    Euler e(adj, n);
}
int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
