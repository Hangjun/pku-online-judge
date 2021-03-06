#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;

const int MAXN = 10050;
int uN, vN;
int linker[MAXN];
bool used[MAXN];
struct systemtree {
  int s, next;
} p[10 * MAXN];
int start[MAXN];
bool dfs(int u) {
  int i, v;
  for (i = start[u]; i != -1; i = p[i].next) {
    v = p[i].s;
    if (!used[v]) {
      used[v] = true;
      if (linker[v] == -1 || dfs(linker[v])) {
        linker[v] = u;
        return true;
      }
    }
  }

  return false;
}
int hungary() {
  int res = 0;
  int u;
  memset(linker, -1, sizeof(linker));
  for (u = 0; u < uN; u++) {
    memset(used, 0, sizeof(used));
    if (dfs(u)) res++;
  }
  return res;
}
int main() {
  int n, m, job, s, temp, num, i;
  while (scanf("%d", &n) != EOF) {
    memset(start, -1, sizeof(start));
    uN = vN = n;
    num = 0;
    while (n--) {
      scanf("%d", &job);
      scanf(": (%d)", &m);
      temp = m;
      start[job] = num;
      p[num].s = -1;
      p[num].next = -1;
      num++;
      while (temp--) {
        scanf("%d", &s);
        p[num].s = s - vN;
        p[num].next = num - 1;

        num++;
      }
      start[job] = num - 1;
    }
    printf("%d\n", hungary());
  }
  return 0;
}
