#include "root_repo.hpp"

RootRepo map_root_repo(const nlohmann::json& value)
{
    RootRepo repo;

    if (value.is_string()) {
        repo.name = value.get<std::string>();
    } else {
        repo.name = value.at("name").get<std::string>();
    }

    return repo;
}
