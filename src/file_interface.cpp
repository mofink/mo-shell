#include "file_interface.hpp"

#include <algorithm>
#include <filesystem>
#include <vector>

namespace shell
{


std::optional<std::string> get_exec_path_if_exists(const std::string& exec_name)
{
    const std::string env = std::getenv("PATH");
    std::vector<std::string> env_paths;
    std::stringstream ss;
    ss << env;
    std::string env_path;
    while (std::getline(ss, env_path, ':'))
    {
        env_paths.push_back(env_path + "/" + exec_name);
    }

    auto loc = std::find_if(env_paths.begin(), env_paths.end(), [](const auto& s) { return std::filesystem::exists(s); });

    return loc != env_paths.end() ? std::optional<std::string>{*loc} : std::nullopt;
}

} //::shell
