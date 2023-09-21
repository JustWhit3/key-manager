//====================================================
//     File data
//====================================================
/**
 * @file password_info_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-07-10
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <states/base_state.hpp>
#include <states/password_info_state.hpp>

// Widgets
#include <widgets/password_toggle.hpp>

// Utility
#include <utility/generic.hpp>

// Qt
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QSharedPointer>
#include <QString>
#include <QWidget>

// STD
#include <string>
#include <unordered_map>

namespace kmanager::state {

    //====================================================
    //     Constants
    //====================================================
    const QString PasswordInfoState::widget_font_size{"font-size: 20px"};

    //====================================================
    //     PasswordInfoState (default constructor)
    //====================================================
    /**
     * @brief Construct a new PasswordInfoState object.
     *
     * @param parent The parent state (if there is one).
     */
    PasswordInfoState::PasswordInfoState(QWidget *host, std::unordered_map<std::string, std::string> info_map,
                                         QState *parent)
        : info_map(info_map), BaseState(parent), host(host) {
        // Create widgets
        this->addWidgets();

        // Assign properties
        this->assignProperties();
    }

    //====================================================
    //     PasswordInfoState (destructor)
    //====================================================
    /**
     * @brief Destruct a new PasswordInfoState object.
     *
     */
    PasswordInfoState::~PasswordInfoState() {}

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     *
     */
    void PasswordInfoState::addWidgets() {
        // Create new password label
        this->title = QSharedPointer<QLabel>(new QLabel(this->host));
        this->title->setVisible(false);
        this->title->setText("Password information");
        this->title->setStyleSheet("font-size: 30px");
        this->title->move(this->title->geometry().x() + 30.f, this->title->geometry().y() + 30.f);

        // Key image label
        this->key_img_label = QSharedPointer<QLabel>(new QLabel(this->host));
        this->key_img_label->setVisible(false);
        this->key_img_label->setPixmap(QPixmap(utility::getRealImgPath("img/key.png")));
        this->key_img_label->move(this->title->geometry().x() + 320.f, this->title->geometry().y() - 20.f);
        this->key_img_label->setStyleSheet("QLabel { background-color: rgba( 255, 255, 255, 0% ) }");

        // Platform / website label
        this->platform_website_label = QSharedPointer<QLabel>(new QLabel(this->host));
        this->platform_website_label->setVisible(false);
        this->platform_website_label->resize(220, 50);
        this->platform_website_label->setText("Platform / website:");
        this->platform_website_label->setStyleSheet(widget_font_size);
        this->platform_website_label->move(this->platform_website_label->geometry().x() + 30.f,
                                           this->platform_website_label->geometry().y() + 100.f);

        // Platform / website textbox
        this->platform_website_textbox = QSharedPointer<QLineEdit>(new QLineEdit(this->host));
        this->platform_website_textbox->setVisible(false);
        this->platform_website_textbox->resize(this->platform_website_label->geometry().width() * 1.75f,
                                               this->platform_website_label->geometry().height());
        this->platform_website_textbox->setStyleSheet(widget_font_size);
        this->platform_website_textbox->move(this->platform_website_label->geometry().x() + 200.f,
                                             this->platform_website_label->geometry().y());
        this->platform_website_textbox->setText(QString::fromStdString(this->info_map["platform"]));
        this->platform_website_textbox->setReadOnly(true);

        // Username label
        this->username_label = QSharedPointer<QLabel>(new QLabel(this->host));
        this->username_label->setVisible(false);
        this->username_label->resize(220, 50);
        this->username_label->setText("Username:");
        this->username_label->setStyleSheet(widget_font_size);
        this->username_label->move(this->platform_website_label->geometry().x(),
                                   this->platform_website_label->geometry().y() + 60.f);

        // Username textbox
        this->username_textbox = QSharedPointer<QLineEdit>(new QLineEdit(this->host));
        this->username_textbox->setVisible(false);
        this->username_textbox->resize(this->username_label->geometry().width() * 1.75f,
                                       this->username_label->geometry().height());
        this->username_textbox->setStyleSheet(widget_font_size);
        this->username_textbox->move(this->username_label->geometry().x() + 200.f,
                                     this->username_label->geometry().y());
        this->username_textbox->setText(QString::fromStdString(this->info_map["username"]));
        this->username_textbox->setReadOnly(true);

        // Password label
        this->password_label = QSharedPointer<QLabel>(new QLabel(this->host));
        this->password_label->setVisible(false);
        this->password_label->resize(220, 50);
        this->password_label->setText("Password:");
        this->password_label->setStyleSheet(widget_font_size);
        this->password_label->move(this->username_label->geometry().x(), this->username_label->geometry().y() + 60.f);

        // Password textbox
        this->password_textbox = QSharedPointer<QLineEdit>(new QLineEdit(this->host));
        this->password_textbox->setStyleSheet(widget_font_size);
        this->password_textbox->setText(QString::fromStdString(this->info_map["password"]));
        this->password_textbox->setReadOnly(true);
        this->password_textbox->setEchoMode(QLineEdit::Password);
        this->password_textbox->setFixedHeight(this->password_label->geometry().height());
        this->password_textbox->setFixedWidth(this->password_label->geometry().width() * 1.75f);
        this->password_toggle = new widget::PasswordToggle(false, this->host);
        this->password_toggle->setVisible(false);
        this->password_toggle->move(this->password_label->geometry().x() + 200.f, this->password_label->geometry().y());
        this->password_toggle->password_label = this->password_textbox.get();
        this->password_toggle->initWidgetProperties();

        // Strength
        this->strength_label = QSharedPointer<QLabel>(new QLabel(this->host));
        this->strength_label->setVisible(false);
        this->strength_label->resize(220, 50);
        this->strength_label->setText("Strength:");
        this->strength_label->setStyleSheet(widget_font_size);
        this->strength_label->move(this->password_label->geometry().x(), this->password_label->geometry().y() + 60.f);

        // Strength textbox
        this->strength_textbox = QSharedPointer<QLineEdit>(new QLineEdit(this->host));
        this->strength_textbox->setVisible(false);
        this->strength_textbox->resize(this->strength_label->geometry().width() * 1.75f,
                                       this->strength_label->geometry().height());
        this->strength_textbox->setStyleSheet(widget_font_size);
        this->strength_textbox->move(this->strength_label->geometry().x() + 200.f,
                                     this->strength_label->geometry().y());
        this->strength_textbox->setText(QString::fromStdString(this->info_map["strength"]));
        this->strength_textbox->setReadOnly(true);

        // Last update
        this->last_update_label = QSharedPointer<QLabel>(new QLabel(this->host));
        this->last_update_label->setVisible(false);
        this->last_update_label->resize(220, 50);
        this->last_update_label->setText("Last update:");
        this->last_update_label->setStyleSheet(widget_font_size);
        this->last_update_label->move(this->strength_label->geometry().x(),
                                      this->strength_label->geometry().y() + 60.f);

        // Last update textbox
        this->last_update_textbox = QSharedPointer<QLineEdit>(new QLineEdit(this->host));
        this->last_update_textbox->setVisible(false);
        this->last_update_textbox->resize(this->last_update_label->geometry().width() * 1.75f,
                                          this->last_update_label->geometry().height());
        this->last_update_textbox->setStyleSheet(widget_font_size);
        this->last_update_textbox->move(this->last_update_label->geometry().x() + 200.f,
                                        this->last_update_label->geometry().y());
        this->last_update_textbox->setText(QString::fromStdString(this->info_map["last_update"]));
        this->last_update_textbox->setReadOnly(true);

        // Creation
        this->creation_label = QSharedPointer<QLabel>(new QLabel(this->host));
        this->creation_label->setVisible(false);
        this->creation_label->resize(220, 50);
        this->creation_label->setText("Creation:");
        this->creation_label->setStyleSheet(widget_font_size);
        this->creation_label->move(this->last_update_label->geometry().x(),
                                   this->last_update_label->geometry().y() + 60.f);

        // Creation textbox
        this->creation_textbox = QSharedPointer<QLineEdit>(new QLineEdit(this->host));
        this->creation_textbox->setVisible(false);
        this->creation_textbox->resize(this->creation_label->geometry().width() * 1.75f,
                                       this->creation_label->geometry().height());
        this->creation_textbox->setStyleSheet(widget_font_size);
        this->creation_textbox->move(this->creation_label->geometry().x() + 200.f,
                                     this->creation_label->geometry().y());
        this->creation_textbox->setText(QString::fromStdString(this->info_map["creation"]));
        this->creation_textbox->setReadOnly(true);
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     *
     */
    void PasswordInfoState::assignProperties() {
        // QLabel
        this->assignProperty(this->title.get(), "visible", true);
        this->assignProperty(this->platform_website_label.get(), "visible", true);
        this->assignProperty(this->username_label.get(), "visible", true);
        this->assignProperty(this->password_label.get(), "visible", true);
        this->assignProperty(this->password_toggle, "visible", true);
        this->assignProperty(this->strength_label.get(), "visible", true);
        this->assignProperty(this->last_update_label.get(), "visible", true);
        this->assignProperty(this->creation_label.get(), "visible", true);
        this->assignProperty(this->key_img_label.get(), "visible", true);

        // QLineEdit
        this->assignProperty(this->platform_website_textbox.get(), "visible", true);
        this->assignProperty(this->username_textbox.get(), "visible", true);
        this->assignProperty(this->strength_textbox.get(), "visible", true);
        this->assignProperty(this->last_update_textbox.get(), "visible", true);
        this->assignProperty(this->creation_textbox.get(), "visible", true);
    }
}  // namespace kmanager::state