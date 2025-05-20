#Here, for the same robot puzzle, we use four
#uninformed search algorithms for the solution.
#And here, the start position is selected by the user.

#The code is as follows:

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
                x = int(input("Enter the row index for the starting position (first coordinate): "))
                y = int(input("Enter the column index for the starting position (second coordinate): "))
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
                print("Invalid input. Please enter valid coordinates given within the grid.")
    def is_move_valid(self, new_position):
        x, y = new_position
        if 0 <= x < 3 and 0 <= y < 3:  
            return self.grid[x][y] != 'X'
        return False
    def move(self, position, direction):
        x, y = position
        if direction == 0: 
            new_position = (x, y + 1)
        elif direction == 1:  
            new_position = (x - 1, y)
        else:
            return None  
        if self.is_move_valid(new_position):
            return new_position
        return None  
    def get_possible_moves(self, position):
        possible_moves = []
        if self.is_move_valid((position[0], position[1] + 1)):  
            possible_moves.append(0)
        if self.is_move_valid((position[0] - 1, position[1])): 
            possible_moves.append(1)
        return possible_moves
    def generic_search(self, search_type='dfs', limit=None):
        OPEN = [(self.position, [])]  
        while OPEN:
            position, path = OPEN.pop(0)
            if position == self.end:
                return path + [position]
            possible_moves = self.get_possible_moves(position)
            for move in possible_moves:
                new_position = self.move(position, move)
                if new_position:
                    if search_type in ['dls', 'ids'] and len(path) + 1 > limit:
                        continue 
                    OPEN.append((new_position, path + [position]))
            if search_type == 'dfs':
                OPEN = OPEN[::-1]  
            if search_type == 'ids' and not OPEN:  
                limit += 1
                OPEN = [(self.position, [])]  
        return None
    def depth_first_search(self):
        return self.generic_search(search_type='dfs')
    def breadth_first_search(self):
        return self.generic_search(search_type='bfs')
    def depth_limited_search(self, limit):
        return self.generic_search(search_type='dls', limit=limit)
    def iterative_deepening_search(self):
        limit = 0
        while True:
            result = self.generic_search(search_type='ids', limit=limit)
            if result:
                return result
            limit += 1
puzzle = Puzzle()
puzzle.display_grid()
puzzle.set_starting_position()
print("DFS Solution:", puzzle.depth_first_search())
print("BFS Solution:", puzzle.breadth_first_search())
print("DLS Solution (limit is 4):", puzzle.depth_limited_search(limit=4))
print("IDS Solution:", puzzle.iterative_deepening_search())
