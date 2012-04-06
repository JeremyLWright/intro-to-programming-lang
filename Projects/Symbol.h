/**
 * @brief Class to manage a single symbol entity
 *
 * @par
 * Copyright Jeremy Wright (c) 2012
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */

#ifndef _SYMBOL
#define _SYMBOL

#include <tr1/memory>
#include <map>
#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

class Symbol
{
public:
    typedef std::tr1::shared_ptr<Symbol> Ptr;
    typedef std::tr1::weak_ptr<Symbol> WeakPtr;
    typedef string Identifier;
    typedef uint32_t valueType;
    static valueType const DEFAULT_INITIAL_VALUE = 4837;
    
    static Symbol::Ptr construct(Identifier Id);
    static Symbol::Ptr construct(Identifier Id, valueType initialValue);
    static Symbol::Ptr construct(Identifier Id, valueType initialValue, bool isConst);
    virtual ~Symbol();
    Identifier GetName() const;
    valueType GetValue() const;
    bool GetConstness() const;
    void SetValue(valueType const value);
private:
    Symbol(Identifier Id);
    Symbol(Identifier Id, valueType initialValue);
    Symbol(Identifier Id, valueType initialValue, bool isConst);
    Identifier const id;
    Symbol::WeakPtr self;

   /* Properties... I don't like this
    * the properties should be organized into a data
    * structure some how.... Tuples? Map of tuples?
    * A union could combine the types, but its not type-safe.
    */
    valueType prop_value;
    bool const prop_isConst;
    Identifier const prop_name;

};


#endif /* end of include guard: _SYMBOL */
