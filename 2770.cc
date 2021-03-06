#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int d[6][2] = {0, 1, 1, 0, 1, -1, 0, -1, -1, 0, -1, 1};
string map[45][45];
int mark[45][45];

struct node {
  int x, y;
  string s;
};
node a[20];

vector<node> list;

string rev(string s) { return s.substr(1) + s[0]; }

int force(int x, int y) {
  int tx, ty, c, t, i, j, D;
  c = t = 0;
  char ch = '-';
  for (i = 0; i < 6; i++) {
    tx = x + d[i][0];
    ty = y + d[i][1];
    if (tx < 0 || tx >= 45 || ty < 0 || ty >= 45) continue;
    if (map[tx][ty] == "") continue;
    D = (i + 3) % 6;

    t++;
    if (map[tx][ty][D] != ch) {
      ch = map[tx][ty][D];
      c = 1;
    } else
      c++;
  }

  if (t != 3) return -1;
  if (c == 3) return 0;
  return 1;
}

bool canput(int x, int y, string s) {
  int i, j, tx, ty, D;
  for (i = 0; i < 6; i++) {
    tx = x + d[i][0];
    ty = y + d[i][1];
    if (map[tx][ty] == "") continue;
    D = (i + 3) % 6;
    if (map[tx][ty][D] != s[i]) return false;
  }
  return true;
}

bool check() {
  int i, j;
  for (int p = 0; p < list.size(); p++) {
    i = list[p].x;
    j = list[p].y;

    if (map[i][j] == "") {
      if (force(i, j) == 0) return false;
    }
  }
  return true;
}

void deal(int x, int y) {
  int i, j, d1, d2, tx, ty;
  bool tmp[6];
  memset(tmp, 0, sizeof(tmp));
  for (i = 0; i < 6; i++) {
    tx = x + d[i][0];
    ty = y + d[i][1];
    if (map[tx][ty] == "")
      continue;
    else
      tmp[i] = true;
  }

  for (i = 0; i < 6; i++) {
    if (tmp[i] && !tmp[(i + 1) % 6]) d2 = (i + 1) % 6;
    j = i - 1;
    if (j < 0) j += 6;
    if (tmp[i] && !tmp[j]) d1 = j;
  }

  if (d1 < 0) d1 += 6;
  for (i = 1; i >= 1; i++) {
    tx = x + d[d1][0] * i;
    ty = y + d[d1][1] * i;
    if (tx < 0 || tx >= 45 || ty < 0 || ty >= 45) break;
    mark[tx][ty] = -1;
  }
  for (i = 1; i >= 1; i++) {
    tx = x + d[d2][0] * i;
    ty = y + d[d2][1] * i;
    if (tx < 0 || tx >= 45 || ty < 0 || ty >= 45) break;
    mark[tx][ty] = -1;
  }
}

int main() {
  int re, i, j, k, n, x, y;
  string s;
  cin >> re;
  while (re--) {
    list.clear();
    node ss;
    for (i = 0; i < 45; i++)
      for (j = 0; j < 45; j++) {
        map[i][j] = "";
        mark[i][j] = -1;
      }
    cin >> n;
    for (i = 0; i < n; i++) {
      cin >> a[i].x >> a[i].y >> a[i].s;
      map[a[i].x + 21][a[i].y + 21] = a[i].s;
      mark[a[i].x + 21][a[i].y + 21] = -1;
      for (j = 0; j < 6; j++) {
        x = a[i].x + 21 + d[j][0];
        y = a[i].y + 21 + d[j][1];
        if (map[x][y] != "") continue;
        mark[x][y] = 0;
        ss.x = x;
        ss.y = y;
        list.push_back(ss);
      }
    }

    vector<string> l;
    for (i = 0; i < 5; i++) {
      cin >> s;
      for (j = 0; j < 6; j++) {
        s = rev(s);
        l.push_back(s);
      }
    }
    for (i = 0; i < 45; i++)
      for (j = 0; j < 45; j++) {
        if (mark[i][j] == -1) continue;
        if (force(i, j) == 1) {
          mark[i][j] = 1;
          deal(i, j);
        }
      }

    int ans = 0;
    for (i = 0; i < l.size(); i++) {
      for (j = 0; j < 45; j++)
        for (k = 0; k < 45; k++) {
          if (mark[j][k] == 1) {
            if (!canput(j, k, l[i])) continue;
            map[j][k] = l[i];
            mark[j][k] = -1;
            if (check()) {
              ans++;
            }
            map[j][k] = "";
            mark[j][k] = 1;
          }
        }
    }

    if (ans) {
      cout << ans << endl;
      continue;
    }
    int tmp = 0;

    for (i = 0; i < l.size(); i++) {
      for (j = 0; j < 45; j++)
        for (k = 0; k < 45; k++) {
          if (mark[j][k] == 0) {
            tmp++;
            if (!canput(j, k, l[i])) continue;

            map[j][k] = l[i];
            mark[j][k] = -1;
            if (check()) ans++;
            map[j][k] = "";
            mark[j][k] = 0;
          }
        }
    }
    cout << ans << endl;
  }
  return 0;
}
