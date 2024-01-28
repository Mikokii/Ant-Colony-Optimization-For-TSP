import matplotlib.pyplot as plt

coordinates = [(565,575),(25,185),(345,750),(945,685),(845,655),(880,660),(25,230),(525,1000),(580,1175),(650,1130),(1605,620),(1220,580),(1465,200),(1530,5),(845,680),(725,370),(145,665),(415,635),(510,875),(560,365),(300,465),(520,585),(480,415),(835,625),(975,580),(1215,245),(1320,315),(1250,400),(660,180),(410,250),(420,555),(575,665),(1150,1160),(700,580),(685,595),(685,610),(770,610),(795,645),(720,635),(760,650),(475,960),(95,260),(875,920),(700,500),(555,815),(830,485),(1170,65),(830,610),(605,625),(595,360),(1340,725),(1740,245)]
path = [1, 22, 31, 18, 3, 17, 21, 42, 7, 2, 30, 23, 20, 50, 29, 16, 46, 44, 34, 35, 36, 39, 40, 37, 38, 48, 24, 5, 15, 6, 4, 25, 12, 28, 27, 26, 47, 13, 14, 52, 11, 51, 33, 43, 10, 9, 8, 41, 19, 45, 32, 49, 1]

for n in range(len(path)):
    path[n] = path[n]-1

def plot_tsp_solution(coordinates, path):
    # Plotting the TSP path
    path_coordinates = [coordinates[i] for i in path]
    px, py = zip(*path_coordinates)
    plt.plot(px, py, color='black', linestyle='-', linewidth=1)

    # Plotting the points
    x, y = zip(*coordinates)
    plt.scatter(x, y, color='dodgerblue', marker='o', zorder=2, s=20)

    # Adding labels and legend
    plt.title('Berlin52 - 7544.37 - Wynik')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.legend()

    # Display the plot
    plt.show()

plot_tsp_solution(coordinates, path)