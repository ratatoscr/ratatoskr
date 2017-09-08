#include "FeatureMapWrapper.h"

FeatureMapWrapper::FeatureMapWrapper(boost::shared_ptr<Session> session) : FeatureMap(*session) {}

FeatureMap* FeatureMapWrapper::clone() const {
    return this->get_override("clone")();
}