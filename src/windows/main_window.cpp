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

// STD
#include <filesystem>

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

        // Get login key path
        #ifdef _WIN32
            this -> login_key_file << "C:\\Users\\" 
                                 << this -> username 
                                 << "\\.key-manager_files\\.key\\";
        #else
            this -> login_key_file << "/home/" 
                                 << this -> username 
                                 << "/.key-manager_files/.key/";
        #endif

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
    //     closeEvent
    //====================================================
    /**
     * @brief MMethod used to deal with close-window event.
     * 
     */
    void MainWindow::closeEvent( QCloseEvent* event ){
        event -> accept();
        qApp -> quit();
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
            
            // Down
            case Qt::Key_Down:
                if( this -> state_machine -> configuration().contains( set_password_state.get() ) ){
                    if( this -> set_password_state -> enter_password_first -> hasFocus() ){
                        this -> set_password_state -> enter_password_second -> setFocus();
                    }
                    else if( this -> set_password_state -> enter_password_second -> hasFocus() ){
                        this -> set_password_state -> enter_password_first -> setFocus();
                    }
                }
                break;

            // Up
            case Qt::Key_Up:
                if( this -> state_machine -> configuration().contains( set_password_state.get() ) ){
                    if( this -> set_password_state -> enter_password_first -> hasFocus() ){
                        this -> set_password_state -> enter_password_second -> setFocus();
                    }
                    else if( this -> set_password_state -> enter_password_second -> hasFocus() ){
                        this -> set_password_state -> enter_password_first -> setFocus();
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
    void MainWindow::initStateMachine(){

        // Create states
        this -> login_state = QSharedPointer<state::LoginState>( 
            new state::LoginState( this ) 
        );
        this -> menu_state = QSharedPointer<state::MenuState>( 
            new state::MenuState( this ) 
        );
        this -> p_manager_state = QSharedPointer<state::PasswordManagerState>( 
            new state::PasswordManagerState( this -> menu_state.get() ) 
        );
        this -> set_password_state = QSharedPointer<state::SetPasswordState>( 
            new state::SetPasswordState( this ) 
        );

        // Create transitions
        this -> menu_state -> addTransition( // menu -> password manager
            this -> menu_state -> p_manager_button.get(), SIGNAL( clicked() ), this -> p_manager_state.get() 
        );
        this -> p_manager_state -> addTransition( // password_manager -> menu
            this -> p_manager_state -> menu_button.get(), SIGNAL( clicked() ), this -> menu_state.get() 
        );
        this -> login_state -> addTransition( // login -> menu
            this -> login_state.get(), SIGNAL( login_successful() ), this -> menu_state.get() 
        );
        this -> menu_state -> addTransition( // menu -> login
            this -> menu_state -> change_password_button.get(), SIGNAL( clicked() ), this -> login_state.get() 
        );
        this -> set_password_state -> addTransition( // set_password -> menu
            this -> set_password_state.get(), SIGNAL( save_password_successful() ), this -> menu_state.get() 
        );

        // States machine properties
        this -> state_machine = QSharedPointer<QStateMachine>( new QStateMachine( this ) );
        this -> state_machine -> addState( this -> login_state.get() );
        this -> state_machine -> addState( this -> menu_state.get() );
        this -> state_machine -> addState( this -> p_manager_state.get() );
        this -> state_machine -> addState( this -> set_password_state.get() );
        if( std::filesystem::exists( this -> login_key_file.str() ) ){
            this -> state_machine -> setInitialState( this -> login_state.get() );
        }
        else{
            this -> state_machine -> setInitialState( this -> set_password_state.get() );
        }
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
            SLOT( MenuState_PasswordManagerState() ) 
        );

        // Password manager state -> Menu state
        QObject::connect( 
            this -> p_manager_state -> menu_button.get(), 
            SIGNAL( clicked() ), 
            this, 
            SLOT( PasswordManagerState_MenuState() ) 
        );

        // Restart time loop when entering password manager state
        QObject::connect( 
            this -> menu_state -> p_manager_button.get(), 
            SIGNAL( clicked() ), 
            this -> p_manager_state.get(), 
            SLOT( startTimeLoop() ) 
        );

        // Login state -> Menu state
        QObject::connect( 
            this -> login_state.get(), 
            SIGNAL( login_successful() ), 
            this, 
            SLOT( LoginState_MenuState() ) 
        );

        // Set password state -> Menu state
        QObject::connect( 
            this -> set_password_state.get(), 
            SIGNAL( save_password_successful() ), 
            this, 
            SLOT( SetPasswordState_MenuState() ) 
        );

        // Menu state -> Login state
        QObject::connect( 
            this -> menu_state -> change_password_button.get(), 
            SIGNAL( clicked() ), 
            this, 
            SLOT( MenuState_PasswordManagerState() ) 
        );
    }

    //====================================================
    //     MenuState_PasswordManagerState
    //====================================================
    /**
     * @brief Hide widgets for the PasswordManager state.
     * 
     */
    void MainWindow::MenuState_PasswordManagerState(){

        // Buttons
        this -> p_manager_state -> assignProperty( this -> menu_state -> p_manager_button.get(), "visible", false );
        this -> p_manager_state -> assignProperty( this -> menu_state -> p_generator_button.get(), "visible", false );
        this -> p_manager_state -> assignProperty( this -> menu_state -> options_button.get(), "visible", false );
        this -> p_manager_state -> assignProperty( this -> menu_state -> exit_button.get(), "visible", false );

        this -> login_state -> assignProperty( this -> menu_state -> p_manager_button.get(), "visible", false );
        this -> login_state -> assignProperty( this -> menu_state -> p_generator_button.get(), "visible", false );
        this -> login_state -> assignProperty( this -> menu_state -> options_button.get(), "visible", false );
        this -> login_state -> assignProperty( this -> menu_state -> exit_button.get(), "visible", false );

        // Labels
        this -> p_manager_state -> assignProperty( this -> menu_state -> version.get(), "visible", false );
        this -> p_manager_state -> assignProperty( this -> menu_state -> logo_img_label.get(), "visible", false );
        this -> p_manager_state -> assignProperty( this -> menu_state -> change_password_button.get(), "visible", false );

        this -> login_state -> assignProperty( this -> menu_state -> version.get(), "visible", false );
        this -> login_state -> assignProperty( this -> menu_state -> logo_img_label.get(), "visible", false );
        this -> login_state -> assignProperty( this -> menu_state -> change_password_button.get(), "visible", false );
    }

    //====================================================
    //     PasswordManagerState_MenuState
    //====================================================
    /**
     * @brief Hide widgets for the MenuState state.
     * 
     */
    void MainWindow::PasswordManagerState_MenuState(){

        // Scroll area widgets
        this -> menu_state -> assignProperty( this -> p_manager_state -> scroll_area.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> scroll_widget.get(), "visible", false );

        // Buttons
        this -> menu_state -> assignProperty( this -> p_manager_state -> find_button.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> add_password_button.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> menu_button.get(), "visible", false );

        // Labels
        this -> menu_state -> assignProperty( this -> p_manager_state -> password_platform.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> password_username.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> password_key.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> p_manager_state -> password_actions.get(), "visible", false );

        // QLineEdit
        this -> menu_state -> assignProperty( this -> p_manager_state -> find_input.get(), "visible", false );
    }

    //====================================================
    //     LoginState_MenuState
    //====================================================
    /**
     * @brief Hide widgets for the MenuState state when coming from the LoginState state.
     * 
     */
    void MainWindow::LoginState_MenuState(){

        // QLineEdit
        this -> menu_state -> assignProperty( this -> login_state -> enter_password.get(), "visible", false );

        // QLabel
        this -> menu_state -> assignProperty( this -> login_state -> enter_password_label.get(), "visible", false );

        // QCheckBox
        this -> menu_state -> assignProperty( this -> login_state -> checkbox.get(), "visible", false );
    }

    //====================================================
    //     SetPasswordState_MenuState
    //====================================================
    /**
     * @brief Hide widgets for the MenuState state when coming from the SetPasswordState state.
     * 
     */
    void MainWindow::SetPasswordState_MenuState(){

        // QLineEdit
        this -> menu_state -> assignProperty( this -> set_password_state -> enter_password_first.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> set_password_state -> enter_password_second.get(), "visible", false );

        // QCheckBox
        this -> menu_state -> assignProperty( this -> set_password_state -> checkbox_first.get(), "visible", false );
        this -> menu_state -> assignProperty( this -> set_password_state -> checkbox_second.get(), "visible", false );

        // QLabel
        this -> menu_state -> assignProperty( this -> set_password_state -> enter_password_label.get(), "visible", false );
    }
}