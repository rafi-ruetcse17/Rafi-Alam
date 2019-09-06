#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[100005],tree[400005];

void build(ll node,ll lo,ll hi)
{
    if(lo==hi)
    {
        tree[node]=a[lo]*a[lo];
        return;
    }
    ll left=node*2,right=left+1;
    ll mid=(lo+hi)/2;
    build(left,lo,mid);
    build(right,mid+1,hi);

    tree[node]=tree[left]+tree[right];
}



void update1(ll node,ll lo,ll hi,ll i,ll j,ll x)
{
    if(lo>j||hi<i)
        return;
    if(lo>=i&&hi<=j&&hi==lo)
    {
        tree[node]=x;
        return ;
    }
    ll left=node*2,right=left+1;
    ll mid=(lo+hi)/2;
    update1(left,lo,mid,i,j,x);
    update1(right,mid+1,hi,i,j,x);

    tree[node]=tree[left]+tree[right];
}

void update2(ll node,ll lo,ll hi,ll i,ll j,ll x)
{

    if(lo>j||hi<i)
        return;
    if(lo>=i&&hi<=j&&lo==hi)
    {
        tree[node]+=x;
        tree[node]*=tree[node];
        return ;
    }
    ll left=node*2,right=left+1;
    ll mid=(lo+hi)/2;
    update2(left,lo,mid,i,j,x);
    update2(right,mid+1,hi,i,j,x);

    tree[node]=tree[left]+tree[right];
}

ll query(ll node,ll lo,ll hi,ll i,ll j)
{

    if(lo>j||hi<i)
        return 0;
    if(lo>=i&&hi<=j)
        return tree[node];
    ll left=node*2,right=left+1;
    ll mid=(lo+hi)/2;
    ll p=query(left,lo,mid,i,j);
    ll q=query(right,mid+1,hi,i,j);
    return p+q;
}

int main()
{
    ll t,cs=0;
    cin >> t;
    while(t--)
    {
        memset(tree,0,sizeof(tree));
        ll n,q;
        cin >> n >> q;
        for(ll i=1;i<=n;i++)
            scanf("%lld",&a[i]);
        build(1,1,n);
        ll type,st,nd,x;
        printf("Case %lld:\n",++cs);
        for(ll i=1;i<=q;i++)
        {
            scanf("%lld",&type);
            if(type==0)
            {
                scanf("%lld %lld %lld",&st,&nd,&x);
                update1(1,1,n,st,nd,x*x);
            }
            else if(type==1)
            {
                scanf("%lld %lld %lld",&st,&nd,&x);
                update2(1,1,n,st,nd,x*x);
            }
            else
            {
                scanf("%lld %lld",&st,&nd);
                ll ans=query(1,1,n,st,nd);
                printf("%lld\n",ans);
            }
        }
    }
}
