#include <iostream>
#include <vector>
#include <queue>

#define MAX 10005
#define INF 9999999

using namespace std;

vector<vector<int>> v;
vector<int> d;

int inc(int a)
{
    return a + 1;
}

int inv(int a)
{
    int r = 0;
    while (a)
    {
        r *= 10;
        r += a % 10;
        a /= 10;
    }
    return r;
}

void init()
{
    v.assign(MAX, vector<int>());
    for (int i = 0; i < MAX; i++)
    {
        v[i].push_back(inc(i));
        v[i].push_back(inv(i));
    }
}

void dijkstra(int a)
{
    d.assign(MAX, INF);
    d[a] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, a));

    while (!pq.empty())
    {
        pair<int, int> u = pq.top();
        pq.pop();
        int w = u.second;
        if (w < MAX)
        {
            for (int i = 0; i < v[w].size(); i++)
            {
                int vx = v[w][i];
                if (vx < MAX - 1 && d[vx] > u.first + 1)
                {
                    d[vx] = u.first + 1;
                    pq.push(make_pair(d[vx], vx));
                }
            }
        }
    }
}

int main(void)
{
    int t, a, b;

    init();

    cin >> t;

    while (t--)
    {
        cin >> a >> b;
        d.clear();
        dijkstra(a);
        cout << d[b] << endl;
    }

    v.clear();

    return 0;
}
