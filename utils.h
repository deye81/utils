#ifndef DEYE81_UTILS_H
#define DEYE81_UTILS_H

#include <type_traits>
#include <limits>
#include <exception>
#include <string>

namespace deye81 { namespace utils {
    
    template<typename T>
    unsigned char numDigits(T number)
    {
        //TODO: Support floating point numbers
        static_assert(std::is_integral<T>::value, "deye81::utils::numDigits(T number): T must be an integral type");

        unsigned char numDigits = 0;

        do {
            numDigits++;
            number /= 10;
        } while(number);

        return numDigits;
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
                                            std::to_string(std::numeric_limits<T>::min()) + "," +
                                            std::to_string(std::numeric_limits<T>::max()) + "]");
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
    
    template<typename T>
    std::string asString(T number)
    {
        using namespace std;

        // TODO: Support floating-point numbers
        static_assert(is_integral<T>::value, "Non-integral types can't be converted to strings");
        
        // Build a string whose size is the number of digits in the number
        auto strLen = numDigits(number) + 1;
        unique_ptr<char[]> strBuffer(new char[strLen]);
        strBuffer[strLen] = '\0'; 
        
        // Iterate over the string in the reverse direction while inserting digits from
        // the number
        auto idx = strLen - 2;  
        while(number) {
            strBuffer[idx--] = (number % 10) + '0';
            number /= 10;
        }

        // Done 
        return string(strBuffer.get());
    }


} }

#endif
