#ifndef MAZE_H
#define MAZE_H
#include<vector>
#include<iostream>
using namespace std;

struct vertex;
struct adjVertex{
    vertex *v;
};

struct vertex{

    int num;
    bool visited = false;
    vector<adjVertex> adj;
};

class Maze
{
    public:
        Maze(int n = 0); 
        ~Maze(); 
        void createDefaultMaze();
        void createPath(int i, int j);
        void printMaze(); 
        int findVertexNumFromPosition(int x, int y);
        void addVertex(int num);
        void addEdge(int v1, int v2);
        void displayEdges();
        vector<int> findOpenAdjacentPaths(int x, int y);
        void convertMazeToAdjacencyListGraph(); 
        bool checkIfValidPath();
        bool findPathThroughMaze(); 

    private:
        int n;
        int ** maze; 
        vector<int> path; 
        vector<vertex*> vertices; //Graph of Vertices from Maze
};

#endif // MAZE_H
