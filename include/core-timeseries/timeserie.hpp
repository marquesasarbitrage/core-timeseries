#pragma once 
#include <iostream>
#include <map>
#include "core-datetime/sequence.hpp"
#include "core-math/interpolation.hpp"
#include "errors/main.hpp"

class TimeSerie {

    public: 
        TimeSerie(const std::map<DateTime, double>& timeSerie); 
        ~TimeSerie() = default;

        TimeDelta getTimeDelta() const;
        bool isRegular() const;
        int getSize() const;
        LinearInterpolation getInterpolatedData() const;

        double getPoint(const DateTime& referenceDate) const; 
        TimeSerie getSub(const DateTime& startDate, const DateTime& endDate) const;
        
        //TimeSerie getRegularizedByInterpolation() const; 
        //TimeSerie getRegularized() const; 

    private: 
        DatetimeSequence timeSequence_; 
        std::vector<double> points_;
        TimeDelta timeDelta_;
        bool isRegular_;
        
};

