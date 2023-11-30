#include <iostream>
#include <string>
#include <fstream>
#include "Graph.hpp"

std::string handleInstanceInput(int argc, char *argv[]);
int handleAlgorithmTypeInput();
std::vector<float> handleACSInput();
void saveResultToFile(float min_distance, std::vector<int> min_route, std::string filename);

Graph graph;

int main(int argc, char *argv[]){
    std::pair<float, std::vector<int>> result;

    std::string filename = handleInstanceInput(argc, argv);
    graph.generateAdjacencyMatrix();

    int algorithm_type = handleAlgorithmTypeInput();

    if (algorithm_type){
        result = graph.greedyTSP();
    }
    else{
        std::vector<float> ACS_input = handleACSInput();
        result = graph.antColonySystem(static_cast<int>(ACS_input[0]), static_cast<int>(ACS_input[1]), ACS_input[2], ACS_input[3], ACS_input[4], ACS_input[5], ACS_input[6]);
    }

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

std::string handleInstanceInput(int argc, char *argv[]){
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

int handleAlgorithmTypeInput(){
    int answer;
    std::cout << "What type of method do you want to use?" << std::endl;
    std::cout << "Ant Colony System (0) or Greedy (1)" << std::endl;
    std::cin >> answer;
    if (answer){
        return 1;
    }
    else{
        return 0;
    }
}

std::vector<float> handleACSInput(){
    float answer;
    std::cout << "Default settings (0) or custom settings (1)" << std::endl;
    std::cout << "Default settings: N of ants: 100, Iterations: 100, Alpha: 1, Beta: 5, p: 0.5, Q: 100, c: 1" << std::endl;
    std::cin >> answer;
    if (answer){
        std::vector<float> input_vector;
        std::cout << "Number of ants: ";
        std::cin >> answer;
        input_vector.push_back(answer);
        std::cout << "Number of iterations: ";
        std::cin >> answer;
        input_vector.push_back(answer);
        std::cout << "Alpha: ";
        std::cin >> answer;
        input_vector.push_back(answer);
        std::cout << "Beta: ";
        std::cin >> answer;
        input_vector.push_back(answer);
        std::cout << "Evaporation rate (p): ";
        std::cin >> answer;
        input_vector.push_back(answer);
        std::cout << "Constant Q: ";
        std::cin >> answer;
        input_vector.push_back(answer);
        std::cout << "Constant c: ";
        std::cin >> answer;
        input_vector.push_back(answer);
        return input_vector;
    }
    return std::vector<float> {100, 100, 1, 5, 0.5, 100, 1};
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