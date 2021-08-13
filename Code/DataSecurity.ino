#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// Replace with your network credentials
const char* ssid = "redmi";
const char* password = "123456789";
//instantiate server at port 80 (http port)
ESP8266WebServer server(80);
int a=random(2,10);
String m="India my country";
long long int p=0;
int q=random(pow(2,8),pow(2,12));
int g=random(2,q);
// gcd function to find the greatest common divisor of two numbers
int gcd(int a,int b)
{
if(a<b)
{
return gcd(b,a);
}
else if(a%b==0)
{
return b;
}
else
{
return gcd(b, a % b);
}
}
int genkey(int q)
{
double po=pow(2,8);
int pp=(int)po;
int key=random(pp,q);
while(gcd(q,key)!=1)
{
key=random(pp,q);
}
return key;
}
int power(int a,int b,int c)
{
int x=1;
int y=a;
while(b>0)
{
if(b%2==0)
{
x=(x*y)%c;
}
y=(y*y)%c;
b=(int)(b/2);
}
return (x%c);
}
String encrypt(String m,int q,int h,int g)
{
int k = genkey(q);
String em="";
long long int s = power(h,k,q);
p = power(g,k,q);
int l=m.length();
char ch,cs;
long long int j;
int i=0;
for(i=0;i<l;i++)
{
ch=m.charAt(i);
j=((int)ch)+s;
cs=(char)j;
em=em+cs;
}
return em;
}
String decrypt(String em,long long int p,int key,int q)
{
String dm="";
long long int h=power(p,key,q);
char ch,cs;
int l=em.length();
int j;
int i=0;
for(i=0;i<l;i++)
{
ch=em.charAt(i);
j=((int)ch)-h;
cs=(char)j;
dm=dm+cs;
}
return dm;
}
int key=genkey(q);
long long int h=power(g,key,q);
String em=encrypt(m,q,h,g);
String answer=decrypt(em,p,key,q);
String page="";
unsigned long ttt;
void setup(void)
{
delay(1000);
Serial.begin(115200);
//begin WIFI connection
WiFi.begin(ssid, password);
Serial.println("");
// Wait for connection
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
server.on("/", [](){
page = "<h1>Message data to Node MCU Web Server</h1><h3>Message:</h3>
<h4>"+m+"</h4>"+"<h3>Encrypted Message:</h3> <h4>"+em+"</h4>"+"<h3>Decrypted
Message:</h3> <h4>"+answer+"</h4>";
server.send(200, "text/html", page);
});
server.begin();
Serial.println("Web server started!");
}
void loop(void){
Serial.print("Time: ");
ttt=millis();
Serial.println(ttt);
delay(1000);
server.handleClient();
}