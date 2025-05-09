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
    // Constants for branch mechanics
    static constexpr double INITIAL_LIFE = 18.00;
    static constexpr double SPAWN_CHILD_THRESHOLD = 25.00;
    static constexpr double LIFE_AFTER_SPAWN = 15.00;
    static constexpr double FALL_DAMAGE = 999.00;

    Branch() : data_(0), life_(INITIAL_LIFE) {}
    Branch(int data) : data_(data), life_(INITIAL_LIFE) {}

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
    int data() const { return data_; }
    double life() const { return life_; }
    const std::vector<std::shared_ptr<Branch>>& children() const { return children_; }

private:
    int data_;
    double life_;
    std::vector<std::shared_ptr<Branch>> children_;
    std::shared_ptr<Branch> parent_;
};
