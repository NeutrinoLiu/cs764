#include "Tournament.h"
#include "Iterator.h"
#include <vector>
#include <cstring>
#include <iostream>

class VectorQueue : public Queue {
    public:
    VectorQueue(std::vector<char*> vec);
    bool next();
    char* get();
    ~VectorQueue();

    std::vector<char*> vec;
    int index;
};

VectorQueue::VectorQueue(std::vector<char*> vec) : vec(vec) {
    index = 0;
}

VectorQueue::~VectorQueue() {
    index = 0;
}

bool VectorQueue::next() {
    return index != vec.size();
}

char* VectorQueue::get() {
    char* ret = vec[index];
    index ++;
    return ret;
}

void testVectorQueue() {
    std::vector<char*> vec;
    char* str1 = new char[20];
    strcpy(str1, "123");
    vec.push_back(str1);

    char* str2 = new char[20];
    strcpy(str2, "456");
    vec.push_back(str2);

    char* str3 = new char[20];
    strcpy(str3, "234");
    vec.push_back(str3);

    VectorQueue iter = VectorQueue(vec);
    while (iter.next()) {
        std::cout << iter.get() << std::endl;
    }
}

void testIteratorTwoPower() {
    std::vector<char*> vec1;
    char* str11 = new char[20];
    strcpy(str11 , "2");
    vec1.push_back(str11);

    char* str12 = new char[20];
    strcpy(str12, "5");
    vec1.push_back(str12);

    VectorQueue iter1 = VectorQueue(vec1);

    std::vector<char*> vec2;
    char* str21 = new char[20];
    strcpy(str21, "1");
    vec2.push_back(str21);

    char* str22 = new char[20];
    strcpy(str22, "6");
    vec2.push_back(str22);

    VectorQueue iter2 = VectorQueue(vec2);

    std::vector<char*> vec3;
    char* str31 = new char[20];
    strcpy(str31, "4");
    vec3.push_back(str31);

    char* str32 = new char[20];
    strcpy(str32, "7");
    vec3.push_back(str32);

    VectorQueue iter3 = VectorQueue(vec3);

    std::vector<char*> vec4;
    char* str41 = new char[20];
    strcpy(str41, "3");
    vec4.push_back(str41);

    char* str42 = new char[20];
    strcpy(str42, "8");
    vec4.push_back(str42);

    VectorQueue iter4 = VectorQueue(vec4);

    std::vector<Queue*> iterators;
    iterators.push_back(&iter1);
    iterators.push_back(&iter2);
    iterators.push_back(&iter3);
    iterators.push_back(&iter4);

    TournamentTreePlan* plan = new TournamentTreePlan(iterators);
	Iterator* it = plan->init();
    while (it->next()) {
        std::cout << it->get() << std::endl;
    }
}

void testIteratorNonTwoPower() {
    std::vector<char*> vec1;
    char* str11 = new char[20];
    strcpy(str11 , "2");
    vec1.push_back(str11);

    char* str12 = new char[20];
    strcpy(str12, "5");
    vec1.push_back(str12);

    VectorQueue iter1 = VectorQueue(vec1);

    std::vector<char*> vec2;
    char* str21 = new char[20];
    strcpy(str21, "1");
    vec2.push_back(str21);

    char* str22 = new char[20];
    strcpy(str22, "6");
    vec2.push_back(str22);

    VectorQueue iter2 = VectorQueue(vec2);

    std::vector<char*> vec3;
    char* str31 = new char[20];
    strcpy(str31, "4");
    vec3.push_back(str31);

    char* str32 = new char[20];
    strcpy(str32, "7");
    vec3.push_back(str32);

    VectorQueue iter3 = VectorQueue(vec3);

    std::vector<Queue*> iterators;
    iterators.push_back(&iter1);
    iterators.push_back(&iter2);
    iterators.push_back(&iter3);

    TournamentTreePlan* plan = new TournamentTreePlan(iterators);
	Iterator* it = plan->init();
    while (it->next()) {
        std::cout << it->get() << std::endl;
    }
}

void testIteratorOne() {
    std::vector<char*> vec1;
    char* str11 = new char[20];
    strcpy(str11 , "2");
    vec1.push_back(str11);

    char* str12 = new char[20];
    strcpy(str12, "5");
    vec1.push_back(str12);

    VectorQueue iter1 = VectorQueue(vec1);

    std::vector<Queue*> iterators;
    iterators.push_back(&iter1);

    TournamentTreePlan* plan = new TournamentTreePlan(iterators);
	Iterator* it = plan->init();
    while (it->next()) {
        std::cout << it->get() << std::endl;
    }
}

int main() {
    std::cout << "Test two power. Expected: 12345678" << std::endl;
    testIteratorTwoPower();
    std::cout << "Test not two power. Expected: 124567" << std::endl;
    testIteratorNonTwoPower();
    std::cout << "Test one. Expected: 25" << std::endl;
    testIteratorOne();
}