#include <iostream>
#include <vector>
#include "Maze.hpp"
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    Maze m(5);
    m.createDefaultMaze();
    m.createPath(0, 3); 
    m.createPath(1, 1); 
    m.createPath(1, 2);
    m.createPath(1, 3);
    m.createPath(2, 1);
    m.createPath(2, 3); 
    m.createPath(2, 4);
    m.createPath(3, 0);
    m.createPath(3, 2);
    m.createPath(4, 1);
    m.createPath(4, 3);          
    m.printMaze();
    m.convertMazeToAdjacencyListGraph();
    m.displayEdges();

    cout << "\n" << endl;
    m.findPathThroughMaze();
    cout << "\nIs valid path?" << endl;
    cout << m.checkIfValidPath() << endl;

    return 0;
}
