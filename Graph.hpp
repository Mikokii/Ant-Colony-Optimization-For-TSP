#pragma once

#include <vector>
#include <iostream>

class Graph{
public:
    int vertices_number;
    std::vector<std::pair<int,int>> vertices_list;
    std::vector<std::vector<float>> adjacency_matrix;

    Graph();
    ~Graph();
    void initRandomGraph(int vertices_number, int range);
    void saveGraphToFile(const char* filename);
    void initGraphFromFile(const char* filename);
    void generateAdjacencyMatrix();
    void printGraph();
    std::pair<float, std::vector<int>> greedyTSP();
};

float calculateDistance(std::pair<int, int> point1, std::pair<int, int> point2);