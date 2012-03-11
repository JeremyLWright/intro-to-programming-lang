#include "SymbolTable.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>

SymbolTable::Ptr SymbolTable::construct()
{
    SymbolTable::Ptr c(new SymbolTable());
    c->self = c;
    return c;
}

SymbolTable::SymbolTable()
{
    Scope::Ptr globalScope = Scope::construct();
    ScopeTable.push(globalScope);
}

SymbolTable::~SymbolTable()
{
}

void SymbolTable::EnterScope()
{
    Scope::Ptr newScope = Scope::construct();
    newScope->parent = ScopeTable.top()->self; //Connect the new scope to the previous scope.
    ScopeTable.push(newScope);
}

void SymbolTable::ExitScope()
{
    // Only pop the scope, if there is at least 1 scope in the table, 
    // i.e. the global scope.  You cannot exit the global scope.
    if(ScopeTable.size() > 1)
    {
        ScopeTable.pop();
    }
    else
    {
        throw std::logic_error("You cannot exit the GLOBAL scope");
    }
}

void SymbolTable::AddSymbol(Symbol::Identifier const & s)
{
    AddSymbol(s, Symbol::DEFAULT_INITIAL_VALUE);
}

void SymbolTable::AddSymbol(Symbol::Identifier const & s, Symbol::valueType v)
{
    AddSymbol(s, v, false);
}

void SymbolTable::AddSymbol(Symbol::Identifier const & s, Symbol::valueType v, bool isConst)
{
    Scope::Ptr currentScope = ScopeTable.top();
    Symbol::Ptr newSymbol = Symbol::construct(s, v, isConst);
    if(currentScope->SymbolDB.find(s) == currentScope->SymbolDB.end())
    {
        currentScope->SymbolDB[s] = newSymbol;
    }
    else
    {
        stringstream ss;
        ss << "Symbol " << s << " Already Defined." << endl;
        throw IdentifierRedefined(ss.str());
    }
}


Symbol::Ptr SymbolTable::GetSymbol(Symbol::Identifier const & s) const
{
    
    return Scope::SearchScope(s, ScopeTable.top());
}

Symbol::Ptr SymbolTable::Scope::SearchScope(Symbol::Identifier const & s, Scope::Ptr aScope)
{
    
    SymbolDB_t::const_iterator i = aScope->SymbolDB.find(s);
    if( i != aScope->SymbolDB.end())
    {
        //Found it!
        return i->second;
    }
    
    Scope::Ptr aScopeParent(aScope->parent);
    Scope::Ptr aScopeSelf(aScope->self);
    
    if(aScopeParent != aScopeSelf) 
    {
        //If we're not at the Global Scope
        //Keep looking
        return SearchScope(s, aScopeParent);
    }

    //We've reach the global scope, and cannot find the value, give up.
    stringstream ss;
    ss << "Cannot find value: " << s;
    throw IdentifierUndefined(ss.str());
}
// ---------------------------------------------------------
//          Scope::Scope()
// ---------------------------------------------------------

SymbolTable::Scope::Ptr SymbolTable::Scope::construct()
{
    Scope::Ptr c(new Scope());
    c->self = c;
    c->parent = c->self;
    return c;
}

SymbolTable::Scope::Scope()
{
}

SymbolTable::Scope::~Scope()
{
}

