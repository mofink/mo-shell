#include <optional>
#include <string>

namespace shell
{
	std::optional<std::string> get_exec_path_if_exists(const std::string& exec_name);
}
