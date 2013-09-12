#ifndef FOO_H
#define FOO_H

class QString;
class QStringList;

enum actions
{
    towar,
    klient,
    usr,
    help
};

bool connect(const QString& ip);
void import(const QString& fileName, QStringList& sl, actions action, bool dryRun = true);
void importTowar(const QString& fileName, QStringList& sl, bool dryRun);
void importKlient(const QString& fileName, QStringList& sl, bool dryRun);
void importUser(const QString& fileName, QStringList& sl, bool dryRun);

#endif // FOO_H
