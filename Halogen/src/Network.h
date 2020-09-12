#pragma once
#include "fixed.h"
#include <array>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <random>
#include <numeric>
#include <algorithm>
#include <sstream>

constexpr auto INPUT_NEURONS = 12 * 64 - 32 + 1 + 4;

typedef BasicFixedReal<16> real;

struct trainingPoint
{
    trainingPoint(std::array<bool, INPUT_NEURONS> input, double gameResult);

    std::array<bool, INPUT_NEURONS> inputs;
    double result;
};

struct deltaPoint
{
    size_t index;
    int delta;
};

struct Neuron
{
    Neuron(const std::vector<real>& Weight, real Bias);
    real FeedForward(std::vector<real>& input) const;
    void Backpropogate(real delta_l, const std::vector<real>& prev_weights, real learnRate);
    void WriteToFile(std::ofstream& myfile);

    std::vector<real> weights;
    real bias;

    std::vector<real> grad;       //for adagrad
};

struct HiddenLayer
{
    HiddenLayer(std::vector<real> inputs, size_t NeuronCount);    // <for first neuron>: weight1, weight2, ..., weightN, bias, <next neuron etc...>
    std::vector<real> FeedForward(std::vector<real>& input);
    void Backpropogate(const std::vector<real>& delta_l, const std::vector<real>& prev_weights, real learnRate);
    void WriteToFile(std::ofstream& myfile);

    std::vector<Neuron> neurons;

    //cache for backprop after feedforward
    std::vector<real> zeta;    //weighted input     
    static std::vector<real> activationPrime(std::vector<real> x);

    void ApplyDelta(std::vector<deltaPoint>& deltaVec, real forward);            //incrementally update the connections between input layer and first hidden layer

private:

    std::vector<real> weightTranspose; //first neuron first weight, second neuron first weight etc...
};

struct Network
{
    Network(std::vector<std::vector<real>> inputs, std::vector<size_t> NeuronCount);
    real FeedForward(std::vector<real> inputs);
    double Backpropagate(trainingPoint data, real learnRate);
    void WriteToFile();
    void Learn();

    void ApplyDelta(std::vector<deltaPoint>& delta);            //incrementally update the connections between input layer and first hidden layer
    void ApplyInverseDelta(std::vector<deltaPoint>& delta);     //for un-make moves
    real QuickEval();                                                         //when used with above, this just calculates starting from the alpha of first hidden layer and skips input -> hidden

private:
    static std::vector<trainingPoint> quietlabeledDataset();
    static std::vector<trainingPoint> Stockfish3PerDataset();
    size_t inputNeurons;

    void AddExtraNullLayer(size_t neurons);   //given a network add another hidden layer at the end that wont change network output.

    //cache for backprop after feedforward (these are for the output neuron)
    real zeta;      //weighted input
    double alpha;   //result after activation function

    std::vector<HiddenLayer> hiddenLayers;
    Neuron outputNeuron;
};

void Learn();

Network InitNetwork(std::string file);
Network CreateRandom(std::vector<size_t> NeuronCount);