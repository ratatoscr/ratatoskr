#include "SimpleSelectionOperator.h"

SimpleSelectionOperator::SimpleSelectionOperator(Configuration &configuration) : SelectionOperator(configuration) {}

Individual* SimpleSelectionOperator::select(std::vector<Individual *> &parents, Thread &thread) const {
    return parents.at(0);
}
