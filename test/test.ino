
#include <SCoop.h>
//定义线程一
defineTask(Task1);
void Task1::setup()
{
  pinMode(13, OUTPUT);
  //多线程的setup
}
void Task1::loop()
{
  digitalWrite(13, HIGH);
  sleep(1000);
  digitalWrite(13, LOW);
  sleep(1000);
  //多线程的loop
}
 
void setup() {
  mySCoop.start();
}
void loop()
{
  yield();
}
 
 
