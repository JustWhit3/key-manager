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

// Entities
#include <entities/password.hpp>

// Widgets
#include <widgets/password_toggle.hpp>

// Qt
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QHBoxLayout>
#include <QSizePolicy>

// STD
#include <filesystem>
#include <algorithm>
#include <iterator>
#include <vector>

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
        host( host ),
        menu_button_pressed( false ),
        repaint_passwords( false ){

        // Get passwords path
        #ifdef _WIN32
            this -> password_dir << "C:\\Users\\" 
                                 << this -> username 
                                 << "\\.key-manager_files\\passwords\\";
        #else
            this -> password_dir << "/home/" 
                                 << this -> username 
                                 << "/.key-manager_files/passwords/";
        #endif

        // Compute old passwords number in the password dir
        this -> old_passwords_number = std::distance(
            std::filesystem::directory_iterator( this -> password_dir.str() ),
            std::filesystem::directory_iterator{}
        );
    
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
    //     setScrollArea
    //====================================================
    /**
     * @brief Method used to set-up the scroll area.
     * 
     */
    void PasswordManagerState::setScrollArea(){

        // Scroll area
        this -> scroll_area = QSharedPointer<QScrollArea>( new QScrollArea( this -> host -> host ) );
        this -> scroll_area -> setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
        this -> scroll_area -> setWidgetResizable( true );
        this -> scroll_area -> setGeometry(
            0.f, 
            150.f,
            this -> host -> host -> geometry().width(),
            this -> host -> host -> geometry().height() - 170.f
        );
        this -> scroll_area -> setVisible( false );

        // Scroll widget
        this -> scroll_widget = QSharedPointer<QWidget>( new QWidget() );
        this -> scroll_area -> setWidget( this -> scroll_widget.get() );
        this -> scroll_widget -> setVisible( false );

        // Scroll layout
        this -> scroll_layout = QSharedPointer<QGridLayout>( new QGridLayout() );
        this -> scroll_layout -> setVerticalSpacing( 10.f );
        this -> scroll_layout -> setHorizontalSpacing( 20.f );
        this -> scroll_widget -> setLayout( this -> scroll_layout.get() );
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
            this -> host -> host -> mapToGlobal( this -> host -> host -> geometry().center() ).y() * 0.249f
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
            this -> password_note -> geometry().x() + 205.f,
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
        this -> find_input -> setPlaceholderText( "Search..." );

        // Menu button
        this -> menu_button = QSharedPointer<QPushButton>( new QPushButton( "", this -> host -> host ) );
        this -> menu_button -> setVisible( false );
        this -> menu_button -> resize( this -> label_height * 2.f, this -> label_height * 2.f );
        this -> menu_button -> setStyleSheet( "font-size: 20px;");
        this -> menu_button -> move( 0.f, 1.f );
        this -> menu_icon.addFile( "img/icons/home_icon.png" );
        this -> menu_button -> setIcon( this -> menu_icon );
        this -> menu_button -> setIconSize( QSize( this -> label_height, this -> label_height ) );

        QObject::connect( 
            this -> menu_button.get(), 
            SIGNAL( clicked() ), 
            this, 
            SLOT( stopTimeLoop() ) 
        );

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

        // Scroll area setup
        this -> setScrollArea();

        // Display password widgets
        this -> displayPasswords();

        // Update passwords at each frame
        this -> timer = QSharedPointer<QTimer>( new QTimer( this ) );
        connect( this -> timer.get(), SIGNAL( timeout() ), this, SLOT( updatePasswordsView() ) );
        timer -> start( 1 );
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
    //     displayPasswords
    //====================================================
    /**
     * @brief Display passwords saved in Json file.
     * 
     */
    void PasswordManagerState::displayPasswords(){
        
        // Iterate over password files
        for( const auto& file: std::filesystem::directory_iterator( this -> password_dir.str() ) ){

            // Append element to vector from Json file
            this -> password_file.setFileName( file.path().c_str() );
            this -> password_file.open( QIODevice::ReadOnly | QIODevice::Text );
            this -> file_val = password_file.readAll();
            this -> password_file.close();
            this -> json_doc = QJsonDocument::fromJson( file_val.toUtf8() );
            this -> json_obj = json_doc.object();
            this -> current_password.username = json_obj.value( QString( "Username" ) ).toString();
            this -> current_password.platform = json_obj.value( QString( "Platform / Website" ) ).toString();
            this -> current_password.note = json_obj.value( QString( "Note" ) ).toString();
            this -> current_password.password_str = json_obj.value( QString( "Password" ) ).toString();

            // Draw platform label for each password
            this -> current_platform_label = new QLineEdit( this -> scroll_widget.get() );
            this -> current_platform_label -> setText( this -> current_password.platform );
            this -> current_platform_label -> setAlignment( Qt::AlignBottom | Qt::AlignCenter );
            this -> current_platform_label -> setStyleSheet( this -> label_list_settings );

            // Add label for username
            this -> current_username_label = new QLineEdit( this -> scroll_widget.get() );
            this -> current_username_label -> setText( this -> current_password.username );
            this -> current_username_label -> setAlignment( Qt::AlignBottom | Qt::AlignCenter );
            this -> current_username_label -> setStyleSheet( this -> label_list_settings );

            // Add label for password
            this -> current_password_label = new QLineEdit( this -> scroll_widget.get() );
            this -> current_password_label -> setText( this -> current_password.password_str );
            this -> current_password_label -> setAlignment( Qt::AlignBottom | Qt::AlignCenter );
            this -> current_password_label -> setStyleSheet( this -> label_list_settings );
            this -> current_password_label -> setEchoMode( QLineEdit::Password );

            // Add label for note
            this -> current_note_label = new QLineEdit( this -> scroll_widget.get() );
            current_note_label -> setText( this -> current_password.note );
            current_note_label -> setAlignment( Qt::AlignBottom | Qt::AlignCenter );
            current_note_label -> setStyleSheet( this -> label_list_settings );

            // Create widget for password toggle
            this -> password_widget = new widget::PasswordToggle( this -> host -> host );
            this -> password_widget -> password_label = this -> current_password_label;
            this -> password_widget -> initWidgetProperties();

            // Fill the label containers
            this -> new_password.platform = current_platform_label;
            this -> new_password.username = current_username_label;
            this -> new_password.password_str = current_password_label;
            this -> new_password.note = current_note_label;
            this -> new_password.password_toggle = password_widget;
            this -> label_vec.push_back( new_password );

            // Reorder vector elements by platform name string
            std::sort(
                this -> label_vec.begin(),
                this -> label_vec.end(),
                []( const auto& a, const auto& b ){
                    return a.platform -> text().toLower() < b.platform -> text().toLower();
                }
            );

            // Place labels on the screen
            for( auto it = this -> label_vec.begin(), end = this -> label_vec.end(); it != end; ++it ){
                auto row = std::distance( this -> label_vec.begin(), it );
                this -> scroll_layout -> addWidget( it -> platform, row, 0 );
                this -> scroll_layout -> addWidget( it -> username, row, 1 );
                this -> scroll_layout -> addWidget( it -> password_toggle, row, 2 );
                this -> scroll_layout -> addWidget( it -> note, row, 3 );
            }
        }
    }

    //====================================================
    //     updatePasswordsView
    //====================================================
    /**
     * @brief Update passwords view on the screen.
     * 
     */
    void PasswordManagerState::updatePasswordsView(){

        if( ! menu_button_pressed ){
            
            // Get current number of password files in the dir
            this -> current_passwords_number = std::distance(
                std::filesystem::directory_iterator( this -> password_dir.str() ),
                std::filesystem::directory_iterator{}
            );

            // Compare with old number and update the view
            if( this -> current_passwords_number > this -> old_passwords_number || this -> repaint_passwords ){

                // Clear previous view
                this -> label_vec.clear();
                for( int64_t i = 0; i < this -> scroll_layout -> count(); i++ ){
                    this -> scroll_layout -> itemAt( i ) -> widget() -> deleteLater();
                }
                
                // Display the new view
                this -> displayPasswords();

                // Reset indicators
                this -> old_passwords_number = this -> current_passwords_number;
                this -> repaint_passwords = false;
            }
        }
    }

    //====================================================
    //     stopTimeLoop
    //====================================================
    /**
     * @brief Stop time loop instructions when back to menu state.
     * 
     */
    void PasswordManagerState::stopTimeLoop(){
        this -> menu_button_pressed = true;
        
    }

    //====================================================
    //     startTimeLoop
    //====================================================
    /**
     * @brief Start time loop instructions when back to menu state.
     * 
     */
    void PasswordManagerState::startTimeLoop(){
        this -> menu_button_pressed = false;
        this -> repaint_passwords = true;
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     * 
     */
    void PasswordManagerState::assignProperties(){

        // Scroll area widgets
        this -> assignProperty( this -> scroll_area.get(), "visible", true );
        this -> assignProperty( this -> scroll_widget.get(), "visible", true );

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