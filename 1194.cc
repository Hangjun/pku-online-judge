#include <iostream>
#include <cstring>
#define M 110
using namespace std;
char str[M][M], text[1000001];
int n, a[M];
__int64 dp[1000001];
int main() {
  //	freopen("1.txt","r",stdin);
  while (scanf("%d", &n) != EOF) {
    int i, j, k, p, q, h, l;
    for (i = 1; i <= n; i++) {
      scanf("%s", str[i] + 1);
      a[i] = strlen(str[i] + 1);
    }
    scanf("%s", text + 1);
    dp[0] = 0;
    q = strlen(text + 1);
    for (i = 1; i <= q; i++) {
      dp[i] = dp[i - 1];
      for (j = 1; j <= n; j++) {
        if (str[j][a[j]] == text[i]) {
          for (k = i - 1, p = a[j] - 1, h = 1; h <= 1000 && p > 0 && k > 0;
               k--, h++) {
            if (str[j][p] == text[k]) p--;
          }
          if (p == 0) {
            if (dp[k] + a[j] > dp[i]) dp[i] = dp[k] + a[j];
          }
        }
      }
    }
    printf("%I64d\n", dp[q]);
  }
  return 0;
}
