#include <random>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <bits/stdc++.h>

class Solution
{
public:
    double a, b, c, rank;
    void calculateRank()
    {
        double answer = pow(a, 2) + pow(b, 3) - c - 2137;
        rank = (answer == 0) ? 10000 : 1 / answer;
    }
};

int main()

{

    const double MUTATION_RATE = 0.03;
    const int POPULATION_SIZE = 100000;
    const int BEST_SAMPLE = 80;
    std::random_device rd;
    std::uniform_real_distribution<double> dist(-100000, 100000);
    std::uniform_real_distribution<double> mutationAmount(1 - MUTATION_RATE, 1 + MUTATION_RATE);
    std::uniform_int_distribution<int> crossover(0, BEST_SAMPLE - 1);

    std::vector<Solution> solutions;
    std::vector<Solution> bestSolutions;

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        Solution solution;
        solution.a = dist(rd);
        solution.b = dist(rd);
        solution.c = dist(rd);
        solutions.push_back(solution);
    }

    while (true)
    {

        for (Solution &s : solutions)
        {
            s.calculateRank();
        }

        std::sort(solutions.begin(), solutions.end(), [](Solution a, Solution b)
                  { return a.rank > b.rank; });

        std::cout << std::setprecision(4) << "Best solution: " << static_cast<int>(solutions[0].rank) << "\t" << solutions[0].a << "\t" << solutions[0].b << "\t" << solutions[0].c << std::endl;

        bestSolutions.clear();
        for (int i = 0; i < BEST_SAMPLE; i++)
        {
            bestSolutions.push_back(solutions[i]);
        }

        for (Solution &s : bestSolutions)
        {
            s.a *= mutationAmount(rd);
            s.b *= mutationAmount(rd);
            s.c *= mutationAmount(rd);
        }

        solutions.clear();

        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            Solution solution;
            solution.a = bestSolutions[crossover(rd)].a;
            solution.b = bestSolutions[crossover(rd)].b;
            solution.c = bestSolutions[crossover(rd)].c;
            solutions.push_back(solution);
        }
    }
    return 0;
}