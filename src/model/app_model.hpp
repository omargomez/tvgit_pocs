#pragma once

#include "root_repo_data_access.hpp"

class AppModel
{
public:
    explicit AppModel(RootRepoDataAccess& root_repo_data_access_value);

    RootRepoDataAccess& root_repo_data_access;
};
