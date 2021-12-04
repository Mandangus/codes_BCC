#include <bits/stdc++.h>

#define MAX 1000

using namespace std;

struct Edge{
    int src,dest,bandwidth,flow;
    Edge(int s,int d,int band,int fl): src(s),dest(d),bandwidth(band),flow(fl){}
};

struct GrafoEK{
    int n,m;
    vector<Edge> edges;
    vector<int> G[MAX];
    int a[MAX];
    int b[MAX];
    bool visitado[MAX];


    void init(int n){
        for (int i = 0; i <= n; i++)
        {
            G[i].clear();
        }
        edges.clear();
    }


    void addEdge(int src,int dest,int band){
        edges.push_back(Edge(src,dest,band,0));
        edges.push_back(Edge(dest,src,band,0));
        m = edges.size();
        G[src].push_back(m-2);
        G[dest].push_back(m-1);
    }

    bool bfs(int comeco,int fim){
        memset(visitado,false,sizeof(visitado));
        queue<int> q;
        q.push(comeco);
        b[comeco] = 0;
        visitado[comeco] = true;
        while (!q.empty())
        {
            int frente = q.front();
            q.pop();
            for (int i = 0; i < (int)G[frente].size(); i++)
            {
                Edge &e = edges[G[frente][i]];
                if(!visitado[e.dest] && e.bandwidth > e.flow){
                    visitado[e.dest] = true;
                    b[e.dest] = b[frente] + 1;
                    q.push(e.dest);
                }
            }
            
        }
        return visitado[fim];
    }

    int dfs(int comeco,int fim,int ma){
        if(comeco == fim || ma == 0) return ma;

        int f, flow = 0;
        for (int &i = a[comeco]; i < (int)G[comeco].size(); i++)
        {
            Edge &e = edges[G[comeco][i]];
            if(b[comeco] + 1 == b[e.dest] && (f = dfs(e.dest,fim,min(ma,e.bandwidth - e.flow)))){
                e.flow += f;
                edges[G[comeco][i]^1].flow -= f;
                flow += f;
                ma -= f;
                if(ma == 0) break;
            }
        }
        return flow;
    }

    int maxFlow(int comeco, int fim){
        int flow = 0;
        while (bfs(comeco,fim))
        {
            memset(a,0,sizeof(a));
            flow += dfs(comeco,fim,100000);
        }
        return flow;
    }

};


int main(){

    GrafoEK grafo;

    int caso = 1;
    int numNodes,src,dest,numEdges;

    while(cin >> numNodes && numNodes != 0)
    {
        grafo.init(numNodes);
        cin >> src >> dest >> numEdges;
        for (int i = 0; i < numEdges; i++)
        {
            int srcNode,destNode,band;
            cin >> srcNode >> destNode >> band;
            grafo.addEdge(srcNode,destNode,band);
        }
         
        cout << "Network " << caso << endl;
        printf("The bandwidth is %d.\n\n",grafo.maxFlow(src,dest));
        caso++;
    }
    
    return 0;
}