#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <stack>
#include <cstring>

#define max_node 1000
using namespace std;

struct Node{

     int id;
     int parent_value;
     bool operator<(const Node& rhs) const
	   {
	    	return parent_value > rhs.parent_value;
       }
};

struct Edge{

     int u;
     int v;
     int length;
};

int ver_num, edge_num;
vector<Edge> Graph[max_node];
int roadkeep[max_node];
bool visit[max_node];
int dis[max_node];
void set_edge(int u, int v, int length)
{
     Graph[u].push_back(Edge{ u,v,length });
     Graph[v].push_back(Edge{ v,u,length });
}

bool dijkstra(int start, int destination)
{
    memset(roadkeep, -1, sizeof(roadkeep));
    memset(visit, false,sizeof(visit));
    for(int i = 0; i< max_node ;i++) dis[i] = INT_MAX;

    priority_queue<Node> PQ;
    PQ.push(Node{start,0});
    dis[start] = 0;

    while(!PQ.empty())
    {
        Node tmp = PQ.top();
        PQ.pop();
        if(visit[tmp.id]) continue;
        visit[tmp.id] = true;
        if(tmp.id == destination) return true;

        for(int i = 0; i < Graph[tmp.id].size(); i++)
        {
            if(dis[Graph[tmp.id][i].v] > dis[tmp.id] + Graph[tmp.id][i].length )
            {
                dis[Graph[tmp.id][i].v] = dis[tmp.id] + Graph[tmp.id][i].length;
                roadkeep[Graph[tmp.id][i].v] = tmp.id;
                PQ.push(Node{Graph[tmp.id][i].v,dis[Graph[tmp.id][i].v]});
            }
        }
    }
    return false;
}

void print_ans(int start , int destanation)
{
    stack<int> R;
    int last = destanation;
    while(roadkeep[destanation]!= start)
    {
        R.push(roadkeep[destanation]);
        destanation = roadkeep[destanation];
    }
    R.push(start);
    while(!R.empty())
    {
        int top = R.top();
        R.pop();
        cout<<top<<"->";
    }
    cout << last;
}

int main()
{
    int id_1,id_2,len;
    cin>>ver_num>>edge_num;
    for(int i = 0; i < edge_num ; i++)
    {
        cin>>id_1>>id_2>>len;
        set_edge(id_1,id_2,len);
    }
    int num;
    while(cin>>num)
    {
        bool ans = false;
        for(int i = 1 ; i <=ver_num ;i++)
        {
            if(i != num)
            {
            ans = dijkstra(num,i);
            print_ans(num,i);
            cout << " " << dis[i] << endl;
            }

        }

    }

//       for(int i = 1; i <= ver_num ; i++)
//    {
//        for(int j = 0;j<E[i].size();j++)
//        cout<<E[i][j].u<<" "<<E[i][j].v<<" "<<E[i][j].length<<endl;
//    }


    return 0;
}
