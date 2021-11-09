#include "Maze.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

Maze::Maze(int n){
    this->n = n; 
}

void Maze::addEdge(int v1, int v2){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->num == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j]->num == v2 && i != j){
                    for(int x = 0; x < vertices[i]->adj.size(); x++){
                        if(vertices[i]->adj[x].v->num == v2){
                            return;
                        }
                    }
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);

                    return;
                }
            }
        }
    }
}

void Maze::addVertex(int num){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->num == n){
            found = true;
        }
    }
    if(found == false){
        vertex * v = new vertex;
        v->num = n;
        vertices.push_back(v);
    }
}

void Maze::displayEdges(){
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i] << " --> ";
        for(int x = 0; x < vertices[i]->adj.size(); x++){
            cout << vertices[i]->adj[x].v->num << " ";
        }
        cout << endl;
    }
}

int Maze::findVertexNumFromPosition(int x, int y){
    return y + n * x;
}

// Creates a default maze of all 1s of size n x n, except for positions (0,0) and (n-1, n-1)
void Maze::createDefaultMaze(){
    
    for(int i = 0; i < n; i++){
        int *x = new int[n];
        for(int j = 0; j < n; j++){
            x[j] = 1;
        }
        maze[i] = x;
    }

}

void Maze::createPath(int i, int j){
    maze[i][j] = 0;
}

void Maze::printMaze(){
    if (n > 0){
        for(int x = 0; x < n; x++){
            for(int i = 0; i < n; i++){
                if(i == 0){
                   cout << "| " << maze[i]; 
                }else if(i == n-1){
                    cout << " | " << maze[i] << " |";
                }else{
                    cout << " | " << maze[i]; 
                }
            }
            cout << endl;
        }
    }
}

vector<int> Maze::findOpenAdjacentPaths(int x, int y){
    // identify the open paths that are adjacent to the vertex at x, y
    // fill adjArr array with the numbers of the adjacent vertices
    vector<int> neighbors; 
    for(int i = x-1; i <= x + 1; i++){
        if(i < 0 || i >= n){
            continue;
        }
        for(int j = y-1; j <= y+1; j++){
            if(j < 0 || j >= n){
                continue;
            }
            // if there is an open path at this adjacent position, add to adjArray
            if(!(i == x && j == y) && maze[i][j] == 0){
                neighbors.push_back(findVertexNumFromPosition(i, j));
            }
        }
    }
    return neighbors;
}

void Maze::convertMazeToAdjacencyListGraph(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int openVector = findVertexNumFromPosition(i, j);
            if(maze[i][j] == 0){
                addVertex(openVector);
            }
        }
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int openVector = findVertexNumFromPosition(i, j);
            if(maze[i][j] == 0){
                vector<int> v = findOpenAdjacentPaths(i, j);
                for(int i = 0; i < v.size(); i++){
                    addVertex(v[i]);
                    addEdge(openVector, v[i]);
                }
            }
        }
    }
}

bool Maze::findPathThroughMaze(){

    
    return false; 
}


bool Maze::checkIfValidPath(){
    if(path[0] = 0 && path[path.size()-1] == (n^2-1)){
        for(int i = 0; i < path.size()-1; i++){
            for(int i = 0; i < path[i].adj)
            if(path[i+1] != path[i].adj){
                return false;
            }
        }
    }
    return false; 
}

Maze::~Maze(){
    if (n > 0){
        for(int i = 0; i < n; i++){
            delete[] maze[i];
        }
        delete[] maze;
    }
    for (unsigned int i = 0; i< vertices.size(); i++){
        delete vertices[i]; 
    }
}
