#ifndef RATATOSKR_SELECTIONOPERATOR_H
#define RATATOSKR_SELECTIONOPERATOR_H


#include "VariationSource.h"

/**
 * The abstract base class for selection operators in a Neuro-Dynamic Evolutionary Algorithm (NDEA). These operators
 * form the leafs of variation trees and simply select a parent from the current population of the evolutionary system.
 * Accordingly, each selection operator may not have any children.
 *
 * @author  Felix Voelker
 * @version 0.1.0
 * @since   25.1.2018
 */
class SelectionOperator : public VariationSource {

public:
    explicit SelectionOperator(const core::Configuration &configuration);

    virtual SelectionOperator * clone() const = 0;

protected:
    SelectionOperator(const SelectionOperator &obj) = default;

    unsigned long expectedSources() const override;

    /**
     * Selects a parent according to the operator's strategy.
     * @param parents A list of parent individuals.
     * @param epoch   Current epoch of the evolutionary run.
     * @param thread  The variating thread.
     */
    virtual Individual * select(std::vector<Individual *> &parents, Thread &thread) const = 0;

    std::vector<Individual *> perform(std::vector<Individual *> &parents, Thread &thread) const override;

};


#endif //RATATOSKR_SELECTIONOPERATOR_H