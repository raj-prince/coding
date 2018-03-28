// weighted graph in 0 - indexing.
// shortest path from a given source s.

const int N = 10010;
const int inf = 1e9;

int d[N];

vector <pair <int, int>> g[N];

void dijkstra(int s, int n) {
  for (int i = 0; i < n; i++) {
    d[i] = inf;
  }
  d[s] = 0;
  // default priority queue gives max, use greater for min.
  priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> pq;
  pq.push(make_pair(d[s], s));
  while (!pq.empty()) {
    pair <int, int> cur = pq.top(); pq.pop();
    int u = cur.second;
    if (cur.first > d[u]) continue; // redundant.
    for (int i = 0; i < (int)g[u].size(); i++) {
      int v = g[u][i].first;
      int wt = g[u][i].second; // cost u -> v.
      if (d[v] > d[u] + wt) {
        d[v] = d[u] + wt;
        pq.push(make_pair(d[v], v));
      }
    }
  }
}
