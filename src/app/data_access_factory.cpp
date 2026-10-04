#include "data_access_factory.hpp"

#include "root_repo_data_access.hpp"
#include "root_repo_json_data_acces.hpp"

RootRepoJsonDataAccess& DataAccessFactory::create_root_repo_json_data_access()
{
    static RootRepoJsonDataAccess data_access;
    return data_access;
}

RootRepoDataAccess& DataAccessFactory::create_root_repo_data_access()
{
    return create_root_repo_json_data_access();
}
