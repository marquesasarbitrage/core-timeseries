#include "../../include/core-timeseries/errors/timeserie.hpp"

namespace TimeSerieErrorRegistry {

    namespace TimeSerie {

        std::string InvalidSizeError::getErrorMessage() const {return "A time serie must be represented by at least 2 points.";}

        std::string StartDateAfterEndDateError::getErrorMessage() const {return "When getting a sub time serie, the given start date must come before the end date.";}

        std::string InvalidReferenceDateError::getErrorMessage() const {return "The reference date must be within the min/max range observed within the time serie.";}

    }
}

