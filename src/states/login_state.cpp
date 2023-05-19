//====================================================
//     File data
//====================================================
/**
 * @file login_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-15
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <states/login_state.hpp>

// Utility
#include <utility/crypto.hpp>

// Qt
#include <QStateMachine>
#include <QLineEdit>
#include <QSharedPointer>
#include <QTimer>

// STD
#include <fstream>
#include <iostream>

namespace kmanager::state{

    //====================================================
    //     LoginState (default constructor)
    //====================================================
    /**
     * @brief Construct a new LoginState object.
     * 
     * @param parent The parent state (if there is one).
     */
    LoginState::LoginState( QWidget *host, QState *parent ): 
        BaseState( parent ),
        host( host ){

        // Get login key path
        #ifdef _WIN32
            this -> login_key_file << "C:\\Users\\" 
                                 << this -> username 
                                 << "\\.key-manager_files\\.key";
        #else
            this -> login_key_file << "/home/" 
                                 << this -> username 
                                 << "/.key-manager_files/.key";
        #endif
    
        // Create widgets
        this -> addWidgets();

        // Assign properties
        this -> assignProperties();
    }

    //====================================================
    //     LoginState (destructor)
    //====================================================
    /**
     * @brief Destruct a new LoginState object.
     * 
     */
    LoginState::~LoginState(){
    
    }

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     * 
     */
    void LoginState::addWidgets(){

        // Enter password line edit
        this -> enter_password = QSharedPointer<QLineEdit>( 
            new QLineEdit( this -> host ) 
        );
        this -> enter_password -> setVisible( false );
        this -> enter_password -> resize( this -> width, this -> height );
        this -> enter_password -> setStyleSheet( "font-size: 20px"  );
        this -> enter_password -> move(
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> enter_password -> mapToGlobal( this -> enter_password -> geometry().center() ).x(),
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() - 
                this -> enter_password -> mapToGlobal( this -> enter_password -> geometry().center() ).y() ) * 0.9f
        );
        this -> enter_password -> setPlaceholderText( "Enter password..." );
        this -> enter_password -> setEchoMode( QLineEdit::Password );

        QObject::connect( 
             this -> enter_password.get(), 
             SIGNAL( returnPressed() ), 
             this, 
             SLOT( login() ) 
        );

        // Setup checkbox
        this -> checkbox = QSharedPointer<QCheckBox>( 
            new QCheckBox( this -> host ) 
        );
        this -> checkbox -> setVisible( false );
        this -> checkbox -> setStyleSheet( 
            "QCheckBox::indicator:unchecked { image: url(img/icons/hide.png); }" 
            "QCheckBox::indicator:checked { image: url(img/icons/eye.png); }"
            "QCheckBox::indicator { width: 35px; height: 35px; background-color: #38394e; }"
            
        );
        this -> checkbox -> move(
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> checkbox -> mapToGlobal( this -> checkbox -> geometry().center() ).x() ) * 1.29f,
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() - 
                this -> checkbox -> mapToGlobal( this -> checkbox -> geometry().center() ).y() ) * 0.9f
        );
        this -> checkbox -> setFixedSize( 35, 35 );

        QObject::connect( 
             this -> checkbox.get(), 
             SIGNAL( clicked() ), 
             this, 
             SLOT( changeToggleState() ) 
        );

        // Welcome label
        this -> enter_password_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> enter_password_label -> setVisible( false );
        this -> enter_password_label -> setText( "Welcome back!" );
        this -> enter_password_label -> move(
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> enter_password_label -> mapToGlobal( this -> enter_password_label -> geometry().center() ).x() ) * 0.89f,
            this -> enter_password -> geometry().y() * 0.75f
        );
        this -> enter_password_label -> resize( this -> width, this -> height );
        this -> enter_password_label -> setStyleSheet( "font-size: 30px" );

        // Error label
        this -> error_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> error_label -> resize( this -> width, this -> height / 2 );
        this -> error_label -> setVisible( false );
        this -> error_label -> setText( "Inserted password is wrong!" );
        this -> error_label -> setStyleSheet( "QLabel { color : rgb(183, 0, 0); font-size: 20px }" );
        this -> error_label -> move(
            this -> enter_password -> geometry().x() + 7.f,
            this -> enter_password -> geometry().y() + 90.f
        );
    }

    //====================================================
    //     changeToggleState
    //====================================================
    /**
     * @brief Slot used to change toggle state of password checkbox when clicked.
     * 
     */
    void LoginState::changeToggleState(){
        this -> enter_password -> setEchoMode(
            this -> checkbox -> checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password 
        );
    }

    //====================================================
    //     login
    //====================================================
    /**
     * @brief Slot used to check if login is successful or not.
     * 
     */
    void LoginState::login(){
        
        // Read encrypted texts
        std::string key, password;
        std::ifstream input( this -> login_key_file.str() );
        std::getline( input, password );
        std::getline( input, key );
        input.close();
        utility::Crypto crypto( this -> enter_password -> text().toStdString(), key );

        // Analyze cases
        if( crypto.decrypt() == password ){
            this -> enter_password -> setText( "" );
            emit this -> login_successful( true );
        }
        else{
            this -> error_label -> setVisible( true );
            QTimer::singleShot( 2000, this -> error_label.get(), &QLabel::hide );
        }
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     * 
     */
    void LoginState::assignProperties(){

        // Line edits
        this -> assignProperty( this -> enter_password.get(), "visible", true );

        // Checkboxes
        this -> assignProperty( this -> checkbox.get(), "visible", true );

        // Labels
        this -> assignProperty( this -> enter_password_label.get(), "visible", true );
    }
}