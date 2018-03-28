// don't forget to call init function before using DSU.
const int N = 100010;

int head[N];
int group_cnt[N];
int height[N];

// pass 1 in case of 1 - indexing initialization of member id.
inline void init(int sz, int idx = 0) {
  for (int i = idx; i < sz + idx; i++) {
    group_cnt[i] = 1;
    head[i] = i;
    height[i] = 1;
  }
}

// return index of head member of the group in which x lies.
inline int headOf(int x) {
  if (x != head[x]) {
    head[x] = headOf(head[x]);
  }
  return head[x];
}

// return false if x and y will be the member of same group.
inline bool mergeGroup(int x, int y) {
  int head_x = headOf(x);
  int head_y = headOf(y);
  if (head_x == head_y) {
    return false;
  }
  if (height[head_x] > height[head_y]) {
    head[head_y] = head_x;
    group_cnt[head_x] += group_cnt[head_y];
  } else {
    head[head_x] = head_y;
    group_cnt[head_y] += group_cnt[head_x];
    if (height[head_x] == height[head_y]) {
      height[head_y]++;
    }
  }
  return true;
}

// return size of the group in which x lies.
inline int sizeOf(int x) {
  int head_x = headOf(x);
  return group_cnt[head_x];
}
