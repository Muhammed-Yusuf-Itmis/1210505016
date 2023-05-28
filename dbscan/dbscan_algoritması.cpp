#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 100

struct Point {
    double x;
    double y;
};

struct Point points[MAX_POINTS]; 
int visited[MAX_POINTS]; 
int cluster[MAX_POINTS]; 

int numPoints; 
double epsilon;
int minPts; 

double calculateDistance(struct Point p1, struct Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

int regionQuery(int pointIndex) {
    int neighbors = 0;
    int i;
    for (i = 0; i < numPoints; i++) {
        if (calculateDistance(points[pointIndex], points[i]) <= epsilon) {
            neighbors++;
        }
    }
    return neighbors;
}

void expandCluster(int pointIndex, int clusterNumber) {
    int i;
    cluster[pointIndex] = clusterNumber;

    for (i = 0; i < numPoints; i++) {
        if (visited[i] == 0) {
            visited[i] = 1;
            int neighbors = regionQuery(i);
            if (neighbors >= minPts) {
                expandCluster(i, clusterNumber);
            }
        }
    }
}

void DBSCAN() {
    int clusterNumber = 1;
    int i;
    for (i = 0; i < numPoints; i++) {
        if (visited[i] == 0) {
            visited[i] = 1;
            int neighbors = regionQuery(i);
            if (neighbors < minPts) {
                cluster[i] = -1; // Gürültü noktasý
            } else {
                expandCluster(i, clusterNumber);
                clusterNumber++;
            }
        }
    }
}

int main() {
 
    numPoints = 10;
    epsilon = 1.0;
    minPts = 3;

  
    DBSCAN();

    int i;
    for (i = 0; i < numPoints; i++) {
        printf("Point (%lf, %lf) - Cluster: %d\n", points[i].x, points[i].y, cluster[i]);
    }

    return 0;
}
