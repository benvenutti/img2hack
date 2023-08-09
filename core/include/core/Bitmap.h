#pragma once

#include <cstdint>
#include <filesystem>
#include <map>
#include <set>
#include <variant>

using Bitmap = std::map<std::int16_t, std::set<int>>;

enum class Error
{
    file_does_not_exit,
    file_is_not_an_image
};

using Result = std::variant<Error, Bitmap>;

Result imageToBitmap( const std::filesystem::path& pathToImage );
