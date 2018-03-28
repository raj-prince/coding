// Time Complexity : O(v * v * e)
// make level graph, find blocking flow and flew it.

// test it :: http://www.spoj.com/problems/FASTFLOW/

const int inf = (int)2e9;

// cap : capacity of edge.
// flow : flow through edge.
struct edge {
  int x, y, cap, flow;
};

struct DinicFlow {
  vector <edge> e;
  vector <int> cur, d;
  vector < vector <int> > g;
  int n, source, sink;

  DinicFlow() {}

  DinicFlow(int v) {
    n = v;
    cur = vector <int> (n + 1); // till which edge processed.
    d = vector <int> (n + 1); // contains level of level graph.
    g = vector < vector <int> > (n + 1); // g[u] contains index of edge which start from u.
  }

  void addEdge(int from, int to, int cap) {
    edge e1 = {from, to, cap, 0};
    edge e2 = {to, from, 0, 0};
    g[from].push_back(e.size());
    e.push_back(e1);
    g[to].push_back(e.size());
    e.push_back(e2);
  }

  // return 0 when we can't approach to sink in level graph.
  int bfs() {
    queue <int> q;
    for(int i = 0; i <= n; ++i) d[i] = -1;
    q.push(source);
    d[source] = 0;
    while(!q.empty() and d[sink] < 0) {
      int x = q.front();
      q.pop();
      for(int i = 0; i < (int)g[x].size(); ++i) {
        int id = g[x][i], y = e[id].y;
        if(d[y] < 0 and e[id].flow < e[id].cap) {
          q.push(y);
          d[y] = d[x] + 1;
        }
      }
    }
    return d[sink] >= 0;
  }

  // max blocking flow in the current level graph.
  int dfs(int x, int flow) {
    if(!flow) return 0;
    if(x == sink) return flow;
    for(; cur[x] < (int)g[x].size(); ++cur[x]) {
      int id = g[x][cur[x]], y = e[id].y;
      if(d[y] != d[x] + 1) continue;
      int pushed = dfs(y, min(flow, e[id].cap - e[id].flow));
      if(pushed) { // because if at 0 edge(u - > v) then at 1 edge(v -> u);
        e[id].flow += pushed;
        e[id ^ 1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

  long long maxFlow(int src, int snk) {
    this->source = src;
    this->sink = snk;
    long long flow = 0;
    while(bfs()) {
      for(int i = 0; i <= n; ++i) cur[i] = 0;
      while(int pushed = dfs(source, inf)) {
        flow += pushed;
      }
    }
    return flow;
  }
};

