#include <iostream>
#include <string>
#include <fstream>
#include "Graph.hpp"

std::string handleInput(int argc, char *argv[]);
void saveResultToFile(float min_distance, std::vector<int> min_route, std::string filename);

Graph graph;

int main(int argc, char *argv[]){
    std::string filename = handleInput(argc, argv);

    graph.generateAdjacencyMatrix();
    // std::pair<float, std::vector<int>> result = graph.greedyTSP();
    std::pair<float, std::vector<int>> result = graph.antColonySystem(50, 100, 1, 5, 0.5, 100);
    float min_distance = result.first;
    std::vector<int> min_route = result.second;

    saveResultToFile(min_distance, min_route, filename);
    std::cout << "Calculated distance: " << min_distance << std::endl;
    std::cout << "Calculated route: ";
    for (int i = 0; i < min_route.size(); i++){
        std::cout << min_route[i] + 1 << " ";
    }

    return 0;
}

std::string handleInput(int argc, char *argv[]){
    int answer=-1;
    std::string filename;
    if(argc < 2){
        std::cout << "What input do you want to use?" << std::endl;
        std::cout << "File (0) or Your input (1)" << std::endl;
        std::cin >> answer;

        if(answer){
            int vert, range;
            std::cout << "Vertex number: ";
            std::cin >> vert;
            std::cout << "Range: ";
            std::cin >> range;
            
            graph.initRandomGraph(vert, range);

            graph.saveGraphToFile("txt_files/out.txt");
            filename = "txt_files/out";
        } else {
            graph.initGraphFromFile("txt_files/test.txt");
            filename = "txt_files/test";
        }
    } else {
        graph.initGraphFromFile(argv[1]);
        filename = argv[1];
        filename =  filename.substr(0, filename.find_last_of("."));
    }
    return filename + "_wynik.txt";
}

void saveResultToFile(float min_distance, std::vector<int> min_route, std::string filename){
    std::ofstream resultFile(filename);
    if (resultFile.is_open()){
        resultFile << "Calculated distance: " << min_distance << std::endl;
        resultFile << "Calculated route: ";
        for (int i = 0; i < min_route.size(); i++){
            resultFile << min_route[i] + 1 << " ";
        }
        resultFile << std::endl;
    } else {
        std::cout << "Error. Couldn't write to file " << std::endl;
    }
}