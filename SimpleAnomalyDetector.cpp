//
// Created by oziyo on 09/11/2020.
//

#include <queue>
#include "SimpleAnomalyDetector.h"
#include <map>

SimpleAnomalyDetector::SimpleAnomalyDetector() {}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {}

/*void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    priority_queue<correlatedFeatures> orderedCorrelates;               //todo make sure can use with struct operators
    vector<string> features = ts.getFeatures();
    map<string, vector<float>> table = ts.getTable();
    int colSize = ts.getColLength();
    // runs over all features as left features
    for (int i = 0; i < features.size(); i++) {
        string fea1 = features[i];
        // runs over all features right to fea1
        for (int j = i + 1; j < features.size(); j++) {
            string fea2 = features[j];
            // correlation between features
            float pear = pearson(table[fea1].data(), table[fea2].data(), colSize);
            if (abs(pear) >= 0.9)  {                         //todo make sure abs
                correlatedFeatures correlated = {fea1, fea2, pear, Line(), 0};       // todo maybe pass 0 0
                orderedCorrelates.push(correlated);
            }
        }
    }
    // map of features and info whether still didnt got inserted into "cf".
    map<string, bool> notUsed;
    for (string fea : features) {
        notUsed[fea] = true;
    }
    // runs over orderedCorrelates queue till empty.
    while (!orderedCorrelates.empty()) {
        correlatedFeatures corr = orderedCorrelates.top();
        orderedCorrelates.pop();
        if (notUsed[corr.feature1] && notUsed[corr.feature2]) {
            // lin_reg and distance
            Point** points = new Point*[colSize];
            // runs over both features cols and creates a point of 2 features values at each row.
            for (int i = 0; i < colSize; i++) {
                Point *p = new Point(table[corr.feature1][i], table[corr.feature2][i]);
                points[i] = p;
            }
            Line reg = linear_reg(points, colSize);
            float maxDis = 0;
            float distance = 0;
            for (int i = 0; i < colSize; i++) {
                distance = abs(reg.f(points[i]->x) - points[i]->y);
                if (distance > maxDis) {
                    maxDis = distance;
                }
            }
            maxDis *= 1.2;                             //todo maybe add little num avoid 0 and move to detect
            corr.lin_reg = reg;
            corr.threshold = maxDis;
            cf.push_back(corr);
            notUsed[corr.feature1] = false;
            notUsed[corr.feature2] = false;
            for (int i = 0; i < colSize; ++i) {
                delete points[i];
            }
            delete[] points;
        }
    }
}
*/

/**
 * return new correlatedFeatures to add to cf.
 */
correlatedFeatures createCorrFea(string fea, string matchedFea, map<string, vector<float>> table,
              vector<string> features, int colSize, float corr) {
    // lin_reg and distance
    Point** points = new Point*[colSize];
    // runs over both features cols and creates a point of 2 features values at each row.
    for (int i = 0; i < colSize; i++) {
        Point *p = new Point(table[fea][i], table[matchedFea][i]);
        points[i] = p;
    }
    Line reg = linear_reg(points, colSize);
    float maxDis = 0;
    float distance = 0;
    for (int i = 0; i < colSize; i++) {
        distance = fabs(reg.f(points[i]->x) - points[i]->y);
        if (distance > maxDis) {
            maxDis = distance;
        }
    }
    // making threshold a bit bigger for end cases.
    maxDis *= 1.2;
    correlatedFeatures correlated = {fea, matchedFea, corr, reg, maxDis};
    for (int i = 0; i < colSize; ++i) {
        delete points[i];
    }
    delete[] points;
    return correlated;
 }

/**
 * gets a ts and use it to learn correlation between features.
 * @param ts a TimeSeries.
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    // features - vector of ordered features. table - the table of ts.
    vector<string> features = ts.getFeatures();
    map<string, vector<float>> table = ts.getTable();
    int colSize = ts.getColLength();
    // runs over all features as left features
    for (int i = 0; i < features.size(); i++) {
        string fea1 = features[i];
        // maxCor - biggest correlation found for fea1. matchedFea - the feature who has maxCor with fea1.
        float maxCor = 0;
        string matchedFea = "";
        // runs over all features right to fea1
        for (int j = i + 1; j < features.size(); j++) {
            string fea2 = features[j];
            // correlation between features
            float pear = pearson(table[fea1].data(), table[fea2].data(), colSize);
            if (fabs(pear) >= 0.9 && fabs(pear) > maxCor)  {
                maxCor = fabs(pear);
                matchedFea = fea2;
            }
        }
        // if correlation was found update 'cf' and add new correlatedFeatures.
        if (maxCor > 0) {
            cf.push_back(createCorrFea(fea1, matchedFea, table, features, colSize, maxCor));
        }
    }
}

/**
 * detect anomaly according to normal known correlation.
 * @param ts
 * @return a vector of AnomalyReports.
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    // detected - vector of anomalies to return.
    vector<AnomalyReport> detected;
    // features - vector of ordered features. table - the table of ts.
    vector<string> features = ts.getFeatures();
    map<string, vector<float>> table = ts.getTable();
    int colLength = ts.getColLength();
    // runs over normal correlations and check if a point is over the threshold of correlatedFeatures.
    for (correlatedFeatures correlated: cf) {
        for (int i = 0; i < colLength; i++) {
            Point p(table[correlated.feature1][i], table[correlated.feature2][i]);
            float dis = dev(p, correlated.lin_reg);
            //cout << "@@@@@@@@@@@@@@@" << dis << "       " << correlated.lin_reg.a << correlated.lin_reg.b << endl;
            if (dis > correlated.threshold) {
                string description = correlated.feature1 + "-" + correlated.feature2;
                AnomalyReport ar(description, i + 1);
                detected.push_back(ar);
                cout << "--- " << ar.description << ", " << ar.timeStep << ", " << correlated.threshold
                << ", " << dis << endl;
            }
        }
    }
    return detected;
}

//todo:    is every feature can be in one pair (as above) or can be 'y' for other pairs?