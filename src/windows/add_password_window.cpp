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
#include <windows/base_window.hpp>
#include <windows/add_password_window.hpp>

// States
#include <states/add_password_state.hpp>
#include <states/password_info_state.hpp>

// Qt
#include <QWidget>
#include <QApplication>
#include <QWindow>
#include <QEvent>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <QScreen>
#include <QSet>
#include <QStateMachine>

// STD
#include <unordered_map>
#include <string>

namespace kmanager::window{

    //====================================================
    //     AddPasswordWindow (default constructor)
    //====================================================
    /**
     * @brief Construct a new AddPasswordWindow object.
     * 
     * @param parent The parent widget (if there is one).
     */
    AddPasswordWindow::AddPasswordWindow( int16_t window_height, std::unordered_map<std::string, std::string> info_map, QWidget *parent ): 
        window_height( window_height ),
        info_map( info_map ),
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
        if( this -> info_map.empty() ){
            this -> setWindowTitle( "Add a new password" );
        }
        else{
            this -> setWindowTitle( "Password information" );
        }
        this -> setWindowState( Qt::WindowActive );
        this -> windowHandle() -> setScreen( qApp -> screens()[0] );
        this -> setWindowIcon( QIcon( "img/icons/app_icon.png" ) );
        this -> setFixedSize( 650, window_height );
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

            // Down
            case Qt::Key_Down:
                if( this -> state_machine -> configuration().contains( add_password_state.get() ) ){
                    if( this -> add_password_state -> platform_website_textbox -> hasFocus() ){
                        this -> add_password_state -> username_textbox -> setFocus();
                    }
                    else if( this -> add_password_state -> username_textbox -> hasFocus() ){
                        this -> add_password_state -> password_textbox -> setFocus();
                    }
                    else if( this -> add_password_state -> password_textbox -> hasFocus() ){
                        this -> add_password_state -> platform_website_textbox -> setFocus();
                    }
                }
                break;

            // Up
            case Qt::Key_Up:
                if( this -> state_machine -> configuration().contains( add_password_state.get() ) ){
                    if( this -> add_password_state -> password_textbox -> hasFocus() ){
                        this -> add_password_state -> username_textbox -> setFocus();
                    }
                    else if( this -> add_password_state -> username_textbox -> hasFocus() ){
                        this -> add_password_state -> platform_website_textbox -> setFocus();
                    }
                    else if( this -> add_password_state -> platform_website_textbox -> hasFocus() ){
                        this -> add_password_state -> password_textbox -> setFocus();
                    }
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
        this -> password_info_state = QSharedPointer<state::PasswordInfoState>(
            new state::PasswordInfoState( this, info_map )
        );

        // States machine properties
        this -> state_machine = QSharedPointer<QStateMachine>( new QStateMachine( this ) );
        this -> state_machine -> addState( this -> add_password_state.get() );
        this -> state_machine -> addState( this -> password_info_state.get() );
        if( this -> info_map.empty() ){
            this -> state_machine -> setInitialState( this -> add_password_state.get() );
        }
        else{
            this -> state_machine -> setInitialState( this -> password_info_state.get() );
        }
        this -> state_machine -> start();
    }
}