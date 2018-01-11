#include "Session.h"
#include "BitVectorCrossover.h"
#include "../common/FitnessProportionateSelection.h"

ndga::Session::Session(common::Problem &problem) : core::Session(problem) {
    configuration = new common::Configuration(dynamic_cast<common::Configuration::ProblemConfiguration &>(problem.getConfiguration()));
}

ndga::Session::Session(common::Problem &problem, Configuration *config) : core::Session(problem, config) {}

EvolutionarySystem* ndga::Session::build() {
    return core::Session::build(constructDefaultBuilder(), constructDefaultNetwork(), constructDefaultVariation());
}

EvolutionarySystem* ndga::Session::build(RandomBitVectorBuilder *builder) {
    return core::Session::build(builder, constructDefaultNetwork(), constructDefaultVariation());
}

EvolutionarySystem* ndga::Session::build(TransitionTable *network) {
    return core::Session::build(constructDefaultBuilder(), network, constructDefaultVariation());
}

EvolutionarySystem* ndga::Session::build(BreedingOperator *variation_tree) {
    return core::Session::build(constructDefaultBuilder(), constructDefaultNetwork(), variation_tree);
}

EvolutionarySystem* ndga::Session::build(RandomBitVectorBuilder *builder, TransitionTable *network) {
    return core::Session::build(builder, network, constructDefaultVariation());
}

EvolutionarySystem* ndga::Session::build(RandomBitVectorBuilder *builder, BreedingOperator *variation_tree) {
    return core::Session::build(builder, constructDefaultNetwork(), variation_tree);
}

EvolutionarySystem* ndga::Session::build(TransitionTable *network, BreedingOperator *variation_tree) {
    return core::Session::build(constructDefaultBuilder(), network, variation_tree);
}

RandomBitVectorBuilder * ndga::Session::constructDefaultBuilder() {
    auto *config = dynamic_cast<common::Configuration *>(configuration);
    auto *cost = new Cost(*configuration);
    auto *featuremap = new FeatureVector(*config);
    auto *fitness = new Fitness(*configuration);
    auto *individual = new VectorIndividual(*config, cost, featuremap, fitness);
    return new RandomBitVectorBuilder(*config, individual);
}

TransitionTable * ndga::Session::constructDefaultNetwork() {
    auto *config = dynamic_cast<common::Configuration *>(configuration);
    return new TransitionTable(*config);
}

BitVectorMutation * ndga::Session::constructDefaultVariation() {
    auto *config = dynamic_cast<common::Configuration *>(configuration);
    auto *selector1 = new FitnessProportionateSelection(*config);
    selector1->setup(*new std::vector<VariationSource *>(0));
    auto *selector2 = new FitnessProportionateSelection(*config);
    selector2->setup(*new std::vector<VariationSource *>(0));
    auto *crossover = new BitVectorCrossover(*config);
    crossover->setup(*new std::vector<VariationSource *>(2) = { selector1, selector2 });
    auto *mutation = new BitVectorMutation(*config);
    mutation->setup(*new std::vector<VariationSource *>(1) = { crossover });
    return mutation;
}