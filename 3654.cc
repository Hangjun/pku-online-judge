#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
const int maxn = 57;
int a[maxn][maxn];

int main()
{
    string tt;
    char str[1017];
    int cas = 0;
    int num[maxn];
    while(scanf("%s",str)!=EOF)
    {
        int len = strlen(str);
        if(len == 1 && str[0] == '#')
            break;
        tt = "";
        memset(a,0,sizeof a);
        for(int i = 0; i < len; i++)
        {
            if(str[i]==',')
                tt = "";//清空
            else if(str[i] == '+')
            {
                for(int j = i+1; str[j]!=',' && j < len; j++)
                {
                    for(int k = 0; k < tt.size(); k++)
                    {
                        a[tt[k]-'A'][str[j]-'a']=1;
                    }
                }
            }
            else if(str[i] == '-')
            {
                for(int j = i+1; str[j]!=',' && j < len; j++)
                {
                    for(int k = 0; k < tt.size(); k++)
                    {
                        a[tt[k]-'A'][str[j]-'a']=0;
                    }
                }
            }
            else if(str[i] == '=')
            {
                for(int k = 0; k < tt.size(); k++)
                {
                    memset(a[tt[k]-'A'],0,sizeof a[0]);
                    for(int j = i+1; str[j]!=',' && j < len; j++)
                    {
                        a[tt[k]-'A'][str[j]-'a']=1;
                    }
                }
            }
            else
                tt+=str[i];
        }
        printf("%d:",++cas);
        int l = 0;
        for(int i = 0; i < 26; i++)//记录下所有有权力的人
        {
            int flag = 0;
            for(int j = 0; j < 26; j++)
            {
                if(a[i][j])
                    flag = 1;
            }
            if(flag)
            {
                num[l++] = i;
            }
        }

        tt = "";
        for(int i = 0; i < l; i++)
        {
            int flag = 0;
            if(i != l-1)
            {
                for(int j = 0; j < 26; j++)
                {
                    if(a[num[i]][j] != a[num[i+1]][j])//所含的权力不同
                    {
                        flag = 1;
                    }
                }
            }
            char tem = 'A'+num[i];
            tt += tem;
            if(flag==1 || i==l-1)
            {
                cout<<tt;
                tt = "";
                for(int j = 0; j < 26; j++)
                {
                    if(a[num[i]][j])
                        printf("%c",'a'+j);
                }
            }
        }
        printf("\n");
    }
    return 0;
}


