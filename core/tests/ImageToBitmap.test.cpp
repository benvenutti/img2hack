#include <core/ImageToBitmap.h>

#include <catch2/catch_test_macros.hpp>

#include <filesystem>

TEST_CASE( "Dummy", "[dummy]" )
{
    const std::filesystem::path root( TESTS_FILES_DIR );

    const std::filesystem::path path = root / "files" / "image1.png";

    const auto result = imageToBitmap( path );

    REQUIRE( std::holds_alternative<Bitmap>( result ) );

    const auto& bitmap = std::get<Bitmap>( result );

    REQUIRE( bitmap.size() == 2 );
    REQUIRE( bitmap.find( std::int16_t( 0b1111111111111111 ) ) != bitmap.end() );
    REQUIRE( bitmap.find( std::int16_t( 0b0000000000000000 ) ) != bitmap.end() );
}
