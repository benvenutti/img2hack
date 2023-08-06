#include <core/ScreenMap.hpp>

#include <catch2/catch_test_macros.hpp>

#include <filesystem>

TEST_CASE("Dummy", "[dummy]")
{
  const std::filesystem::path root(TESTS_FILES_DIR);

  const std::filesystem::path path = root / "files" / "image1.png";

  ScreenMap screenMap(path);

  const auto& map = screenMap.map();

  REQUIRE(map.size() == 2);
  REQUIRE(map.find(std::int16_t(0b1111111111111111)) != map.end());
  REQUIRE(map.find(std::int16_t(0b0000000000000000)) != map.end());
}
