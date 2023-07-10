//====================================================
//     File data
//====================================================
/**
 * @file password_info_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-07-10
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_PASSWORD_INFO_STATE
#define KEY_MANAGER_PASSWORD_INFO_STATE

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>

// Widgets
#include <widgets/password_toggle.hpp>

// Qt
#include <QSharedPointer>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

// STD
#include <map>
#include <string>
#include <sstream>

namespace kmanager::state{

    //====================================================
    //     PasswordInfoState
    //====================================================
    /**
     * @brief Class used to construct the password info state of the app.
     * 
     */
    class PasswordInfoState: public BaseState{

        // Macro for Qt
        Q_OBJECT
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit PasswordInfoState( QWidget* host, std::map<std::string, std::string> info_map, QState *parent = nullptr );
            ~PasswordInfoState();

            // Variables (widgets)
            QSharedPointer<QLabel> title;
            QSharedPointer<QLabel> platform_website_label;
            QSharedPointer<QLabel> username_label;
            QSharedPointer<QLabel> password_label;
            QSharedPointer<QLabel> strength_label;
            QSharedPointer<QLabel> last_update_label;
            QSharedPointer<QLabel> creation_label;
            QSharedPointer<QLineEdit> platform_website_textbox;
            QSharedPointer<QLineEdit> username_textbox;
            QSharedPointer<QLineEdit> password_textbox;
            QSharedPointer<QLineEdit> strength_textbox;
            QSharedPointer<QLineEdit> last_update_textbox;
            QSharedPointer<QLineEdit> creation_textbox;
            widget::PasswordToggle* password_toggle;

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
            std::map<std::string, std::string> info_map;

            // Constants
            const QString widget_font_size{ "font-size: 20px" };
    };
}

#endif