#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "wrapper/core/CostWrapper.h"
#include "wrapper/core/FeatureMapWrapper.h"
#include "wrapper/core/FitnessWrapper.h"
#include "wrapper/core/IndividualWrapper.h"
#include "wrapper/core/ProblemWrapper.h"
#include "wrapper/core/SessionWrapper.h"


using namespace boost::python;

BOOST_PYTHON_MODULE(core) {
    class_<std::vector<float>>("std::vector<float>")
            .def(vector_indexing_suite<std::vector<float>>());

    class_<ProblemWrapper, boost::noncopyable>("Problem", init<unsigned int>())
            .add_property("popsize", &Problem::getPopsize, &Problem::setPopsize)
            .def("__copy__", pure_virtual(&Problem::clone), return_value_policy<manage_new_object>());
//            .def("eval", pure_virtual(&Problem::eval));

    class_<FeatureMapWrapper, boost::noncopyable>("FeatureMap", init<boost::shared_ptr<Session>>())
            .def("__copy__", pure_virtual(&FeatureMap::clone), return_value_policy<manage_new_object>());

    class_<FitnessWrapper, boost::noncopyable>("Fitness", init<boost::shared_ptr<Session>>())
            .add_property("fitness", &Fitness::getFitness, &Fitness::setFitness)
            .def("__copy__", &Fitness::clone, return_value_policy<manage_new_object>())
            .def("isideal", &Fitness::isIdeal, &FitnessWrapper::default_isIdeal)
            .def("__lt__", &Fitness::operator<, &FitnessWrapper::default_lt)
            .def("__le__", &Fitness::operator<=, &FitnessWrapper::default_leq)
            .def("__gt__", &Fitness::operator>, &FitnessWrapper::default_gt)
            .def("__ge__", &Fitness::operator>=, &FitnessWrapper::default_geq)
            .def("__eq__", &Fitness::operator==, &FitnessWrapper::default_eq)
            .def("__neq__", &Fitness::operator!=, &FitnessWrapper::default_neq);

    class_<CostWrapper, boost::noncopyable>("Cost", init<boost::shared_ptr<Session>>())
            .add_property("cost", &Cost::getCost, &Cost::setCost)
            .def("__copy__", &Cost::clone, return_value_policy<manage_new_object>())
            .def("error", &Cost::error)
            .def("__lt__", &Cost::operator<, &CostWrapper::default_lt)
            .def("__le__", &Cost::operator<=, &CostWrapper::default_leq)
            .def("__gt__", &Cost::operator>, &CostWrapper::default_gt)
            .def("__ge__", &Cost::operator>=, &CostWrapper::default_geq)
            .def("__eq__", &Cost::operator==, &CostWrapper::default_eq)
            .def("__neq__", &Cost::operator!=, &CostWrapper::default_neq);

    class_<IndividualWrapper, boost::noncopyable>("Individual", init<boost::shared_ptr<Session>>())
            .add_property("evaluated", &Individual::isEvaluated, &Individual::setEvaluated)
            .def("__copy__", &Individual::clone, return_value_policy<manage_new_object>())
            .def("relevance", &Individual::relevance)
            .def("tostring", pure_virtual(&Individual::toString))
            .def("getCost", &Individual::getCost, return_internal_reference<>())
            .def("getFeaturemap", &Individual::getFeaturemap, return_internal_reference<>())
            .def("getFitness", &Individual::getFitness, return_internal_reference<>());

    class_<SessionWrapper, boost::noncopyable>("Session", init<boost::shared_ptr<Problem>>())
            .add_property("epochs", &Session::getEpochs, &Session::setEpochs)
            .add_property("episodes", &Session::getEpisodes, &Session::setEpisodes)
            .add_property("generations", &Session::getGenerations, &Session::setGenerations)
            .add_property("complete", &Session::isComplete, &Session::setComplete)
            .add_property("evalthreads", &Session::getEvalthreads, &Session::setEvalthreads)
            .add_property("varythreads", &Session::getVarythreads, &Session::setVarythreads)
            .add_property("learning_rate", &Session::getLearningRate, &Session::setLearningRate)
            .add_property("discount_factor", &Session::getDiscountFactor, &Session::setDiscountFactor)
            .add_property("fitness", make_function(&Session::getFitness, return_value_policy<manage_new_object>()), &SessionWrapper::pyFitness)
            .def("fitness", pure_virtual(&Session::setFitness));

//            .def("getNetwork", pure_virtual(static_cast<void(Session::*)(EvolutionaryNetwork&)>(&Session::getNetwork)))
//            .def("getBuilder", pure_virtual(static_cast<void(Session::*)(Builder&)>(&Session::getBuilder)))
//            .def("setCost", pure_virtual(static_cast<void(Session::*)(Cost&)>(&Session::getCost)))
//            .def("getFeaturemap", pure_virtual(static_cast<void(Session::*)(FeatureMap&)>(&Session::getFeaturemap)))
//            .def("getIndividual", pure_virtual(static_cast<void(Session::*)(Individual&)>(&Session::getIndividual)))
//            .def("getPipeline", pure_virtual(static_cast<void(Session::*)(BreedingOperator&)>(&Session::getPipeline)));

//    class_<Statistics>("Statistics", init<Session &>())
//            .def("bestFitnesses", static_cast<vector<float>(Statistics::*)(unsigned int)const>(&Statistics::bestFitnesses))
//            .def("averageFitnesses", static_cast<vector<float>(Statistics::*)(unsigned int)const>(&Statistics::averageFitnesses))
//            .def("worstFitnesses", static_cast<vector<float>(Statistics::*)(unsigned int)const>(&Statistics::worstFitnesses));

//    class_<EvolutionarySystem>("EvolutionarySystem", init<Session &>())
//            .add_property("statistics", &EvolutionarySystem::getStatistics)
//            .def("run", &EvolutionarySystem::run);
}