//====================================================
//     File data
//====================================================
/**
 * @file password_manager_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/add_password_window.hpp>

// States
#include <states/password_manager_state.hpp>

// Qt
#include <QLabel>
#include <QPushButton>

namespace kmanager::state{

    //====================================================
    //     PasswordManagerState (default constructor)
    //====================================================
    /**
     * @brief Construct a new PasswordManagerState object.
     * 
     * @param parent The parent state (if there is one).
     */
    PasswordManagerState::PasswordManagerState( MenuState *host, QState *parent ):
        BaseState( parent ),
        host( host ){
    
        // Create widgets
        this -> addWidgets();

        // Assign properties
        this -> assignProperties();
    }

    //====================================================
    //     MenuState (destructor)
    //====================================================
    /**
     * @brief Destruct a new MenuState object.
     * 
     */
    PasswordManagerState::~PasswordManagerState(){
    
    }

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     * 
     */
    void PasswordManagerState::addWidgets(){

        // Password platform label
        this -> password_platform = QSharedPointer<QLabel>( new QLabel( this -> host -> host ) );
        this -> password_platform -> setVisible( false );
        this -> password_platform -> setText( "Platform / Website" );
        this -> password_platform -> setFrameStyle( QFrame::Panel | QFrame::Sunken );
        this -> password_platform -> setAlignment( Qt::AlignBottom | Qt::AlignCenter );
        this -> password_platform -> setStyleSheet( this -> label_settings );
        this -> password_platform -> resize( this -> label_width, this -> label_height );
        this -> password_platform -> move(
            0,
            this -> host -> host -> mapToGlobal( this -> host -> host -> geometry().center() ).y() * 0.235f
        );

        // Username label
        this -> password_username = QSharedPointer<QLabel>( new QLabel( this -> host -> host ) );
        this -> password_username -> setVisible( false );
        this -> password_username -> setText( "Username" );
        this -> password_username -> setFrameStyle( QFrame::Panel | QFrame::Sunken );
        this -> password_username -> setAlignment( Qt::AlignBottom | Qt::AlignCenter );
        this -> password_username -> setStyleSheet( this -> label_settings );
        this -> password_username -> resize( this -> label_width, this -> label_height );
        this -> password_username -> move(
            this -> password_platform -> geometry().x() + this -> label_width,
            this -> password_platform -> geometry().y()
        );

        // Password key label
        this -> password_key = QSharedPointer<QLabel>( new QLabel( this -> host -> host ) );
        this -> password_key -> setVisible( false );
        this -> password_key -> setText( "Password" );
        this -> password_key -> setFrameStyle( QFrame::Panel | QFrame::Sunken );
        this -> password_key -> setAlignment( Qt::AlignBottom | Qt::AlignCenter );
        this -> password_key -> setStyleSheet( this -> label_settings );
        this -> password_key -> resize( this -> label_width, this -> label_height );
        this -> password_key -> move(
            this -> password_username -> geometry().x() + this -> label_width,
            this -> password_username -> geometry().y()
        );

        // Note label
        this -> password_note = QSharedPointer<QLabel>( new QLabel( this -> host -> host ) );
        this -> password_note -> setVisible( false );
        this -> password_note -> setText( "Note" );
        this -> password_note -> setFrameStyle( QFrame::Panel | QFrame::Sunken );
        this -> password_note -> setAlignment( Qt::AlignBottom | Qt::AlignCenter );
        this -> password_note -> setStyleSheet( this -> label_settings );
        this -> password_note -> resize( this -> label_width, this -> label_height );
        this -> password_note -> move(
            this -> password_key -> geometry().x() + this -> label_width,
            this -> password_key -> geometry().y()
        );

        // Find button
        this -> find_button = QSharedPointer<QPushButton>( new QPushButton( "Find", this -> host -> host ) );
        this -> find_button -> setVisible( false );
        this -> find_button -> resize( this -> label_width * 0.25f, this -> label_height );
        this -> find_button -> setStyleSheet( "font-size: 20px;");
        this -> find_button -> move(
            this -> password_note -> geometry().x() + 210.f,
            this -> password_note -> geometry().y() - label_height
        );

        // Find textbox
        this -> find_input = QSharedPointer<QLineEdit>( new QLineEdit( this -> host -> host ) );
        this -> find_input -> setVisible( false );
        this -> find_input -> resize( this -> label_width * 0.76f, this -> label_height );
        this -> find_input -> setStyleSheet( "font-size: 20px;");
        this -> find_input -> move(
            this -> password_note -> geometry().x(),
            this -> password_note -> geometry().y() - label_height
        );
        this -> find_input -> setPlaceholderText( "Search" );

        // Menu button
        this -> menu_button = QSharedPointer<QPushButton>( new QPushButton( "", this -> host -> host ) );
        this -> menu_button -> setVisible( false );
        this -> menu_button -> resize( this -> label_height * 2.f, this -> label_height * 2.f );
        this -> menu_button -> setStyleSheet( "font-size: 20px;");
        this -> menu_button -> move( 0.f, 1.f );
        this -> menu_icon.addFile( "img/icons/home_icon.png" );
        this -> menu_button -> setIcon( this -> menu_icon );
        this -> menu_button -> setIconSize( QSize( this -> label_height, this -> label_height ) );

        // Add password button
        this -> add_password_button = QSharedPointer<QPushButton>( new QPushButton( "", this -> host -> host ) );
        this -> add_password_button -> setVisible( false );
        this -> add_password_button -> resize( this -> label_height * 2.f, this -> label_height * 2.f );
        this -> add_password_button -> setStyleSheet( "font-size: 20px;");
        this -> add_password_button -> move(
            this -> menu_button -> geometry().x() + 101.f,
            this -> menu_button -> geometry().y()
        );
        this -> add_password_icon.addFile( "img/icons/plus_icon.png" );
        this -> add_password_button -> setIcon( this -> add_password_icon );
        this -> add_password_button -> setIconSize( QSize( this -> label_height, this -> label_height ) );

        QObject::connect( 
            this -> add_password_button.get(), 
            SIGNAL( clicked() ), 
            this, 
            SLOT( addPassword() ) 
        );
    }

    //====================================================
    //     addPassword
    //====================================================
    /**
     * @brief Add a new password to the database.
     * 
     */
    void PasswordManagerState::addPassword(){
        this -> add_password_window = QSharedPointer<window::AddPasswordWindow>( new window::AddPasswordWindow() );
        this -> add_password_window -> show();
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     * 
     */
    void PasswordManagerState::assignProperties(){

        // Buttons
        this -> assignProperty( this -> find_button.get(), "visible", true );
        this -> assignProperty( this -> add_password_button.get(), "visible", true );
        this -> assignProperty( this -> menu_button.get(), "visible", true );

        // Labels
        this -> assignProperty( this -> password_platform.get(), "visible", true );
        this -> assignProperty( this -> password_username.get(), "visible", true );
        this -> assignProperty( this -> password_key.get(), "visible", true );
        this -> assignProperty( this -> password_note.get(), "visible", true );

        // LineEdits
        this -> assignProperty( this -> find_input.get(), "visible", true );
    }
}