//
// Created by oziyo on 09/11/2020.
//

#include "timeseries.h"

TimeSeries::TimeSeries(const char *CSVfileName) {
    ifstream file;
    file.open(CSVfileName);                             //todo check if open
    string line;
    getline(file, line);
    stringstream ss(line);
    // first line - strings vector
    while (getline(ss, line, ',')) {
        m_orderedFeatures.push_back(line);
        m_featuresNum++;
    }
    // rest lines seperately
    while(getline(file, line)) {
        addRowData(line);
    }
    file.close();
}

map<string, vector<float>> TimeSeries::getTable() const{
    return m_features;
}
vector<float> TimeSeries::featureValues(string feature) {
    return m_features[feature];
}

vector<string> TimeSeries::getFeatures() const{
    return m_orderedFeatures;
}

/**
 * returns num of elements for each feature. all feature must have same amount.
 * @return num of rows in table without feature.
 */
int TimeSeries::getColLength() const{
    return colLength;
}

void TimeSeries::addRowData(float* rowData, int size) {
    for (int i = 0; i < size; i++) {
        m_features[m_orderedFeatures[i]].push_back(rowData[i]);
    }
    colLength++;
}

void TimeSeries::addRowData(string line) {
    stringstream ss(line);
    int i = 0;
    // each line goes into different float vector (each vector is part of table).
    while (getline(ss, line, ',')) {
        m_features[m_orderedFeatures[i]].push_back(stof(line));             //todo working??
        i++;
    }
    colLength++;
}

//todo - need to get specific row?
// todo - get i val in feature j
// todo - get more info from csv file - need to learn appeand?
// todo - whats up with const \ const char \ string
// todo maybe need to cancel fea amount