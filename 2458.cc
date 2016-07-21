#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <cstdlib>
#define INF 100000000
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
bool vis[(1 << 25) + 5], can[6][6], inq[6][6];
int mp[6][6], tot = 0;
inline int bh(int i, int j) { return (i - 1) * 5 + j - 1; }

void dfs(int zt, int dep, int sum) {
  // if(vis[zt])
  // return;
  vis[zt] = 1;
  if (dep == 7) {
    if (sum >= 4) tot++;
    return;
  }
  int i, j, x;
  for (i = 1; i <= 5; i++)
    for (j = 1; j <= 5; j++) {
      x = bh(i, j);
      if (can[i][j] && !(zt & (1 << x)))
        if ((i != 1 && (zt & (1 << x - 5))) ||
            (i != 5 && (zt & (1 << x + 5))) ||
            (j != 1 && (zt & (1 << x - 1))) || (j != 5 && (zt & (1 << x + 1))))
          if (!vis[zt | (1 << x)]) dfs(zt | (1 << x), dep + 1, sum + mp[i][j]);
    }
}

int main() {
  int i, j;
  /*
  char t;
  for(i=1;i<=5;i++)
      for(j=1;j<=5;j++)
      {
          cin>>t;
          if(t=='J')
              mp[i][j]=1;
          can[i][j]=1;
      }*/
  char ch;
  for (i = 1; i <= 5; i++)
    for (j = 1; j <= 5; j++) {
      char ch = getchar();
      while (ch != 'H' && ch != 'J') ch = getchar();
      if (ch == 'J') mp[i][j] = 1;
      can[i][j] = 1;
    }
  for (i = 1; i <= 5; i++)
    for (j = 1; j <= 5; j++) {
      dfs(1 << bh(i, j), 1, mp[i][j]);
      can[i][j] = 0;
    }
  cout << tot << endl;
  return 0;
}
