//====================================================
//     File data
//====================================================
/**
 * @file login_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-15
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <states/base_state.hpp>
#include <states/login_state.hpp>

// Utility
#include <utility/crypto.hpp>
#include <utility/generic.hpp>

// Qt
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPixmap>
#include <QSharedPointer>
#include <QSize>
#include <QState>
#include <QTimer>
#include <QWidget>

// STD
#include <string>

namespace kmanager::state {

    //====================================================
    //     Constants
    //====================================================
    const QString LoginState::checkbox_style =
        "QCheckBox::indicator:unchecked { image: url(" + utility::getRealImgPath("img/hide.png") +
        "); }"
        "QCheckBox::indicator:checked { image: url(" +
        utility::getRealImgPath("img/eye.png") +
        "); }"
        "QCheckBox::indicator { width: 35px; height: 35px; background-color: #38394e; }";
    ;

    //====================================================
    //     LoginState (default constructor)
    //====================================================
    /**
     * @brief Construct a new LoginState object.
     *
     * @param parent The parent state (if there is one).
     */
    LoginState::LoginState(QWidget *host, QState *parent) : BaseState(parent), host(host) {
        // Create widgets
        this->addWidgets();

        // Assign properties
        this->assignProperties();
    }

    //====================================================
    //     LoginState (destructor)
    //====================================================
    /**
     * @brief Destruct a new LoginState object.
     *
     */
    LoginState::~LoginState() {}

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     *
     */
    void LoginState::addWidgets() {
        // Background rectangle decoration
        this->background_rectangle = QSharedPointer<QLabel>(new QLabel(this->host));
        this->background_rectangle->setVisible(false);
        this->background_rectangle->resize(this->host->geometry().width(), this->host->geometry().height() * 0.57f);
        this->background_rectangle->setStyleSheet("background-color: rgba( 255, 156, 43, 80% );");
        this->background_rectangle->move(
            this->host->mapToGlobal(this->host->geometry().center()).x() -
                this->background_rectangle->mapToGlobal(this->background_rectangle->geometry().center()).x(),
            0);

        // Rectangle decoration
        this->rectangle = QSharedPointer<QLabel>(new QLabel(this->host));
        this->rectangle->setVisible(false);
        this->rectangle->resize(400, 600);
        this->rectangle->setStyleSheet(
            "background-color: rgba( 35, 36, 48, 100% );"
            "color: #c1c1c1;"
            "border-style: solid;"
            "border-width: 5px;"
            "border-color: #4a4c68;"
            "border-radius: 50%");
        this->rectangle->move(this->host->mapToGlobal(this->host->geometry().center()).x() -
                                  this->rectangle->mapToGlobal(this->rectangle->geometry().center()).x(),
                              this->host->mapToGlobal(this->host->geometry().center()).y() -
                                  this->rectangle->mapToGlobal(this->rectangle->geometry().center()).y());

        // Enter password line edit
        this->enter_password = QSharedPointer<QLineEdit>(new QLineEdit(this->host));
        this->enter_password->setVisible(false);
        this->enter_password->resize(this->width, this->height);
        this->enter_password->setStyleSheet("font-size: 20px;");
        this->enter_password->move(this->host->mapToGlobal(this->host->geometry().center()).x() -
                                       this->enter_password->mapToGlobal(this->enter_password->geometry().center()).x(),
                                   (this->host->mapToGlobal(this->host->geometry().center()).y() -
                                    this->enter_password->mapToGlobal(this->enter_password->geometry().center()).y()) *
                                       1.3f);
        this->enter_password->setPlaceholderText("Enter password...");
        this->enter_password->setEchoMode(QLineEdit::Password);
        this->enter_password->setContextMenuPolicy(Qt::NoContextMenu);

        QObject::connect(this->enter_password.get(), SIGNAL(returnPressed()), this, SLOT(login()));

        // Setup checkbox
        this->checkbox = QSharedPointer<QCheckBox>(new QCheckBox(this->host));
        this->checkbox->setVisible(false);
        this->checkbox->setStyleSheet(this->checkbox_style);
        this->checkbox->move(
            (this->enter_password->geometry().center().x() - this->checkbox->geometry().center().x() * 0.5f) + 115.f,
            (this->enter_password->geometry().center().y() - this->checkbox->geometry().center().y() * 0.5f) - 7.8f);
        this->checkbox->setFixedSize(35, 35);

        QObject::connect(this->checkbox.get(), SIGNAL(clicked()), this, SLOT(changeToggleState()));

        // Welcome label
        this->enter_password_label = QSharedPointer<QLabel>(new QLabel(this->host));
        this->enter_password_label->setVisible(false);
        this->enter_password_label->setText("Welcome back!");
        this->enter_password_label->move(this->enter_password->geometry().x() * 1.06f,
                                         this->enter_password->geometry().y() * 0.83f);
        this->enter_password_label->resize(this->width, this->height);
        this->enter_password_label->setStyleSheet(
            "QLabel { background-color: rgba( 255, 255, 255, 0% ); font-size: 30px }");

        // Error label
        this->error_label = QSharedPointer<QLabel>(new QLabel(this->host));
        this->error_label->resize(this->width, this->height / 2);
        this->error_label->setVisible(false);
        this->error_label->setText("Inserted password is wrong!");
        this->error_label->setStyleSheet("QLabel { color : rgb(183, 0, 0); font-size: 20px }");
        this->error_label->move(this->enter_password->geometry().x() * 1.f,
                                this->enter_password->geometry().y() + 170.f);

        // User image label
        this->user_img_label = QSharedPointer<QLabel>(new QLabel(this->host));
        this->user_img_label->setVisible(false);
        this->user_img_label->setPixmap(QPixmap(utility::getRealImgPath("img/user.png")));
        this->user_img_label->move(this->enter_password_label->geometry().x() * 1.04f,
                                   this->enter_password_label->geometry().y() * 0.55f);
        this->user_img_label->setStyleSheet("QLabel { background-color: rgba( 255, 255, 255, 0% ); }");

        // Confirm button
        this->confirm_button = QSharedPointer<QPushButton>(new QPushButton("", this->host));
        this->confirm_button->setVisible(false);
        this->confirm_button->setStyleSheet(
            "font-size: 20px;"
            "border-radius: 11px;");
        this->confirm_button->move(this->enter_password->geometry().x(), this->enter_password->geometry().y() * 1.18f);
        this->confirm_button->setFixedSize(
            QSize(this->enter_password->geometry().width(), this->enter_password->geometry().height()));
        this->confirm_button->setText("Confirm");

        QObject::connect(this->confirm_button.get(), SIGNAL(clicked()), this, SLOT(login()));
    }

    //====================================================
    //     changeToggleState
    //====================================================
    /**
     * @brief Slot used to change toggle state of password checkbox when clicked.
     *
     */
    void LoginState::changeToggleState() {
        this->enter_password->setEchoMode(this->checkbox->checkState() == Qt::Checked ? QLineEdit::Normal
                                                                                      : QLineEdit::Password);
    }

    //====================================================
    //     login
    //====================================================
    /**
     * @brief Slot used to check if login is successful or not.
     *
     */
    void LoginState::login() {
        // Read encrypted texts
        std::string password = this->settings.value("Master").toString().toStdString();
        std::string key = this->settings.value("Key").toString().toStdString();
        utility::Crypto crypto(password, key);

        // Analyze cases
        if (this->enter_password->text().toStdString() == crypto.decrypt()) {
            this->enter_password->setText("");
            emit this->login_successful(true);
        } else {
            this->error_label->setVisible(true);
            QTimer::singleShot(2000, this->error_label.get(), &QLabel::hide);
        }
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     *
     */
    void LoginState::assignProperties() {
        // Line edits
        this->assignProperty(this->enter_password.get(), "visible", true);

        // Checkboxes
        this->assignProperty(this->checkbox.get(), "visible", true);

        // Labels
        this->assignProperty(this->enter_password_label.get(), "visible", true);
        this->assignProperty(this->user_img_label.get(), "visible", true);
        this->assignProperty(this->rectangle.get(), "visible", true);
        this->assignProperty(this->background_rectangle.get(), "visible", true);

        // Buttons
        this->assignProperty(this->confirm_button.get(), "visible", true);
    }
}  // namespace kmanager::state