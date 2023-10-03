//====================================================
//     File data
//====================================================
/**
 * @file login_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-15
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_LOGIN_STATE
#define KEY_MANAGER_LOGIN_STATE

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>

// Qt
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QSharedPointer>
#include <QState>
#include <QString>

// STD
#include <cstdint>

namespace kmanager::state {

    //====================================================
    //     LoginState
    //====================================================
    /**
     * @brief Class used to construct the login state of the app.
     *
     */
    class LoginState : public BaseState {
            Q_OBJECT

        public:

            // Constructors / destructor
            explicit LoginState(QWidget* host, QState* parent = nullptr);
            ~LoginState();

            // Variables (widgets)
            QSharedPointer<QLineEdit> enter_password;
            QSharedPointer<QCheckBox> checkbox;
            QSharedPointer<QLabel> enter_password_label;
            QSharedPointer<QLabel> error_label;
            QSharedPointer<QLabel> user_img_label;
            QSharedPointer<QLabel> rectangle;
            QSharedPointer<QLabel> background_rectangle;
            QSharedPointer<QPushButton> confirm_button;

            // Variables (other)
            QWidget* host;

        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;

            // Constants
            const uint32_t width{280};
            const uint32_t height{70};
            static const QString checkbox_style;

        private slots:

            void changeToggleState();
            void login();

        signals:

            void login_successful(bool checked = false);
    };
}  // namespace kmanager::state

#endif