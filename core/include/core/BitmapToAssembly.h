#pragma once

#include <core/Bitmap.h>

#include <cstddef>
#include <fstream>

std::size_t bitmapToAssembly( std::ofstream& out, const Bitmap& bitmap );
