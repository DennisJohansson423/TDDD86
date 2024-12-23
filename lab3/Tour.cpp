//This is our implementation of a solution for the TSP problem.
//Denjo163, Anthu456

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

//Create an empty tour.
Tour::Tour() {}

//Free all the memory that is used by list nodes.
Tour::~Tour() {
    if (front != nullptr) {
        Node* current = front;
        while (current->next != front) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        delete current;
        front = nullptr;
    }
}

//Print out the tour.
void Tour::show() {
    if (front == nullptr) {
        return;
    } else {
        Node* current = front;
        do {
            Node* next = current;
            cout << current -> point << endl;
            current = current -> next;
        } while (current != front);
    }
}

//Draw the tour.
void Tour::draw(QGraphicsScene *scene) {
    if (front == nullptr) {
        return;
    } else {
        Node* current = front;
        do {
            current -> point.drawTo(current -> next -> point, scene);
            current = current -> next;
        } while (current != front);
    }
}

//Count the number of points in the tour.
int Tour::size() {
    int size = 0;
    if (front == nullptr) {
        size = 0;
    } else {
        Node* current = front;
        do {
            size++;ont == nullptr) {
                front
            current = current -> next;
        } while (current != front);
    }
    cout << "The size of the tour is: " << size << endl;
}

//Return the total distance of the tour.
double Tour::distance() {
    double distance = 0;
    if (front == nullptr) {
        distance = 0;
    } else {
        Node* current = front;
        do {
            distance += current -> point.distanceTo(current -> next -> point);
            current = current -> next;
        } while (current != front);
    }
    return distance;
}

//Insert p by using the nearest neighbour.
void Tour::insertNearest(Point p) {
    double shortestDistance = 0;
    if (front == nullptr) {
        front = new Node(p, nullptr);
        front -> next = front;
        return;
    } else {
        Node* current = front;
        Node* nearestNode = current;
        do {
            double tempDistance = current -> point.distanceTo(p);
            if (tempDistance <= shortestDistance || shortestDistance == 0) {
                shortestDistance = tempDistance;
                nearestNode = current;
            }
            current = current -> next;
        } while (current != front);
        Node* currentNode = new Node(p, nearestNode -> next);
        nearestNode -> next = currentNode;
    }
}

//Insert p by using the smallest increase.
void Tour::insertSmallest(Point p) {
    double shortestTour = 0;
    if (front == nullptr) {
        front = new Node(p, nullptr);
        front -> next = front;
        return;
    } else {
        Node* current = front;
        Node* nearestNode = current;
        do {
            double firstTour = current -> point.distanceTo(current -> next -> point);
            double newTour = p.distanceTo(current -> point) + p.distanceTo(current -> next -> point);
            double finalTour = newTour - firstTour;
            if (finalTour <= shortestTour || shortestTour == 0) {
                shortestTour = finalTour;
                nearestNode = current;
            }
            current = current -> next;
        } while (current != front);
        Node* currentNode = new Node(p, nearestNode -> next);
        nearestNode -> next = currentNode;
    }
}
