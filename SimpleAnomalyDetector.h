//
// Created by oziyo on 09/11/2020.
//

#ifndef FLIGHTSIMULATOR_SIMPLEANOMALYDETECTOR_H
#define FLIGHTSIMULATOR_SIMPLEANOMALYDETECTOR_H

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;

    bool operator<(const correlatedFeatures& cor) const {
        return corrlation < cor.corrlation;
    }

    bool operator>(const correlatedFeatures& cor) const {
        return corrlation > cor.corrlation;
    }
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    vector<correlatedFeatures> cf;
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);

    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }

};

#endif //FLIGHTSIMULATOR_SIMPLEANOMALYDETECTOR_H

/*
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#endif /* SIMPLEANOMALYDETECTOR_H_ */
