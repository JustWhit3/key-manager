//====================================================
//     File data
//====================================================
/**
 * @file add_password_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-24
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <states/add_password_state.hpp>

// Qt
#include <QStateMachine>
#include <QLabel>
#include <QSize>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QTimer>

// STD
#include <filesystem>

namespace kmanager::state{

    //====================================================
    //     AddPasswordState (default constructor)
    //====================================================
    /**
     * @brief Construct a new AddPasswordState object.
     * 
     * @param parent The parent state (if there is one).
     */
    AddPasswordState::AddPasswordState( QWidget *host, QState *parent ): 
        BaseState( parent ),
        host( host ){
    
        // Create widgets
        this -> addWidgets();

        // Assign properties
        this -> assignProperties();
    }

    //====================================================
    //     AddPasswordState (destructor)
    //====================================================
    /**
     * @brief Destruct a new AddPasswordState object.
     * 
     */
    AddPasswordState::~AddPasswordState(){
    
    }

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     * 
     */
    void AddPasswordState::addWidgets(){

        // Create new password label
        this -> create_new_password_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> create_new_password_label -> setVisible( false );
        this -> create_new_password_label -> setText( "Create a new password:" );
        this -> create_new_password_label ->  setStyleSheet( "font-size: 30px" );
        this -> create_new_password_label -> move(
            this -> create_new_password_label -> geometry().x() + 30.f,
            this -> create_new_password_label -> geometry().y() + 30.f
        );

        // Platform / website label
        this -> platform_website_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> platform_website_label -> setVisible( false );
        this -> platform_website_label -> resize( 220, 50 );
        this -> platform_website_label -> setText( "Platform / website:" );
        this -> platform_website_label ->  setStyleSheet( widget_font_size );
        this -> platform_website_label -> move(
            this -> platform_website_label -> geometry().x() + 30.f,
            this -> platform_website_label -> geometry().y() + 100.f
        );

        // Platform / website textbox
        this -> platform_website_textbox = QSharedPointer<QLineEdit>(
            new QLineEdit( this -> host )
        );
        this -> platform_website_textbox -> setVisible( false );
        this -> platform_website_textbox -> resize( 
            this -> platform_website_label -> geometry().width() * 1.75f,
            this -> platform_website_label -> geometry().height()
        );
        this -> platform_website_textbox -> setStyleSheet( widget_font_size );
        this -> platform_website_textbox -> move(
            this -> platform_website_label -> geometry().x() + 200.f,
            this -> platform_website_label -> geometry().y()
        );
        this -> platform_website_textbox -> setPlaceholderText( "Enter platform name" );

        // Username label
        this -> username_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> username_label -> setVisible( false );
        this -> username_label -> resize( 220, 50 );
        this -> username_label -> setText( "Username:" );
        this -> username_label -> setStyleSheet( widget_font_size );
        this -> username_label -> move(
            this -> platform_website_label -> geometry().x(),
            this -> platform_website_label -> geometry().y() + 60.f
        );

        // Username textbox
        this -> username_textbox = QSharedPointer<QLineEdit>(
            new QLineEdit( this -> host )
        );
        this -> username_textbox -> setVisible( false );
        this -> username_textbox -> resize( 
            this -> username_label -> geometry().width() * 1.75f,
            this -> username_label -> geometry().height()
        );
        this -> username_textbox -> setStyleSheet( widget_font_size );
        this -> username_textbox -> move(
            this -> username_label -> geometry().x() + 200.f,
            this -> username_label -> geometry().y()
        );
        this -> username_textbox -> setPlaceholderText( "Enter username" );

        // Password label
        this -> password_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> password_label -> setVisible( false );
        this -> password_label -> resize( 220, 50 );
        this -> password_label -> setText( "Password:" );
        this -> password_label -> setStyleSheet( widget_font_size );
        this -> password_label -> move(
            this -> username_label -> geometry().x(),
            this -> username_label -> geometry().y() + 60.f
        );

        // Password textbox
        this -> password_textbox = QSharedPointer<QLineEdit>(
            new QLineEdit( this -> host )
        );
        this -> password_textbox -> setVisible( false );
        this -> password_textbox -> resize( 
            this -> password_label -> geometry().width() * 1.75f,
            this -> password_label -> geometry().height()
        );
        this -> password_textbox -> setStyleSheet( widget_font_size );
        this -> password_textbox -> move(
            this -> password_label -> geometry().x() + 200.f,
            this -> password_label -> geometry().y()
        );
        this -> password_textbox -> setPlaceholderText( "Enter password" );

        // Save button
        this -> save_button = QSharedPointer<QPushButton>( new QPushButton( "Save", this -> host ) );
        this -> save_button -> setVisible( false );
        this -> save_button -> resize( 100, 50 );
        this -> save_button -> setStyleSheet( "font-size: 20px;");
        this -> save_button -> move(
            this -> save_button -> geometry().x() + 515.f,
            this -> save_button -> geometry().y() + 25.f
        );
        QObject::connect( 
            this -> save_button.get(), 
            SIGNAL( clicked() ), 
            this, 
            SLOT( savePassword() ) 
        );

        // Error label
        this -> error_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> error_label -> resize( 370, 50 );
        this -> error_label -> setVisible( false );
        this -> error_label -> setText( "Some of the main fields are still missing!" );
        this -> error_label -> setStyleSheet( "QLabel { color : rgb(183, 0, 0); font-size: 20px }" );
        this -> error_label -> move(
            this -> password_label -> geometry().x(),
            this -> password_label -> geometry().y() + 53.f
        );
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     * 
     */
    void AddPasswordState::assignProperties(){

        // Labels
        this -> assignProperty( this -> create_new_password_label.get(), "visible", true );
        this -> assignProperty( this -> platform_website_label.get(), "visible", true );
        this -> assignProperty( this -> username_label.get(), "visible", true );
        this -> assignProperty( this -> password_label.get(), "visible", true );
        this -> assignProperty( this -> error_label.get(), "visible", false );

        // Textbox
        this -> assignProperty( this -> platform_website_textbox.get(), "visible", true );
        this -> assignProperty( this -> username_textbox.get(), "visible", true );
        this -> assignProperty( this -> password_textbox.get(), "visible", true );

        // Buttons
        this -> assignProperty( this -> save_button.get(), "visible", true );
    }

    //====================================================
    //     savePassword
    //====================================================
    /**
     * @brief Save password values entered in textbox.
     * 
     */
    void AddPasswordState::savePassword(){

        // Initialize password object
        this -> new_password.platform = this -> platform_website_textbox -> text();
        this -> new_password.password_str = this -> password_textbox -> text();
        this -> new_password.username = this -> username_textbox -> text();

        // Save results on Json
        this -> main_container.insert( "Platform / Website", QJsonValue::fromVariant( this -> new_password.platform ) );
        this -> main_container.insert( "Password", QJsonValue::fromVariant( this -> new_password.password_str ) );
        this -> main_container.insert( "Username", QJsonValue::fromVariant( this -> new_password.username ) );
        this -> json_doc.setObject( main_container );
        this -> json_doc_bytes = this -> json_doc.toJson( QJsonDocument::Indented );

        // Set file name and save file
        this -> file_oss.str( "" );
        this -> file_oss.clear();
        #ifdef _WIN32
            this -> file_oss << "C:\\Users\\" 
                             << this -> username 
                             << "\\.key-manager_files\\passwords\\"
                             << this -> new_password.username.toStdString() 
                             << ".json";
        #else
            this -> file_oss << "/home/" 
                             << this -> username 
                             << "/.key-manager_files/passwords/"
                             << this -> new_password.username.toStdString() 
                             << ".json";
        #endif
        this -> json_doc_file.setFileName( QString::fromStdString( this -> file_oss.str() ) );

        // Create dirs
        std::filesystem::create_directories( 
            this -> file_oss.str().erase( this -> file_oss.str().size() - 5 - this -> new_password.username.size() ) 
        );

        // Check if all the mandatory fields have been filled
        if( this -> new_password.platform.isEmpty() || 
            this -> new_password.username.isEmpty() || 
            this -> new_password.password_str.isEmpty() ){
            this -> error_label -> setVisible( true );
            QTimer::singleShot( 2000, this -> error_label.get(), &QLabel::hide );
        }
        else {

            // Check if the doc can be opened and write into it
            if( this -> json_doc_file.open( QIODevice::WriteOnly | QIODevice::Text ) ){
                QTextStream iStream( &this -> json_doc_file );
                iStream.setEncoding( QStringConverter::Utf8 );
                iStream << this -> json_doc_bytes;
                this -> json_doc_file.close();
                this -> host -> close();
            }
            else {
                this -> error_label -> setText( "Unable to open the passwords file!" );
                this -> error_label -> setVisible( true );
                QTimer::singleShot( 2000, this -> error_label.get(), &QLabel::hide );
            }
        }
    }
}