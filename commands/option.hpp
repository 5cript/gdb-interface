#pragma once

#include <unordered_map>
#include <string>
#include <optional>

namespace DebuggerInterface
{
    using Option = std::pair <std::string, std::optional <std::string>>;
    using OptionList = std::unordered_map <std::string, std::optional <std::string>>;
}
