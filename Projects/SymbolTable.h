/**
 * @brief Symbol Table manager for controlling lexical scope.
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */

#ifndef _SYMBOLTABLE
#define _SYMBOLTABLE

#include <tr1/memory>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include "Symbol.h"
#include "SymbolTableExceptions.h"

using namespace std;

class SymbolTable
{
public:
    typedef std::tr1::shared_ptr<SymbolTable> Ptr;
    typedef std::tr1::weak_ptr<SymbolTable> WeakPtr;
    static SymbolTable::Ptr construct();
    virtual ~SymbolTable();
    // Add a scope to the Scope Table
    void EnterScope();
    // Pop the current scope from the Scope Table
    void ExitScope(); 
    // Add a Symbol to the current scope
    void AddSymbol(Symbol::Identifier const & s);
    void AddSymbol(Symbol::Identifier const & s, Symbol::valueType v);
    void AddSymbol(Symbol::Identifier const & s, Symbol::valueType v, bool isConst);

    void EndDeclarations();
    Symbol::Ptr GetSymbol(Symbol::Identifier const & s) const;
private:
    struct Scope
    {
            typedef std::tr1::shared_ptr<Scope> Ptr;
            typedef std::tr1::weak_ptr<Scope> WeakPtr;
            static Scope::Ptr construct();
            virtual ~Scope();
            typedef map<Symbol::Identifier, Symbol::Ptr> SymbolDB_t; 
            SymbolDB_t SymbolDB;
            Scope::WeakPtr parent;
            Scope::WeakPtr self;
            static Symbol::Ptr SearchScope(Symbol::Identifier const & s, Scope::Ptr aScope);
            bool DeclarationsComplete;
        private:
            Scope();

    };

    SymbolTable();
    SymbolTable::WeakPtr self;
    
    stack<Scope::Ptr> ScopeTable;


};

#endif /* end of include guard: _SYMBOLTABLE */
