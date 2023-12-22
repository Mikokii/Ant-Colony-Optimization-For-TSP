#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "Graph.hpp"

std::string handleInstanceInput(int argc, char *argv[]);
int handleAlgorithmTypeInput();
std::vector<float> handleACSInput();
std::pair<std::vector<float>, std::vector<float>> handleAutomaticACSInput();
void startAutomaticACS(std::vector<float> a_ACS_input, std::vector<float> a_ACS_intervals, std::string filename);
void saveResultToFile(float min_distance, std::vector<int> min_route, std::string filename);

Graph graph;

int main(int argc, char *argv[]){
    float min_distance;
    std::vector<int> min_route;

    std::string filename = handleInstanceInput(argc, argv);
    graph.generateAdjacencyMatrix();

    int algorithm_type = handleAlgorithmTypeInput();

    if (algorithm_type == 1){
        graph.greedyTSP();
    }
    else if (algorithm_type == 2){
        std::pair<std::vector<float>, std::vector<float>> automatic_ACS_result = handleAutomaticACSInput();
        std::vector<float> automatic_ACS_input = automatic_ACS_result.first;
        std::vector<float> automatic_ACS_intervals = automatic_ACS_result.second;
        startAutomaticACS(automatic_ACS_input, automatic_ACS_intervals, filename);
    }
    else{
        std::vector<float> ACS_input = handleACSInput();
        graph.antColonySystem(static_cast<int>(ACS_input[0]), static_cast<int>(ACS_input[1]), ACS_input[2], ACS_input[3], ACS_input[4], ACS_input[5], ACS_input[6], false);
    }

    min_distance = graph.getMinDistance();
    min_route = graph.getBestRoute();

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
    std::cout << "Ant Colony System (0), Greedy (1) or Automatic ACS (2)" << std::endl;
    std::cin >> answer;
    if (answer == 1){
        return 1;
    }
    else if (answer == 2){
        return 2;
    }
    else{
        return 0;
    }
}

std::pair<std::vector<float>, std::vector<float>> handleAutomaticACSInput(){
    float answer;
    std::vector<float> input_vector;
    std::vector<float> interval_vector;
    std::cout << "ACS will be tested with interval:" << std::endl;
    std::cout << "N of ants: ";
    std::cin >> answer;
    interval_vector.push_back(answer);
    std::cout << "Iterations: ";
    std::cin >> answer;
    interval_vector.push_back(answer);
    std::cout << "Alpha: ";
    std::cin >> answer;
    interval_vector.push_back(answer);
    std::cout << "Beta: ";
    std::cin >> answer;
    interval_vector.push_back(answer);
    std::cout << "p: ";
    std::cin >> answer;
    interval_vector.push_back(answer);
    std::cout << "Q: ";
    std::cin >> answer;
    interval_vector.push_back(answer);
    std::cout << "c: ";
    std::cin >> answer;
    interval_vector.push_back(answer);
    std::cout << "--- Input data --- " << std::endl;
    std::cout << "N_min: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "N_max: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "It_min: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "It_max: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "Alpha_min: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "Alpha_max: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "Beta_min: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "Beta_max: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "p_min: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "p_max: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "Q_min: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "Q_max: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "c_min: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    std::cout << "c_max: ";
    std::cin >> answer;
    input_vector.push_back(answer);
    return std::pair<std::vector<float>, std::vector<float>>(input_vector, interval_vector);
}

void startAutomaticACS(std::vector<float> a_ACS_input, std::vector<float> a_ACS_intervals, std::string filename){
    int N_min = static_cast<int>(a_ACS_input[0]), N_max = static_cast<int>(a_ACS_input[1]);
    int it_min = static_cast<int>(a_ACS_input[2]), it_max = static_cast<int>(a_ACS_input[3]);
    float alpha_min = a_ACS_input[4], alpha_max = a_ACS_input[5];
    float beta_min = a_ACS_input[6], beta_max = a_ACS_input[7];
    float p_min = a_ACS_input[8], p_max = a_ACS_input[9];
    float Q_min = a_ACS_input[10], Q_max = a_ACS_input[11];
    float c_min = a_ACS_input[12], c_max = a_ACS_input[13];
    float N_interval = a_ACS_intervals[0], it_interval = a_ACS_intervals[1], alpha_interval = a_ACS_intervals[2], beta_interval = a_ACS_intervals[3], p_interval = a_ACS_intervals[4], Q_interval = a_ACS_intervals[5], c_interval = a_ACS_intervals[6];
    std::pair<float, std::vector<int>> result;
    float min_distance, best_distance = std::numeric_limits<float>::max();
    std::vector<int> min_route, best_route;
    std::vector<float> best_parameters;
    std::string fname = filename.substr(0, filename.find_last_of("_"));
    fname += "_auto.txt";

    std::ofstream resultFile(fname);
    int count = 0;
    int max_count = (int)((N_max-N_min)/N_interval + 1) * (int)((it_max-it_min)/it_interval + 1) * (int)((alpha_max-alpha_min)/alpha_interval + 1) * (int)((beta_max-beta_min)/beta_interval + 1) * (int)((p_max-p_min)/p_interval + 1) * (int)((Q_max-Q_min)/Q_interval + 1) * (int)((c_max-c_min)/c_interval + 1);
    for (int N = N_min; N <= N_max; N+=N_interval){
        for (int it = it_min; it <= it_max; it+=it_interval){
            for (float alpha = alpha_min; alpha <= alpha_max; alpha+=alpha_interval){
                for (float beta = beta_min; beta <= beta_max; beta+=beta_interval){
                    for (float p = p_min; p <= p_max; p+=p_interval){
                        for (float Q = Q_min; Q <= Q_max; Q+=Q_interval){
                            for (float c = c_min; c <= c_max; c+=c_interval){
                                auto start = std::chrono::high_resolution_clock::now();
                                graph.antColonySystem(N, it, alpha, beta, p, Q, c, true);
                                auto stop = std::chrono::high_resolution_clock::now();
                                auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(stop - start);
                                float time = duration.count();
                                min_distance = graph.getMinDistance();
                                min_route = graph.getBestRoute();
                                if (min_distance < best_distance){
                                    best_distance = min_distance;
                                    best_route = min_route;
                                    best_parameters.assign({static_cast<float>(N), static_cast<float>(it), alpha, beta, p, Q, c, time});
                                }
                                if (resultFile.is_open()){
                                    resultFile << "N: " << N << " It: " << it << " Alpha: " << alpha << " Beta: " << beta << " p: " << p << " Q: " << Q << " c: " << c << " t: " << time << std::endl;
                                    resultFile << "Calculated distance: " << min_distance << std::endl;
                                    resultFile << "Calculated route: ";
                                    for (int i = 0; i < min_route.size(); i++){
                                        resultFile << min_route[i] + 1 << " ";
                                    }
                                    resultFile << std::endl;
                                    resultFile << std::endl;
                                } else {
                                    std::cout << "Error. Couldn't write to file " << std::endl;
                                }
                                count ++;
                                std::cout << count << "/" << max_count << " (" << ((float)count/(float)max_count)*100 << " %)" << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }
    if (resultFile.is_open()){
        resultFile << std::endl;
        resultFile << "---------- Best Result ----------" << std::endl;
        resultFile << "N: " << best_parameters[0] << " It: " << best_parameters[1] << " Alpha: " << best_parameters[2] << " Beta: " << best_parameters[3] << 
            " p: " << best_parameters[4] << " Q: " << best_parameters[5] << " c: " << best_parameters[6] << " t: " << best_parameters[7] << std::endl;
        resultFile << "Calculated distance: " << best_distance << std::endl;
        resultFile << "Calculated route: ";
        for (int i = 0; i < best_route.size(); i++){
            resultFile << best_route[i] + 1 << " ";
        }
        resultFile << std::endl;
    }
    else{
        std::cout << "Error. Couldn't write to file " << std::endl;
    }
    resultFile.close();
    graph.setMinDistance(min_distance);
    graph.setBestRoute(best_route);
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
    resultFile.close();
}