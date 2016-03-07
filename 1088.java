import java.util.Scanner;
public class Main{
  private int h[][]=new int[101][101];
  private int m[][]=new int[101][101];
  private int r,c;

  private void init(){
    Scanner sc=new Scanner(System.in);
    r=sc.nextInt();
    c=sc.nextInt();     
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            h[i][j]=sc.nextInt();
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            m[i][j]=-1;
  }

  //���ȴ�(i,j)���е״��  private int GetHigh(int i,int j){    
    if(m[i][j]!=-1)//ȹm[i][j]��Ҿ��˹�      return m[i][j];
    else{
      int max=0;
      int temp;
      if(j>1)//(i,j)�ױ      {
        if(h[i][j]>h[i][j-1]){
            temp=GetHigh(i,j-1);
            if(max< temp)
                max=temp;
        }
      }
      if(j< c)//(i,j)�ױ      {
        if(h[i][j]>h[i][j+1]){
            temp=GetHigh(i,j+1);
            if(max< temp)
                max=temp;
        }
       }
       if(i>1)//(i,j)�ɱ      {
        if(h[i][j]>h[i-1][j]){
            temp=GetHigh(i-1,j);
            if(max< temp)
                max=temp;
        }
       }
       if(i< r)//(i,j)�ϱ       {
         if(h[i][j]>h[i+1][j]){
            temp=GetHigh(i+1,j);
            if(max< temp)
               max=temp;
         }
        }
        m[i][j]=max+1;//̳���        return m[i][j];
    }
}

 public int getMaxHeight(){
   int temp;
   int Max=-1;
   for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            temp=GetHigh(i,j);
            if(Max< temp)
                Max=temp;    
        }
    }
    return Max;
  }

  public static void main(String args[]){
    Main m=new Main();
    m.init();
    System.out.println(m.getMaxHeight());
 }
}

