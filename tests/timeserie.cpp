#include <iostream>
#include <cassert>
#include "../include/core-timeseries/timeserie.hpp"

std::vector<double> getRawData() {

    std::vector<double> values = {
        100.000, 110.000, 118.800, 119.988, 122.388,
        117.492, 116.317, 119.807, 110.222, 101.405,

        103.433, 105.501, 113.941, 125.335, 120.322,
        129.948, 120.851, 114.809, 107.920, 112.237,

        115.604, 104.044,  97.801, 107.581,  97.899,
        106.710, 101.374, 100.361, 100.361, 109.393,

        107.205, 106.133, 115.685, 116.842, 111.000,
        109.890, 108.791, 110.967, 110.967, 122.064,

        109.857, 106.562,  96.971,  99.880, 102.877,
        104.934,  96.539
    };

    return values;
}

TimeSerie getRegularTimeSerie() {

    DateTime initialDate(2026,12,5); 
    TimeDelta dt(1,0,0,0,0,0,0);
    std::vector<double> points = getRawData();
    std::map<DateTime, double> data = {{initialDate, points[0]}};

    for (int i = 1; i<points.size(); i++) {

        initialDate += dt;
        data[initialDate] = points[i];
    }

    return TimeSerie(data);
}

void testRegularTimeSerie() {

    TimeSerie ts = getRegularTimeSerie(); 
    assert(ts.isRegular() == true); 
    assert(ts.getSize() == 47); 
    assert(ts.getTimeDelta() == TimeDelta(1,0,0,0,0,0,0)); 

    assert(ts.getPoint(DateTime(2026, 12, 20))==129.948);
    assert(ts.getPoint(DateTime(2027, 1, 18))==102.877);

    assert(ts.getPoint(DateTime(2026, 12, 20, 18,0,0))==129.948);
    assert(ts.getPoint(DateTime(2027, 1, 18, 18,0,0))==102.877);

    try {
        double onePoint = ts.getPoint(DateTime(2027, 1, 20, 18,0,0));
        assert(false);
    } catch (const TimeSerieErrorRegistry::TimeSerie::InvalidReferenceDateError& e) {

        assert(true);
    }

    assert(ts.getSub(DateTime(2026, 12, 4),DateTime(2027, 1, 21)).getSize() == 47);
    assert(ts.getSub(DateTime(2026, 12, 11),DateTime(2026, 12, 17)).getSize() == 7);


}


int main() {

    testRegularTimeSerie();
    std::cout << "All tests for the Time Serie object have been passed successfully!" << std::endl;
    return 0;
}