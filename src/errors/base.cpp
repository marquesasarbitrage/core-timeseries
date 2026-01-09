#include "../../include/core-timeseries/errors/base.hpp"

namespace TimeSerieErrorRegistry {

    const char* TimeSerieLibraryError::what() const noexcept {

        if (cachedMessage_.empty()) {

                cachedMessage_ = getErrorMessage();  
        }

        return cachedMessage_.c_str();
    }
}