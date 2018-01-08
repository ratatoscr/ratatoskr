#include "Individual.h"

Individual::Individual(Configuration &configuration, Cost *cost, FeatureMap *featuremap, Fitness *fitness)
        : Prototype(configuration)
{
    this->cost = cost;
    this->featuremap = featuremap;
    this->fitness = fitness;
}

Individual::~Individual() {
    delete cost;
    delete featuremap;
    delete fitness;
}

float Individual::relevance(float fraction) {
    fraction = fraction < 0? 0 : fraction;
    fraction = fraction > 1? 1: fraction;
    return 1 / (1 + (1 - fraction) * fitness->getFitness() + fraction * cost->getCost());
}

Cost & Individual::getCost() const {
    return *cost;
}

FeatureMap & Individual::getFeaturemap() const {
    return *featuremap;
}

Fitness & Individual::getFitness() const {
    return *fitness;
}

bool Individual::isEvaluated() const {
    return evaluated;
}

void Individual::setEvaluated(const bool evaluated) {
    this->evaluated = evaluated;
}

Individual::Individual(const Individual &obj) : Prototype(obj) {
    cost = obj.cost->clone();
    featuremap = obj.featuremap->clone();
    fitness = obj.fitness->clone();
}