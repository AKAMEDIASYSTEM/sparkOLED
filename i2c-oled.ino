#include "application.h"
// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
// This #include statement was automatically added by the Spark IDE.

// This #include statement was automatically added by the Spark IDE.
#include "glcdfont.h"




// Address for 128x64 is 0x3D (default) or 0x3C (if SA0 is grounded)
char OLED_Address = 0x3D;
char OLED_Command_Mode = 0x80;
char OLED_Data_Mode = 0x40;


int rst = D3;
int led = D7;

Adafruit_SSD1306 scr(rst);

void setup() {
    //begin Wire communication with OLED
    Wire.begin();
    
    //set the one external function to call to update the OLED with a message
    Spark.function("update", update);
    pinMode(led,OUTPUT);
    //initialize screen
    scr.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
    // scr.display();
    // delay(2000);
    scr.clearDisplay();

}

void loop() {
//nothing happens in loop in this example
//just call 'update' from the web to update screen

}

int update(String args) {
    digitalWrite(led,HIGH);
    scr.clearDisplay();
    int status_code = args.length();
    
    scr.clearDisplay(); // ** Clear display
    scr.setTextColor(WHITE);
    scr.setCursor(10,10);
    if(status_code>20){
        scr.setTextSize(1);
    } else {
        scr.setTextSize(2);
    }
    args.replace("%20","\r");
    // args.replace("%20"," ");
    scr.print(args);
    scr.display();

    //how many lines sent to display
    // delay(1000);
    digitalWrite(led,LOW);
    return status_code;
}