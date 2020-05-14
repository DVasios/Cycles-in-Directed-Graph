#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph
{
public:
    Graph(int V) : num_vertices(V) {
        vertice = new list<int>[num_vertices];
    };

    ~Graph() { 
        num_vertices = 0;
        delete[] vertice;
    }

    void addEdge(int u, int v) {
        vertice[u].push_back(v);
    }

    enum state { UNVISITED, SEEN, VISITED };
    void cycle_help (vector<int> &path, vector<state> &status, vector<int> &p, vector<int> &cycle, int u, bool &check) const {
        status[u] = SEEN;
        cycle.push_back(u);

        for (int v: vertice[u] ) {
            if ( status[v] == UNVISITED ) {
                p[v] = u;
                cycle_help(path, status, p, cycle, v, check);
            }
            else if ((status[v] == SEEN ) && !check) {
                
                vector<int>::iterator ptr = cycle.begin();
                while (*ptr != v) ptr++;

                for (ptr; ptr < cycle.end(); ptr++) {
                    path.push_back(*ptr);
                }

                check = true;
            }
        }
        status[u] = VISITED;
    }  

    bool cycle(vector<int> &path) const {
        
        vector<state> status(num_vertices);
        vector<int> p(num_vertices);
        vector<int> cycle;
        bool check = false;

        for (int i: status) {
            status[i] = UNVISITED;
            p[i] = -1;
        }

        for (int u = 0; u < num_vertices; ++u)  {
            if ( status[u] == UNVISITED ) {
                cycle_help(path, status, p, cycle, u, check);
            }
        }

        return check;
    }

private:
    int num_vertices;
    list<int> *vertice;
};

#ifndef CONTEST

int main() {
    int V, E;
    cin >> V >> E;
    Graph g(V);
    for (int i = 0; i < E; ++i) { 
        int u, v; 
        cin >> u >> v; 
        g.addEdge(u, v); 
    }
    vector<int> path;
    bool c = g.cycle(path);
    if (c) {
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i] << " ";
        }
    }
    cout << endl;
}

#endif

