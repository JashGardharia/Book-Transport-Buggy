// NOTE: THIS CODE IS NOT THE ACTUAL CODE FOR THE BOOK TRANSPORT BUGGY, BUT INSTEAD, IS AN DEMONSTRATIVE PROTOTYPE STRUCTURAL CODE.
// THE ACTUAL CODE IS NOT PROVIDED DUE TO COPYRIGHT ISSUES.©
#include <WiFi.h>
#include <WiFiClient.h>
#include <AccelStepper.h>

const char* ssid = "BookBuggyNet";
const char* password = "12345678";

WiFiServer server(80);

const int IN1 = 14;
const int IN2 = 27;
const int IN3 = 26;
const int IN4 = 25;

const int lidarPin = 34;

const int motorLeftA = 18;
const int motorLeftB = 19;
const int motorRightA = 21;
const int motorRightB = 22;

const int enableLeft = 5;
const int enableRight = 17;

int currentClassroom = 0;
bool navigationActive = false;

unsigned long navigationTimer = 0;
unsigned long lidarCheckTimer = 0;

int motorSpeed = 180;

struct Waypoint {
  int leftSpeed;
  int rightSpeed;
  int duration;
};

Waypoint corridorPath[] = {
  {180,180,3000},
  {180,150,1500},
  {180,180,2500},
  {150,180,1200},
  {180,180,2000}
};

Waypoint classroom1[] = {
  {180,180,2000},
  {150,180,1000},
  {180,180,1500}
};

Waypoint classroom2[] = {
  {180,180,1500},
  {180,150,900},
  {180,180,1800}
};

Waypoint classroom3[] = {
  {180,180,2500},
  {150,180,800},
  {180,180,1300}
};

int corridorSize = sizeof(corridorPath)/sizeof(Waypoint);
int class1Size = sizeof(classroom1)/sizeof(Waypoint);
int class2Size = sizeof(classroom2)/sizeof(Waypoint);
int class3Size = sizeof(classroom3)/sizeof(Waypoint);

void setMotor(int left,int right)
{
  if(left > 0)
  {
    digitalWrite(motorLeftA,HIGH);
    digitalWrite(motorLeftB,LOW);
  }
  else
  {
    digitalWrite(motorLeftA,LOW);
    digitalWrite(motorLeftB,HIGH);
  }

  if(right > 0)
  {
    digitalWrite(motorRightA,HIGH);
    digitalWrite(motorRightB,LOW);
  }
  else
  {
    digitalWrite(motorRightA,LOW);
    digitalWrite(motorRightB,HIGH);
  }

  analogWrite(enableLeft,abs(left));
  analogWrite(enableRight,abs(right));
}

void stopMotor()
{
  analogWrite(enableLeft,0);
  analogWrite(enableRight,0);
}

bool lidarObstacle()
{
  int value = digitalRead(lidarPin);
  if(value == HIGH) return true;
  return false;
}

void executePath(Waypoint path[], int size)
{
  for(int i=0;i<size;i++)
  {
    unsigned long start = millis();
    setMotor(path[i].leftSpeed,path[i].rightSpeed);

    while(millis()-start < path[i].duration)
    {
      if(lidarObstacle())
      {
        stopMotor();
        while(lidarObstacle()) delay(50);
        setMotor(path[i].leftSpeed,path[i].rightSpeed);
      }
      delay(5);
    }

    stopMotor();
    delay(200);
  }
}

void navigateToClass(int classID)
{
  executePath(corridorPath,corridorSize);

  if(classID == 1)
  {
    executePath(classroom1,class1Size);
  }

  if(classID == 2)
  {
    executePath(classroom2,class2Size);
  }

  if(classID == 3)
  {
    executePath(classroom3,class3Size);
  }

  stopMotor();
}

void processCommand(String cmd)
{
  if(cmd == "CLASS1")
  {
    currentClassroom = 1;
    navigationActive = true;
  }

  if(cmd == "CLASS2")
  {
    currentClassroom = 2;
    navigationActive = true;
  }

  if(cmd == "CLASS3")
  {
    currentClassroom = 3;
    navigationActive = true;
  }

  if(cmd == "STOP")
  {
    navigationActive = false;
    stopMotor();
  }
}

void handleClient()
{
  WiFiClient client = server.available();

  if(!client) return;

  String request = "";

  while(client.connected())
  {
    if(client.available())
    {
      char c = client.read();
      request += c;
      if(c == '\n') break;
    }
  }

  if(request.indexOf("CLASS1") >= 0) processCommand("CLASS1");
  if(request.indexOf("CLASS2") >= 0) processCommand("CLASS2");
  if(request.indexOf("CLASS3") >= 0) processCommand("CLASS3");
  if(request.indexOf("STOP") >= 0) processCommand("STOP");

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/plain");
  client.println();
  client.println("Book Buggy Ready");
  client.stop();
}

void wifiSetup()
{
  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
  }

  server.begin();
}

void setup()
{
  pinMode(motorLeftA,OUTPUT);
  pinMode(motorLeftB,OUTPUT);
  pinMode(motorRightA,OUTPUT);
  pinMode(motorRightB,OUTPUT);

  pinMode(enableLeft,OUTPUT);
  pinMode(enableRight,OUTPUT);

  pinMode(lidarPin,INPUT);

  stopMotor();

  wifiSetup();
}

void loop()
{
  handleClient();

  if(navigationActive)
  {
    navigationActive = false;
    navigateToClass(currentClassroom);
  }
} 
