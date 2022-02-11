#ifndef SAVETODISK_H
#define SAVETODISK_H

#include <QObject>

class SaveToDisk : public QObject
{
    Q_OBJECT
public:
    SaveToDisk(QObject* parent = nullptr);

    Q_INVOKABLE bool save(const QString& resourceFilename) const;
    Q_INVOKABLE QString getDocumentsFolder() const;

private:
    bool requestAndroidPermissions() const;
};

#endif // SAVETODISK_H
