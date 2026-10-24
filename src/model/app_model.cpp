#include "app_model.hpp"

AppModel::AppModel(std::unique_ptr<RootRepoDataAccess> root_repo_data_access_value) :
    root_repo_data_access(std::move(root_repo_data_access_value))
{
}
