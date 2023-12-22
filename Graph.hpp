#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <limits>
#include <chrono>
class Graph{
private:
    int vertices_number;
    float min_distance;
    std::vector<int> best_route;
    std::vector<std::pair<int,int>> vertices_list;
    std::vector<std::vector<float>> adjacency_matrix;
    int ants_number;
    int iterations;
public:
    Graph();
    ~Graph();
    void initRandomGraph(int vertices_number, int range);
    void saveGraphToFile(const char* filename);
    void initGraphFromFile(const char* filename);
    void generateAdjacencyMatrix();
    void printGraph();
    void greedyTSP();
    std::vector<std::vector<float>> getAdjacencyMatrix();
    void antColonySystem(int ants_number, int iterations, float alpha, float beta, float p, float Q, float c, bool isAutomatic);
    void calculateProbability(int current_point, std::vector<int> &allowed, std::vector<long double> &probabilities, std::vector<std::vector<float>> &trail_matrix, float alpha, float beta);
    int pickNextPoint(std::vector<long double> &probabilities, std::vector<int> &allowed);
    float getMinDistance();
    std::vector<int> getBestRoute();
    void setMinDistance(float min_distance);
    void setBestRoute(std::vector<int> best_route);
};

float calculateDistance(std::pair<int, int> point1, std::pair<int, int> point2);
