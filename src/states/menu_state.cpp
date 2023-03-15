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

// Windows
#include <states/menu_state.hpp>

// Qt
#include <QStateMachine>
#include <QLabel>

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
        this -> p_manager_button = QSharedPointer<widgets::CustomButton>( 
            new widgets::CustomButton( "Password manager", this -> host ) 
        );
        this -> p_manager_button -> resize( 220, 70 );
        this -> p_manager_button -> centering();

        // Version and license label
        this -> version = QSharedPointer<widgets::CustomLabel>(
            new widgets::CustomLabel( this -> host )
        );
        this -> version -> setText( "Current version: 0.0.0\nCopyright (c) 2023 Gianluca Bianco under the GPL v3.0 license" );
        this -> version ->  setStyleSheet( "font-size: 15px" );
        this -> version -> move(
            this -> version -> mapToGlobal( this -> version -> geometry().center() ).x() * 0.5f,
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() * 1.75f
        );

        // Image logo
        this -> logo_img_label = QSharedPointer<widgets::CustomLabel>(
            new widgets::CustomLabel( this -> host )
        );
        this -> logo_img = "img/images/logo_app.png";
        this -> img.load( this -> logo_img );
        this -> logo_img_label -> setPixmap( img );
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
        this -> assignProperty( this -> p_manager_button.get(), "visible", true );
        this -> assignProperty( this -> version.get(), "visible", true );
        this -> assignProperty( this -> logo_img_label.get(), "visible", true );
    }
}