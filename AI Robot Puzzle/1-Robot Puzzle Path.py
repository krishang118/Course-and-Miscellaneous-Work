#We are desiging a puzzle for a robot in which the robot moves from
#the start position to the end position in the following 3x3 grid.

#Grid:
#  X , ' ' ,  E
# ' ', ' ' , ' '
#  S , ' ' ,  X

#Here, S and E indicate the start and ending positions.
#And, the X's indicate blocked positons which the robot can't go to.
#Also, the robot can only move right or up.

#Everytime the code is run, we receive a path (on a random basis) for the
#robot to reach the end position.

#The code is as follows:

import random
class Puzzle:
    def initialize(self):
        self.grid = [['X', ' ', 'End'],
                     [' ', ' ', ' '],
                     ['Start', ' ', 'X']]
        self.position = (2, 0)  
    def is_move_valid(self, new_position):
        x, y = new_position
        if 0 <= x < 3 and 0 <= y < 3:  
            return self.grid[x][y] != 'X'
        return False
    def move(self, direction):
        x, y = self.position
        if direction == 0:  
            new_position = (x, y + 1)
        elif direction == 1:  
            new_position = (x - 1, y)
        else:
            return None  
        if self.is_move_valid(new_position):
            self.position = new_position
            return self.position
        return None  
    def get_possible_moves(self):
        possible_moves = []
        if self.is_move_valid((self.position[0], self.position[1] + 1)):
            possible_moves.append(0)  
        if self.is_move_valid((self.position[0] - 1, self.position[1])):
            possible_moves.append(1)
        return possible_moves
    def play(self, k):
        self.initialize()  
        print(f'Starting Position: {self.position}')
        for _ in range(k):
            possible_moves = self.get_possible_moves()
            if possible_moves:
                move_direction = random.choice(possible_moves)
                result = self.move(move_direction)
                if result is not None:
                    print(result)  
                    if self.position == (0, 2):
                        print("End position reached!")
                        break
puzzle = Puzzle()
puzzle.play(5)
