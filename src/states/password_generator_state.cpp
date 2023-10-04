//====================================================
//     File data
//====================================================
/**
 * @file password_generator_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-28
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>
#include <states/menu_state.hpp>
#include <states/password_generator_state.hpp>

// Utility
#include <utility/generic.hpp>

// Qt
#include <QCheckBox>
#include <QClipboard>
#include <QGuiApplication>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QSharedPointer>
#include <QString>
#include <QTimer>

// STD
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>

namespace kmanager::state {

    //====================================================
    //     password_generator_state (default constructor)
    //====================================================
    /**
     * @brief Construct a new PasswordGeneratorState object.
     *
     * @param host The state hosting the password generator.
     * @param parent The parent state (if there is one).
     */
    PasswordGeneratorState::PasswordGeneratorState(MenuState *host, QState *parent)
        : BaseState(parent), host(host), chars_container(""), output_password("") {
        // Create widgets
        this->addWidgets();

        // Assign properties
        this->assignProperties();
    }

    //====================================================
    //     PasswordGeneratorState (destructor)
    //====================================================
    /**
     * @brief Destruct a new PasswordGeneratorState object.
     *
     */
    PasswordGeneratorState::~PasswordGeneratorState() {}

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     *
     */
    void PasswordGeneratorState::addWidgets() {
        // Rectangle decoration
        this->rectangle = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->rectangle->setVisible(false);
        this->rectangle->resize(800, 600);
        this->rectangle->setStyleSheet(
            "background-color: rgba( 0, 0, 0, 15% );"
            "color: #c1c1c1;"
            "border-style: solid;"
            "border-width: 5px;"
            "border-color: #4a4c68;"
            "border-radius: 50%");
        this->rectangle->move(this->host->host->mapToGlobal(this->host->host->geometry().center()).x() -
                                  this->rectangle->mapToGlobal(this->rectangle->geometry().center()).x(),
                              this->host->host->mapToGlobal(this->host->host->geometry().center()).y() -
                                  this->rectangle->mapToGlobal(this->rectangle->geometry().center()).y());

        // Password generator label
        this->password_generator_label = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->password_generator_label->setVisible(false);
        this->password_generator_label->resize(400, 70);
        this->password_generator_label->setStyleSheet(
            "QLabel{ background-color: rgba( 255, 255, 255, 0% ); font-size: 38px; }");
        this->password_generator_label->move(
            (this->host->host->mapToGlobal(this->host->host->geometry().center()).x() -
             this->password_generator_label->mapToGlobal(this->password_generator_label->geometry().center()).x()) *
                1.02f,
            (this->host->host->mapToGlobal(this->host->host->geometry().center()).y() -
             this->password_generator_label->mapToGlobal(this->password_generator_label->geometry().center()).y()) *
                0.65f);
        this->password_generator_label->setText("Password Generator");

        // Comment label
        this->comment_label = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->comment_label->setVisible(false);
        this->comment_label->resize(400, 25);
        this->comment_label->setStyleSheet("QLabel{ background-color: rgba( 255, 255, 255, 0% ); font-size: 20px; }");
        this->comment_label->move((this->host->host->mapToGlobal(this->host->host->geometry().center()).x() -
                                   this->comment_label->mapToGlobal(this->comment_label->geometry().center()).x()) *
                                      1.03f,
                                  (this->host->host->mapToGlobal(this->host->host->geometry().center()).y() -
                                   this->comment_label->mapToGlobal(this->comment_label->geometry().center()).y()) *
                                      0.85f);
        this->comment_label->setText("Generate strong and safe passwords!");

        // Menu button
        this->menu_button = QSharedPointer<QPushButton>(new QPushButton("", this->host->host));
        this->menu_button->setVisible(false);
        this->menu_button->resize(100.f, 100.f);
        this->menu_button->setStyleSheet("font-size: 20px;");
        this->menu_button->move(0.f, 1.f);
        this->menu_icon.addFile(utility::getRealImgPath("img/home_icon.png"));
        this->menu_button->setIcon(this->menu_icon);
        this->menu_button->setIconSize(QSize(50.f, 50.f));

        // Password generator output
        this->password_generator_output = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->password_generator_output->setVisible(false);
        this->password_generator_output->resize(500, 70);
        this->password_generator_output->setStyleSheet(
            "background-color: #38394e;"
            "color: #c1c1c1;"
            "font-size: 20px;"
            "border-style: solid;"
            "border-width: 1px;"
            "border-color: #4a4c68;");
        this->password_generator_output->move(
            this->host->host->mapToGlobal(this->host->host->geometry().center()).x() -
                this->password_generator_output->mapToGlobal(this->password_generator_output->geometry().center()).x(),
            this->host->host->mapToGlobal(this->host->host->geometry().center()).y() -
                this->password_generator_output->mapToGlobal(this->password_generator_output->geometry().center()).y());
        this->password_generator_output->setTextInteractionFlags(Qt::TextSelectableByMouse);

        // Generate button
        this->generate_button = QSharedPointer<QPushButton>(new QPushButton("", this->host->host));
        this->generate_button->setVisible(false);
        this->generate_button->resize(70.f, 70.f);
        this->generate_button->setStyleSheet("font-size: 20px;");
        this->generate_icon.addFile(utility::getRealImgPath("img/refresh_icon.png"));
        this->generate_button->setIcon(this->generate_icon);
        this->generate_button->setIconSize(QSize(35.f, 35.f));
        this->generate_button->move(this->password_generator_output->geometry().center().x() + 180.f,
                                    this->password_generator_output->geometry().center().y() - 34.f);

        QObject::connect(this->generate_button.get(), SIGNAL(clicked()), this, SLOT(generatePassword()));

        // Copy button
        this->copy_button = QSharedPointer<QPushButton>(new QPushButton("", this->host->host));
        this->copy_button->setVisible(false);
        this->copy_button->resize(70.f, 70.f);
        this->copy_button->setStyleSheet(
            "QPushButton{ font-size: 20px; background-color: rgba(255, 255, 255, 0); }"
            "QPushButton::hover { background-color: rgba(255, 255, 255, 50); }"
            "QPushButton::pressed { background-color: rgba(255, 255, 255, 70); }");
        this->copy_icon.addFile(utility::getRealImgPath("img/copy.png"));
        this->copy_button->setIcon(this->copy_icon);
        this->copy_button->setIconSize(QSize(35.f, 35.f));
        this->copy_button->move(this->password_generator_output->geometry().center().x() + 109.f,
                                this->password_generator_output->geometry().center().y() - 34.f);

        QObject::connect(this->copy_button.get(), SIGNAL(clicked()), this, SLOT(copiedPassword()));

        // Copied label
        this->copied = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->copied->setVisible(false);
        this->copied->resize(70, 25);

        // Separator line
        this->separator = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->separator->setVisible(false);
        this->separator->resize(1, 100);
        this->separator->setStyleSheet(
            "background-color: #38394e;"
            "color: #c1c1c1;"
            "padding: 8%;"
            "font-size: 20px;"
            "border-style: solid;"
            "border-width: 1px;"
            "border-color: #4a4c68;");
        this->separator->move(this->host->host->mapToGlobal(this->host->host->geometry().center()).x() -
                                  this->separator->mapToGlobal(this->separator->geometry().center()).x(),
                              (this->host->host->mapToGlobal(this->host->host->geometry().center()).y() -
                               this->separator->mapToGlobal(this->separator->geometry().center()).y()) +
                                  130.f);

        // Length line edit
        this->length_line_edit = QSharedPointer<QLineEdit>(new QLineEdit(this->host->host));
        this->length_line_edit->setVisible(false);
        this->length_line_edit->setStyleSheet("font-size: 15px");
        this->length_line_edit->setFixedSize(25, 25);
        this->length_line_edit->move(this->separator->geometry().center().x() - 35.f,
                                     this->separator->geometry().center().y() - 45.f);

        // Length label
        this->length_label = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->length_label->setVisible(false);
        this->length_label->resize(100, 25);
        this->length_label->setStyleSheet("QLabel{ background-color: rgba( 255, 255, 255, 0% ); font-size: 18px; }");
        this->length_label->move(length_line_edit->geometry().x() - 300.f, length_line_edit->geometry().y());
        this->length_label->setText("Length");

        // Upper case checkbox
        this->uppercase_checkbox = QSharedPointer<QCheckBox>(new QCheckBox(this->host->host));
        this->uppercase_checkbox->setVisible(false);
        this->uppercase_checkbox->setStyleSheet(this->checkbox_style);
        this->uppercase_checkbox->setFixedSize(25, 25);
        this->uppercase_checkbox->move(this->separator->geometry().center().x() - 35.f,
                                       this->separator->geometry().center().y() - 12.f);

        // Upper case label
        this->uppercase_label = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->uppercase_label->setVisible(false);
        this->uppercase_label->resize(300, 25);
        this->uppercase_label->setStyleSheet("QLabel{ background-color: rgba( 255, 255, 255, 0% ); font-size: 18px; }");
        this->uppercase_label->move(uppercase_checkbox->geometry().x() - 300.f,
                                    uppercase_checkbox->geometry().y() - 2.f);
        this->uppercase_label->setText("Uppercase characters (ABCDE...)");

        // Lower case checkbox
        this->lowercase_checkbox = QSharedPointer<QCheckBox>(new QCheckBox(this->host->host));
        this->lowercase_checkbox->setVisible(false);
        this->lowercase_checkbox->setStyleSheet(this->checkbox_style);
        this->lowercase_checkbox->setFixedSize(25, 25);
        this->lowercase_checkbox->move(this->separator->geometry().center().x() - 35.f,
                                       this->separator->geometry().center().y() + 21.f);

        // Lower case label
        this->lowercase_label = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->lowercase_label->setVisible(false);
        this->lowercase_label->resize(300, 25);
        this->lowercase_label->setStyleSheet("QLabel{ background-color: rgba( 255, 255, 255, 0% ); font-size: 18px; }");
        this->lowercase_label->move(lowercase_checkbox->geometry().x() - 300.f,
                                    lowercase_checkbox->geometry().y() - 2.f);
        this->lowercase_label->setText("Lowercase characters (abcde...)");

        // Symbols checkbox
        this->symbols_checkbox = QSharedPointer<QCheckBox>(new QCheckBox(this->host->host));
        this->symbols_checkbox->setVisible(false);
        this->symbols_checkbox->setStyleSheet(this->checkbox_style);
        this->symbols_checkbox->setFixedSize(25, 25);
        this->symbols_checkbox->move(this->separator->geometry().center().x() + 320.f,
                                     this->separator->geometry().center().y() - 45.f);

        // Symbols label
        this->symbols_label = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->symbols_label->setVisible(false);
        this->symbols_label->resize(170, 25);
        this->symbols_label->setStyleSheet("QLabel{ background-color: rgba( 255, 255, 255, 0% ); font-size: 18px; }");
        this->symbols_label->move(symbols_checkbox->geometry().x() - 310.f, symbols_checkbox->geometry().y());
        this->symbols_label->setText("Symbols (@#$%...)");

        // Numbers checkbox
        this->numbers_checkbox = QSharedPointer<QCheckBox>(new QCheckBox(this->host->host));
        this->numbers_checkbox->setVisible(false);
        this->numbers_checkbox->setStyleSheet(this->checkbox_style);
        this->numbers_checkbox->setFixedSize(25, 25);
        this->numbers_checkbox->move(this->separator->geometry().center().x() + 320.f,
                                     this->separator->geometry().center().y() - 12.f);

        // Numbers label
        this->numbers_label = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->numbers_label->setVisible(false);
        this->numbers_label->resize(160, 25);
        this->numbers_label->setStyleSheet("QLabel{ background-color: rgba( 255, 255, 255, 0% ); font-size: 18px; }");
        this->numbers_label->move(numbers_checkbox->geometry().x() - 310.f, numbers_checkbox->geometry().y());
        this->numbers_label->setText("Numbers (1234...)");

        // Ambiguous characters checkbox
        this->ambiguous_characters_checkbox = QSharedPointer<QCheckBox>(new QCheckBox(this->host->host));
        this->ambiguous_characters_checkbox->setVisible(false);
        this->ambiguous_characters_checkbox->setStyleSheet(this->checkbox_style);
        this->ambiguous_characters_checkbox->setFixedSize(25, 25);
        this->ambiguous_characters_checkbox->move(this->separator->geometry().center().x() + 320.f,
                                                  this->separator->geometry().center().y() + 21.f);

        // Ambiguous characters label
        this->ambiguous_characters_label = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->ambiguous_characters_label->setVisible(false);
        this->ambiguous_characters_label->resize(300, 25);
        this->ambiguous_characters_label->setStyleSheet(
            "QLabel{ background-color: rgba( 255, 255, 255, 0% ); font-size: 18px; }");
        this->ambiguous_characters_label->move(ambiguous_characters_checkbox->geometry().x() - 310.f,
                                               ambiguous_characters_checkbox->geometry().y());
        this->ambiguous_characters_label->setText("Ambiguous characters ({}()[]:/...)");

        // Lock img
        this->lock_img = QSharedPointer<QLabel>(new QLabel(this->host->host));
        this->lock_img->setVisible(false);
        this->lock_img->setPixmap(QPixmap(utility::getRealImgPath("img/lock.png")));
        this->lock_img->move(
            this->password_generator_label->geometry().center().x() - this->lock_img->geometry().width() * 0.5f - 10.f,
            (this->password_generator_label->geometry().center().y() - this->lock_img->geometry().height() * 0.5f) *
                0.55f);
        this->lock_img->setStyleSheet("background-color: rgba( 255, 255, 255, 0% );");
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     *
     */
    void PasswordGeneratorState::assignProperties() {
        // QLabel
        this->assignProperty(this->password_generator_label.get(), "visible", true);
        this->assignProperty(this->password_generator_output.get(), "visible", true);
        this->assignProperty(this->separator.get(), "visible", true);
        this->assignProperty(this->lowercase_label.get(), "visible", true);
        this->assignProperty(this->uppercase_label.get(), "visible", true);
        this->assignProperty(this->symbols_label.get(), "visible", true);
        this->assignProperty(this->ambiguous_characters_label.get(), "visible", true);
        this->assignProperty(this->numbers_label.get(), "visible", true);
        this->assignProperty(this->length_label.get(), "visible", true);
        this->assignProperty(this->comment_label.get(), "visible", true);
        this->assignProperty(this->rectangle.get(), "visible", true);
        this->assignProperty(this->lock_img.get(), "visible", true);

        // QPushButton
        this->assignProperty(this->menu_button.get(), "visible", true);
        this->assignProperty(this->generate_button.get(), "visible", true);
        this->assignProperty(this->copy_button.get(), "visible", true);

        // QCheckBox
        this->assignProperty(this->lowercase_checkbox.get(), "visible", true);
        this->assignProperty(this->uppercase_checkbox.get(), "visible", true);
        this->assignProperty(this->symbols_checkbox.get(), "visible", true);
        this->assignProperty(this->ambiguous_characters_checkbox.get(), "visible", true);
        this->assignProperty(this->numbers_checkbox.get(), "visible", true);

        // QLineEdit
        this->assignProperty(this->length_line_edit.get(), "visible", true);
    }

    //====================================================
    //     copiedPassword
    //====================================================
    /**
     * @brief Slot used to manage the copy button action.
     *
     */
    void PasswordGeneratorState::copiedPassword() {
        // Copy text to clipboard
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(this->password_generator_output->text());

        // Display message
        this->copied->setStyleSheet(
            "font-size: 20px;"
            "color: #c1c1c1;"
            "background-color: rgba( 255, 255, 255, 0% );");
        this->copied->move(this->copy_button->geometry().center().x() + 120.f,
                           this->copy_button->geometry().center().y() - 12.f);
        this->copied->setText("Copied!");
        this->copied->setVisible(true);
        QTimer::singleShot(2000, this->copied.get(), &QLabel::hide);
    }

    //====================================================
    //     generatePassword
    //====================================================
    /**
     * @brief Slot used to manage the generate password button action.
     *
     */
    void PasswordGeneratorState::generatePassword() {
        // Check if at least one field has been filled
        if (!this->numbers_checkbox->isChecked() && !this->uppercase_checkbox->isChecked() &&
            !this->lowercase_checkbox->isChecked() && !this->symbols_checkbox->isChecked() &&
            !this->ambiguous_characters_checkbox->isChecked()) {
            this->copied->setStyleSheet(
                "font-size: 18px;"
                "color: rgb(183, 0, 0);"
                "background-color: rgba( 255, 255, 255, 0% );");
            this->copied->setText("Select at least one!");
            this->copied->resize(250, 25);
            this->copied->move(separator->geometry().center().x() - 80.f, separator->geometry().center().y() + 70.f);
            this->copied->setVisible(true);
            QTimer::singleShot(2000, this->copied.get(), &QLabel::hide);
        } else if (this->length_line_edit->text() == "") {
            this->copied->setStyleSheet(
                "font-size: 18px;"
                "color: rgb(183, 0, 0);"
                "background-color: rgba( 255, 255, 255, 0% );");
            this->copied->setText("Insert a lenght!");
            this->copied->resize(250, 25);
            this->copied->move(separator->geometry().center().x() - 70.f, separator->geometry().center().y() + 70.f);
            this->copied->setVisible(true);
            QTimer::singleShot(2000, this->copied.get(), &QLabel::hide);
        } else {
            // Create the chars container string
            if (this->lowercase_checkbox->isChecked()) {
                this->chars_container += "abcdefghijklmnopqrstuvwxyz";
            }
            if (this->uppercase_checkbox->isChecked()) {
                this->chars_container += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            }
            if (this->numbers_checkbox->isChecked()) {
                this->chars_container += "1234567890";
            }
            if (this->symbols_checkbox->isChecked()) {
                this->chars_container += "@#$%!&-_?";
            }
            if (this->ambiguous_characters_checkbox->isChecked()) {
                this->chars_container += "{}[]():/*\"'+,.\\;<>=|~°";
            }

            // Generate random password
            try {
                srand(time(0));
                for (int32_t i = 0; i < std::stoi(this->length_line_edit->text().toStdString()); ++i) {
                    this->output_password += this->chars_container[rand() % this->chars_container.size()];
                }
                this->password_generator_output->setText(QString::fromStdString(this->output_password));
                this->output_password.clear();
            } catch (const std::invalid_argument &) {
                this->copied->setStyleSheet(
                    "font-size: 20px;"
                    "color: rgb(183, 0, 0);"
                    "background-color: rgba( 255, 255, 255, 0% );");
                this->copied->setText("Insert numbers, not letters!");
                this->copied->resize(250, 25);
                this->copied->move(separator->geometry().center().x() - 125.f,
                                   separator->geometry().center().y() + 70.f);
                this->copied->setVisible(true);
                QTimer::singleShot(2000, this->copied.get(), &QLabel::hide);
            }

            // Clear containers
            this->chars_container.clear();
        }
    }
}  // namespace kmanager::state