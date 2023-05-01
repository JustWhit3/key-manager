//====================================================
//     File data
//====================================================
/**
 * @file add_password_window.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-24
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/add_password_window.hpp>

// Qt
#include <QtWidgets>

namespace kmanager::window{

    //====================================================
    //     AddPasswordWindow (default constructor)
    //====================================================
    /**
     * @brief Construct a new AddPasswordWindow object.
     * 
     * @param parent The parent widget (if there is one).
     */
    AddPasswordWindow::AddPasswordWindow( QWidget *parent ): 
        BaseWindow( parent ){

        // Set basic window properties
        this -> setWindowProperties();

        // Initialize the state machine
        this -> initStateMachine();
    }

    //====================================================
    //     AddPasswordWindow (destructor)
    //====================================================
    /**
     * @brief Destruct a new AddPasswordWindow object.
     * 
     */
    AddPasswordWindow::~AddPasswordWindow(){

    }

    //====================================================
    //     setWindowProperties
    //====================================================
    /**
     * @brief Set basic properties of the window.
     * 
     */
    void AddPasswordWindow::setWindowProperties(){
        this -> setWindowTitle( "Add a new password" );
        this -> setWindowState( Qt::WindowActive );
        this -> windowHandle() -> setScreen( qApp -> screens()[0] );
        this -> setWindowIcon( QIcon( "img/icons/app_icon.png" ) );
        this -> setFixedSize( 650,  qApp -> screens()[0] -> geometry().height() * 0.38f );
        this -> move(
            ( qApp -> screens()[0] -> geometry().width() - this->width() ) * 0.5f,
            ( qApp -> screens()[0] -> geometry().height() - this->height() ) * 0.5f
        );
    }

    //====================================================
    //     keyPressEvent
    //====================================================
    /**
     * @brief Method used to set key commands for the window.
     * 
     */
    void AddPasswordWindow::keyPressEvent( QKeyEvent *event ){
        switch( event -> key() ){

            // ESC
            case Qt::Key_Escape:
                this -> close();
                break;

            // Enter
            case Qt::Key_Return:
                if( this -> state_machine -> configuration().contains( this -> add_password_state.get() ) ){
                    this -> add_password_state -> save_button -> animateClick();
                }
                break;

            // Default
            default:
                break;
        }
    }

    //====================================================
    //     initStateMachine
    //====================================================
    /**
     * @brief Set basic properties of the window state machine.
     * 
     */
    void AddPasswordWindow::initStateMachine(){

        // Create states
        this -> add_password_state = QSharedPointer<state::AddPasswordState>( 
            new state::AddPasswordState( this ) 
        );

        // States machine properties
        this -> state_machine = QSharedPointer<QStateMachine>( new QStateMachine( this ) );
        this -> state_machine -> addState( this -> add_password_state.get() );
        this -> state_machine -> setInitialState( this -> add_password_state.get() );
        this -> state_machine -> start();
    }
}