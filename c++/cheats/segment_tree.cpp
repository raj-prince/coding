// divide and conquer strategy;
// use to find solution from two independent subproblem.

// change the Segment structure.
// implement unite function according to that.
// check build, update, query.

const int N = 100010;

struct Segment {
  int mx, mn;

  Segment(int x = 0, int y = 0) : mx(x), mn(y) {}

};

Segment seg[4 * N];
int a[N];

// merge two segment using it.
Segment unite(const Segment &a, const Segment &b) {
  Segment c;
  c.mx = max(a.mx, b.mx);
  c.mn = min(a.mn, b.mn);
  return c;
}

// build - O(n)
void build(int id, int sl, int sr) {
  if (sl < sr) {
    int smid = (sl + sr) >> 1;
    build(id + id, sl, smid);
    build(id + id + 1, smid + 1, sr);
    seg[id] = unite(seg[id + id], seg[id + id + 1]);
  } else {
    seg[id] = Segment(a[sl], a[sl]);
  }
}

// point update O(log n).
void update(int id, int sl, int sr, int pos, int val) {
  if (sl == sr) {
    seg[id] = Segment(val, val);
    return;
  }
  int smid = (sl + sr) >> 1;
  if (pos <= smid) {
    update(id + id, sl, smid, pos, val);
  } else {
    update(id + id + 1, smid + 1, sr, pos, val);
  }
  seg[id] = unite(seg[id + id], seg[id + id + 1]);
}

// range - query O(log_n).
Segment query(int id, int sl, int sr, int ql, int qr) {
  if (sl >= ql && sr <= qr) {
    return seg[id];
  }
  int smid = (sl + sr) >> 1;
  Segment res;
  if (qr <= smid) {
    res = query(id + id, sl, smid, ql, qr);
  } else {
    if (ql > smid) {
      res = query(id + id + 1, smid + 1, sr, ql, qr);
    } else {
      res = unite(query(id + id, sl, smid, ql, qr), query(id + id + 1, smid + 1, sr, ql, qr));
    }
  }
  return res;
}
