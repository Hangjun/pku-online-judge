///G++
///������
#include <stdio.h>
#include <algorithm>
 
using namespace std;
 
const int maxn = 100005;
///num������õ����飬dat��ԭ���е������У�cnt�ǵ�ǰλ�ü�ǰ�������������Ԫ�ظ���
int num[maxn], dat[20][maxn], cnt[20][maxn];
int N, M, K;
 
void build(int L, int R, int o)
{
        if(L==R) return ;
        int M = (L+R)>>1;
        int lc = 0;  ///num[M]���ظ��Ļ������Խ�����������num[M]�ĸ���
        for(int i=M; num[i]==num[M]; i--) lc++;
        int lp = L, rp = M+1, p = 0;
        for(int i=L; i<=R; i++) {
                if(dat[o][i]<num[M] || (dat[o][i]==num[M] && (lc-->0))) {
                        cnt[o][i] = ++p;
                        dat[o+1][lp++] = dat[o][i];
                } else {
                        cnt[o][i] = p;
                        dat[o+1][rp++] = dat[o][i];
                }
        }
        build(L, M, o+1);
        build(M+1, R, o+1);
}
 
int _l, _r, _x;
int query(int L, int R, int o)
{
        if(L==R) return dat[o][L];
        int M = (L+R)>>1;
        int ls = _l-1<L?0:cnt[o][_l-1];
        if(cnt[o][_r]-ls>=_x) {
                _l = L+ls;
                _r = L+cnt[o][_r]-1;
                return query(L, M, o+1);
        } else {
                _x -= cnt[o][_r]-ls;
                _l = M+1 + (_l-L-ls);
                _r = M+1 + (_r-L+1-cnt[o][_r]) - 1;
                return query(M+1, R, o+1);
        }
}
 
int main()
{
        scanf("%d%d", &N, &M);
        for(int i=1; i<=N; i++) {
                scanf("%d", &num[i]);
                dat[1][i] = num[i];
        }
        sort(num+1, num+1+N);
        build(1, N, 1);
        while(M--) {
                scanf("%d%d%d", &_l, &_r, &_x);
                printf("%d\n", query(1, N, 1));
        }
 
        return 0;
}