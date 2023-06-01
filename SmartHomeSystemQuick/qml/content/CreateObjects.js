var component;
var DeviceCardSize = qmlCtrl.getDeviceListSize();


var DeviceCardArray = new Array;
var DeviceFuncArray = new Array;
var DeviceRVCard = new Array;

function createAllFunc(parent, deviceIndex) {
    var DeviceFuncSize = qmlCtrl.getDeviceFuncSize(deviceIndex);
    var DeviceFuncArrayTemp = new Array;
    for (var i = 0; i < DeviceFuncSize; i++) {
        DeviceFuncArrayTemp.push(createFuncCtrlObjects(parent, qmlCtrl.getDeviceFuncNameByIndex(deviceIndex, i), qmlCtrl.getDeviceFuncDescByIndex(deviceIndex, i), deviceIndex, i, qmlCtrl.getDeviceFuncTypeByIndex(deviceIndex, i), qmlCtrl.getDeviceFuncValueByIndex(deviceIndex, i), qmlCtrl.getDeviceFuncEnabledForAiByIndex(deviceIndex, i)));
    }
    //    DeviceCardArray = DeviceCardArrayTemp;
    DeviceFuncArray = DeviceFuncArrayTemp;
    return;
}



function createFuncCtrlObjects(parent, funcname, desc, deviceIndex, funcIndex, type, value, enabledForAi) {
    component = Qt.createComponent("FuncCtrlPanel.qml")
    console.log("doing creating object");
    var CtrlPanel;
    switch (type) {
        case 0:
            CtrlPanel = component.createObject(parent, { funcName: funcname, desc: desc, deviceIndex: deviceIndex, funcIndex: funcIndex, type: type, valueBool: Number(value), funcEnableForAI: enabledForAi });
            break;
        case 1:
            CtrlPanel = component.createObject(parent, { funcName: funcname, desc: desc, deviceIndex: deviceIndex, funcIndex: funcIndex, type: type, valueInt: Number(value), funcEnableForAI: enabledForAi });
            break;
        case 2:
            CtrlPanel = component.createObject(parent, { funcName: funcname, desc: desc, deviceIndex: deviceIndex, funcIndex: funcIndex, type: type, valueStr: value, funcEnableForAI: enabledForAi });
            break;
        default:
            console.warn("invaild funcCtrlObject");
    }
    if (CtrlPanel === null) {
        //错误处理
        console.log("Error creating object");
    }
    return CtrlPanel;
}



function destoryAllDeviceFuncObjects() {
    for (var i = 0; i < DeviceFuncArray.length; i++) {
        DeviceFuncArray[i].destroy();
    }
}


function createAllDevices(parent) {
    DeviceCardSize = qmlCtrl.getDeviceListSize();
    var DeviceCardArrayTemp = new Array;
    for (var i = 0; i < DeviceCardSize; i++) {
        qmlCtrl.getDeviceRecordFromDB(i);
        if (qmlCtrl.getDeviceEnable(i) === 0)
            continue;
        qmlCtrl.readDeviceSetting(i);

        DeviceCardArrayTemp.push(createDeviceCardObjects(parent, qmlCtrl.getDeviceNameFromIndex(i), qmlCtrl.getDeviceIDFromIndex(i), i));
    }
    DeviceCardArray = DeviceCardArrayTemp;
    return;
}


function createDeviceCardObjects(parent, deviceName, deviceIdName, deviceIndex) {
    component = Qt.createComponent("DeviceCard.qml")
    console.log("doing creating object");
    var DevicePanel;
    var banned = qmlCtrl.getDeviceIsBanned(deviceIdName) ? true : false;
    DevicePanel = component.createObject(parent, { deviceName: deviceName, deviceIdName: deviceIdName, deviceIndex: deviceIndex, lockDevice: banned });
    if (DevicePanel === null) {
        //错误处理
        console.log("Error creating object");
    }
    return DevicePanel;
}


function destoryAllDeviceCardObjects() {
    for (var i = 0; i < DeviceCardArray.length; i++) {
        DeviceCardArray[i].destroy();
    }
    // DeviceCardArray = new Array();
}




function createALLRvDevicePanel(parent) {
    component = Qt.createComponent("DeviceRvPanel.qml")
    var DeviceRVCardArrayTemp = new Array;
    var rvDeviceListSize = qmlCtrl.getDeviceRvListSize();
    for (var i = 0; i < rvDeviceListSize; ++i) {
        var rvDeviceSize = qmlCtrl.getDeviceRvSize(i);
        for (var j = 0; j < rvDeviceSize; ++j) {
            var DeviceRvPanel;
            DeviceRvPanel = component.createObject(parent,
                {
                    rvName: qmlCtrl.getDeviceRvName(i, j),
                    rvValue: qmlCtrl.getDeviceRvValue(i, j),
                    rvDesc: qmlCtrl.getDeviceRvDesc(i, j),
                    rvDeviceName: qmlCtrl.getRvDeviceName(i)
                });
            if (DeviceRvPanel === null) {
                //错误处理
                console.log("Error creating object");
                break;
            }
            DeviceRVCardArrayTemp.push(DeviceRvPanel);
        }
    }
    DeviceRVCard = DeviceRVCardArrayTemp;
}

function destoryAllRvDevicePanel() {
    for (var i = 0; i < DeviceRVCard.length; i++) {
        DeviceRVCard[i].destroy();
    }
}