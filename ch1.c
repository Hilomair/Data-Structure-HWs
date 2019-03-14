#include <stdio.h>
#include <math.h>
#include <string.h>

/*
    時間複雜度 ： O(N^2)
*/


/*
    Edge 記錄邊 ， (x,y)為兩點中點 ， r為圓半徑 (x,y)為圓心，
    right left為邊的左右兩點
*/
typedef struct Edge
{
    float x,y,r;
    int right,left;
}edge;
/*
    Vertex 記錄點 ， num 為編號
*/
typedef struct Vertex
{
    float x,y;
    int num;
}vertex;
/*
    distance 計算兩點距離
*/
float distance(struct Vertex a, struct Vertex b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
/*
    distance2 計算邊中點與各點距離
*/
float distance2(struct Edge a, struct Vertex b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
/*
    此為廢案
    int cmp_edge(const void *a,const void *b)
    {
        edge *c = (edge *)a;
        edge *d = (edge *)b;
        if(c->x != d->x)    return c->x - d->x;
        else return d->y - c->y;
    }
    int cmp_vertex(const void *a,const void *b)
    {
        vertex *c = (vertex *)a;
        vertex *d = (vertex *)b;
        if(c->x != d->x)    return c->x - d->x;
        else return d->y - c->y;
    }

    int cmp_num( const void *a ,const void *b)
    {
        vertex *c = (vertex *)a;
        vertex *d = (vertex *)b;
        return c->num > d->num ? 1 : -1;
    }
*/

/*
    flag記錄邊的狀態 0代表被捨棄掉了
*/
int flag[200200];
vertex v[10002];
edge e[200200];

int main()
{
    /*edges記錄邊數*/
    int N ,i ,j ,cnt = 0 ,edges = 0;


    memset(flag,1,200200);
    freopen("node.txt","r",stdin);
    freopen("link.txt","w",stdout);
    scanf("%d",&N);

    for(i=0;i<N;i++)
        scanf("%d%f%f",&v[i].num,&v[i].x,&v[i].y);

    for(i=0;i<N;i++)
        for(j=i+1;j<N;j++)
            if(distance(v[i],v[j])<=1.0) //兩點距離小於1 有邊
            {
                e[cnt].x = (v[i].x + v[j].x)/2; //存中點
                e[cnt].y = (v[i].y + v[j].y)/2;
                e[cnt].r = distance(v[i],v[j])/2; //半徑
                e[cnt].right = j; //右端點
                e[cnt].left = i; //左端點
                cnt++; //計算邊數
            }

    printf("%d\n",cnt);
    for(i=0;i<cnt;i++)
        printf("%d %d %d\n",i,e[i].left,e[i].right);

    edges = cnt; //保存邊數 cnt之後會動到
    for(i=0;i<edges;i++)
        for(j=0;j<N;j++)
            if(e[i].right != v[j].num && e[i].left != v[j].num) //確保點不再邊上
            {
                float tmp = distance2(e[i],v[j]);
                if(tmp<e[i].r)
                {
                    flag[i] = 0;
                    cnt--;
                    break;
                }
            }

    printf("%d\n",cnt);
    for(i=0;i<edges;i++)
        if(flag[i])
            printf("%d %d %d\n",i,e[i].left,e[i].right);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
