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
    
    //initialize screen
    // SetupScreen();
    scr.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
    scr.display();
    delay(2000);
    scr.clearDisplay();
    
    // sendCommand(0x01); // ** Clear display
    // sendMessage("started");
    
    // delay(1000);//wait one sec to see the started message
    
    // sendCommand(0x01); // ** Clear display
}

void loop() {
//nothing happens in loop in this example
//just call 'update' from the web to update screen

}

int update(String args) {
    pinMode(led,OUTPUT);
    digitalWrite(led,HIGH);
    int status_code = 0;
    
    scr.clearDisplay(); // ** Clear display
    
    args.replace("%20"," ");
    
    int commaPosition = args.indexOf(",");//find if there is a delim character
    
    if(commaPosition>-1){
        //two lines
        // scr.drawChar(args.substring(0,commaPosition));//send first part
        // sendCommand(0xC0); // ** New Line
        // scr.drawChar(args.substring(commaPosition+1, args.length()));//send second part
        scr.drawRoundRect(32,32,16,16,4,WHITE);
        scr.display();
        status_code = 2;//lines

    }   else {
        //one line
        // scr.drawChar(args);
        scr.drawRoundRect(16,16,16,16,4,WHITE);
        scr.display();
        status_code = 1;//lines
    }

    //how many lines sent to display
    digitalWrite(led,LOW);
    return status_code;
}

void SetupScreen(void){
    // using Adafruit ssd1306 init steps here to see if we can get it working
    pinMode(rst,OUTPUT);
    pinMode(led,OUTPUT);
    digitalWrite(rst,HIGH);
    digitalWrite(led,HIGH);
    delay(1);
    digitalWrite(rst,LOW);
    delay(10);
    digitalWrite(rst,HIGH);
    digitalWrite(led,LOW);
    
    sendCommand(SSD1306_DISPLAYOFF);                    // 0xAE
    sendCommand(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    sendCommand(0x80);                                  // the suggested ratio 0x80
    sendCommand(SSD1306_SETMULTIPLEX);                  // 0xA8
    sendCommand(0x3F);
    sendCommand(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    sendCommand(0x0);                                   // no offset
    sendCommand(SSD1306_SETSTARTLINE | 0x0);            // line #0
    sendCommand(SSD1306_CHARGEPUMP);                    // 0x8D
    // if (vccstate == SSD1306_EXTERNALVCC) 
    //   { sendCommand(0x10); }
    // else 
    //   { sendCommand(0x14); }
    sendCommand(0x14);
    sendCommand(SSD1306_MEMORYMODE);                    // 0x20
    sendCommand(0x00);                                  // 0x0 act like ks0108
    sendCommand(SSD1306_SEGREMAP | 0x1);
    sendCommand(SSD1306_COMSCANDEC);
    sendCommand(SSD1306_SETCOMPINS);                    // 0xDA
    sendCommand(0x12);
    sendCommand(SSD1306_SETCONTRAST);                   // 0x81
    // if (vccstate == SSD1306_EXTERNALVCC) 
    //   { sendCommand(0x9F); }
    // else 
    //   { sendCommand(0xCF); }
    sendCommand(0xCF);
    sendCommand(SSD1306_SETPRECHARGE);                  // 0xd9
    // if (vccstate == SSD1306_EXTERNALVCC) 
    //   { sendCommand(0x22); }
    // else 
    //   { sendCommand(0xF1); }
    sendCommand(0xF1); 
    sendCommand(SSD1306_SETVCOMDETECT);                 // 0xDB
    sendCommand(0x40);
    sendCommand(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    sendCommand(SSD1306_NORMALDISPLAY);                 // 0xA6
    
    
    sendCommand(SSD1306_DISPLAYON);
  
}

void sendData(unsigned char data) {
    Wire.beginTransmission(OLED_Address); // ** Start I2C
    Wire.write(OLED_Data_Mode); // ** Set OLED Data mode
    Wire.write(data);
    Wire.endTransmission(); // ** End I2C
    }

void sendCommand(unsigned char command) {
    Wire.beginTransmission(OLED_Address); // ** Start I2C
    Wire.write(OLED_Command_Mode); // ** Set OLED Command mode
    Wire.write(command);
    Wire.endTransmission(); // ** End I2C
    delay(10);
    }

void sendMessage(String message) {
    unsigned char i=0;
    while(message[i]) {
            sendData(message[i]); // * Show String to OLED
            i++;
        }
    }