#pragma once

#include <core/Bitmap.h>

#include <cstddef>
#include <fstream>

namespace Writer
{

std::size_t compile( std::ofstream& out, const Bitmap& bitmap );

} // namespace Writer
