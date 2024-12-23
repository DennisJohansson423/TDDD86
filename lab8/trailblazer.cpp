// Our implementation of the DFS, BFS, Dijkstra's, and A* search algorithms

#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"
#include <queue>

using namespace std;

// Function to build the path from the end node to the start node
vector<Node *> buildPath(BasicGraph& graph, Node* node) {
    vector<Node*> path;
    // Traverse the path from the end to the start
    for (auto currNode = node; currNode != nullptr; currNode = currNode->previous) {
        path.insert(path.begin(), currNode);
    }
    return path;
}

// DFS algorithm
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    return innerDepthFirstSearch(graph, start, end);
}

// Inner function for DFS
vector<Node *> innerDepthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    if (!start || !end) {
        return {};
    }
    if (start == end) {
        return buildPath(graph, end);
    }
    start->visited = true;
    start->setColor(GREEN);

    // Explore each neighboring node
    for (auto edge : start->arcs) {
        auto tempNode = edge->finish;
        if (!tempNode->visited) {
            tempNode->previous = start;
            auto temp = innerDepthFirstSearch(graph, tempNode, end);
            if (!temp.empty()) {
                return temp;
            }
        }
    }
    start->setColor(GRAY);
    return {};
}

// BFS algorithm
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    queue<Node *> queue;
    start->visited = true;
    queue.push(start);
    start->cost = 0;

    // Explore the nodes in breadth first order
    while (!queue.empty()) {
        auto currentNode = queue.front();
        currentNode->setColor(GREEN);
        queue.pop();
        if (currentNode == end) {
            return buildPath(graph, currentNode);
        }
        // Explore each neighboring node
        for (auto edge : currentNode->arcs) {
            auto nextNode = edge->finish;
            if (!nextNode->visited) {
                nextNode->visited = true;
                nextNode->previous = currentNode;
                nextNode->cost = edge->cost + currentNode->cost;
                queue.push(nextNode);
                nextNode->setColor(YELLOW);
            }
        }
    }
    return {};
}

// Dijkstras Algorithm
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    PriorityQueue<Node*> pQueue;

    auto nodes = graph.getNodeSet();

    // Initialize costs to infinity
    for (auto n : nodes) {
        n->cost = numeric_limits<double>::infinity();
    }
    start->cost = 0;
    start->visited = true;
    start->setColor(YELLOW);
    pQueue.enqueue(start, start->cost);

    // Explore nodes with lowest cost first
    while (!pQueue.isEmpty()) {
        auto tempNode = pQueue.dequeue();
        tempNode->visited = true;
        tempNode->setColor(GREEN);

        if (tempNode == end) {
            return buildPath(graph, end);
        }

        // Update costs and enqueue neighboring nodes
        for (auto edge : tempNode->arcs) {
            auto n = edge->finish;
            if (!n->visited) {
                auto tempCost = tempNode->cost + edge->cost;
                if (tempCost < n->cost) {
                    n->cost = tempCost;
                    n->previous = tempNode;
                    pQueue.enqueue(n, n->cost);
                    n->setColor(YELLOW);
                }
            }
        }
    }
    return {};
}

// A* Algorithm
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    PriorityQueue<Vertex*> openSet;
    start->visited = true;
    start->setColor(YELLOW);

    vector<Vertex*> path;
    openSet.enqueue(start, 0);

    auto nodes = graph.getNodeSet();

    // Initialize costs to infinity
    for (auto n : nodes) {
        n->cost = numeric_limits<double>::infinity();
    }
    start->cost = 0;

    // Explore nodes based on estimated total cost
    while (!openSet.isEmpty()) {
        // Dequeue node with the lowest estimated total cost
        Vertex* current = openSet.dequeue();
        if (current == end) {
            return buildPath(graph, end);
        }

        // Update costs and enqueue neighboring nodes
        for (auto edge : current->arcs) {
            Vertex* n = edge->finish;
            double temp_gScore = current->cost + edge->cost;

            if (temp_gScore < n->cost) {
                n->previous = current;
                n->cost = temp_gScore;
                double fScore = temp_gScore + n->heuristic(end);

                if (!n->visited) {
                    n->visited = true;
                    openSet.enqueue(n, fScore);
                    n->setColor(YELLOW);
                } else {
                    openSet.changePriority(n, fScore);
                }
            }
        }
        current->setColor(GREEN);
    }
    return {};
}
