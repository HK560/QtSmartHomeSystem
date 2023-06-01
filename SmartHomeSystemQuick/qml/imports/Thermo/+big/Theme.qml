/******************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Quick Ultralite module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/
pragma Singleton
import QtQuick 2.15

QtObject {
    readonly property bool isBig: true
    readonly property int screenWidth: 800
    readonly property int screenHeight: 480
    readonly property int topBarHeight: 84
    readonly property int topBarFontSize: 32
    readonly property int bottomBarHeight: 72
    readonly property int bottomBarFontSize: 24
    readonly property int dialogBarHeight: 62
    readonly property int dialogLeftMargin: 30
    readonly property int dialogRightMargin: 30
    readonly property int dialogButtonHeight: 48

    readonly property int thermoY: 18
    readonly property int thermoHandleSize: 60
    readonly property int tempControlOffset: 6
    readonly property int roomButtonsY: 48

    readonly property int wheelStatusTextSize: 18
    readonly property int wheelTempTextSize: 80
    readonly property int wheelTempUnitSize: 21
    readonly property real wheelSize: 142.5
    readonly property real wheelControlSize: 7

    readonly property real roomButtonSize: 80
    readonly property real roomButtonSpacing: 30
    readonly property real roomButtonMargin: 81

    readonly property int cardRoomFontSize: 30
    readonly property int cardFloorFontSize: 16
    readonly property int cardTemperatureTopMargin: 22
    readonly property int cardTemperatureLeftMargin: 23
    readonly property int cardSeparatorLeftMargin: 25
    readonly property int cardSeparatorTopMargin: 178
    readonly property int cardRoomColumnSpacing: 4
    readonly property int cardRoomColumnTopMargin: 95
    readonly property int cardRoomColumnLeftMargin: 23
    readonly property int cardIndicatorSpacing: 11
    readonly property int cardStateFontSize: 22

    readonly property int powerSwitchWidth: 100
    readonly property int powerSwitchHeight: 42
    readonly property int powerSwitchRightMargin: 11
    readonly property int powerSwitchTopMargin: 11

    readonly property int cardWidth: 325
    readonly property int cardHeight: 250
    readonly property int cardCornerRadius: 12
    readonly property int cardRowSpacing: 20
    readonly property int cardRowOffset: 35
    readonly property int cardRowIndicatorSpacing: 16
    readonly property int cardRowIndicatorBottomMargin: 18

    readonly property int roomViewTempWidth: 14 + 80
    readonly property int roomViewTempHeight: 9 + 80

    readonly property int scheduleViewListTextSize: 22
    readonly property int scheduleViewListWidth: 208

    readonly property int roomScheduleTopMargin: -4

    readonly property int statsTopGradientSpacer: 10
    readonly property int statsViewToggleTopMargin: 24
    readonly property int statsViewChartLabelFontSize: 20
    readonly property int statsViewChartLeftMargin: 110
    readonly property int statsViewChartRightMargin: 50
    readonly property int statsViewChartBottomMargin: 50
    readonly property int statsViewChartTopMargin: 50
    readonly property int statsViewButtonFontSize: 20
    readonly property int statsViewButtonVCenter: 38
    readonly property int statsViewButtonMonthHCenter: 80
    readonly property int statsViewButtonYearHCenter: 216


    readonly property int sliderLabelFontSize: 18
    readonly property int sliderHandleLabelFontSize: 16
    readonly property int sliderHandleSize: 54

    readonly property int sliderSpacing: 24
    readonly property int sliderLabelSpacing: 44
    readonly property int sliderWidth: 472
}
