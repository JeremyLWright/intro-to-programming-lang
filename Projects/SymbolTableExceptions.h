#ifndef _SYMBOLTABLEEXCEPTIONS
#define _SYMBOLTABLEEXCEPTIONS

/**
 * @brief Exceptions for the Symbol Table
 *
 * @par
 * Copyright Jeremy Wright (c) 2012 
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */

#include <stdexcept>
#include <string>

class IdentifierUndefined : public std::runtime_error {
    public:
    IdentifierUndefined(std::string m): std::runtime_error(m){}
        
};

class IdentifierRedefined : public std::runtime_error {
    public:
        IdentifierRedefined(std::string m):std::runtime_error(m){}
};

#endif /* end of include guard: _SYMBOLTABLEEXCEPTIONS */
