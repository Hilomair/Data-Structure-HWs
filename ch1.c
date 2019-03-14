#include <stdio.h>
#include <math.h>
#include <string.h>

/*
    �ɶ������� �G O(N^2)
*/


/*
    Edge �O���� �A (x,y)�����I���I �A r����b�| (x,y)����ߡA
    right left���䪺���k���I
*/
typedef struct Edge
{
    float x,y,r;
    int right,left;
}edge;
/*
    Vertex �O���I �A num ���s��
*/
typedef struct Vertex
{
    float x,y;
    int num;
}vertex;
/*
    distance �p����I�Z��
*/
float distance(struct Vertex a, struct Vertex b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
/*
    distance2 �p���䤤�I�P�U�I�Z��
*/
float distance2(struct Edge a, struct Vertex b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
/*
    �����o��
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
    flag�O���䪺���A 0�N��Q�˱󱼤F
*/
int flag[200200];
vertex v[10002];
edge e[200200];

int main()
{
    /*edges�O�����*/
    int N ,i ,j ,cnt = 0 ,edges = 0;


    memset(flag,1,200200);
    freopen("node.txt","r",stdin);
    freopen("link.txt","w",stdout);
    scanf("%d",&N);

    for(i=0;i<N;i++)
        scanf("%d%f%f",&v[i].num,&v[i].x,&v[i].y);

    for(i=0;i<N;i++)
        for(j=i+1;j<N;j++)
            if(distance(v[i],v[j])<=1.0) //���I�Z���p��1 ����
            {
                e[cnt].x = (v[i].x + v[j].x)/2; //�s���I
                e[cnt].y = (v[i].y + v[j].y)/2;
                e[cnt].r = distance(v[i],v[j])/2; //�b�|
                e[cnt].right = j; //�k���I
                e[cnt].left = i; //�����I
                cnt++; //�p�����
            }

    printf("%d\n",cnt);
    for(i=0;i<cnt;i++)
        printf("%d %d %d\n",i,e[i].left,e[i].right);

    edges = cnt; //�O�s��� cnt����|�ʨ�
    for(i=0;i<edges;i++)
        for(j=0;j<N;j++)
            if(e[i].right != v[j].num && e[i].left != v[j].num) //�T�O�I���A��W
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
