#include "Graph.h"

int main() {
    cout << "Test date1.in\n";
    Graph g1("C:\\Users\\Alesia\\CLionProjects\\712\\alg_graf4\\date1.in");
    g1.printAdjList();
    g1.shortestPath(0, 3);

    cout << "\nTest date2.in\n";
    Graph g2("C:\\Users\\Alesia\\CLionProjects\\712\\alg_graf4\\date2.in");
    g2.printAdjList();
    g2.shortestPath(0, 2);

    return 0;
}
