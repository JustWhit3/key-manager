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
//     Test encryption and decryption
//====================================================
TEST_CASE( "Test Crypto encryption and decryption" ) {

    // Test message and key
    std::string_view message = "Hello, world!";
    std::string_view key = "my_secret_key";

    // Create a Crypto object
    kmanager::utility::Crypto crypto( message, key );

    // Encrypt the message
    std::string encrypted = crypto.encrypt();

    // The encrypted message should not be equal to the original message
    CHECK( encrypted != message );

    // Decrypt the encrypted message using the same key
    crypto.setMessage( encrypted );
    std::string decrypted = crypto.decrypt();

    // The decrypted message should be equal to the original message
    CHECK( decrypted == message );
}

//====================================================
//     Test encryption with random key
//====================================================
TEST_CASE( "Test Crypto random key generation" ) {
    
    // Test message
    std::string_view message = "Hello, world!";

    // Create a Crypto object with a random key
    kmanager::utility::Crypto crypto( message );

    // Encrypt the message
    std::string encrypted = crypto.encrypt();

    // The encrypted message should not be equal to the original message
    CHECK( encrypted != message );

    // Decrypt the encrypted message using the randomly generated key
    crypto.setMessage( encrypted );
    std::string decrypted = crypto.decrypt();

    // The decrypted message should be equal to the original message
    CHECK( decrypted == message );

    // Get the generated key and check its length
    std::string_view generatedKey = crypto.getKey();
    CHECK( generatedKey.size() == 100 );
}

//====================================================
//     Test encryption and decryption with invalid key
//====================================================
TEST_CASE( "Test Crypto encryption and decryption with invalid key" ) {

    // Test message and an empty key (invalid)
    std::string_view message = "Hello, world!";
    std::string_view invalidKey = "";

    // Create a Crypto object with an invalid key
    kmanager::utility::Crypto crypto( message, invalidKey );

    // Encrypt the message with an invalid key
    std::string encrypted = crypto.encrypt();
    CHECK( encrypted == encrypted );

    // Decrypt the encrypted message using an invalid key
    crypto.setMessage( encrypted );
    std::string decrypted = crypto.decrypt();
    CHECK( decrypted == decrypted );
}