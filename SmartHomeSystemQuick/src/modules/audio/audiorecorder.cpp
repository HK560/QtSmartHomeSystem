#include "audiorecorder.h"

void testAudioRecorder(const QString &device, const QString &filePath) {
  AudioRecorder recorder(NULL);
  recorder.printAvailableDevices();
  recorder.setAudioDeviceByName(device);
  // 定时器，5秒后停止录制
  recorder.startRecording();

  QTimer timer;
  timer.setSingleShot(true);
  QObject::connect(&timer, &QTimer::timeout,
                   [&recorder]() { recorder.stopRecording(); });
  timer.start(60000); // 60秒钟

  // 运行事件循环，直到录制完成
  QEventLoop loop;
  QObject::connect(&recorder, &AudioRecorder::recordingFinished, &loop,
                   &QEventLoop::quit);
  loop.exec();
}

QStringList AudioRecorder::getAvailableDevices() {
  updateAvailableDevices();
  return m_availableDevices;
}

void AudioRecorder::updateAvailableDevices() {
  m_availableDevices.clear();
  QAudioDeviceInfo defaultDevice = QAudioDeviceInfo::defaultInputDevice();
  m_availableDevices << defaultDevice.deviceName();
  for (const auto &device :
       QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
    if (device.deviceName() != defaultDevice.deviceName()) {
      m_availableDevices << device.deviceName();
    }
  }
}

// bool AudioRecorder::setAudioDeviceByName(const QString &name) {
//   updateAvailableDevices();
//   if (m_availableDevices.contains(name)) {
//     audioDevice = name;
//     QList<QAudioDeviceInfo> devices =
//         QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
//     for (const QAudioDeviceInfo &device : devices) {
//       if (device.deviceName() == audioDevice) {
//         m_deviceInfo = device;
//         outInfo << "m_deviceInfo" << device.deviceName();
//         return true;
//       }
//     }
//     outInfo << "Cant find " << audioDevice;

//     return false;
//   }
//   outWarn << name << "is not available!";
//   return false;
// }
