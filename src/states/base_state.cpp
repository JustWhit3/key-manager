//====================================================
//     File data
//====================================================
/**
 * @file base_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <states/base_state.hpp>

// Qt
#include <QChar>
#include <QCoreApplication>
#include <QStateMachine>
#include <QString>

// STD
#include <algorithm>
#include <ctime>
#include <vector>

namespace kmanager::state {

    //====================================================
    //     BaseState (default constructor)
    //====================================================
    /**
     * @brief Construct a new BaseState object.
     *
     * @param parent The parent state (if there is one).
     */
    BaseState::BaseState(QState* parent) : QState(parent), settings(QCoreApplication::applicationName()) {}

    //====================================================
    //     BaseState (destructor)
    //====================================================
    /**
     * @brief Destruct a new BaseState object.
     *
     */
    BaseState::~BaseState() {}

    //====================================================
    //     getCurrentDateTime
    //====================================================
    /**
     * @brief Method used to save the date of creation of a password.
     *
     * @return QString the date of creation with signature dd/mm/yyyy - hh:mm:ss.
     */
    QString BaseState::getCurrentDateTime() {
        std::time_t currentTime = std::time(nullptr);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%d/%m/%Y - %H:%M", std::localtime(&currentTime));
        return QString(buffer);
    }

    //====================================================
    //     getCurrentDateTime
    //====================================================
    /**
     * @brief Evaluate the strength of a password.
     *
     * @param password The password to evaluate.
     * @return A string representing the password strength as a percentage compared to 100%. The returned string has the
     * format "XX.XX%", where XX.XX represents the percentage value.
     */
    QString BaseState::evaluatePasswordStrength(const QString& password) {
        int score = 0;
        std::vector<QString> patterns = {"abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "0123456789",
                                         "!@#$%^&*()-=_+[]{}|;':,.<>?/"};

        // Increment score if password contains characters from different categories
        for (const auto& pattern: patterns) {
            if (std::any_of(password.begin(), password.end(), [pattern](QChar c) { return pattern.contains(c); })) {
                score++;
            }
        }

        // Increase score if password is sufficiently long
        if (password.length() >= 8) {
            score++;
        }

        // Compute the strength percentage
        double strengthPercentage = static_cast<double>(score) / (patterns.size() + 1) * 100.0;
        QString strengthString = QString::number(strengthPercentage, 'f', 2) + "%";

        return strengthString;
    }
}  // namespace kmanager::state