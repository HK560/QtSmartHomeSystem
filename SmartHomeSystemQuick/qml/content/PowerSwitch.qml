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

import QtQuick 2.15
import QtQuick.Templates 2.15
import QtGraphicalEffects 1.15
import Thermo 1.0

Switch {
    id: control
    implicitWidth: Math.max(background.implicitWidth + leftInset + rightInset,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background.implicitHeight + topInset + bottomInset,
                             contentItem.implicitHeight + topPadding + bottomPadding)
    leftInset: 14
    topInset: 14
    rightInset: 14
    bottomInset: 14

    background:     Rectangle {
//        color: "#ff4747"
//        color: "#3bea8a"
        color: control.checkable ? (control.checked ? "#3bea8a" :"#ff4747"):"#000000"

        radius: 5
        Behavior on color {
            ColorAnimation {
                id:colorTofalse
                duration: 200
            }}
//        hue: control.checked ? 0.2 : 1.0
//        source: "assets/switch-bg.png"

        Row {
            anchors.centerIn: parent
            spacing: 8

            Image {
                source: "assets/switch-i.png"
            }
            Image {
                source: "assets/switch-o.png"
            }
        }
    }

    // TODO: move this to indicator when AbstractButton gets it.
    // We don't use text with our switches, but moving it to indicator
    // will allow us to remove this intermediate Item, since we have
    // full control over indicator's geometry.
    contentItem: Item {
        Image {
            source: "assets/switch-handle.png"
            // 9 is the space on each side of the handle in the image.
            x: Math.max(-9 + control.leftInset, Math.min((parent.width - width - control.rightInset) + 9,
                control.visualPosition * parent.width - (width / 2)))
            y: (Theme.isBig ? -3 : -4) + control.topInset

            Behavior on x { NumberAnimation { duration: 150 } }
        }
    }

    Rectangle {
        id: rectangle
        visible: false
        color: "#ffffff"
        anchors.fill: parent
        implicitWidth:parent.implicitWidth
        anchors.topMargin: -10
    }
}
