#pragma once

#include <vector>

#include "branch.hpp"

class BranchDataAccess
{
public:
    virtual ~BranchDataAccess() = 0;

    virtual std::vector<BranchEntry> get_branches() const = 0;
};