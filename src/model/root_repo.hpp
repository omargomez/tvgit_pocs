#pragma once

#include <string>
#include <utility>
#include <nlohmann/json.hpp>

class RootRepo
{
public:
    explicit RootRepo(std::string name_value = "", std::string path_value = "") :
        name(std::move(name_value)),
        path(std::move(path_value))
    {
    }

    std::string name;
    std::string path;
};

RootRepo map_root_repo(const nlohmann::json& value);
