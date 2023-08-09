#pragma once

#include <cstdint>
#include <filesystem>
#include <map>
#include <set>

class ScreenMap
{
public:
    explicit ScreenMap( const std::filesystem::path& imagePath );

    auto begin()
    {
        return m_words.begin();
    }

    auto begin() const
    {
        return m_words.begin();
    }

    auto end()
    {
        return m_words.end();
    }

    auto end() const
    {
        return m_words.end();
    }

    const auto& map() const
    {
        return m_words;
    }

private:
    void add( std::int16_t word, int address );

    void read( const std::filesystem::path& imagePath );

    std::map<std::int16_t, std::set<int>> m_words;
};