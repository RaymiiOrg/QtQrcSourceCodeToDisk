#include "SaveToDisk.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QStandardPaths>
#if defined Q_OS_ANDROID
#include <QtAndroid>
#endif

SaveToDisk::SaveToDisk(QObject* parent) : QObject(parent)
{

}


bool SaveToDisk::requestAndroidPermissions() const
{
#if defined Q_OS_ANDROID
    // These permissions must also be in your AndroidManifest.xml file
    std::vector<QString> permissions({"android.permission.WRITE_EXTERNAL_STORAGE",
                                      "android.permission.READ_EXTERNAL_STORAGE"});

    for(const auto& p : permissions){
        auto result = QtAndroid::checkPermission(p);
        if(result == QtAndroid::PermissionResult::Denied){
            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({p}));
            if(resultHash[p] == QtAndroid::PermissionResult::Denied)
                return false;
        }
    }

#endif
    return true;

}

bool SaveToDisk::save(const QString& resourceFilename) const
{
    QString destinationFolder =  getDocumentsFolder();
#if defined Q_OS_ANDROID
    if(!requestAndroidPermissions())
        return false;
#endif
    // if QStandardPaths::DocumentsLocation is empty, there is an error.
    if(destinationFolder.isEmpty())
        return false;

    // create the folder if it does not exist already
    if(!QDir(destinationFolder).exists())
        QDir().mkdir(destinationFolder);

    QString destinationFileName;
    // take only the last part of the filename, ignore folders in qrc
    // for the filename to save to and remove any non alphanumeric
    // characters from the original filename (e.g. :/).
    QStringList parts = resourceFilename.split("/");
    destinationFileName = parts.value( parts.length() - 1 );
    destinationFileName.remove(QRegExp("[^a-zA-Z\\d\\s\\.]"));

    QString newFilePath = destinationFolder + "/" + destinationFileName;

    if(QFile::exists(newFilePath)) {
        qInfo() << "file " + newFilePath + " already exists, removing";
        QFile::remove(newFilePath);
    }

    QFile to(newFilePath);
    to.setPermissions(QFile::WriteUser);

    qInfo() << "saving file " << resourceFilename << " to: " << newFilePath;
    return QFile::copy(resourceFilename, newFilePath);
}

QString SaveToDisk::getDocumentsFolder() const
{
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}
