#include "../include/core-timeseries/timeserie.hpp"

TimeSerie::TimeSerie(const std::map<DateTime, double>& timeSerie) {

    TimeDelta dt;
    bool isRegular = true;

    if (timeSerie.size() <= 1) throw TimeSerieErrorRegistry::TimeSerie::InvalidSizeError();

    std::set<DateTime> timestamps;
    std::vector<double> values;

    auto it = timeSerie.begin();
    auto prev = it++;
    dt = it->first - prev->first;  

    timestamps.insert(prev->first);
    values.push_back(prev->second);

    for (; it != timeSerie.end(); ++it) {

        if ((it->first - prev->first) != dt) {
            isRegular = false;
        }

        timestamps.insert(it->first);
        values.push_back(it->second);

        dt = std::max((it->first - prev->first), dt);
        prev = it;
    }

    timeSequence_ = DatetimeSequence(timestamps); 
    points_ = values; 
    timeDelta_ = dt;
    isRegular_ = isRegular;

}

TimeDelta TimeSerie::getTimeDelta() const { return timeDelta_; }

bool TimeSerie::isRegular() const { return isRegular_; }

int TimeSerie::getSize() const { return points_.size(); }

LinearInterpolation TimeSerie::getInterpolatedData() const {

    std::map<double,double> data; 
    std::vector<DateTime> timestamps(timeSequence_.get().begin(), timeSequence_.get().end());
    for (int i = 0; i<=getSize(); i++) {

        data[timestamps[i].getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()] = points_[i];
    }
    return LinearInterpolation(data);
}

double TimeSerie::getPoint(const DateTime& referenceDate) const {

    if (referenceDate<timeSequence_.getStart() or referenceDate>timeSequence_.getEnd()) throw TimeSerieErrorRegistry::TimeSerie::InvalidReferenceDateError();
    int i = timeSequence_.getIndex(referenceDate); 
    if (i == -1) {
        return points_[timeSequence_.getIndex(timeSequence_.getPrevious(referenceDate).value())];
    } else {

        return points_[i];
    }
}

TimeSerie TimeSerie::getSub(const DateTime& startDate, const DateTime& endDate) const {

    if (startDate>=endDate) throw TimeSerieErrorRegistry::TimeSerie::StartDateAfterEndDateError();
    int startIndex = timeSequence_.getIndex(startDate); 
    int endIndex = timeSequence_.getIndex(endDate); 
    if (startIndex == -1) startIndex = timeSequence_.getIndex(timeSequence_.getNext(startDate).value()); 
    if (endIndex == -1) endIndex = timeSequence_.getIndex(timeSequence_.getPrevious(endDate).value());

    std::map<DateTime, double> data;  
    std::vector<DateTime> timestamps = timeSequence_.getAsVector();
    for (int i = startIndex; i<=endIndex; i++) {

        data[timestamps[i]] = points_[i];
    }

    return TimeSerie(data);

}