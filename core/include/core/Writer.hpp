#pragma once

#include <cstddef>
#include <fstream>

class ScreenMap;

namespace Writer
{

std::size_t compile( std::ofstream& out, const ScreenMap& screenMap );

} // namespace Writer
