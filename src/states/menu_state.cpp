//====================================================
//     File data
//====================================================
/**
 * @file menu_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>
#include <states/menu_state.hpp>

// Qt
#include <QState>
#include <QLabel>
#include <QSize>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QSharedPointer>
#include <QIcon>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QWidget>

namespace kmanager::state{

    //====================================================
    //     MenuState (default constructor)
    //====================================================
    /**
     * @brief Construct a new MenuState object.
     * 
     * @param parent The parent state (if there is one).
     */
    MenuState::MenuState( QWidget *host, QState *parent ): 
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
    MenuState::~MenuState(){
    
    }

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     * 
     */
    void MenuState::addWidgets(){

        // Password manager button
        this -> p_manager_button = QSharedPointer<QPushButton>( 
            new QPushButton( "Password manager", this -> host ) 
        );
        this -> p_manager_button -> setVisible( false );
        this -> p_manager_button -> resize( this -> button_width, this -> button_height );
        this -> p_manager_button -> setStyleSheet( this -> button_font_size );
        this -> p_manager_button -> move(
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> p_manager_button -> mapToGlobal( this -> p_manager_button -> geometry().center() ).x(),
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() - 
                this -> p_manager_button -> mapToGlobal( this -> p_manager_button -> geometry().center() ).y() ) * 0.9f
        );

        // Password generator button
        this -> p_generator_button = QSharedPointer<QPushButton>( 
            new QPushButton( "Password generator", this -> host ) 
        );
        this -> p_generator_button -> setVisible( false );
        this -> p_generator_button -> resize( this -> button_width, this -> button_height );
        this -> p_generator_button -> setStyleSheet( this -> button_font_size );
        this -> p_generator_button -> move(
            this -> p_manager_button -> geometry().x(),
            this -> p_manager_button -> geometry().y() + 80.f
        );

        // Options button
        this -> options_button = QSharedPointer<QPushButton>( 
            new QPushButton( "Options", this -> host ) 
        );
        this -> options_button -> setVisible( false );
        this -> options_button -> resize( this -> button_width, this -> button_height );
        this -> options_button -> setStyleSheet( this -> button_font_size );
        this -> options_button -> move(
            this -> p_generator_button -> geometry().x(),
            this -> p_generator_button -> geometry().y() + 80.f
        );

        // Exit button
        this -> exit_button = QSharedPointer<QPushButton>( 
            new QPushButton( "Exit", this -> host ) 
        );
        this -> exit_button -> setVisible( false );
        this -> exit_button -> resize( this -> button_width, this -> button_height );
        this -> exit_button -> setStyleSheet( this -> button_font_size );
        this -> exit_button -> move(
            this -> options_button -> geometry().x(),
            this -> options_button -> geometry().y() + 80.f
        );

        QObject::connect( 
            this -> exit_button.get(), 
            SIGNAL( clicked() ), 
            this -> host, 
            SLOT( close() ) 
        );

        // Change password button
        this -> change_password_button = QSharedPointer<QPushButton>( 
            new QPushButton( "", this -> host ) 
        );
        this -> change_password_button -> setVisible( false );
        this -> change_password_button -> setStyleSheet( "background-color: rgba(255, 255, 255, 0);" );
        this -> change_password_button -> move(
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() * 1.84f,
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() + 315.f
        );
        this -> change_password_icon.addFile( "img/icons/password_icon.png" );
        this -> change_password_button -> setIcon( this -> change_password_icon );
        this -> change_password_button -> setIconSize( QSize( this -> button_height, this -> button_height ) );

        // Version and license label
        this -> version = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> version -> setVisible( false );
        this -> version -> setText( "Current version: 0.2.0\nCopyright (c) 2023 Gianluca Bianco under the GPL v3.0 license" );
        this -> version -> setStyleSheet( "font-size: 15px" );
        this -> version -> move(
            this -> version -> mapToGlobal( this -> version -> geometry().center() ).x() * 0.5f,
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() + 350.f
        );

        // Image logo label
        this -> logo_img_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> logo_img_label -> setVisible( false );
        this -> logo_img_label -> setPixmap( QPixmap( "img/images/logo_app.png" ) );
        this -> logo_img_label -> move(
            this -> p_manager_button -> geometry().x() * 0.80f,
            this -> p_manager_button -> geometry().y() * 0.2f
        );
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     * 
     */
    void MenuState::assignProperties(){

        // Buttons
        this -> assignProperty( this -> p_manager_button.get(), "visible", true );
        this -> assignProperty( this -> p_generator_button.get(), "visible", true );
        this -> assignProperty( this -> options_button.get(), "visible", true );
        this -> assignProperty( this -> exit_button.get(), "visible", true );
        this -> assignProperty( this -> change_password_button.get(), "visible", true );

        // Labels
        this -> assignProperty( this -> version.get(), "visible", true );
        this -> assignProperty( this -> logo_img_label.get(), "visible", true );
    }
}