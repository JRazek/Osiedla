#include <bits/stdc++.h>

using namespace std;

struct Vertex;

struct Edge{
    Vertex * v1;
    Vertex * v2;
    const int id;
    bool bridge = false;
    bool direction;//true for v1 to v2, false for v2 to v1
    Edge(int id, Vertex * v1, Vertex * v2): id(id), v1(v1), v2(v2){}
};

struct Vertex{
    const int id;
    bool visited = false;
    int entryTime = -1;
    int lowVal = -1;
    vector<Edge *> edges;
    Vertex(int id): id(id){}
};

struct Graph{
    const int id;
    Graph(int id): id(id){}
    vector<Vertex *> vertices;
};

struct Component{
    const int id;
    Component(int id): id(id){};
    vector<Vertex *> vertices;
};

void lowDFS(Vertex * v, Edge * comingThrough, int currentTime){
    v->visited = true;
    v->lowVal = currentTime;
    v->entryTime = currentTime;

    for(auto e : v->edges){
        if(e != comingThrough) {
            Vertex * n = e->v1 != v ? e->v1 : e->v2;
            if(n->visited != true){
                lowDFS(n, e, ++currentTime);
            }
            if(n->lowVal <= v->lowVal){
                v->lowVal = n->lowVal;
            }
            if (v->entryTime < n->lowVal){
                e->bridge = true;
                e->direction = true;
            }

            cout<<"";
        }
    }

}
void detectBridges(vector<Vertex *> vertices){
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
    lowDFS(vertices[0], NULL, 0);
    cout<<"";
}
void visitDFS(Vertex * v, Graph * g, bool * visited){
    visited[v->id] = true;
    g->vertices.push_back(v);
    for(Edge * e : v->edges){
        Vertex * n = e->v1 != v ? e->v1 : e->v2;
        if(visited[n->id] != true){
            visitDFS(n, g,  visited);
        }
    }
}

void separateComponents(Vertex * v, Component * c, bool * visited){
    visited[v->id] = true;
    c->vertices.push_back(v);
    for(Edge * e : v->edges){
        Vertex * n = e->v1 != v ? e->v1 : e->v2;
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

        Edge * e = new Edge(i, v1, v2);
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
    cout<<components.size()<<"\n";
    for(auto e : edges){
        cout << (e->direction ? ">" : "<");
    }


    cout<<"";
    return 0;
}
