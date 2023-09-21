//====================================================
//     File data
//====================================================
/**
 * @file generic.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-07-20
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Utility
#include <utility/generic.hpp>

// Qt
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QStandardPaths>
#include <QString>

namespace kmanager::utility {

    //====================================================
    //     copyToSystem
    //====================================================
    /**
     * @brief Copy a file to the app system directory.
     *
     * @param fileNameToCopy The file to be copied.
     * @return QString The path of the app system directory.
     */
    QString copyToSystem(const QString& fileNameToCopy) {
        // Create app data directory
        QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir appDataDir(appDataLocation);
        if (!appDataDir.exists()) {
            appDataDir.mkpath(".");
        }

        // Copy file to app data directory
        QString fileName = QFileInfo(fileNameToCopy).fileName();
        QString destinationFilePath = QDir(appDataLocation).filePath(fileName);
        if (!QFile::exists(destinationFilePath)) {
            QFile::copy(fileNameToCopy, destinationFilePath);
        }

        return destinationFilePath;
    }

    //====================================================
    //     copyToSystem
    //====================================================
    /**
     * @brief Copy a directory into the app system location.
     *
     * @param sourceDir The directory to be copied.
     */
    void copyDirectory(const QString& sourceDir, const QString& extra_info) {
        // Variables
        QDir sourceDirectory(sourceDir);
        QString extra_path = "";
        if (extra_info.isEmpty()) {
            extra_path = "";
        } else {
            extra_path = extra_info + QDir::separator().toLatin1();
        }
        QDir destinationDirectory(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
                                  QDir::separator() + extra_path + "img");
        QFileInfoList fileList = sourceDirectory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

        // Create the destination dir if it doesn't exist
        if (!destinationDirectory.exists()) {
            destinationDirectory.mkpath(".");
        }

        // Copy files of the sourceDir
        foreach (const QFileInfo& fileInfo, fileList) {
            QString srcFilePath = fileInfo.filePath();
            QString destFilePath = destinationDirectory.filePath(fileInfo.fileName());

            if (fileInfo.isDir())
                copyDirectory(srcFilePath, extra_info);
            else
                QFile::copy(srcFilePath, destFilePath);
        }
    }

    //====================================================
    //     getRealImgPath
    //====================================================
    /**
     * @brief Get the real path of an image, based on the application system path.
     *
     * @param img The image which path should be given.
     * @return QString The real application system path of the image.
     */
    QString getRealImgPath(const QString& img) {
        QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        if (appDataLocation.contains("key-manager")) {
            return appDataLocation + QDir::separator() + img;
        } else {
            return appDataLocation + QDir::separator() + "key-manager" + QDir::separator() + img;
        }
    }
}  // namespace kmanager::utility