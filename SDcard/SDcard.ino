/*
Arduino Sketch to read and display contents of a SD card.
©AgamjeetSingh

*Please set the baud rate to 57600 in Serial Monitor for effective communication

Pins for attaching SD card shield to Arduino Uno
  1. MOSI - pin 11 on Arduino Uno
  2. MISO - pin 12 on Arduino Uno
  3. SCK - pin 13 on Arduino Uno
  4. CS - Chip Select according to preference (Default 7)
 */
// including Serial Communication (SPI) and SD library:
#include <SPI.h>
#include <SD.h>

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = 7;
float volsz;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }


  Serial.print("A Project by AgamjeetSingh(ajs811) \n\nInitializing SD card...\n");

  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Please try again:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    Serial.println("\nReading...");
  }

  // print the type of card
  Serial.print("\nCard type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }


  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       
  volumesize *= 512;                            // SD card blocks are always 512 bytes
  volsz = volumesize/(1024*1024);
  Serial.print("Volume size is ") ;
  Serial.print(volumesize); 
  Serial.print(" Megabytes");

 
  Serial.println("\nFiles found on the card (name, date and size in MegaBytes): \n");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
}


void loop(void) {

}
