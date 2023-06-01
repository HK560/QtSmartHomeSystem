#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H
#include "qobjectdefs.h"
#include <QObject>

#include <QAudioRecorder>
#include <QUrl>

#include "../global/init.h"
#include "src/modules/global/init.h"
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioRecorder>
#include <QCoreApplication>
#include <QEventLoop>
#include <QFile>
#include <QMultimedia>
#include <QTimer>
#include <QUrl>

class AudioRecorder : public QObject {
  Q_OBJECT

public:
  AudioRecorder(QObject *parent) : QObject(parent) {
    updateAvailableDevices();
    // recorder = new QAudioRecorder();
    // audioSettings = new QAudioEncoderSettings();
    // // 设置编码器设置
    m_deviceInfo = QAudioDeviceInfo::defaultOutputDevice();
    m_format.setSampleRate(16000);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::SignedInt);
  };
  ~AudioRecorder() { delete recorder; };
  // ~AudioRecorder() { delete recorder; };
  Q_INVOKABLE void startRecording() {
    // 如果已经在录制，则不执行任何操作
    // if (recording) {
    //   outWarn << "ALREADY RECORDING;Going to stop recording";
    //   recorder->stop();
    //   recorder->deleteLater();
    //   // return;
    // }
    // audioSettings->setCodec("audio/pcm");
    // //     audioSettings->setQuality(QMultimedia::LowQuality);
    // audioSettings->setSampleRate(16000);
    // outInfo << audioSettings->sampleRate();
    // audioSettings->setChannelCount(1);
    // audioSettings->setBitRate(320000);
    // //  audioSettings.setSampleSize(16);
    // audioSettings->setEncodingMode(QMultimedia::ConstantQualityEncoding);
    // recorder->setOutputLocation(QUrl::fromLocalFile(
    //     QCoreApplication::applicationDirPath() + "/shit.wav"));
    // recorder->setEncodingSettings(*audioSettings);
    // // 设置音频输入设备
    // //    recorder->setAudioInput(audioDevice);
    // recorder->setEncodingSettings(*audioSettings);
    // //    QAudioFormat auido_input_format;
    // //    auido_input_format.setSampleRate(16000); //设置采样率以对赫兹采样。
    // //           auido_input_format.setChannelCount(1);
    // //将通道数设置为通道。
    // //           auido_input_format.setSampleSize(16);
    // //
    // /*将样本大小设置为指定的sampleSize（以位为单位）通常为8或16，但是某些系统可能支持更大的样本量。*/
    // //           auido_input_format.setCodec("audio/pcm"); //设置编码格式
    // //           auido_input_format.setByteOrder(QAudioFormat::LittleEndian);
    // //           //样本是小端字节顺序
    // //           auido_input_format.setSampleType(QAudioFormat::UnSignedInt);
    // //           //样本是无符号整数
    // QList<int> sampleRates =
    //     recorder->supportedAudioSampleRates(QAudioEncoderSettings());
    // foreach (int sampleRate, sampleRates) {
    //   qDebug() << sampleRate;
    // }

    // //    recorder->setEncodingSettings(auido_input_format);
    // // 设置编码器设置和输出位置

    // // 开始录制
    // outInfo << "Using " << audioDevice << "to record audio";
    // recorder->record();

    // // 标记为正在录制
    // recording = true;

    ////////////////////////////////////////////////

    if (m_audioInput) {
      delete m_audioInput;
      m_audioInput = nullptr;
      // return;
    }
    m_buffer.clear();

    // 创建音频输入对象
    m_audioInput = new QAudioInput(m_deviceInfo, m_format, this);

    // 打开音频输入设备
    m_audioDevice = m_audioInput->start();
    outInfo << "start recording";

    // 连接读取数据的信号槽
    connect(m_audioDevice, &QIODevice::readyRead, this,
            &AudioRecorder::readData);

    m_recording = true;
  }

  void stopRecording() {
    // 如果没有在录制，则不执行任何操作
    // if (!recording) {
    //   outWarn << "NO RECORDING";
    //   return;
    // }

    // recorder->stop();
    // // recorder->deleteLater();
    // outInfo << "Stopped recording";
    // // 标记为已停止录制
    // recording = false;

    // emit recordingFinished();
    ///////////////////////////////////////////

    if (!m_recording) {
      return;
    }

    // 停止录音
    m_audioInput->stop();
    if (m_audioDevice->isOpen()) {
      // 释放音频缓冲区
      m_audioInput->reset();
    }
    // m_audioDevice->close();
    outInfo << "Stopped recording";
    delete m_audioInput;
    m_audioInput = nullptr;
    // delete m_audioDevice;
    m_audioDevice = nullptr;

    // 清空录音缓冲区和录制状态
    m_recording = false;
  }

  void printAvailableDevices() {
    QList<QAudioDeviceInfo> devices =
        QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    qDebug() << "Available audio devices:";
    for (const auto &device : devices) {
      qDebug() << device.deviceName();
    }
  }

  void setAudioDevice(int index) {
    if (index < 0 || index >= m_availableDevices.size()) {
      return;
    }
    outInfo << "Set audioDevice index" << index << m_availableDevices[index];
    audioDevice = m_availableDevices[index];
    // m_deviceInfo = m_availableDevices[index];
    // 如果正在录制，则重新打开音频设备
    // if (recording && recorder->state() == QMediaRecorder::RecordingState) {
    //   recorder->stop();
    //   recording = false;
    // }

    QList<QAudioDeviceInfo> devices =
        QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    for (const QAudioDeviceInfo &device : devices) {
      if (device.deviceName() == m_availableDevices[index]) {
        m_deviceInfo = device;
        outInfo << "m_deviceInfo" << device.deviceName();
        return;
      }
    }
    outInfo << "Cant find " << m_availableDevices[index];
    return;
  };
  void setAudioDeviceByName(const QString& name) {

    audioDevice = name;

    // 如果正在录制，则重新打开音频设备
    // if (recording && recorder->state() == QMediaRecorder::RecordingState) {
    //   recorder->stop();
    //   recording = false;
    // }

    QList<QAudioDeviceInfo> devices =
        QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    for (const QAudioDeviceInfo &device : devices) {
      if (device.deviceName() == name) {
        m_deviceInfo = device;
        outInfo << "m_deviceInfo" << device.deviceName();
        return;
      }
    }
    outInfo << "Cant find " << name;
    return;
  };

  void readData() {
    if (!m_audioDevice) {
      return;
    }

    // 读取录音数据
    m_buffer.append(m_audioDevice->readAll());

    // 发送数据可用信号
    emit dataReady(m_buffer);
    saveToFile(QCoreApplication::applicationDirPath() + "/tmp/sttTmp.wav");
  }

  void saveToFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      qDebug() << "Cannot open file for writing:" << fileName;
      return;
    }

    // 写入录音数据
    file.write(m_buffer);

    // 关闭文件
    file.close();
  }

  QStringList getAvailableDevices();

  // bool setAudioDeviceByName(const QString &name);

  void updateAvailableDevices();

  QString getAudioDevice() { return audioDevice; }

signals:
  void recordingFinished();

  void dataReady(const QByteArray &data);

private:
  QAudioRecorder *recorder = nullptr;
  bool recording = false;
  QString audioDevice = "default";
  QAudioEncoderSettings *audioSettings = nullptr;

  QStringList m_availableDevices;

  bool m_recording;
  QAudioFormat m_format;
  QAudioDeviceInfo m_deviceInfo;
  QAudioInput *m_audioInput = nullptr;
  QIODevice *m_audioDevice= nullptr;
  QByteArray m_buffer;
};
void testAudioRecorder(const QString &device, const QString &filePath);
#endif // AUDIORECORDER_H
