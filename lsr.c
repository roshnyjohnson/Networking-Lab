#include<stdio.h>
#include<stdlib.h>

int main()
{

        int n,i,j,k,src,min,v;
        int adj[100][100],flag[100],last[100],dist[100];
        printf("ENter thr number of nodes\n");
        scanf("%d",&n);
        printf("\nenter the distance matrix\n");
        for(i=0;i<n;i++)
        {
                for(j=0;j<n;j++)
                {
                        scanf("%d",&adj[i][j]);
                        if(adj[i][j]==0&&i!=j)
                        {
                                adj[i][j]=1000;
                        }
                }
        }
        printf("Enter the source\n");
        scanf("%d",&src);
        for(i=0;i<n;i++)
        {
                flag[i]=0;
                dist[i]=adj[src][i];
                last[i]=src;
        }
        flag[src]=1;
        dist[src]=0;
        for(i=0;i<n;i++)
        {
                min=1000;
                for(j=0;j<n;j++)
                {
                        //min=1000;
                        if (dist[j]<min&&flag[j]==0)
                        {
                                min=dist[j];
                                //flag[j]=1;
                                v=j;
                        }
                }
                flag[v]=1;
                for(j=0;j<n;j++)
                {
                        if(flag[j]==0)
                        {
                        if(dist[j]>adj[v][j]+dist[v])
                        {
                                dist[j]=adj[v][j]+dist[v];
                                last[j]=v;
                        }
                        }
                }
        }
        printf("\nrouter\t dist\tnext\n");
        for(i=0;i<n;i++)
        {
                printf("%d\t%d\t%d\n",i,dist[i],last[i]);
        }
        return 0;
}

