#include "Graph.h"
#include <algorithm>

Graph::Graph() : nodes(0), edges(0) {}

Graph::Graph(const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Fehler: Datei konnte nicht geoffnet werden." << endl;
        exit(1);
    }

    if (!(file >> nodes >> edges)) {
        cout << "Der Graph ist leer." << endl;
        nodes = 0;
        edges = 0;
        return;
    }

    adjList.resize(nodes);

    for (int i = 0; i < edges; ++i) {
        int source, destination, weight;
        if (!(file >> source >> destination >> weight)) {
            cout << "Fehler beim Lesen der Kanten." << endl;
            break;
        }
        adjList[source].emplace_back(destination, weight);
    }

    file.close();
}

void Graph::printAdjList() {
    if (nodes == 0) {
        cout << "Der Graph ist leer." << endl;
        return;
    }

    cout << "Adjazenzliste mit Gewichten:" << endl;
    for (int source = 0; source < nodes; ++source) {
        cout << source << ": ";

        // parcurgem vecinii acelui nod
        for (const auto& [destination, weight] : adjList[source]) {
            cout << "(" << destination << ", Gewicht: " << weight << ") ";
        }
        cout << endl;
    }
}

void Graph::shortestPath(int source, int destination) {
    if (nodes == 0 || edges == 0) {
        cout << "Der Graph ist leer." << endl;
        return;
    }

    vector<int> dist(nodes, std::numeric_limits<int>::max());
    vector<int> parent(nodes, -1);// Păstrăm părinții pentru reconstrucția drumului
    dist[source] = 0;

    //cautam sa gasim dist mai mici folosind muchille existinse
    for (int i = 0; i < nodes - 1; ++i) {
        for (int sourceNode = 0; sourceNode < nodes; ++sourceNode) {
            for (const auto& [destinationNode, weight] : adjList[sourceNode]) {
                // daca gasim drum mai scurt => act dist
                if (dist[sourceNode] != std::numeric_limits<int>::max() && dist[sourceNode] + weight < dist[destinationNode]) {
                    dist[destinationNode] = dist[sourceNode] + weight;
                    parent[destinationNode] = sourceNode;
                }
            }
        }
    }
//verificam dacă există un ciclu negativ
    for (int sourceNode = 0; sourceNode < nodes; ++sourceNode) {
        for (const auto& [destinationNode, weight] : adjList[sourceNode]) {
            // daca mai putem îmbunatati distanțele, inseamna ca ex  un ciclu negativ
            if (dist[sourceNode] != std::numeric_limits<int>::max() && dist[sourceNode] + weight < dist[destinationNode]) {
                cout << "Negativer Zyklus entdeckt" << endl;
                return;
            }
        }
    }

    if (dist[destination] == std::numeric_limits<int>::max()) {
        cout << "Kein Weg von " << source << " zu " << destination << endl;
        return;
    }
//dest->surs
    vector<int> path;
    for (int at = destination; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    cout << "Kurzester Weg von " << source << " zu " << destination << ":" << endl;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int sourceNode = path[i], destinationNode = path[i + 1];
        for (const auto& [neighbor, weight] : adjList[sourceNode]) {
            if (neighbor == destinationNode) { //cautam muchia corectă
                cout << sourceNode << " -> " << destinationNode << " (Gewicht: " << weight << ")" << endl;
                break;
            }
        }
    }

    cout << "Gesamtkosten: " << dist[destination] << endl;
}
