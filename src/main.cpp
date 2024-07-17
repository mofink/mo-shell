#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <filesystem>
#include <optional>
#include <stdlib.h>
#include <source_location>

#include "file_interface.hpp"


namespace shell
{
    std::filesystem::path current_dir;
}


int main(int argc, char *argv[])
{

    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    
    shell::current_dir = std::filesystem::path(std::source_location::current().file_name()).parent_path();
    std::unordered_set<std::string> cmds = {"exit", "echo", "type", "cd"};

    std::cout << "$ ";

    std::string input;

    while (std::getline(std::cin, input) && input.find("q") != 0 && input.find("exit") != 0)
    {  
        if (input.find("echo") == 0)
        {
            constexpr int ECHO_LEN = 5;
            const std::string str = input.substr(ECHO_LEN);
            std::cout << str << std::endl;
        }
        else if (input.find("type") == 0)
        {
            constexpr int TYPE_LEN = 5;
            
            const std::string str = input.substr(TYPE_LEN);
            
            if (cmds.count(str))
            {
                std::cout << str << " is a shell builtin" << std::endl;
            }
            else
            {
                std::optional<std::string> exec_path = shell::get_exec_path_if_exists(str);
                if (exec_path.has_value())
                {
                    std::cout << str << " is " << *exec_path << std::endl;
                }
                else
                {
                    std::cout << str << ": not found" << std::endl;
                }
            }
        }
	else if (input.find("cd") == 0)
	{
	    std::size_t first_space_idx = input.find_first_of(' ');
	    if (first_space_idx == std::string::npos)
	    {
                shell::current_dir = std::string(std::getenv("HOME"));
	    }
	}
        else 
        {
            std::size_t first_space_idx = input.find_first_of(' ');
            std::optional<std::string> exec_path = shell::get_exec_path_if_exists(input.substr(0, first_space_idx));
            
            if (exec_path.has_value())
            {
                bool has_args = first_space_idx != std::string::npos && first_space_idx < input.size() - 1;
                std::string cmd_with_args = has_args ? exec_path.value() + " " + input.substr(first_space_idx + 1) : exec_path.value();
                std::system(cmd_with_args.c_str());
            }
            else
            {
                std::cout << input.substr(0, first_space_idx - 1) << ": command not found" << std::endl;
            }
        }

        std::cout << "$ ";
    }

  return 0;
}
