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
    readonly property bool isBig: false
    readonly property int screenWidth: 480
    readonly property int screenHeight: 272
    readonly property int topBarHeight: 45
    readonly property int topBarFontSize: 16
    readonly property int bottomBarHeight: 35
    readonly property int bottomBarFontSize: 14
    readonly property int dialogBarHeight: 39
    readonly property int dialogLeftMargin: 20
    readonly property int dialogRightMargin: 20
    readonly property int dialogButtonHeight: 32

    readonly property int thermoY: 10
    readonly property int thermoHandleSize: 50
    readonly property int tempControlOffset: 13
    readonly property int roomButtonsY: 26

    readonly property int wheelStatusTextSize: 10 // FIXME: not in zeplin
    readonly property int wheelTempTextSize: 48
    readonly property int wheelTempUnitSize: 16
    readonly property real wheelSize: 85.5
    readonly property real wheelControlSize: 4

    readonly property real roomButtonSize: 45
    readonly property real roomButtonSpacing: 20
    readonly property real roomButtonMargin: 35

    readonly property int cardRoomFontSize: 22
    readonly property int cardFloorFontSize: 10
    readonly property int cardTemperatureTopMargin: 15
    readonly property int cardTemperatureLeftMargin: 17
    readonly property int cardSeparatorLeftMargin: 123
    readonly property int cardSeparatorTopMargin: 63
    readonly property int cardRoomColumnSpacing: 0
    readonly property int cardRoomColumnTopMargin: 15
    readonly property int cardRoomColumnLeftMargin: 122
    readonly property int cardIndicatorSpacing: 5
    readonly property int cardStateFontSize: 18

    readonly property int powerSwitchWidth: 64
    readonly property int powerSwitchHeight: 28
    readonly property int powerSwitchRightMargin: 5
    readonly property int powerSwitchTopMargin: 69

    readonly property int cardWidth: 324
    readonly property int cardHeight: 132
    readonly property int cardCornerRadius: 12
    readonly property int cardRowSpacing: 10
    readonly property int cardRowOffset: 20
    readonly property int cardRowIndicatorSpacing: 5
    readonly property int cardRowIndicatorBottomMargin: 12

    readonly property int roomViewTempWidth: 15 + 42
    readonly property int roomViewTempHeight: 2 + 52

    readonly property int scheduleViewListTextSize: 15
    readonly property int scheduleViewListWidth: 160

    readonly property int roomScheduleTopMargin: 0

    readonly property int statsTopGradientSpacer: 5
    readonly property int statsViewToggleTopMargin: 12
    readonly property int statsViewChartLabelFontSize: 12
    readonly property int statsViewChartLeftMargin: 70
    readonly property int statsViewChartRightMargin: 30
    readonly property int statsViewChartBottomMargin: 35
    readonly property int statsViewChartTopMargin: 30
    readonly property int statsViewButtonFontSize: 12
    readonly property int statsViewButtonVCenter: 31
    readonly property int statsViewButtonMonthHCenter: 75
    readonly property int statsViewButtonYearHCenter: 212

    readonly property int sliderLabelFontSize: 10
    readonly property int sliderHandleLabelFontSize: 12
    readonly property int sliderHandleSize: 27

    readonly property int sliderSpacing: 21
    readonly property int sliderLabelSpacing: 28
    readonly property int sliderWidth: 233
}
