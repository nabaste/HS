#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <iostream>

#include"Entity.h"
class Tree;

class Branch : public Entity
{
public:

    Branch() : data_(0), life_(18.00) {}
    Branch(int data) : data_(data), life_(18.00) {}

    void update();

    void grow();
    void addChild(std::shared_ptr<Branch> child) {
        children_.push_back(child);
    }
    void looseLife(double amount);

    // Getters
    int const data() { return data_; }
    double const life() { return life_; }
    const std::vector<std::shared_ptr<Branch>>& children() { return children_; }

private:
    int data_;
    double life_;
    std::vector<std::shared_ptr<Branch>> children_;
};
