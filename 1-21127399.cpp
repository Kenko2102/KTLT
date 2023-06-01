#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
// Declare struct for a tree
struct Tree {
    float x;
    float y;
    int type; // 0-coffee, 1-tea
};

// Declare struct for a point
struct Point {
    float x;
    float y;
};

// Declare struct for the plantation
struct Plantation {
    int numTrees;
    Tree trees[100]; // Assume a maximum of 100 trees
};

// Count trees of a specific type
int countTrees(const Plantation& p, int type) {
    int count = 0;
    for (int i = 0; i < p.numTrees; i++) {
        if (p.trees[i].type == type) {
            count++;
        }
    }
    return count;
}

// Count coffee trees
int countCoffeeTrees(const Plantation& p) {
    return countTrees(p, 0);
}

// Count tea trees
int countTeaTrees(const Plantation& p) {
    return countTrees(p, 1);
}
// Find upper left point
Point findUpperLeft(const Plantation& p) {
    Point upperLeft;
    upperLeft.x = p.trees[0].x;
    upperLeft.y = p.trees[0].y;

    for (int i = 1; i < p.numTrees; i++) {
        if (p.trees[i].x < upperLeft.x) {
            upperLeft.x = p.trees[i].x;
        }
        if (p.trees[i].y > upperLeft.y) {
            upperLeft.y = p.trees[i].y;
        }
    }

    return upperLeft;
}

// Find lower right point
Point findLowerRight(const Plantation& p) {
    Point lowerRight;
    lowerRight.x = p.trees[0].x;
    lowerRight.y = p.trees[0].y;

    for (int i = 1; i < p.numTrees; i++) {
        if (p.trees[i].x > lowerRight.x) {
            lowerRight.x = p.trees[i].x;
        }
        if (p.trees[i].y < lowerRight.y) {
            lowerRight.y = p.trees[i].y;
        }
    }

    return lowerRight;
}

// Calculate perimeter of rectangular fence
float calcFenceLength(const Plantation& p) {
    Point upperLeft = findUpperLeft(p);
    Point lowerRight = findLowerRight(p);

    float length = 2 * (lowerRight.x - upperLeft.x) + 2 * (upperLeft.y - lowerRight.y);
    return length;
}

// Find position of the pump (center of all trees)
Point findPump(const Plantation& p) {
    Point pump;
    float sumX = 0.0;
    float sumY = 0.0;

    for (int i = 0; i < p.numTrees; i++) {
        sumX += p.trees[i].x;
        sumY += p.trees[i].y;
    }

    pump.x = sumX / p.numTrees;
    pump.y = sumY / p.numTrees;

    return pump;
}

// Calculate distance between two points
float distance(const Point& p, const Point& q) {
    return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
}

// Convert tree to point
Point treeToPoint(const Tree& t) {
    Point p;
    p.x = t.x;
    p.y = t.y;
    return p;
}

// Calculate total length of tubes
float calculateTotalLength(const Plantation& p) {
    Point pump = findPump(p);
    float totalLength = 0.0;

    for (int i = 0; i < p.numTrees; i++) {
        float dist = distance(treeToPoint(p.trees[i]), pump);
        totalLength += dist;
    }

    return totalLength;
}

int main() {
    Plantation p;
    ifstream inputFile("Plantation.in");
    ofstream outputFile("NongTrai.out");

    // Read number of trees
    inputFile >> p.numTrees;

    // Read tree information
    for (int i = 0; i < p.numTrees; i++) {
        inputFile >> p.trees[i].x >> p.trees[i].y >> p.trees[i].type;
    }

    // Count tree types
    int coffeeCount = countCoffeeTrees(p);
    int teaCount = countTeaTrees(p);

    // Calculate fence length
    float fenceLength = calcFenceLength(p);

    // Calculate total tube length
    float totalTubeLength = calculateTotalLength(p);

    // Write output to file
    outputFile << coffeeCount << " " << teaCount << endl;
    outputFile << fixed << setprecision(2) << fenceLength << endl;
    outputFile << fixed << setprecision(2) << totalTubeLength << endl;

    // Close files
    inputFile.close();
    outputFile.close();

    return 0;
}
