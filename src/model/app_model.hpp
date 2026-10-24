#pragma once

#include <memory>

#include "root_repo_data_access.hpp"

class AppModel
{
public:
    explicit AppModel(std::unique_ptr<RootRepoDataAccess> root_repo_data_access_value);

    std::unique_ptr<RootRepoDataAccess> root_repo_data_access;
};
