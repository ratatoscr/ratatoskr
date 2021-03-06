#ifndef RATATOSKR_BITVECTORMUTATION_H
#define RATATOSKR_BITVECTORMUTATION_H


#include "../../core/variation/BreedingOperator.h"
#include "../common/Configuration.h"

/**
 * The bit flip mutation breeding operator as described in "Melanie Mitchell: An Introduction to
 * Genetic Algorithms (1996)."
 *
 * @author  Felix Voelker
 * @version 0.1.0
 * @since   25.1.2018
 */
class BitVectorMutation : public BreedingOperator {

public:
    explicit BitVectorMutation(const common::Configuration &configuration);

    BitVectorMutation * clone() const override;

protected:
    float pm;

    BitVectorMutation(const BitVectorMutation &obj);

    unsigned long expectedSources() const override;

    /**
     * Performs a bit flip on each locus of the parents' chromosomes with a probability pm.
     * @param parents Parent individuals to be mutated.
     * @param thread  The variating thread.
     */
    std::vector<Individual *> & breed(std::vector<Individual *> &parents, Thread &thread) const override;

};


#endif //RATATOSKR_BITVECTORMUTATION_H
