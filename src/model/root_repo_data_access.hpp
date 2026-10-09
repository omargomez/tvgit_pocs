#pragma once

#include <vector>

#include "root_repo.hpp"

class RootRepoDataAccess
{
public:
    virtual ~RootRepoDataAccess() = 0;

    virtual std::vector<RootRepo> get_root_repos() const = 0;
};
