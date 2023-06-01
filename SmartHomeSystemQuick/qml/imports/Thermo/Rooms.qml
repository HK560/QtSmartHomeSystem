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
    function getByIndex(index : int) : Room {
        switch(index) {
            case 0: return Rooms.livingRoom
            case 1: return Rooms.diningRoom
            case 2: return Rooms.kitchenRoom
            case 3: return Rooms.kidsRoom
            case 4: return Rooms.kids2Room
            case 5: return Rooms.bedRoom
            default: return Rooms.livingRoom
        }
    }
    property Room livingRoom: Room {
        id: livingRoom
        name: qsTr("Living room")
        floor: qsTr("First floor")
        temperature: Units.fahrenheitToTemperatureUnit(69)
        status: Room.Heating
        fan: Room.FanHalf
    }

    property Room diningRoom: Room {
        id: diningRoom
        name: qsTr("Dining room")
        floor: qsTr("First floor")
        temperature: Units.fahrenheitToTemperatureUnit(71)
        status: Room.Cooling
        fan: Room.FanQuarter
    }

    property Room kitchenRoom: Room {
        id: kitchenRoom
        name: qsTr("Kitchen")
        floor: qsTr("First floor")
        power: false
        temperature: Units.fahrenheitToTemperatureUnit(68)
        status: Room.Off
    }

    property Room kidsRoom: Room {
        id: kidsRoom
        name: qsTr("Kids bedroom")
        floor: qsTr("Second floor")
        temperature: Units.fahrenheitToTemperatureUnit(65)
        status: Room.Cooling
    }

    property Room kids2Room: Room {
        id: kids2Room
        name: qsTr("Kids bedroom 2")
        floor: qsTr("Second floor")
        temperature: Units.fahrenheitToTemperatureUnit(71)
        status: Room.Heating
        fan: Room.FanFull
    }

    property Room bedRoom: Room {
        id: bedRoom
        name: qsTr("Master bedroom")
        floor: qsTr("Second floor")
        temperature: Units.fahrenheitToTemperatureUnit(68)
        status: Room.Heating
    }
}
