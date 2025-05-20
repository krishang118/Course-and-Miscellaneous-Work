#Now here, the robot can move left, right, bottom, or up.
#And, we are to define the heuristic value which gives the euclidian distance
#from a user-selected node to the goal node.

import math
class Puzzle:
    def __init__(self):
        self.grid = [['X', ' ', 'E'],
                     [' ', ' ', ' '],
                     [' ', ' ', 'X']]
        self.end = (0, 2)  
        self.position = None
    def display_grid(self):
        print("The grid layout is:")
        for i, row in enumerate(self.grid):
            for j, cell in enumerate(row):
                print(f"{cell}({i},{j})", end=" ")
            print()
    def set_starting_position(self):
        while True:
            try:
                x = int(input("Enter row index for the starting position (first coordinate): "))
                y = int(input("Enter column index for the starting position (second coordinate): "))
                if (x, y) == self.end:
                    print("You can't choose the end point. Try once more.")
                elif self.grid[x][y] == 'X':
                    print("You can't choose a blocked position ('X'). Try once more.")
                else:
                    self.position = (x, y)
                    self.grid[x][y] = 'S'
                    print(f"Starting position is set to: {self.position}")
                    break
            except (ValueError, IndexError):
                print("Invalid input. Please enter valid coordinates within the grid.")
    def heuristic(self, position):
        return math.sqrt((position[0] - self.end[0])**2 + (position[1] - self.end[1])**2)
    def print_heuristic_value(self):
        if self.position:
            h_value = self.heuristic(self.position)
            print(f"The heuristic value (Euclidean distance) from {self.position} to the goal {self.end} is: {h_value}")
        else:
            print("Starting position isn't set.")
puzzle = Puzzle()
puzzle.display_grid()
puzzle.set_starting_position()
puzzle.print_heuristic_value()
