#include <iostream>                             // For cout etc
#include <string>                               // For string class
#include <vector>                               // For vector class
#include <time.h>                               // For random seed
#include <stdlib.h>                             // For random function

#define POPULATION_SIZE 250                     // GA population size
#define MAX_ITERATION 14000                     // GA max iterations
#define MUTATION_RATE 5                         // GA mutation rate in percentage

using namespace std;

string TARGET;		// to set the target phrase type it as a command-line argument

struct ga_struct
{
    string str;             // The string to be evolved
    unsigned int fitness;   // Its fitness
};

typedef vector<ga_struct> ga_vector;
// Generating a random DNA
char char_generator()
{
    int c = (rand() % 63) + 60;
    switch(c)
    {
    case 60:        // For space
        c = 32;
        break;
    case 61:        // For exclamation mark (!)
        c = 33;
        break;
    case 62:        // For comma (,)
        c = 44;
        break;
    case 64:        // For full stop (.)
        c = 46;
        break;
    }

    return c;
}
// Initializing the population with random characters
void initial_pop(ga_vector &population)
{
    int tsize = TARGET.size();
    ga_struct individuo;
    for (int i = 0; i < POPULATION_SIZE; i++){
        individuo.fitness = 0;
        individuo.str.erase();
        for(int j = 0; j < tsize; j++){
            individuo.str += char_generator();
        }
        population.push_back(individuo);
    }
}
// Calculating its fitness
void calcFitness(ga_vector &population)
{
    int tsize = TARGET.size();
    for (int i = 0; i < POPULATION_SIZE; i++){
        int fitness = 0;
        for (int j = 0; j < tsize; j++){
            if (population[i].str[j] == TARGET[j]) fitness++;
        }
        population[i].fitness = fitness;
    }
}
// Evolving the population based on its fitness
void naturalSelection(ga_vector &population)
{
    ga_vector matingPool;
    // Creating the matting pool
    for (int i = 0; i < POPULATION_SIZE; ++i){
        for (unsigned int j = 0; j < population[i].fitness; j++)
            matingPool.push_back(population[i]);
    }
    int parentA, parentB;
    ga_struct child;
    int tsize = TARGET.size();
    for (int i = 0; i < POPULATION_SIZE; i++){
        child.str.erase();
        // Choosing the parents based on its probability
        parentA = rand() % matingPool.size();
        parentB = rand() % matingPool.size();
        int middle = rand() % tsize;
        for (int j = 0; j < tsize; j++){
            int mutate = (rand() % 100) + 1;
            if (mutate <= MUTATION_RATE)                        // Mutating its genes
                child.str += char_generator();
            else{
                // Crossover
                if (j < middle)
                    child.str += matingPool[parentA].str[j];
                else
                    child.str += matingPool[parentB].str[j];
            }
        }
        population[i] = child;          // Replacing the new population in the previous
    }
}
// Finding the best DNA in the population
ga_struct find_best(ga_vector &population)
{
    ga_struct best;
    int maxFitness = 0;
    for (int i = 0; i < POPULATION_SIZE; i++){
        if (maxFitness < population[i].fitness){
            maxFitness = population[i].fitness;
            best = population[i];
        }
    }
    return best;
}

int main(int argc, const char *argv[])
{
	if(argc > 1){
		for(int i=1; i<argc; i++){
			TARGET += argv[i];
			if(i+1 < argc)
				TARGET += ' ';
		}
	}
	else
		TARGET = "Hello, world";
	
    srand(unsigned(time(NULL)));    // initialize random seed

    ga_vector population;
    initial_pop(population);        // initialize random population
    int generation = 0;
    for (int i = 0; i < MAX_ITERATION; i++, generation++){
        calcFitness(population);                    // calculate its fitness
        ga_struct best = find_best(population);     // find the best DNA
        naturalSelection(population);               // Mate the population together
        cout << "best: " << best.str << " || generation: " << generation << endl;
        if (best.fitness == TARGET.size())          // If fitness is the maximum possible
            break;
    }

    return 0;
}
