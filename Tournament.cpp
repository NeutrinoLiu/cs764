#include "Tournament.h"
#include <vector>
#include <cstring>
#include <iostream> //TODO comment
#include "Queue.h"

TournamentTreeNode::TournamentTreeNode(char* row, int chunk_num) : row(row), chunk_num(chunk_num) {}

TournamentTreePlan::TournamentTreePlan(std::vector<Queue*> iterators) {
    for (auto iter : iterators) {
        this->read_iterators.push_back(iter);
    }
}

TournamentTreePlan::~TournamentTreePlan() {

}

Iterator* TournamentTreePlan::init() {
    // load leaves
    for (int i = 0; i < read_iterators.size(); i++) {
        TournamentTreeNode* node = new TournamentTreeNode(read_iterators[i]->get(), i);
        leaves.push_back(node); // no chunk should be empty, so no need to check next()
    }

    // compute tree
    computeTournament();

    return new TournamentTreeIterator(this);
}

void TournamentTreePlan::computeTournament() {
    // build the tree
    int n = leaves.size();
    int totalNodes = 2 * n - 1; // Total nodes in a complete binary tree
    tree.resize(totalNodes);

    // Insert leaves in the tree
    for (int i = 0; i < n; ++i) {
        tree[n - 1 + i] = leaves[i];
    }

    // Build the tournament tree
    for (int i = n - 2; i >= 0; --i) {
        // Compare the rows and choose the winner
        char* leftRow = tree[2 * i + 1]->row;
        char* rightRow = tree[2 * i + 2]->row;
        if (leftRow == (char*) NULL) {
            // left is infinitely large
            tree[i] = tree[2 * i + 2];
        } else if (rightRow == (char*) NULL) {
            // right is infinitely large
            tree[i] = tree[2 * i + 1]; 
        } else if (strcmp(leftRow, rightRow) < 0) {
            // left < right -> left up
            tree[i] = tree[2 * i + 1]; 
        } else {
            // left > right (or equal) -> right up
            tree[i] = tree[2 * i + 2]; 
        }
    }

    // print tree
    // for (auto node : tree) {
    //     if (node->row != (char*) NULL) {
    //         std::cout << node->row << " ";
    //     } else {
    //         std::cout << "NULL ";
    //     }
    // }
    // std::cout << std::endl;
}

char* TournamentTreePlan::getRoot() {
    return tree[0]->row;
}

char* TournamentTreePlan::popRoot() {
    char* rt = getRoot();
    int chunk = tree[0]->chunk_num;
    // check if chunk exhausted
    if (read_iterators[chunk]->next()) {
        // replace with new elements
        leaves[chunk] = new TournamentTreeNode(read_iterators[chunk]->get(), chunk);
    } else {
        // exhausted
        leaves[chunk] = new TournamentTreeNode((char*) NULL, chunk);
    }
    computeTournament();
    return rt;
}

TournamentTreeIterator::TournamentTreeIterator(TournamentTreePlan* plan) : plan(plan) {}

TournamentTreeIterator::~TournamentTreeIterator() {}

bool TournamentTreeIterator::next() {
    return plan->getRoot() != (char*) NULL;
}

char* TournamentTreeIterator::get() {
    // return root
    return plan->popRoot();
}
