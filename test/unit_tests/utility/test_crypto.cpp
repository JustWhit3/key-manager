//====================================================
//     Preprocessor settings
//====================================================
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

//====================================================
//     Headers
//====================================================

// Utility
#include <utility/crypto.hpp>

// Tests
#include <doctest/doctest.h>

//====================================================
//     Crypto
//====================================================
TEST_CASE( "Testing the Crypto class." ){

    // Declare variables
    kmanager::utility::Crypto crypto( "Test message", "0x0c238rh2h1711182h82sh18" );
    kmanager::utility::Crypto crypto_wrong( "Test message", "0x0c238rh2h1711182h82sh18" );
    kmanager::utility::Crypto crypto_empty_key( "Test message", "" );

    //====================================================
    //     encrypt
    //====================================================
    SUBCASE( "Testing the encrypt method." ){
        CHECK_EQ( crypto.encrypt(), "dC^]ST" );
        CHECK( crypto_wrong.encrypt() != "Test message" );
        CHECK( crypto_wrong.encrypt() == "Test message" );
        CHECK_EQ( crypto_empty_key.encrypt(), "Test message" );
    }

    //====================================================
    //     decrypt
    //====================================================
    SUBCASE( "Testing the decrypt method." ){
        crypto.encrypt();
        CHECK_EQ( crypto.decrypt(), "Test message" );
    }

    //====================================================
    //     getMessage
    //====================================================
    SUBCASE( "Testing the getMessage getter" ){
        CHECK_EQ( crypto.getMessage(), "Test message" );
    }

    //====================================================
    //     getKey
    //====================================================
    SUBCASE( "Testing the getKey getter" ){
        CHECK_EQ( crypto.getKey(), "0x0c238rh2h1711182h82sh18" );
    }

    //====================================================
    //     clear
    //====================================================
    SUBCASE( "Testing the clear method." ){
        crypto.encrypt();
        crypto.clear();
        CHECK_EQ( crypto.getMessage(), "" );
        CHECK_EQ( crypto.getKey(), "" );
    }

    //====================================================
    //     setMessage
    //====================================================
    SUBCASE( "Testing the setMessage setter." ){
        crypto.setMessage( "Ciao" );
        CHECK_EQ( crypto.getMessage(), "Ciao" );
    }

    //====================================================
    //     setKey
    //====================================================
    SUBCASE( "Testing the setKey setter." ){
        crypto.setKey( "12345" );
        CHECK_EQ( crypto.getKey(), "12345" );
    }

    //====================================================
    //     generateRandomKey
    //====================================================
    SUBCASE( "Testing the generateRandomKey method." ){

        // Check length of generated key
        kmanager::utility::Crypto crypto_random_key( "Test message" );
        CHECK_EQ( crypto_random_key.getKey().length(), 100 );

        // Check that starting seed is the same
        kmanager::utility::Crypto crypto_random_key_2( "Test message" );
        CHECK( crypto_random_key.getKey() == crypto_random_key_2.getKey() );
    }
}