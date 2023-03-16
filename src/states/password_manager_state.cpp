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
#include <states/password_manager_state.hpp>

// Qt
#include <QLabel>

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
        this -> password_platform -> setStyleSheet( "background-color : #4682b4; color: white; font-size: 15px; padding: 8%; font-size: 20px" );
        this -> password_platform -> resize( 250, 50 );
        this -> password_platform -> move(
            this -> password_platform -> geometry().x(),
            this -> host -> host -> mapToGlobal( this -> host -> host -> geometry().center() ).y() * 0.4f
        );
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     * 
     */
    void PasswordManagerState::assignProperties(){

        // Properties
        this -> assignProperty( this -> password_platform.get(), "visible", true );

        // Hide previous state widgets
        this -> assignProperty( this -> host -> p_manager_button.get(), "visible", false );
        this -> assignProperty( this -> host -> p_generator_button.get(), "visible", false );
        this -> assignProperty( this -> host -> options_button.get(), "visible", false );
        this -> assignProperty( this -> host -> exit_button.get(), "visible", false );
        this -> assignProperty( this -> host -> version.get(), "visible", false );
        this -> assignProperty( this -> host -> logo_img_label.get(), "visible", false );
        this -> assignProperty( this -> host -> change_password_button.get(), "visible", false );
    }
}