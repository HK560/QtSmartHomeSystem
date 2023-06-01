#ifndef TERMINALEXEC_H
#define TERMINALEXEC_H

#include <QObject>
#include <QProcess>
#include "init.h"

class TerminalExec : public QObject
{
    Q_OBJECT

    QProcess *terminalProcess = nullptr;

public:
    explicit TerminalExec(QObject *parent = nullptr);
    // void init();
    ~TerminalExec();
    QString execute(const QString &command,const QStringList args);
public slots:
    void errorPrint(QProcess::ProcessError error){
        outDebug <<"error code: "<<error;
    }
signals:

};

#endif // TERMINALEXEC_H
