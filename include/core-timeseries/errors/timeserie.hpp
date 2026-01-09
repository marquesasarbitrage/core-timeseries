#pragma once 
#include <iostream>
#include "base.hpp"

namespace TimeSerieErrorRegistry {

    namespace TimeSerie {

        class InvalidSizeError final: public TimeSerieLibraryError {
            protected: 
                std::string getErrorMessage() const override; 
        };

        class StartDateAfterEndDateError final: public TimeSerieLibraryError {
            protected: 
                std::string getErrorMessage() const override; 
        };

        class InvalidReferenceDateError final: public TimeSerieLibraryError {
            protected: 
                std::string getErrorMessage() const override; 
        };
    }
}