#include "deneyap.h"

String MORSE_CODE[] = {
  ".-",   // A
  "-...", // B
  "-.-.", // C
  "-..",  // D
  ".",    // E
  "..-.", // F
  "--.",  // G
  "....", // H
  "..",   // I
  ".---", // J
  "-.-",  // K
  ".-..", // L
  "--",   // M
  "-.",   // N
  "---",  // O
  ".--.", // P
  "--.-", // Q
  ".-.",  // R
  "...",  // S
  "-",    // T
  "..-",  // U
  "...-", // V
  ".--",  // W
  "-..-", // X
  "-.--", // Y
  "--.."  // Z
};

void setup() {
  Serial.begin(9600); // Seri bağlantı başlatılır
  pinMode(RGBLED, OUTPUT); // RGB LED çıkış olarak ayarlanır

}

void sendMorseCode(String message) {
  for (int i = 0; i < message.length(); i++) {
    char character = message.charAt(i);
    if (character == ' ') {
      delay(1000); // Boşluk için bekletme
    } else {
      int morseIndex = character - 'A'; // Karakterin morse kodu dizinini bul
      if (morseIndex >= 0 && morseIndex < 26) {
        String morseCode = MORSE_CODE[morseIndex]; // Karakterin morse kodunu al
        for (int j = 0; j < morseCode.length(); j++) {
          if (morseCode.charAt(j) == '.') {
           neopixelWrite(RGBLED, 0, 0, 64);  // Nokta için LED'i yak
            delay(100); // Nokta süresi
            neopixelWrite(RGBLED, 0, 0, 0); 
            delay(500);
          } else if (morseCode.charAt(j) == '-') {
             neopixelWrite(RGBLED, 0, 0, 64); // Çizgi için LED'i yak
            delay(300); // Çizgi süresi
          }
           neopixelWrite(RGBLED, 0, 0, 0);  // LED'i kapat
          delay(100); // Harf içindeki boşluk süresi
        }
        delay(300); // Harfler arası boşluk süresi
      }
    }
  }
}

void loop() {
  if (Serial.available() > 0) { // Eğer seri monitörden mesaj varsa
  String  message = Serial.readStringUntil('\n'); // Mesajı oku
    sendMorseCode(message); // Morse koduna dönüştürülen mesajı RGB LED'e gönder
  }
}
