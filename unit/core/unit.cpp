#define CATCH_CONFIG_MAIN


#include <catch.hpp>
#include "util/SimpleProblem.h"
#include "util/SimpleSession.h"
#include "../../core/representation/Cost.h"
#include "util/SimpleIndividual.h"

/**
 * Unit tests for the core functionality of an evolutionary system.
 *
 * @author  Felix Voelker
 * @version 0.0.2
 * @since   1.12.2017
 */
TEST_CASE("Core", "[core]") {
    auto problem = new SimpleProblem(1);
    auto session = new SimpleSession(*problem);
    SECTION("Cost") {
        auto *c1 = new Cost(*session);
        c1->setCost(2);
        auto *c2 = new Cost(*session);
        c2->setCost(5);
        auto *c3 = new Cost(*session);
        c3->setCost(0);

        SECTION("Checking computation of error...") {
            REQUIRE(c1->error(1, 0.5, 0) == -1.5);
            REQUIRE(c2->error(1, 0.5, 2) == -2.5);
            REQUIRE(c3->error(1, 0.5, 0) == 0.5);
        }

        SECTION("Checking comparison of costs...") {
            REQUIRE(*c1 > *c2);
            REQUIRE(*c2 < *c3);
            REQUIRE(*c1 < *c3);
        }

        delete(c1);
        delete(c2);
        delete(c3);
    }
    SECTION("Fitness") {
        auto *f1 = new Fitness(*session);
        f1->setFitness(2);
        auto *f2 = new Fitness(*session);
        f2->setFitness(5);
        auto *f3 = new Fitness(*session);
        f3->setFitness(0);

        SECTION("Checking optimality of fitnesses...") {
            REQUIRE(!f1->isIdeal());
            REQUIRE(!f2->isIdeal());
            REQUIRE(f3->isIdeal());
        }
        SECTION("Checking comparison of fitnesses...") {
            REQUIRE(*f1 > *f2);
            REQUIRE(*f2 < *f3);
            REQUIRE(*f1 < *f3);
        }

        delete(f1);
        delete(f2);
        delete(f3);
    }
    SECTION("Individual") {
        auto *i1 = session->getIndividual();
        i1->getFitness().setFitness(2.5);
        i1->getCost().setCost(5);

        SECTION("Checking computation of relevance...") {
            REQUIRE(i1->relevance(-1) == static_cast<float>(1 / (1 + 2.5)));
            REQUIRE(i1->relevance(0.5) == static_cast<float>(1 / (1 + 3.75)));
            REQUIRE(i1->relevance(2) == static_cast<float>(1 / (1 + 5.0)));
        }

        SECTION("Checking cloning...") {
            auto *i2 = i1->clone();
            REQUIRE(i1 != i2);
            REQUIRE(i1->getCost().getCost() == i2->getCost().getCost());
            REQUIRE(i1->getFitness().getFitness() == i2->getFitness().getFitness());
            delete(i2);
        }
    }
    /*SECTION("Problem") {
        auto task = new SimpleProblem(1);
        auto session = new SimpleSession(*task);
        auto pop = new Population(*session);
        SECTION("Evaluating an individual...") {
            pop->initialize();

            auto evaluator = new Evaluator(*session);
            evaluator->evaluatePopulation(*pop);

            REQUIRE(pop->getIndividuals().at(0)->getRelevance().getFitness().fitness() == 1);
        }

        delete session;
        delete task;
    }
    SECTION("Evaluator") {
        auto task = new SimpleProblem(10);
        auto session = new SimpleSession(*task);
        SECTION("Checking evaluation...") {
            auto pop = new Population(*session);
            pop->initialize();

            auto evaluator = new Evaluator(*session);
            evaluator->evaluatePopulation(*pop);

            bool all_ones = true;
            for (auto individual : pop->getIndividuals())
                all_ones &= individual->getRelevance().getFitness().setFitness() == 1;

            REQUIRE(all_ones);
        }

        SECTION("Checking multithreading...") {
            session->setEvalthreads(4);

            auto pop = new Population(*session);
            pop->initialize();

            auto evaluator = new Evaluator(*session);
            evaluator->evaluatePopulation(*pop);

            bool all_ones = true;
            for (auto setIndividual : pop->getIndividuals())
                all_ones &= getIndividual->getRelevance().getFitness().getFitness() == 1;

            REQUIRE(all_ones);
        }

        delete session;
        delete task;
    }

    SECTION("VariationSource") {
        SECTION("Check initialization...") {
            bool initialized = false;
            vector<VariationSource *> sources(1);
            sources.at(0) = new FitnessProportionateSelection(*session);
            TestSource source = TestSource(*session);
            source.connect(sources);
            initialized = true;
            REQUIRE(initialized);
        }
    }*/

    delete session;
    delete problem;
}