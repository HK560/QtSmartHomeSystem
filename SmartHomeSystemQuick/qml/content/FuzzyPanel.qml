import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.12
Rectangle{
   clip: true

   // 属性
   property Item target
   radius: 30
   border.width: 0  // 模糊源

   // 毛玻璃效果
   FastBlur {
       id: blur
       source: parent.target
       transparentBorder: true
        width: source.width;
        height: source.height
        radius: 32
    }

    // 设置模糊组件的位置
    onXChanged: setBlurPosition();
    onYChanged: setBlurPosition();
    Component.onCompleted: setBlurPosition();
    function setBlurPosition(){
        blur.x = target.x - x;
        blur.y = target.y - y;
    }
}
