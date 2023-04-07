//====================================================
//     File data
//====================================================
/**
 * @file add_password_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-24
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_ADD_PASSWORD_STATE
#define KEY_MANAGER_ADD_PASSWORD_STATE

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>

// Entities
#include <entities/password.hpp>

// Qt
#include <QStateMachine>
#include <QSharedPointer>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

// STD
#include <sstream>
#include <cstdlib>

namespace kmanager::state{

    //====================================================
    //     AddPasswordState
    //====================================================
    /**
     * @brief Class used to construct the add password state of the app.
     * 
     */
    class AddPasswordState: public BaseState{

        // Macro for Qt
        Q_OBJECT
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit AddPasswordState( QWidget* host, QState *parent = nullptr );
            ~AddPasswordState();

            // Variables (widgets)
            QSharedPointer<QLabel> create_new_password_label;
            QSharedPointer<QLabel> platform_website_label;
            QSharedPointer<QLabel> username_label;
            QSharedPointer<QLabel> password_label;
            QSharedPointer<QLabel> note_label;
            QSharedPointer<QLabel> error_label;
            QSharedPointer<QLineEdit> create_new_password_textbox;
            QSharedPointer<QLineEdit> platform_website_textbox;
            QSharedPointer<QLineEdit> username_textbox;
            QSharedPointer<QLineEdit> password_textbox;
            QSharedPointer<QLineEdit> note_textbox;
            QSharedPointer<QPushButton> save_button;

            // Variables (other)
            QWidget* host;
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;

            // Variables
            entity::Password<QString> new_password;
            std::ostringstream file_oss;
            QJsonObject main_container;
            QJsonDocument json_doc;
            QByteArray json_doc_bytes;
            QFile json_doc_file;

            // Constants
            const QString widget_font_size{ "font-size: 20px" };
            const std::string username = std::getenv( "USERNAME" );

        //====================================================
        //     Private slots
        //====================================================
        private slots:
        
            // Methods
            void savePassword();
    };
}

#endif