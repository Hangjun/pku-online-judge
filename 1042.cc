#include <iostream>
using namespace std;
const int iMax = 30;
const int jMax = 200;

int max(int a, int b) { return a > b ? a : b; }

int main() {
  int fish[iMax][jMax], decr[iMax], move[iMax];
  int LakeNum, Hour, i, j, k;
  while (cin >> LakeNum && LakeNum != 0) {
    cin >> Hour;
    for (i = 1; i <= LakeNum; i++) cin >> fish[i][1];
    for (i = 1; i <= LakeNum; i++) cin >> decr[i];
    for (i = 2; i <= LakeNum; i++) cin >> move[i];
    int min5 = Hour * 12;
    for (i = 1; i <= LakeNum; i++)
      for (j = 2; j <= min5; j++) fish[i][j] = max(fish[i][j - 1] - decr[i], 0);

    int fishnum = 0, time[iMax];
    memset(time, 0, sizeof(time));
    time[1] = min5;  //  考虑全部没有鱼的情况，所有时间耗在time[1]。
    for (k = 1; k <= LakeNum; k++) {  //  枚举所经过的湖数k。
      int t[iMax], f = 0, count = min5;
      memset(t, 0, sizeof(t));
      for (i = 1; i <= k; i++) count -= move[i];
      if (count <= 0) break;  //  当总时间不够耗在路程上时，跳出。
      while (count--) {       //  贪心选择count个湖点。
        int m = 0, p = 1;
        for (i = 1; i <= k; i++)
          if (fish[i][t[i] + 1] > m) {
            m = fish[i][t[i] + 1];
            p = i;
          }
        f += m;
        t[p]++;
      }
      if (f > fishnum) {  //  当由于前面的最优解时，构造新的最优解。
        fishnum = f;
        for (i = 1; i <= k; i++) time[i] = t[i];
        for (i = k + 1; i <= LakeNum; i++) time[i] = 0;
      }
    }
    for (i = 1; i <= LakeNum - 1; i++) cout << time[i] * 5 << ", ";
    cout << time[i] * 5 << endl;
    cout << "Number of fish expected: " << fishnum << endl
         << endl;
  }
  return 0;
}
