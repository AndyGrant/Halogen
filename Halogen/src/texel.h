#pragma once
#include "Search.h"
#include <random>

void Texel(std::vector<int*> params);

void LoadBench4Per(std::vector<std::pair<Position, double>>& positions, std::string& line, int lineCount, Position& position);
void Loadquietlabeled(std::vector<std::pair<Position, double>>& positions, std::string& line, int lineCount, Position& position);
void PrintIteration(double error, std::vector<int*>& params, std::vector<double> paramiterValues, double step_size, int iteration);
double CalculateError(std::vector<std::pair<Position, double>>& positions, ThreadData& data, double k, unsigned int subset);
double CalculateK(std::vector<Position>& positionList, std::vector<double>& positionScore, std::vector<double>& positionResults);