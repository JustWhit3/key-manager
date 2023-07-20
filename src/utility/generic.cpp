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
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

namespace kmanager::utility{

    //====================================================
    //     copyToSystem
    //====================================================
    /**
     * @brief Copy a file to the app system directory.
     * 
     * @param fileNameToCopy The file to be copied.
     * @return QString The path of the app system directory.
     */
    QString copyToSystem( const QString& fileNameToCopy ){

        // Create app data directory
        QString appDataLocation = QStandardPaths::writableLocation( QStandardPaths::AppDataLocation );
        QDir appDataDir( appDataLocation );
        if ( ! appDataDir.exists() ) {
            appDataDir.mkpath( "." );
        }
        
        // Copy file to app data directory
        QString fileName = QFileInfo( fileNameToCopy ).fileName();
        QString destinationFilePath = QDir( appDataLocation ).filePath( fileName );
        if ( ! QFile::exists( destinationFilePath ) ) {
            QFile::copy( fileNameToCopy, destinationFilePath );
        }

        return destinationFilePath;
    }
}