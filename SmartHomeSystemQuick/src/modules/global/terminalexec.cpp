#include "terminalexec.h"
#include "src/modules/global/terminalexec.h"

TerminalExec::TerminalExec(QObject *parent) : QObject{parent} {
  terminalProcess = new QProcess(this);
  connect(terminalProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this,
          SLOT(errorPrint(QProcess::ProcessError)));
}

TerminalExec::~TerminalExec() { delete terminalProcess; }

// void TerminalExec::init()
// {
//     return;
// }

QString TerminalExec::execute(const QString &command, const QStringList args) {
  if (terminalProcess == nullptr) {
    outDebug << "terminalProcess has not been initialized";
    return QString("");
  }

  terminalProcess->start(command, args);
  terminalProcess->waitForStarted();
  terminalProcess->waitForFinished();

  QString result = terminalProcess->readAllStandardOutput();
  // outDebug << result;
  terminalProcess->close();
  terminalProcess->waitForFinished();
  return result;
}
