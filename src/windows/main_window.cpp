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

        // Set actions when buttons are pressed
        this -> buttonsPressedActions();
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
        this -> setFixedSize( 1100,  qApp -> screens()[0] -> geometry().height() * 0.95f );
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
        this -> p_manager_state -> addTransition( 
            this -> p_manager_state -> menu_button.get(), &QPushButton::clicked, this -> menu_state.get() 
        );

        // States machine properties
        this -> state_machine = QSharedPointer<QStateMachine>( new QStateMachine( this ) );
        this -> state_machine -> addState( this -> menu_state.get() );
        this -> state_machine -> addState( this -> p_manager_state.get() );
        this -> state_machine -> setInitialState( this -> menu_state.get() );
        this -> state_machine -> start();
    }

    //====================================================
    //     buttonsPressedActions
    //====================================================
    /**
     * @brief Set actions when buttons are pressed in transition.
     * 
     */
    void MainWindow::buttonsPressedActions(){

        // Menu state -> Password manager state
        QObject::connect( 
            this -> menu_state -> p_manager_button.get(), 
            SIGNAL( clicked() ), 
            this, 
            SLOT( hidePasswordManagerWidgets() ) 
        );

        // Password manager state -> Menu state
        QObject::connect( 
            this -> p_manager_state -> menu_button.get(), 
            SIGNAL( clicked() ), 
            this, 
            SLOT( hideMenuStateWidgets() ) 
        );

        // Restart time loop when entering password manager state
        QObject::connect( 
            this -> menu_state -> p_manager_button.get(), 
            SIGNAL( clicked() ), 
            this -> p_manager_state.get(), 
            SLOT( startTimeLoop() ) 
        );
    }

    //====================================================
    //     hidePasswordManagerWidgets
    //====================================================
    /**
     * @brief Hide widgets for the PasswordManager state.
     * 
     */
    void MainWindow::hidePasswordManagerWidgets(){

        // Buttons
        this -> p_manager_state -> assignProperty( this -> menu_state -> p_manager_button.get(), "visible", false );
        this -> p_manager_state -> assignProperty( this -> menu_state -> p_generator_button.get(), "visible", false );
        this -> p_manager_state -> assignProperty( this -> menu_state -> options_button.get(), "visible", false );
        this -> p_manager_state -> assignProperty( this -> menu_state -> exit_button.get(), "visible", false );

        // Labels
        this -> p_manager_state -> assignProperty( this -> menu_state -> version.get(), "visible", false );
        this -> p_manager_state -> assignProperty( this -> menu_state -> logo_img_label.get(), "visible", false );
        this -> p_manager_state -> assignProperty( this -> menu_state -> change_password_button.get(), "visible", false );
    }

    //====================================================
    //     hideMenuStateWidgets
    //====================================================
    /**
     * @brief Hide widgets for the MenuState state.
     * 
     */
    void MainWindow::hideMenuStateWidgets(){

        // Buttons
        this -> menu_state -> assignProperty( this -> p_manager_state -> find_button.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> add_password_button.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> menu_button.get(), "visible", false );

        // Labels
        this -> menu_state -> assignProperty( this -> p_manager_state -> password_platform.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> password_username.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> password_key.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> password_note.get(), "visible", false );

        // QLineEdit
        this -> menu_state -> assignProperty( this -> p_manager_state -> find_input.get(), "visible", false );

        // Vector of password labels
        std::for_each(
            this -> p_manager_state -> label_vec.cbegin(),
            this -> p_manager_state -> label_vec.cend(),
            [ this ]( const auto& el ){
                this -> menu_state -> assignProperty( el.platform.get(), "visible", false );
                this -> menu_state -> assignProperty( el.username.get(), "visible", false );
                this -> menu_state -> assignProperty( el.password_str.get(), "visible", false );
                this -> menu_state -> assignProperty( el.note.get(), "visible", false );
            }
        );
    }
}