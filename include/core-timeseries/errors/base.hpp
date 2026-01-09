#pragma once 
#include <iostream>
#include <exception>

namespace TimeSerieErrorRegistry {


    class TimeSerieLibraryError: public std::exception {

        public:
            const char* what() const noexcept override;
            explicit TimeSerieLibraryError(){};
            virtual ~TimeSerieLibraryError() = default;
        protected: 
            virtual std::string getErrorMessage() const = 0; 
        private:
            mutable std::string cachedMessage_;  // must be mutable to modify in const what()
    };

    

}