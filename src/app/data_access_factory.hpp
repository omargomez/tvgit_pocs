#pragma once

class RootRepoDataAccess;
class RootRepoJsonDataAccess;

class DataAccessFactory
{
public:
    static RootRepoDataAccess& create_root_repo_data_access();
    static RootRepoJsonDataAccess& create_root_repo_json_data_access();
};
