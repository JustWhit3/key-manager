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
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QSharedPointer>

// STD
#include <sstream>
#include <string>
#include <unordered_map>

namespace kmanager::state {

    //====================================================
    //     PasswordInfoState
    //====================================================
    /**
     * @brief Class used to construct the password info state of the app.
     *
     */
    class PasswordInfoState : public BaseState {
            Q_OBJECT

        public:

            // Constructors / destructor
            explicit PasswordInfoState(QWidget* host, std::unordered_map<std::string, std::string> info_map,
                                       QState* parent = nullptr);
            ~PasswordInfoState();

            // Variables (widgets)
            QSharedPointer<QLabel> title;
            QSharedPointer<QLabel> platform_website_label;
            QSharedPointer<QLabel> username_label;
            QSharedPointer<QLabel> password_label;
            QSharedPointer<QLabel> strength_label;
            QSharedPointer<QLabel> last_update_label;
            QSharedPointer<QLabel> creation_label;
            QSharedPointer<QLabel> key_img_label;
            QSharedPointer<QLineEdit> platform_website_textbox;
            QSharedPointer<QLineEdit> username_textbox;
            QSharedPointer<QLineEdit> password_textbox;
            QSharedPointer<QLineEdit> strength_textbox;
            QSharedPointer<QLineEdit> last_update_textbox;
            QSharedPointer<QLineEdit> creation_textbox;
            widget::PasswordToggle* password_toggle;

            // Variables (other)
            QWidget* host;

        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;

            // Variables
            std::unordered_map<std::string, std::string> info_map;

            // Constants
            static const QString widget_font_size;
    };
}  // namespace kmanager::state

#endif