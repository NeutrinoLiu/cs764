#include "common.h"
#include "Iterator.h"

class TournamentTreePlan : public Plan
{
    friend class TournamentTreeIterator;
public:
    TournamentTreePlan(const std::vector<Iterator*>& iterators);
    ~TournamentTreePlan();
    Iterator* init() const;
private:
    std::vector<Iterator*> read_iterators; // iterators for reading chunks
};

class TournamentTreeIterator : public Iterator
{
public:
    TournamentTreeIterator(TournamentTreePlan const * const plan);
    ~TournamentTreeIterator();
    bool next();
    char* get();

private:
    TournamentTreePlan const * const _plan;
};