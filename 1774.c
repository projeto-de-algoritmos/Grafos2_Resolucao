#include <iostream>
#include <algorithm>

struct Edge
{
int v;
int w;
int p;
};

Edge g[205];
int p[65];

bool compare(const Edge &a, const Edge &b)
{
return a.p < b.p;
}

int parent(int i)
{
if (i == p[i])
return i;
return parent(p[i]);
}

int kruskal(int c)
{
int i, mst, v, w;

for (i = 0, mst = 0; i < c; i++)
{
    v = parent(g[i].v);
    w = parent(g[i].w);

    if (v != w)
    {
        p[v] = p[w];
        mst += g[i].p;
    }
}

return mst;
}

int main()
{
int r, c, i;

std::cin >> r >> c;

for (i = 0; i < c; i++)
{
    std::cin >> g[i].v >> g[i].w >> g[i].p;
}

std::sort(g, g + c, compare);
for (i = 1; i <= r; i++)
    p[i] = i;

std::cout << kruskal(c) << std::endl;

return 0;
}