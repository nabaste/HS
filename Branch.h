#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <iostream>

#include"Entity.h"
class Tree;

class Branch : public Entity, public std::enable_shared_from_this<Branch>
{
public:

    Branch() : data_(0), life_(18.00) {}
    Branch(int data) : data_(data), life_(18.00) {}

    void update();
    void lateUpdate();

    void grow();
    void spawnChild();
    void addChild(std::shared_ptr<Branch> child);
    void setParent(std::shared_ptr<Branch> parent);
    void looseChildren(int data);

    void looseLife(double amount);
    void fallDown();
    void die();

    // Getters
    int const data() { return data_; }
    double const life() { return life_; }
    const std::vector<std::shared_ptr<Branch>>& children() { return children_; }

private:
    int data_;
    double life_;
    std::vector<std::shared_ptr<Branch>> children_;
    std::shared_ptr<Branch> parent_;
};
