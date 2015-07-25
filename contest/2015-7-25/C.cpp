#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<vector>
using namespace std;

#define N 100005
#define MP(x,y) make_pair(x,y)

int start[N],tot=0,w[N],n,Max[N],father[N],deep[N],now;

struct node
{
	int x,y,next;
}road[N*2];

pair<int,int> t[N];

void build(int x,int y)
{
	tot++;
	road[tot].x=x,road[tot].y=y,road[tot].next=start[x],start[x]=tot;
}

void dfs(int x,int fa)
{
	father[x]=fa;
	deep[x]=deep[fa]+1;
	for(int i=start[x];i;i=road[i].next)
	{
		int to=road[i].y;
		if(to==fa) continue;
		dfs(to,x);
	}
	return ;
}

bool check(int x,int num)
{
	if(x==0) return false;
	if(num==0) return false;
	if(Max[x]>=deep[now]-deep[x]) return true;
	return check(father[x],num-1);	
}

pair<int,int> get(int x,int num)
{
	pair<int,int> t=MP(0x3f3f3f3f,0x3f3f3f3f);
	if(x==0) return t;
	if(num==0) return t;
	if(deep[now]<=deep[x]+w[x]) t=MP(deep[x]-w[x],x);
	return min(t,get(father[x],num-1));
}
	

void add(int x,int k)
{
	if(x==0||k==0) return ;
	Max[x]=max(Max[x],k);
	add(father[x],k-1);
	return ;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for(int i=1;i<n;i++)
	{
		int p,q;
		build(p,q),build(q,p);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
		t[i]=MP(deep[i],i);
	sort(t+1,t+1+n);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		pair<int,int> tmp=t[i];
		now=tmp.second;
		bool t=check(tmp.second,100);
		if(t) continue;
		pair<int,int> k=get(tmp.second,100);
		ans++;add(k.second,w[k.second]);
	}
	printf("%d\n",ans);
	return 0;
}
