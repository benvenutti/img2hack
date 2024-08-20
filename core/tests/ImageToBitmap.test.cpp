#include <core/ImageToBitmap.h>

#include <catch2/catch_test_macros.hpp>

#include <filesystem>

std::filesystem::path testFilesPath()
{
    return std::filesystem::path( TESTS_FILES_DIR ) / "files";
}

TEST_CASE( "ImageToBitmap: file does not exist" )
{
    const auto result = imageToBitmap( std::filesystem::path( "invalid_file_name" ) );

    REQUIRE( std::holds_alternative<Error>( result ) );

    const auto error = std::get<Error>( result );

    REQUIRE( error == Error::file_does_not_exit );
}

TEST_CASE( "ImageToBitmap: file exists but it is not an image" )
{
    const auto result = imageToBitmap( testFilesPath() / "text.txt" );

    REQUIRE( std::holds_alternative<Error>( result ) );

    const auto error = std::get<Error>( result );

    REQUIRE( error == Error::file_is_not_an_image );
}

TEST_CASE( "ImageToBitmap: valid image" )
{
    const auto result = imageToBitmap( testFilesPath() / "image1.png" );

    REQUIRE( std::holds_alternative<Bitmap>( result ) );

    const auto& bitmap = std::get<Bitmap>( result );

    REQUIRE( bitmap.size() == 2 );
    REQUIRE( bitmap.find( std::int16_t( -1 ) ) != bitmap.end() );
    REQUIRE( bitmap.find( std::int16_t( 0 ) ) != bitmap.end() );
}
