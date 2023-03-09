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
        this -> p_manager_button = QSharedPointer<QPushButton>( new QPushButton( "Password manager", this -> host ) );
        this -> p_manager_button -> setVisible( false );
        this -> p_manager_button -> setGeometry( QRect( 200, 50, 140, 100 ) );
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
    }
}