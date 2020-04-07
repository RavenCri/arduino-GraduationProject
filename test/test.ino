#include <WiFi.h>
#include <PubSubClient.h>
const char* ssid = "F";
const char* password =  "13892393046";
const char* mqtt_server = "192.168.0.104";
const int mqttPort = 1883;
const char* user = "raven";
const char* pass = "123456";

#define arduinoSerial Serial2
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  arduinoSerial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String data = "";
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    data += (char)payload[i];
  }
  Serial.println(data);
  arduinoSerial.print(data);
  if ((char)payload[0] == '1') {
    //digitalWrite(BUILTIN_LED, LOW);   
    
  } else {
   // digitalWrite(BUILTIN_LED, HIGH);  
  }

}

void reconnect() {
  // 如果wifi连接成功
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // 创建一个随机id
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // 开始连接mqtt服务器
    if (client.connect(clientId.c_str(),user,pass)) {
      Serial.println("connected");
      // 发布消息
      client.publish("outTopic", "hello world");
      //订阅消息
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
//  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqttPort);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}
