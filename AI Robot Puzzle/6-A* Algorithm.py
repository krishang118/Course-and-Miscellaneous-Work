#Here, heuristic value is used as the preference for the A* algorithm
import math
from queue import PriorityQueue
class RobotPuzzle:
    def __init__(self):
        self.grid = [['X', ' ', 'G'],
                     [' ', ' ', ' '],
                     [' ', ' ', 'X']]
        self.target = (0, 2)
        self.start_pos = None
    def display_grid(self):
        print("Grid with coordinates:")
        for r_idx, row in enumerate(self.grid):
            for c_idx, cell in enumerate(row):
                print(f"{cell}({r_idx},{c_idx})", end=" ")
            print()
    def select_start(self):
        while True:
            try:
                r = int(input("Enter the row index for the starting point (first coordinate): "))
                c = int(input("Enter the column index for the starting point (second coordinate): "))
                if (r, c) == self.target:
                    print("You cannot choose the goal as the start. Try again.")
                elif self.grid[r][c] == 'X':
                    print("This position is blocked. Pick another one.")
                else:
                    self.start_pos = (r, c)
                    self.grid[r][c] = 'R'
                    print(f"Start position set to: {self.start_pos}")
                    break
            except (ValueError, IndexError):
                print("Invalid input. Please enter valid grid coordinates.")
    def is_move_valid(self, pos):
        r, c = pos
        return 0 <= r < len(self.grid) and 0 <= c < len(self.grid[0]) and self.grid[r][c] != 'X'
    def get_adjacent(self, pos):
        adjacent_moves = []
        r, c = pos
        if self.is_move_valid((r - 1, c)):
            adjacent_moves.append((r - 1, c))
        if self.is_move_valid((r + 1, c)):
            adjacent_moves.append((r + 1, c))
        if self.is_move_valid((r, c - 1)):
            adjacent_moves.append((r, c - 1))
        if self.is_move_valid((r, c + 1)):
            adjacent_moves.append((r, c + 1))
        return adjacent_moves
    def heuristic(self, pos):
        return math.sqrt((pos[0] - self.target[0]) ** 2 + (pos[1] - self.target[1]) ** 2)
    def execute_a_star(self):
        open_list = PriorityQueue()
        open_list.put((0, self.start_pos))
        visited = {self.start_pos: None}
        g_scores = {self.start_pos: 0}
        while not open_list.empty():
            current_pos = open_list.get()[1]
            if current_pos == self.target:
                return self.reconstruct_path(visited)
            for next_pos in self.get_adjacent(current_pos):
                temp_g_score = g_scores[current_pos] + 1
                if next_pos not in g_scores or temp_g_score < g_scores[next_pos]:
                    g_scores[next_pos] = temp_g_score
                    f_score = temp_g_score + self.heuristic(next_pos)
                    open_list.put((f_score, next_pos))
                    visited[next_pos] = current_pos
        return None
    def reconstruct_path(self, visited):
        path = []
        step = self.target
        while step is not None:
            path.append(step)
            step = visited[step]
        return path[::-1]
game = RobotPuzzle()
game.display_grid()
game.select_start()
path = game.execute_a_star()
if path:
    print("Path found using A* algorithm:", path)
else:
    print("No valid path could be found.")
