//====================================================
//     File data
//====================================================
/**
 * @file copy_files.cpp
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

//====================================================
//     Main
//====================================================
int main(){

    // Create app data directory
    QString appDataLocation = QStandardPaths::writableLocation( QStandardPaths::AppDataLocation );
    QDir appDataDir( appDataLocation );
    appDataDir.mkpath( "key-manager" );
    
    // Copy the themes file
    QString themes = QFileInfo( "themes/Obit.qss" ).fileName();
    QFile::copy( "themes/Obit.qss", QDir( appDataLocation ).filePath( "key-manager/" + themes ) );

    // Copy the html file
    QString html = QFileInfo( "html/metadata.html" ).fileName();
    QFile::copy( "html/metadata.html", QDir( appDataLocation ).filePath( "key-manager/" + html ) );

    // Copy the img directory into the system app directory
    kmanager::utility::copyDirectory( "img", "key-manager" );
}