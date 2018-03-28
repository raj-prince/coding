#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

char txt[N];
char wrd[N];

int n, m; // length of text as well as word string
int ra[N], tmpra[N]; // rank array
int sa[N], tmpsa[N]; // suffix array
int cnt[N];

int phi[N]; // previous suffix
int plcp[N]; // permuted longest common prefix
int lcp[N]; // LCP[i] stores the LCP b/w suffix SA[i] & SA[i - 1];

// k for offset (sort based on rank of suffix i + k).
inline void countingSort(int k) {
  int sum = 0, mx = max(300, n);
  memset(cnt, 0, sizeof cnt);
  for(int i = 0; i < n; i++) {
    cnt[i + k < n ? ra[i + k] : 0]++;
  }
  for(int i = 0; i < mx; i++) {
    int t = cnt[i];
    cnt[i] = sum;
    sum += t;
  }
  for(int i = 0; i < n; i++) {
    tmpsa[cnt[sa[i] + k < n ? ra[sa[i] + k] : 0]++] = sa[i];
  }
  for(int i = 0; i < n; i++) {
    sa[i] = tmpsa[i];
  }
}

// compute SA in O(n log n).
// makes SA of the TEXT string.
inline void constructFast() {
  for(int i = 0; i < n; i++) {
    ra[i] = txt[i];
    sa[i] = i;
  }
  for(int k = 1; k < n; k <<= 1) {
    countingSort(k); // first sorting based on second pair
    countingSort(0); // finally stable sorting based on first pair.
    int r = 0;
    tmpra[sa[0]] = 0;
    for(int i = 1; i < n; i++) {
      tmpra[sa[i]] = (ra[sa[i]] == ra[sa[i - 1]] && ra[sa[i] + k] == ra[sa[i - 1] + k]) ? r : ++r;
    }
    for(int i = 0; i < n; i++) {
      ra[i] = tmpra[i];
    }
    if(ra[sa[n - 1]] == n - 1) break; // optimization
  }
}

// compute LCP in O(n)
inline void computelcpFast() {
  phi[sa[0]] = -1;
  for(int i = 1; i < n; i++) {
    phi[sa[i]] = sa[i - 1];
  }
  for(int i = 0, l = 0; i < n; i++) {
    if(phi[i] == -1) {
      plcp[i] = 0;
      continue;
    }
    while(txt[i + l] == txt[phi[i] + l]) l++; // increase maximum n times
    plcp[i] = l;
    l = max(l - 1, 0); // decrease maximum n times
  }
  for(int i = 0; i < n; i++) {
    lcp[i] = plcp[sa[i]];
  }
}

// return lower and upper bound as an pair.
// return [-1, -1], in case mismatch.
pair <int, int> stringMatching() {
  int low = 0, high = n - 1;
  while (low < high) {
    int mid = (low + high) >> 1;
    int res = strncmp(txt + sa[mid], wrd, m); // match till m length
    if (res < 0) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  if (strncmp(txt + sa[low], wrd, m) != 0) {
    return make_pair(-1, -1);
  }
  int ll = low;
  low = 0, high = n - 1;
  while (low < high) {
    int mid = (low + high) >> 1;
    int res = strncmp(txt + sa[mid], wrd, m);
    if (res <= 0) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  if (strncmp(txt + sa[high], wrd, m) == 0) {
    high++;
  }
  return make_pair(ll, high);
}

// return length and index of longest repeated substring.
pair <int, int> longestRepeatedSubstr() {
  int idx = 0, maxlcp = -1;
  for(int i = 1; i < n; i++) {
    if(lcp[i] > maxlcp) {
      maxlcp = lcp[i];
      idx = i;
    }
  }
  return make_pair(maxlcp, idx);
}

// used to differentiate when we do something by concatenating the string.
inline int owner(int idx) { // used after joining text and word
  return (idx < n - m - 1) ? 1 : 2;
}

// returns a pair (LCS and starting index.
pair <int, int> longestCommonSubstr() { // return a pair(LCS and its index)
  int idx = 0, maxlcp = -1;
  for(int i = 1; i < n; i++) {
    if(owner(sa[i]) != owner(sa[i - 1]) && lcp[i] > maxlcp) {
      maxlcp = lcp[i];
      idx = i;
    }
  }
  return make_pair(maxlcp, idx);
}

int main() {
  // take text
  scanf("%s", txt);
//  n = (int)strlen(txt);
//  txt[n++] = '#';
//
//  constructFast(); // construct suffix array of text.
//  for (int i = 0; i < n; i++) {
//    if (i > 0) {
//      putchar(' ');
//    }
//    printf("%d", sa[i]);
//  }

//  computelcpFast(); // construct LCP of the text
//  putchar('\n');
//  for (int i = 0; i < n; i++) {
//    if (i > 0) {
//      putchar(' ');
//    }
//    printf("%d", lcp[i]);
//  }

//    pair <int, int> z = longestRepeatedSubstr();
//    char cs[N];
//    strncpy(cs, txt + sa[z.second], z.first);
//    puts(cs);


//  scanf("%s", wrd); // take pattern, initialize with length. and search in text.
//  m = (int)strlen(wrd);
//  pair <int, int> match_idx = stringMatching();
//  for (int i = match_idx.first; i < match_idx.second; i++) {
//    puts(txt + sa[i]);
//  }


//  strcpy(wrd, "dalbc");
//  m = (int)strlen(wrd);
//  strcat(txt, wrd);
//  strcat(txt, "#");
//  n = (int)strlen(txt);
//  constructFast();
//  computelcpFast();
//  pair <int, int> ans = longestCommonSubstr();
//  char lcsans[N];
//  strncpy(lcsans, txt + sa[ans.second], ans.first);
//  printf("lcs is %s with length=%d\n", lcsans, ans.first);
}


