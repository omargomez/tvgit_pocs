#pragma once

#include <string>
#include <utility>
#include <nlohmann/json.hpp>

class RootRepo
{
public:
    explicit RootRepo(std::string name_value = "") :
        name(std::move(name_value))
    {
    }

    std::string name;
};

RootRepo map_root_repo(const nlohmann::json& value);
