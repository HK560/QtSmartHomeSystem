import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 1024
    height: 500
    visible: true

    property string cityCode


    Rectangle {
        id: rectangle
        color: "#97282828"
        anchors.fill: parent

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked:{
                item1.visible = false
            }
        }
    }

    Rectangle {
        id: rectangle1
        width: 1000
        height: 341
        color: "#00318fc9"
        radius: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter

        WeatherDayInfo{
            id: day1
            width: 200
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            anchors.leftMargin: 0

        }
        WeatherDayInfo{
            id: day2
            y: 0
            width: 200
            height: 341
            anchors.left: day1.right
            anchors.leftMargin: 0

        }

        WeatherDayInfo {
            id: day3
            y: 0
            width: 200
            height: 341
            anchors.left: day2.right
            anchors.leftMargin: 0

        }

        WeatherDayInfo {
            id: day4
            y: 0
            width: 200
            height: 341
            anchors.left: day3.right
            anchors.leftMargin: 0

        }

        WeatherDayInfo {
            id: day5
            x: 827
            y: 0
            width: 200
            height: 341
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Rectangle {
        id: rectangle2
        y: 420
        width: 50
        height: 50
        color: "#ffffff"
        radius: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: settings_gear_icon
            anchors.fill: parent
            source: "images/icon/settings_gear_icon.png"
            fillMode: Image.PreserveAspectFit
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                settingCity.visible = true
            }
        }
    }

    Rectangle {
        id: settingCity
                visible: false

        color: "#c2383838"
        anchors.fill: parent

        MouseArea {
            id: mouseArea2
            anchors.fill: parent
            onClicked:{

                settingCity.visible = false
            }
        }

        Rectangle {
            id: rectangle3
            width: 518
            height: 366
            visible: true
            color: "#ffffff"
            radius: 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            MLineEdit1 {
                id: cityLineEdit
                y: 35
                width: 279
                height: 50
                anchors.left: parent.left
                textInputText: ""
                anchors.leftMargin: 38
            }

            MbuttonBlue {
                id: searchBtn
                x: 340
                y: 35
                text: "搜索"
                anchors.right: parent.right
                anchors.rightMargin: 28
                onClicked: {
                    console.log("doing addcitymodel");
                    cityListModel.clear();
                    var max = qmlCtrl.searchCityCode(cityLineEdit.textInputText)
                    for(var i = 0;i<max;i++){
                        addCityModel(qmlCtrl.getCityNameByIndex(i),qmlCtrl.getCityCodeByIndex(i));
                    }
                    //                    var max = qmlCtrl.getWifiListSize();
                    //                    for(var i = 0; i<max;i++){
                    //                        addWifiModel(qmlCtrl.getWifiName(i),qmlCtrl.getWifiLevel(i));
                    //                    }
                }
            }

            Rectangle {
                id: rectangle22
                x: 39
                y: 95
                width: 440
                height: 250
                color: "#32000000"
                radius: 30
                border.width: 0
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 37
                anchors.horizontalCenter: parent.horizontalCenter

                //        FastBlur {
                //            anchors.fill: parent
                //            source: rectangle
                //            focus: false
                //            activeFocusOnTab: false
                //            antialiasing: false
                //            clip: true
                //            transparentBorder: true
                //            cached: false
                //            radius: 32
                //        }

                ListView {
                    id: listView
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    // anchors.bottom: parent.bottom

                    anchors.fill: parent
                    anchors.bottomMargin: 31
                    anchors.rightMargin: 15
                    anchors.leftMargin: 25
                    // anchors.bottomMargin: 20
                    anchors.topMargin: 48

                    model: ListModel {
                        id: cityListModel
                        ListElement {
                            cityNameText: "Grey"
                            cityCodeText: "1"
                        }
                        ListElement {
                            cityNameText: "Grey"
                            cityCodeText: "1"
                        }
                    }
                    delegate: cityDelegate
                    focus: true;
                }
            }
        }





        Component {
            id: cityDelegate
            //            property bool selected : ListView.isCurrentItem
            Item {
                id: wrapper
                property bool selected : ListView.isCurrentItem
                width: listView.width
                height: 50
                Rectangle{
                    id:cityNameRectangle
                    width: parent.width/2
                    height: 30
                    color: "#00ffffff"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    MLabel2{
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        labelText:cityNameText+"\t\t"+cityCodeText
                        labelHorizontalAlignment: Text.AlignLeft
                        labelColor: listView.currentIndex === index ?"#157efb":"#ffffff"}
                }
                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
//                        console.info("click listview")
                        wrapper.ListView.view.currentIndex = index;
                        item1.cityCode = getCityCode(index);
                        qmlCtrl.getWeatherReq(item1.cityCode);
                        qmlCtrl.setCityCodeToDB(item1.cityCode);
                    }
                }
            }
        }

    }

    Connections{
        target: qmlCtrl;
        function onWeatherInfoChanged(){
            day1.week = qmlCtrl.getWeatherInfo(0,0)
            day1.date= qmlCtrl.getWeatherInfo(1,0)
            day1.tempRange= qmlCtrl.getWeatherInfo(2,0)
            day1.weather= qmlCtrl.getWeatherInfo(3,0)
            day1.wind=qmlCtrl.getWeatherInfo(4,0)

            day2.week=qmlCtrl.getWeatherInfo(0,1)
            day2.date= qmlCtrl.getWeatherInfo(1,1)
            day2.tempRange= qmlCtrl.getWeatherInfo(2,1)
            day2.weather= qmlCtrl.getWeatherInfo(3,1)
            day2.wind=qmlCtrl.getWeatherInfo(4,1)

            day3.week= qmlCtrl.getWeatherInfo(0,2)
            day3.date= qmlCtrl.getWeatherInfo(1,2)
            day3.tempRange= qmlCtrl.getWeatherInfo(2,2)
            day3.weather= qmlCtrl.getWeatherInfo(3,2)
            day3.wind=qmlCtrl.getWeatherInfo(4,2)

            day4.week= qmlCtrl.getWeatherInfo(0,3)
            day4.date= qmlCtrl.getWeatherInfo(1,3)
            day4.tempRange= qmlCtrl.getWeatherInfo(2,3)
            day4.weather= qmlCtrl.getWeatherInfo(3,3)
            day4.wind=qmlCtrl.getWeatherInfo(4,3)

            day5.week= qmlCtrl.getWeatherInfo(0,4)
            day5.date= qmlCtrl.getWeatherInfo(1,4)
            day5.tempRange= qmlCtrl.getWeatherInfo(2,4)
            day5.weather= qmlCtrl.getWeatherInfo(3,4)
            day5.wind=qmlCtrl.getWeatherInfo(4,4)
        }
    }

    function getCityCode(index){
        var item = cityListModel.get(index);
        return item.cityCodeText;
    }

    function addCityModel(cityName,cityCode){
        console.log("add city:",cityName,cityCode);
        cityListModel.append({cityNameText:cityName, cityCodeText:cityCode})
    }

    Component.onCompleted: {
            cityListModel.clear();

        day1.week = qmlCtrl.getWeatherInfo(0,0)
        day1.date= qmlCtrl.getWeatherInfo(1,0)
        day1.tempRange= qmlCtrl.getWeatherInfo(2,0)
        day1.weather= qmlCtrl.getWeatherInfo(3,0)
        day1.wind=qmlCtrl.getWeatherInfo(4,0)

        day2.week=qmlCtrl.getWeatherInfo(0,1)
        day2.date= qmlCtrl.getWeatherInfo(1,1)
        day2.tempRange= qmlCtrl.getWeatherInfo(2,1)
        day2.weather= qmlCtrl.getWeatherInfo(3,1)
        day2.wind=qmlCtrl.getWeatherInfo(4,1)

        day3.week= qmlCtrl.getWeatherInfo(0,2)
        day3.date= qmlCtrl.getWeatherInfo(1,2)
        day3.tempRange= qmlCtrl.getWeatherInfo(2,2)
        day3.weather= qmlCtrl.getWeatherInfo(3,2)
        day3.wind=qmlCtrl.getWeatherInfo(4,2)

        day4.week= qmlCtrl.getWeatherInfo(0,3)
        day4.date= qmlCtrl.getWeatherInfo(1,3)
        day4.tempRange= qmlCtrl.getWeatherInfo(2,3)
        day4.weather= qmlCtrl.getWeatherInfo(3,3)
        day4.wind=qmlCtrl.getWeatherInfo(4,3)

        day5.week= qmlCtrl.getWeatherInfo(0,4)
        day5.date= qmlCtrl.getWeatherInfo(1,4)
        day5.tempRange= qmlCtrl.getWeatherInfo(2,4)
        day5.weather= qmlCtrl.getWeatherInfo(3,4)
        day5.wind=qmlCtrl.getWeatherInfo(4,4)
    }
}
