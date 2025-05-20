#Here, heuristic value is used as the preference for the greedy search algorithm
import math
from queue import PriorityQueue
class RobotPuzzle:
    def __init__(self):
        self.map = [['X', ' ', 'G'],
                    [' ', ' ', ' '],
                    [' ', ' ', 'X']]
        self.goal = (0, 2)  
        self.start = None    
    def show_map(self):
        print("Puzzle grid with coordinates:")
        for row_idx, row in enumerate(self.map):
            for col_idx, cell in enumerate(row):
                print(f"{cell}({row_idx},{col_idx})", end=" ")
            print()
    def choose_start(self):
        while True:
            try:
                row = int(input("Enter the row index for the starting position (first coordinate): "))
                col = int(input("Enter the column index for the starting position (second coordinate): "))
                if (row, col) == self.goal:
                    print("Cannot choose the goal as the start. Try once more.")
                elif self.map[row][col] == 'X':
                    print("This position is blocked. Choose another position.")
                else:
                    self.start = (row, col)
                    self.map[row][col] = 'R'
                    print(f"Start position set to: {self.start}")
                    break
            except (ValueError, IndexError):
                print("Invalid input. Please choose valid coordinates within the grid given.")
    def valid_move(self, new_pos):
        r, c = new_pos
        return 0 <= r < len(self.map) and 0 <= c < len(self.map[0]) and self.map[r][c] != 'X'
    def get_neighbors(self, pos):
        neighbors = []
        r, c = pos
        if self.valid_move((r - 1, c)):  
            neighbors.append((r - 1, c))
        if self.valid_move((r + 1, c)):  
            neighbors.append((r + 1, c))
        if self.valid_move((r, c - 1)):  
            neighbors.append((r, c - 1))
        if self.valid_move((r, c + 1)):  
            neighbors.append((r, c + 1))
        return neighbors
    def calculate_distance(self, pos):
        return math.sqrt((pos[0] - self.goal[0]) ** 2 + (pos[1] - self.goal[1]) ** 2)
    def greedy_search(self):
        pq = PriorityQueue()
        pq.put((0, self.start))
        trace_path = {self.start: None}
        visited_cost = {self.start: 0}
        while not pq.empty():
            current_pos = pq.get()[1]      
            if current_pos == self.goal:
                return self.build_path(trace_path)
            for next_pos in self.get_neighbors(current_pos):
                move_cost = visited_cost[current_pos] + 1
                if next_pos not in visited_cost or move_cost < visited_cost[next_pos]:
                    visited_cost[next_pos] = move_cost
                    priority = self.calculate_distance(next_pos)
                    pq.put((priority, next_pos))
                    trace_path[next_pos] = current_pos
        return None
    def build_path(self, trace_path):
        path = []
        step = self.goal
        while step is not None:
            path.append(step)
            step = trace_path[step]
        path.reverse()
        return path
puzzle_game = RobotPuzzle()
puzzle_game.show_map()
puzzle_game.choose_start()
solution_path = puzzle_game.greedy_search()
if solution_path:
    print("The path to goal:", solution_path)
else:
    print("No valid path found.")
