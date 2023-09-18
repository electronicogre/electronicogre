// Shows the content of a Mifare Classic tag formatted as an NDEF tag
// This example requires #define NDEF_USE_SERIAL to be uncommented in Ndef.h


#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif
RH_ASK rf_driver(2000, PA4, PA3);
#include <MFRC522.h>
#include <NfcAdapter.h>
#include <LiquidCrystal.h>
int n;

const int rs = PB12, en = PB13, d4 = PB14, d5 = PB15, d6 = PA8, d7 = PA9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Initialize the LCD
#define SS_PIN PA4
#define RST_PIN  7
#define msg "Authorized"
int j=-2;
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

NfcAdapter nfc = NfcAdapter(&mfrc522);

void setup(void) {
    #ifdef RH_HAVE_SERIAL
    Serial.begin(9600);    // Debugging only
#endif
    if (!rf_driver.init())
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
  ;
#endif
    Serial.begin(9600);
    nfc.begin();
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("tag Reader");
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522
    
}

void loop(void) {
   
     if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  lcd.clear();
  lcd.print("UID tag :");
  delay(3000);
  String  content= "";
  byte letter;
  lcd.setCursor(0,1);
  for (byte i = 0; i < mfrc522.uid.size; i++)  
  {
    lcd.setCursor(0, 1);
     lcd.print(mfrc522.uid.uidByte[i] < 0x10  ? " 0" : " ");
     lcd.print(mfrc522.uid.uidByte[i], HEX);
     lcd.setCursor(j+2, 1);
     delay(2000);
     content.concat(String(mfrc522.uid.uidByte[i]  < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i],  HEX));
  }
  
 lcd.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "31 DA 6F 23") //Plz change  to your cards UID
  {
   lcd.setCursor(0,1);
    lcd.print("Authorized");
    delay(3000);
    lcd.clear();
    while(1){
  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();
  if(n==0)
  {
  
  lcd.print("sent");
  delay(1000);
  n=1;
  lcd.setCursor(0,0);
  lcd.clear();
  }
  else
  {
    lcd.print("sent");
    delay(1000);
    n=0;
    lcd.setCursor(0,1);
    lcd.clear();
  }
  
    }
   
    
  }
 
 else   {
  lcd.setCursor(0, 1);
    lcd.print(" Access denied");
    delay(3000);
    lcd.clear();
      
      }
} 
