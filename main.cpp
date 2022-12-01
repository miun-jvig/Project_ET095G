#include "mbed.h"
#include "RGBled.h"
#include "LM75B.h"
#include "C12832.h"

// DECLARATIONS
LocalFileSystem local("local"); // define the local file system
InterruptIn center(p14);
RGBled LED(p23, p24, p25);
LM75B sensor(p28, p27);
C12832 lcd(p5, p7, p6, p8, p11);
Timer writeFileTimer;
char buffer[32];

/*
    getTime() is supposed to return a string with the current date and time. Unfortunately
    I didn't have time to finish the function properly.
*/
char* getTime(){    
    time_t seconds = time(NULL);
    strftime(buffer, 64, "%Y/%m/%d %H:%M:%S: ", localtime(&seconds));
    return buffer;   
}

/*
    writeToFile() will open a stream and write the current temperature and the to the file.
    At the end of the function the stream will be closed.
*/
void writeToFile(){    
    FILE* file_ptr = fopen("/local/datafile.txt", "a"); // open stream
    fprintf(file_ptr, "%s", getTime());
    fprintf(file_ptr, "%.3f degrees C.\n\r", sensor.read()); // write the current temperature from sensor to file_ptr
    printf("Current temperature is %1.3f.\n\r", sensor.read());
    printf("Current time is: %s", getTime());
    fclose(file_ptr); // close the stream as writing is done
}

/*
    writeCurrentTemp() will print the current temperature to the LCD-screen.
*/
void writeCurrentTemp(){
    lcd.locate(0, 3);
    lcd.printf("Current temperature:");
    lcd.locate(0, 15);
    lcd.printf("%1.1f degrees C.", sensor.read());
}

int main() {
    set_time(1640798290 + 3600); // set to Unix-time + Stockholm offset (1 hour)
    writeFileTimer.start();
    lcd.cls();
    /*
        writeToFile() will open a filestream and write the current time and temperature to logfile 
        DATAFILE.TXT.
    */
    center.rise(&writeToFile);
    
    while(1){  
        LED.setColourRange(sensor.read(), 10, 30);     
        LED.write(LED.getColour().red, LED.getColour().green, LED.getColour().blue);
        writeCurrentTemp(); // write current temperature to LCD-screen
        // write to log-file every 10th minute
        if(writeFileTimer.read() > 600){
            writeToFile();
            writeFileTimer.reset();
        }
    }
}
