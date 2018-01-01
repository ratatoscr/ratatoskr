#ifndef RATATOSKR_SIMPLESELECTIONOPERATOR_H
#define RATATOSKR_SIMPLESELECTIONOPERATOR_H


#include "../../../core/variation/SelectionOperator.h"

/**
 * A simple instance of SelectionOperator to test core functionality.
 *
 * @author  Felix Voelker
 * @version 0.0.2
 * @since   31.12.2017
 */
class SimpleSelectionOperator : public SelectionOperator {

public:
    explicit SimpleSelectionOperator(Session &session);

    Individual * select(std::vector<Individual *> &parents, unsigned int epoch, Thread &thread) const override;

};


#endif //RATATOSKR_SIMPLESELECTIONOPERATOR_H