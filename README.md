# Ant-Colony-Optimization-For-TSP
Project made for Combinatorial Optimization at Poznań University of Technology.

## General Description
The goal of this project was to create program solving travelling salesman problem using metaheuristic algorithm and improve parameters to produce the best results.
The program written in C++ can solve both generated instances and the ones provided in text files like [these](txt_files) using ant colony optimization algorithm. It can solve given problem one time or try over and over again with different parameters. The second option is used to improve parameters used in algorithm for given instance. It would be impossible to analyze these results manually, so they are saved in text file and can be later analyzed by [Python program](results_analyzer.py) to calculate average results. If certain result is intresting another [Python program](iteration_visualizer.py) can be used to visualize iteration.
