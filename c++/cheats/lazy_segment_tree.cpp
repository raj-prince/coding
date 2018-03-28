// change the Segment structure.
// implement unite, push function accordingly.
// check build, update, query.

const int N = 100010;

// change data according to problem.
struct Segment {
  int mx, mn;
  int lazy;
  bool on;

  Segment(int x = 0, int y = 0) : mx(x), mn(y), on(false) {}
};

int a[N];
Segment seg[4 * N];

// on value always false when it is called.
Segment unite(const Segment &a, const Segment &b) {
  Segment c;
  c.mx = max(a.mx, b.mx);
  c.mn = min(a.mn, b.mn);
  c.on = false;
  c.lazy = 0;
  return c;
}

// push the value of lazy to it's children.
inline void push(int id) {
  if (seg[id].on) {
    seg[id + id].mx = seg[id + id].mn = seg[id + id].lazy = seg[id].lazy;
    seg[id + id + 1].mx = seg[id + id + 1].mn = seg[id + id + 1].lazy = seg[id].lazy;
    seg[id + id].on = seg[id + id + 1].on = true;
    seg[id].on = false;
  }
}

// initialize the tree with initial array.
inline void build(int id, int sl, int sr) {
  if (sl < sr) {
    int smid = (sl + sr) >> 1;
    build(id + id, sl, smid);
    build(id + id + 1, smid + 1, sr);
    seg[id] = unite(seg[id + id], seg[id + id + 1]);
  } else {
    seg[id] = Segment(a[sl], a[sr]);
  }
}

// update the given range with the given value. (log n)
inline void update(int id, int sl, int sr, int ql, int qr, int val) {
  if (sl >= ql && sr <= qr) {
    seg[id] = Segment(val, val);
    seg[id].lazy = val;
    seg[id].on = true;
    return;
  }
  push(id);
  int smid = (sl + sr) >> 1;
  if (ql <= smid) {
    update(id + id, sl, smid, ql, qr, val);
  }
  if (qr > smid) {
    update(id + id + 1, smid + 1, sr, ql, qr, val);
  }
  seg[id] = unite(seg[id + id], seg[id + id + 1]);
}

// range query (log n)
inline Segment query(int id, int sl, int sr, int ql, int qr) {
  if (sl >= ql && sr <= qr) {
    return seg[id];
  }
  push(id);
  Segment res;
  int smid = (sl + sr) >> 1;
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
