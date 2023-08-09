#pragma once

#include <core/Bitmap.h>

#include <filesystem>
#include <variant>

enum class Error
{
    file_does_not_exit,
    file_is_not_an_image
};

using Result = std::variant<Error, Bitmap>;

Result imageToBitmap( const std::filesystem::path& pathToImage );
