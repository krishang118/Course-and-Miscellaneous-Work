#Question:

#Suppose a Genetic Algorithm uses chromosomes of the form x=abcdefgh
#with a fixed length of eight genes. Each gene can be any digit between 0 and 9.
#Let the fitness of individual x be calculated as:
#f(x) = (a+b)-(c+d)+(e+f)-(g+h)

#And let the initial population consist of four individuals
#x1, ..., x4 with the following chromosomes :
#X1 = 6 5 4 1 3 5 3 2
#X2 = 8 7 1 2 6 6 0 1
#X3 = 2 3 9 2 1 2 8 5
#X4 = 4 1 8 5 2 0 9 4

#Evaluate the fitness of each individual, showing all your workings,
#and arrange them in order with the fittest first and the least fit last.
#For above problem perform the following crossover operations:

# i) Cross the fittest two individuals
#using one-point crossover at the middle point.

# ii) Cross the second and third fittest individuals
#using a two-point crossover (point’s b and f).


#Answer:
def fitness(chromosome):
    a, b, c, d, e, f, g, h = chromosome
    return (a + b) - (c + d) + (e + f) - (g + h)
population = {
    "x1": [6, 5, 4, 1, 3, 5, 3, 2],
    "x2": [8, 7, 1, 2, 6, 6, 0, 1],
    "x3": [2, 3, 9, 2, 1, 2, 8, 5],
    "x4": [4, 1, 8, 5, 2, 0, 9, 4]}
fitness_scores = {key: fitness(chrom) for key, chrom in population.items()}
print("Fitness Evaluation for each Individual:", fitness_scores)
sorted_population = sorted(fitness_scores.items(), key=lambda x: x[1], reverse=True)
sorted_individuals = [indv[0] for indv in sorted_population]
def one_point_crossover(parent1, parent2, point=4):
    offspring1 = parent1[:point] + parent2[point:]
    offspring2 = parent2[:point] + parent1[point:]
    return offspring1, offspring2
fittest1 = population[sorted_individuals[0]]
fittest2 = population[sorted_individuals[1]]
offspring1, offspring2 = one_point_crossover(fittest1, fittest2)
print("After carrying out the Crossover Operations, we get four Offsprings.")
print("One-point Crossover Offsprings:")
print("Offspring 1:", offspring1)
print("Offspring 2:", offspring2)
def two_point_crossover(parent1, parent2, point1=1, point2=5):
    offspring1 = parent1[:point1] + parent2[point1:point2] + parent1[point2:]
    offspring2 = parent2[:point1] + parent1[point1:point2] + parent2[point2:]
    return offspring1, offspring2
second_fittest = population[sorted_individuals[1]]
third_fittest = population[sorted_individuals[2]]
offspring3, offspring4 = two_point_crossover(second_fittest, third_fittest)
print("Two-point Crossover Offsprings:")
print("Offspring 3:", offspring3)
print("Offspring 4:", offspring4)
offspring_fitness = {
    "Offspring 1": fitness(offspring1),
    "Offspring 2": fitness(offspring2),
    "Offspring 3": fitness(offspring3),
    "Offspring 4": fitness(offspring4)}
print("Fitness Evaluation for each Offspring:", offspring_fitness)
