//====================================================
//     File data
//====================================================
/**
 * @file crypto.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-13
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Utility
#include <utility/crypto.hpp>

// crypto++
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>

// STD
#include <string>
#include <string_view>
#include <exception>

namespace kmanager::utility{

    //====================================================
    //     Crypto (parametric constructor)
    //====================================================
    /**
     * @brief Construct a new Crypto object, by using a default input key.
     * 
     */
    Crypto::Crypto( std::string_view message, std::string_view key ): 
        message( message ),
        key( key ){

    }

    //====================================================
    //     Crypto (parametric constructor)
    //====================================================
    /**
     * @brief Construct a new Crypto object, by using a random key of lenght 100.
     * 
     */
    Crypto::Crypto( std::string_view message ): 
        message( message ){

        // Generate random key
        this -> key = this -> generateRandomKey( 100 );

    }

    //====================================================
    //     Crypto (default constructor)
    //====================================================
    /**
     * @brief Destroy the Crypto object.
     * 
     */
    Crypto::~Crypto(){

    }

    //====================================================
    //     encrypt
    //====================================================
    /**
     * @brief Encrypt the "message" string using the "key" string.
     * 
     */
    std::string Crypto::encrypt(){

        // Case for empty key
        if ( ! this -> key.size() ) {
            return "";
        }

        // Try to perform encryption
        try{

            // AES Encryption
            CryptoPP::byte iv[ CryptoPP::AES::BLOCKSIZE ];
            CryptoPP::OS_GenerateRandomBlock( true, iv, CryptoPP::AES::BLOCKSIZE );

            std::string ciphertext;
            CryptoPP::AES::Encryption aesEncryption( reinterpret_cast<const CryptoPP::byte*>( this -> key.data() ), CryptoPP::AES::MAX_KEYLENGTH);
            CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

            CryptoPP::StringSource( this->message.data(), true,
                new CryptoPP::StreamTransformationFilter(cbcEncryption,
                    new CryptoPP::StringSink( ciphertext ) ) );

            // Prepend the IV to the ciphertext
            ciphertext = std::string( reinterpret_cast<const char*>( iv ), CryptoPP::AES::BLOCKSIZE ) + ciphertext;

            // Base64 encode the ciphertext and IV
            std::string encodedCiphertext;
            CryptoPP::StringSource( ciphertext, true,
                new CryptoPP::Base64Encoder(
                    new CryptoPP::StringSink( encodedCiphertext ),
                    false
                )
            );

            return encodedCiphertext;
        } 
        catch ( const std::exception& e ) {
            return "";
        }        
    }

    //====================================================
    //     decrypt
    //====================================================
    /**
     * @brief Decrypt the encrypted "message" string using the "key" string.
     * 
     */
    std::string Crypto::decrypt(){

        // Case for empty key
        if ( ! this -> key.size() ) {
            return "";
        }

        // Try to perform decryption
        try{

            // Base64 decode the input message
            std::string decodedMessage;
            CryptoPP::StringSource( this->message, true,
                new CryptoPP::Base64Decoder(
                    new CryptoPP::StringSink( decodedMessage )
                )
            );

            // Extract the IV from the beginning of the ciphertext
            CryptoPP::byte iv[ CryptoPP::AES::BLOCKSIZE ];
            std::string ciphertextWithoutIV = decodedMessage.substr( CryptoPP::AES::BLOCKSIZE );
            decodedMessage.copy( reinterpret_cast<char*>( iv ), CryptoPP::AES::BLOCKSIZE, 0 );

            std::string decrypted;
            CryptoPP::AES::Decryption aesDecryption( reinterpret_cast<const CryptoPP::byte*>( this->key.data() ), CryptoPP::AES::MAX_KEYLENGTH );
            CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

            CryptoPP::StringSource( ciphertextWithoutIV.data(), true,
                new CryptoPP::StreamTransformationFilter( cbcDecryption,
                    new CryptoPP::StringSink( decrypted ) ) );

            return decrypted;
        }
        catch ( const std::exception& e ) {
            return "";
        }     
    }

    //====================================================
    //     clear
    //====================================================
    /**
     * @brief Clear the "message" and "key" strings.
     * 
     */
    void Crypto::clear(){
        this -> message.clear();
        this -> key.clear();
    }

    //====================================================
    //     getMessage
    //====================================================
    /**
     * @brief Return value of "message" variable.
     * 
     */
    std::string Crypto::getMessage() const {
        return this -> message;
    }    

    //====================================================
    //     getKey
    //====================================================
    /**
     * @brief Return value of "key" variable.
     * 
     */
    std::string Crypto::getKey() const {
        return this -> key;
    }

    //====================================================
    //     setMessage
    //====================================================
    /**
     * @brief Change value of the "message" variable.
     * 
     * @param message The new value of the "message" variable.
     */
    void Crypto::setMessage( std::string_view message ){
        this -> message = message;
    }

    //====================================================
    //     setKey
    //====================================================
    /**
     * @brief Change value of the "key" variable.
     * 
     * @param message The new value of the "key" variable.
     */
    void Crypto::setKey( std::string_view key ){
        this -> key = key;
    }

    //====================================================
    //     generateRandomKey
    //====================================================
    /**
     * @brief Generate a random alpha-numeric key of length "length".
     * 
     */
    std::string Crypto::generateRandomKey( int64_t length ){

        // Array of alphanumeric characters used to generate the random key
        const char alpha_num[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        // Initialize the Crypto++ random number generator
        CryptoPP::AutoSeededRandomPool rng;

        std::string result;
        result.reserve( length );

        // // Generate a random number between 0 and the size of the alpha_num array - 1
        for ( int64_t i = 0; i < length; ++i ) {
            int randomIndex = rng.GenerateWord32( 0, sizeof( alpha_num ) - 2 );
            result += alpha_num[ randomIndex ];
        }

        return result;
    }
}