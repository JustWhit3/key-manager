//====================================================
//     File data
//====================================================
/**
 * @file password_manager_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_PASSWORD_MANAGER_STATE
#define KEY_MANAGER_PASSWORD_MANAGER_STATE

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/add_password_window.hpp>

// States
#include <states/base_state.hpp>
#include <states/menu_state.hpp>

// Entities
#include <entities/password.hpp>

// Widgets
#include <widgets/password_toggle.hpp>

// Qt
#include <QSharedPointer>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QScrollBar>

// STD
#include <sstream>
#include <cstdlib>
#include <vector>

namespace kmanager::state{
    
    //====================================================
    //     PasswordManagerState
    //====================================================
    /**
     * @brief Class used to construct the password manager state of the app.
     * 
     */
    class PasswordManagerState: public BaseState{

        // Macro for Qt
        Q_OBJECT
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit PasswordManagerState( MenuState* host, QState *parent = nullptr );
            ~PasswordManagerState();

            // Variables (widgets)
            QSharedPointer<QLabel> password_platform;
            QSharedPointer<QLabel> password_key;
            QSharedPointer<QLabel> password_username;
            QSharedPointer<QLabel> password_note;
            QSharedPointer<QPushButton> find_button;
            QSharedPointer<QPushButton> add_password_button;
            QSharedPointer<QPushButton> menu_button;
            QSharedPointer<QLineEdit> find_input;
            QSharedPointer<window::AddPasswordWindow> add_password_window;
            std::vector<entity::Password<QLineEdit*>> label_vec;

            // Variables (widgets fro scroll area)
            QSharedPointer<QScrollArea> scroll_area;
            QSharedPointer<QWidget> scroll_widget;
            QSharedPointer<QGridLayout> scroll_layout;

            // Variables (widgets for scroll area)
            QLineEdit* current_platform_label;
            QLineEdit* current_username_label;
            QLineEdit* current_password_label;
            QLineEdit* current_note_label;
            widget::PasswordToggle* password_widget;
            entity::Password<QLineEdit*> new_password;
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;
            void displayPasswords();
            void setScrollArea();

            // Variables
            MenuState* host;
            QIcon add_password_icon;
            QIcon menu_icon;
            entity::Password<QString> current_password;
            std::ostringstream password_dir;
            QFile password_file;
            QString file_val;
            QJsonDocument json_doc;
            QJsonObject json_obj;
            size_t old_passwords_number;
            size_t current_passwords_number;
            QSharedPointer<QTimer> timer;
            bool menu_button_pressed;
            bool repaint_passwords;
            
            // Constants
            const float label_width = this -> host -> host -> width() * 0.2482f;
            static constexpr float label_height{ 50.f };
            const QString label_settings{ "background-color: #4682b4; color: white; padding: 8%; font-size: 20px" };
            const QString label_list_settings{ "background-color: rgba( 255, 255, 255, 0% ); padding: 8%" };
            const std::string username{ std::getenv( "USERNAME" ) };

        //====================================================
        //     Private slots
        //====================================================
        private slots:

            // Methods
            void addPassword();
            void updatePasswordsView();
            void stopTimeLoop();
            void startTimeLoop();
    };
}

#endif