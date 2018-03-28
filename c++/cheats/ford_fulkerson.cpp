// dfs implementation of ford fulkerson algo.
// O(max_flow * (V + E)).
// always make undirected adjacency graph.
// initialize the cost matrix with zero.
const int N = 1010;

int par[N], cost[N][N];
bool vis[N];
stack<int> stk;
vector<int> g[N];
int source, sink;
vector< pair< pair<int, int> , int> > edges;

inline bool findAugPath() {
  int u, v, i;
  memset(vis, false, sizeof(vis));
  stk.push(source);
  vis[source] = true;
  while(!stk.empty()) {
    u = stk.top();
    stk.pop();
    if(vis[sink] == true) {
      continue;
    }
    for(i = g[u].size() - 1; i >= 0; i--) {
      v = g[u][i];
      if(vis[v] == false) {
        if(cost[u][v] > 0) {
          par[v] = u;
          vis[v] = true;
          stk.push(v);
        }
      }
    }
  }
  if(vis[sink] == false) {
    return false;
  }
  u = sink;
  while(u != source) {
    cost[par[u]][u]--;
    cost[u][par[u]]++;
    u = par[u];
  }
  return true;
}

inline int maxFlow() {
  int mf = 0;
  while(findAugPath()) {
    mf++;
  }
  return mf;
}
