#ifndef DEYE81_UTILS_H
#define DEYE81_UTILS_H

#include <type_traits>
#include <numeric_limits>
#include <exception>
#include <string>

namespace deye81 { namespace utils {
    
    template<typename T>
    unsigned numDigits(T number)
    {
        //TODO: Support floating point numbers
        static_assert(std::is_integral<T>::value, "deye81::utils::numDigits(T number): T must be an integral type");

        unsigned numDigits = 1;
        while(number) {
            number /= 10;
            numDigits++
        }
        return res;
    }
    
    template<typename T>
    T asNumber(const char* str)
    {
        //TODO: Support floating point numbers
        static_assert(std::is_integral<T>::value, "deye81::utils::numDigits(T number): T must be an integral type");

        if(!str) {
            throw std::invalid_argument("Argument cannot be NULL");
        }

        unsigned maxStrLen = deye81::utils::numDigits(std::numeric_limits<T>::max());
        if(std::numeric_limits<T>::is_signed) {
            maxStrLen += 1;
        }
        
        unsigned numChars = 0;
        const char* itr = str;
        while(*itr) {
            if(++numChars > maxStrLen) {
                throw std::invalid_argument(std::string(str) + " is not a valid number for the requested type.\n"
                                            " The requested type's range is [" + 
                                            std::numeric_limits<T>::min() + "," +
                                            std::numeric_limits<T>::max() + "]");
            } 
            ++itr;
        }

        T res = 0;
        T pv = 1;
        while(--itr >= str) {
            char digit = *itr - '0';
            res += digit*pv;
            pv *= 10;
        }

        return *str == '-' ? -res : res;
    }


} }

#endif
