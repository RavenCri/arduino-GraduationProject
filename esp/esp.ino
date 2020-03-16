// 电机引脚
const int djz = 2;
const int djf = 3;
const int leds[5] = {13,0,0,0,0};
const int ledLength = sizeof(leds)/sizeof(leds[0]);
int aroundSpeed = 100;
String data;
void setup() {
  pinMode(djz, OUTPUT);
  pinMode(djf, OUTPUT);
  Serial.begin(9600);
}
char buffer[100]; 
void loop() {
   
  if( Serial.available()>0 )
  {
    data = "";
    while( Serial.available()>0 ){
       data += char(Serial.read());
    }
    int index = data.indexOf("_");
    String type = data.substring(0,index);
    String motion = data.substring(index+1);
    executeCmd(type,motion);
  }
}
void executeCmd(String type,String motion){
  if(type.compareTo("electricMachinery")){
     int mot = motion.toInt();
     operationElectricMachinery(mot);
  }else if(type.compareTo("led")){
     int index = motion.indexOf("_");
     // 获取要操作几号灯
     int ledIndex = motion.substring(0,index).toInt();
     int mot = motion.substring(index+1).toInt();
     operationLED(ledIndex,mot);
  }
  
}
/**
 * 控制电机
 */
void operationElectricMachinery(int motion){
   switch(motion){
    case 0: // 停止转动
         digitalWrite(djz, HIGH);
         digitalWrite(djf, HIGH);
          break;
    case 1: // 正向转动
          digitalWrite(djz,aroundSpeed );
          digitalWrite(djf, HIGH);
          break;
    case 2:// 反向转动
          digitalWrite(djz, HIGH);
          digitalWrite(djf, aroundSpeed);
          break;
    case 3: //加速转动
          aroundSpeed += 50;
          if(aroundSpeed  >255){
            Serial.println("达到最大转速阈值");
            aroundSpeed = 255;
          }
          digitalWrite(djf, aroundSpeed);
          break;
    case 4: //减速转动
          aroundSpeed -= 50;
          if(aroundSpeed  < 0 ){
            aroundSpeed = 10;
            Serial.println("达到最小转速阈值");
          }
          digitalWrite(djf, aroundSpeed);
          break;
  }
}
/**
 * 控制灯
 */
void operationLED(int ledIndex,int motion){
   switch(ledIndex){
    case 0: // 0号灯
          digitalWrite(leds[ledIndex], motion);
          break;
    case 1: // 1号灯
          digitalWrite(leds[ledIndex], motion);
          break;
    case 99: //操作所有灯
         for(int i = 0; i<ledLength; i++){
            digitalWrite(leds[i], motion);
            delay(10);
         }
          break;
  }
}
