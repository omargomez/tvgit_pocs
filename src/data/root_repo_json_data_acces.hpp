#pragma once

#include <vector>

#include "root_repo_data_access.hpp"

class RootRepoJsonDataAccess final : public RootRepoDataAccess
{
public:
    std::vector<RootRepo> get_root_repos() const override;
};
