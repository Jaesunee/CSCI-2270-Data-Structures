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
        if(vertices[i]->num == num){
            found = true;
        }
    }
    if(found == false){
        vertex * v = new vertex;
        v->num = num;
        vertices.push_back(v);
    }
}

void Maze::displayEdges(){
    cout << endl<<"Adjacency List Graph:" << endl;
    
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i]->num << " --> ";
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
    
    maze = new int*[n];
    for(int i = 0; i < n; i++){
        maze[i] = new int[n];
        for(int j = 0; j < n; j++){
            maze[i][j] = 1;
        }
    }
    
    maze[0][0] = 0;
    maze[n - 1][n-1] = 0;
}

void Maze::createPath(int i, int j){
    maze[i][j] = 0;
}

void Maze::printMaze(){

    cout<< "Maze of size (" <<n << "x" << n << ")" << endl;
    if (n > 0){
        for(int x = 0; x < n; x++){
            for(int i = 0; i < n; i++){
                if(i == 0){
                   cout << "| " << maze[x][i]; 
                }else if(i == n-1){
                    cout << " | " << maze[x][i] << " |";
                }else{
                    cout << " | " << maze[x][i]; 
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

bool depthFirstTraversal(vertex* v, int n, vector<int>& path){
    cout << "Reached vertex: " << v->num << endl; 
    v->visited = true;

    if(v->num == ((n*n)-1))
    {
        return true;
    }

    for(int i = 0; i < v->adj.size(); i++){
        if(v->adj[i].v->visited != true){
            path.push_back(v->adj[i].v->num);

            if(depthFirstTraversal(v->adj[i].v, n, path) == true){
                return true;
            }
            cout << "Backtracked to vertex: " << v->num << endl;
            path.pop_back();
        }
    }
    return false;
}

bool Maze::findPathThroughMaze(){
    cout << "Starting at vertex: 0" << endl; 
    path.push_back(0);

    if(depthFirstTraversal(vertices[0], n, path) == false){
        return false;
    }
    
    return checkIfValidPath();
}



bool Maze::checkIfValidPath(){

    if(path[0] == 0 && path[path.size()-1] == (n*n-1)){
        for(int i = 0; i < path.size()-1; i++){
            int row = path[i] / n;
            int col = path[i] % n;
            bool valid = false;
            vector<int> openAdjNodes = findOpenAdjacentPaths(row, col); 

            for(int j = 0; j < openAdjNodes.size(); j++){
                if(path[i + 1] == openAdjNodes[j]){
                    valid = true;
                }
            }
            
            if(!valid){
                
                return false;
                
            }
        }
        return true;
    }else{

        return false;
    }
    
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
