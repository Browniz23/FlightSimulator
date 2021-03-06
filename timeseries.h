//
// Created by oziyo on 09/11/2020.
//

#ifndef FLIGHTSIMULATOR_TIMESERIES_H
#define FLIGHTSIMULATOR_TIMESERIES_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class TimeSeries{
private:
    int colLength = 0;
    int m_featuresNum = 0;
    vector<string> m_orderedFeatures;
    map<string, vector<float>> m_features;
public:
    TimeSeries(const char *CSVfileName);

    vector<float> featureValues(string feature);

    vector<string> getFeatures() const;

    void addRowData(float *rowData, int size);

    void addRowData(string line);

    map<string, vector<float>> getTable() const;

    int getColLength() const;
};

#endif //FLIGHTSIMULATOR_TIMESERIES_H


/*
#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#endif /* TIMESERIES_H_ */