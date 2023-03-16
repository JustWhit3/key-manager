//====================================================
//     File data
//====================================================
/**
 * @file main_window.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-06
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/main_window.hpp>

// Qt
#include <QtWidgets>

namespace kmanager::window{

    //====================================================
    //     MainWindow (default constructor)
    //====================================================
    /**
     * @brief Construct a new MainWindow object.
     * 
     * @param parent The parent widget (if there is one).
     */
    MainWindow::MainWindow( QWidget *parent ): 
        BaseWindow( parent ){

        // Set basic window properties
        this -> setWindowProperties();

        // Initialize the state machine
        this -> initStateMachine();
    }

    //====================================================
    //     MainWindow (destructor)
    //====================================================
    /**
     * @brief Destruct a new MainWindow object.
     * 
     */
    MainWindow::~MainWindow(){

    }

    //====================================================
    //     setWindowProperties
    //====================================================
    /**
     * @brief Set basic properties of the window.
     * 
     */
    void MainWindow::setWindowProperties(){
        this -> setWindowTitle( "Key Manager" );
        this -> setWindowState( Qt::WindowActive );
        this -> windowHandle() -> setScreen( qApp -> screens()[0] );
        this -> setWindowIcon( QIcon( "img/icons/app_icon.png" ) );
        this -> setFixedSize( 1100,  qApp -> screens()[0] -> geometry().height() );
    }

    //====================================================
    //     keyPressEvent
    //====================================================
    /**
     * @brief Method used to set key commands for the window.
     * 
     */
    void MainWindow::keyPressEvent( QKeyEvent *event ){
        switch( event -> key() ){

            // ESC
            case Qt::Key_Escape:
                this -> close();
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
    void MainWindow::initStateMachine(){

        // Create states
        this -> menu_state = QSharedPointer<state::MenuState>( 
            new state::MenuState( this ) 
        );
        this -> p_manager_state = QSharedPointer<state::PasswordManagerState>( 
            new state::PasswordManagerState( this -> menu_state.get() ) 
        );

        // Create transitions
        this -> menu_state -> addTransition( 
            this -> menu_state -> p_manager_button.get(), &QPushButton::clicked, this -> p_manager_state.get() 
        );

        // States machine properties
        this -> state_machine = QSharedPointer<QStateMachine>( new QStateMachine( this ) );
        this -> state_machine -> addState( this -> menu_state.get() );
        this -> state_machine -> addState( this -> p_manager_state.get() );
        this -> state_machine -> setInitialState( this -> menu_state.get() );
        this -> state_machine -> start();
    }
}