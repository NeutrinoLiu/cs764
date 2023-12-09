#include "Iterator.h"
#include "Queue.h"
#include <vector>

class TournamentTreeNode
{
public:
    TournamentTreeNode(char* row, int chunk_num);
    char* row;
    int chunk_num;
};

class TournamentTreePlan : public Plan
{
    friend class TournamentTreeIterator;
public:
    TournamentTreePlan(std::vector<Queue*> iterators);
    ~TournamentTreePlan() override;
    // load leaves, and compute one root
    Iterator* init() override;
private:
    std::vector<Queue*> read_iterators; // iterators for reading chunks
    std::vector<TournamentTreeNode*> tree; // tournament tree
    std::vector<TournamentTreeNode*> leaves; // tournament tree leaves

    // build the tree from leaves
    void computeTournament(); 
    // return the root
    char* getRoot(); 
    // return and remove the root
    char* popRoot(); 
};

class TournamentTreeIterator : public Iterator
{
public:
    TournamentTreeIterator(TournamentTreePlan* plan);
    ~TournamentTreeIterator() override;
    bool next() override;
    // return root and fetch new data
    char* get() override; 

private:
    TournamentTreePlan* plan;
};