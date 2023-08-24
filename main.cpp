#include <random>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <bits/stdc++.h>

class Solution
{
public:
    Solution(double a, double b, double c, double rank = 0)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        calculateRank();
    };
    double a, b, c, rank;
    void calculateRank()
    {
        double answer = pow(a, 2) + pow(b, 3) - c * 100 - 25;
        rank = (answer == 0) ? 10000 : 1 / answer;
    }
};

int main()

{

    const double MUTATION_RATE = 0.1;
    const int POPULATION_SIZE = 100000;
    const int BEST_SAMPLE = 80;
    std::random_device rd;
    std::uniform_real_distribution<double> dist(-100000, 100000);
    std::uniform_real_distribution<double> mutationAmount(1 - MUTATION_RATE, 1 + MUTATION_RATE);
    std::uniform_int_distribution<int> crossover(0, BEST_SAMPLE - 1);

    std::vector<Solution> solutions;
    std::vector<Solution> bestSolutions;

    // Creating the initial population
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        solutions.push_back(Solution(dist(rd), dist(rd), dist(rd)));
    }

    while (true)
    {
        // Sorting the solutions by rank so that the best ones are at the front
        std::nth_element(solutions.begin(), solutions.begin() + BEST_SAMPLE, solutions.end(), [](Solution a, Solution b)
                         { return a.rank > b.rank; });

        // Because of using nth_element the first solution isn't the best one but it's still into the first BEST_SAMPLE solutions
        std::printf("Best solution: %5d   %5.4f   %5.4f   %5.4f   \n", static_cast<int>(solutions[0].rank), solutions[0].a, solutions[0].b, solutions[0].c);

        bestSolutions.clear();

        // Copying the best solutions
        for (int i = 0; i < BEST_SAMPLE; i++)
        {
            bestSolutions.emplace_back(std::move(solutions[i].a), std::move(solutions[i].b), std::move(solutions[i].c));
        }

        // Mutating the best solutions
        for (Solution &s : bestSolutions)
        {
            s.a *= mutationAmount(rd);
            s.b *= mutationAmount(rd);
            s.c *= mutationAmount(rd);
        }

        solutions.clear();

        // Creating new solutions from the best ones using crossover
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            solutions.emplace_back(std::move(bestSolutions[crossover(rd)].a), std::move(bestSolutions[crossover(rd)].b), std::move(bestSolutions[crossover(rd)].c));
        }
    }
    return 0;
}