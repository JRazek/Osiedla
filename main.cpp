#include <bits/stdc++.h>

using namespace std;

struct Vertex;

struct Edge{
    const Vertex * v1;
    const Vertex * v2;
    bool bridge = false;
    bool direction;//true for v1 to v2, false for v2 to v1
    Edge(Vertex * v1, Vertex * v2): v1(v1), v2(v2){}
};

struct Vertex{
    const int id;
    vector<Edge *> edges;
    Vertex(int id): id(id){}
};

struct Graph{
    const int id;
    Graph(int id): id(id){}
    vector<const Vertex *> vertices;
};

struct Component{
    const int id;
    Component(int id): id(id){};
    vector<const Vertex *> vertices;
};

void lowDFS(const Vertex * v, int * parentTable, bool * visitedTab, int currentTime, int * lowTab, int * entryTimeTab){
    visitedTab[v->id] = true;
    lowTab[v->id] = currentTime;
    entryTimeTab[v->id] = currentTime;
    for(auto e : v->edges){
        const Vertex * n = e->v1 != v ? e->v1 : e->v2;
        if(parentTable[n->id] != v->id){
            if(visitedTab[n->id] == false){
                parentTable[n->id] = v->id;
                lowDFS(n, parentTable, visitedTab, ++currentTime, lowTab, entryTimeTab);
            }

            int ltv = lowTab[v->id];
            int ltn = lowTab[n->id];

            int entryTimeV = entryTimeTab[v->id];
            int entryTimeN = entryTimeTab[n->id];

            if(ltn <= ltv){
                lowTab[v->id] = lowTab[n->id];
            }else{
                e->bridge = true;
            }
        }
    }
}
void detectBridges(vector<const Vertex *> vertices){
    bool visited[vertices.size()];
    int entry[vertices.size()];
    int low[vertices.size()];
    int parents[vertices.size()];
    for(int i = 0; i < vertices.size(); i ++){
        visited[i] = false;
        entry[i] = -1;
        low[i] = -1;
        parents[i] = -1;
    }
    vector<Edge *> bridges;
    lowDFS(vertices[0], parents, visited, 0, low, entry);
    cout<<"";
}
void visitDFS(const Vertex * v, Graph * g, bool * visited){
    visited[v->id] = true;
    g->vertices.push_back(v);
    for(Edge * e : v->edges){
        const Vertex * n = e->v1 != v ? e->v1 : e->v2;
        if(visited[n->id] != true){
            visitDFS(n, g,  visited);
        }
    }
}

void separateComponents(const Vertex * v, Component * c, bool * visited){
    visited[v->id] = true;
    c->vertices.push_back(v);
    for(Edge * e : v->edges){
        const Vertex * n = e->v1 != v ? e->v1 : e->v2;
        if(visited[n->id] != true){
            if(!e->bridge) {
                e->direction = e->v1 == v;
                separateComponents(n, c, visited);
            }
        }
    }
}

int main() {
    int verticesCount, edgesCount;
    cin >> verticesCount >> edgesCount;
    vector<Vertex *> vertices;
    vector<Edge *> edges;


    for(int i = 0; i < verticesCount; i ++){
        vertices.push_back(new Vertex(i));
    }
    for(int i = 0; i < edgesCount; i ++){
        int id1, id2;
        cin >> id1 >> id2;
        id1--;
        id2--;

        Vertex * v1 = vertices[id1];
        Vertex * v2 = vertices[id2];

        Edge * e = new Edge(v1, v2);
        edges.push_back(e);

        v1->edges.push_back(e);
        v2->edges.push_back(e);
    }

    //separate graphs
    vector<Graph *> graphs;
    bool visited[verticesCount];
    for(auto &v : visited){
        v = false;
    }

    for(auto v : vertices){
        if(visited[v->id] == false){
            graphs.push_back(new Graph(graphs.size()));
            visitDFS(v, graphs.back(), visited);
        }
    }
    for(auto g : graphs) {
        detectBridges(g->vertices);
        cout<<"";
    }

    vector<Component *> components;
    for(auto &v : visited){
        v = false;
    }

    for(auto v : vertices){
        if(visited[v->id] == false){
            components.push_back(new Component(components.size()));
            separateComponents(v, components.back(), visited);
        }
    }
    cout<<components.size();
    for(auto e : edges){
        cout << (e->direction ? ">" : "<");
    }


    cout<<"";
    return 0;
}
