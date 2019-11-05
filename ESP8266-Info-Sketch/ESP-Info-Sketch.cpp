// BOF preprocessor bug prevent - insert me on top of your arduino-code
#if 1
__asm volatile ("nop");
#endif

/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/

#include "Arduino.h"

#include "Esp.h"
#include "ESP8266WiFi.h"
#include "FS.h"

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Wifi-Setup done");

  pinMode(LED_BUILTIN, OUTPUT);

  //ADC_MODE(ADC_VCC);

  Serial.println("\r\nCPU Information");
  Serial.print("Chip-ID          : "); printHex(ESP.getChipId(), 8, true);
  Serial.print("SDK-Version      : "); Serial.println(ESP.getCoreVersion());
  Serial.print("Core-Clock  (MHz): "); Serial.println(ESP.getCpuFreqMHz());

  uint32_t before, after;
  before = ESP.getCycleCount();
  delayMicroseconds(1000);
  after = ESP.getCycleCount();
  Serial.print("Cycles/ms delay  : "); Serial.println(abs(after - before));

  float a = 0.0f;
  float b = PI;
  before = ESP.getCycleCount();
  for (int cnt=0; cnt<99; cnt++) {
    a = sqrt(b);
    b = a * (float)cnt;
  }
  after = ESP.getCycleCount();
  Serial.print("Cycles (100SQRT*): "); Serial.println(abs(after - before));

  Serial.println("\r\nMEMORY Information");
  Serial.print("Flash-ID         : "); printHex(ESP.getFlashChipId(), 8, true);
  Serial.print("Flash-Size (real): "); Serial.println(ESP.getFlashChipRealSize());
  Serial.print("Flash-Size  (SDK): "); Serial.println(ESP.getFlashChipSize());
  Serial.print("Flash-Speed (MHz): "); Serial.println(ESP.getFlashChipSpeed() / 1000000);
  Serial.print("Sketch-Size      : "); Serial.println(ESP.getSketchSize());
  Serial.print("Sketch-Free      : "); Serial.println(ESP.getFreeSketchSpace());
  Serial.print("Sketch-MD5       : "); Serial.println(ESP.getSketchMD5());
  Serial.print("Free Heap Space  : "); Serial.println(ESP.getFreeHeap());

  //http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html#uploading-files-to-file-system
  //Activate SPI file system
  SPIFFS.begin();
  Serial.println("\r\nFile system Information");
  FSInfo fs_info;
  SPIFFS.info(fs_info);
  Serial.print("Total Size       : "); Serial.println(fs_info.totalBytes);
  Serial.print("Used Bytes       : "); Serial.println(fs_info.usedBytes);
  Serial.print("Used Percent     : "); Serial.println((float)(fs_info.usedBytes * 100 / fs_info.totalBytes));
  Serial.print("Block Size       : "); Serial.println(fs_info.blockSize);
  Serial.print("Page Size        : "); Serial.println(fs_info.pageSize);
  Serial.print("MaxOpenFile      : "); Serial.println(fs_info.maxOpenFiles);
  Serial.print("MaxPathLength    : "); Serial.println(fs_info.maxPathLength);

  Serial.println("\r\nFile system Content");
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    Serial.print(dir.fileName() + "   Size:");
    File f = dir.openFile("r");
    Serial.println(f.size());
    f.close();
  }

  Serial.println("\r\nPIN Information");
  Serial.print("LED(BI): "); Serial.println(LED_BUILTIN);
#if defined(TX)
  Serial.print("PIN TX : "); Serial.println(digitalRead(TX));
#endif
#if defined(RX)
  Serial.print("PIN RX : "); Serial.println(digitalRead(RX));
#endif
  Serial.print("ADC0   : "); Serial.println(analogRead(A0));
#if defined(A1)
  Serial.print("ADC1   : "); Serial.println(analogRead(A1));
#endif
#if defined(A2)
  Serial.print("ADC2   : "); Serial.println(analogRead(A2));
#endif
#if defined(A3)
  Serial.print("ADC3   : "); Serial.println(analogRead(A3));
#endif
#if defined(A4)
  Serial.print("ADC4   : "); Serial.println(analogRead(A4));
#endif
#if defined(A5)
  Serial.print("ADC5   : "); Serial.println(analogRead(A5));
#endif

  Serial.print("PIN D0 : "); Serial.println(digitalRead(D0));
  Serial.print("PIN D1 : "); Serial.println(digitalRead(D1));
  Serial.print("PIN D2 : "); Serial.println(digitalRead(D2));
  Serial.print("PIN D3 : "); Serial.println(digitalRead(D3));
  Serial.print("PIN D4 : "); Serial.println(digitalRead(D4));
  Serial.print("PIN D5 : "); Serial.println(digitalRead(D5));
  Serial.print("PIN D6 : "); Serial.println(digitalRead(D6));
  Serial.print("PIN D7 : "); Serial.println(digitalRead(D7));
  Serial.print("PIN D8 : "); Serial.println(digitalRead(D8));
#if defined(D9)
  Serial.print("PIN D9 : "); Serial.println(digitalRead(D9));
#endif
#if defined(D10)
  Serial.print("PIN D10: "); Serial.println(digitalRead(D10));
#endif
#if defined(D11)
  Serial.print("PIN D11: "); Serial.println(digitalRead(D11));
#endif
#if defined(D12)
  Serial.print("PIN D12: "); Serial.println(digitalRead(D12));
#endif
#if defined(D13)
  Serial.print("PIN D13: "); Serial.println(digitalRead(D13));
#endif
#if defined(D14)
  Serial.print("PIN D14: "); Serial.println(digitalRead(D14));
#endif
#if defined(D15)
  Serial.print("PIN D15: "); Serial.println(digitalRead(D15));
#endif
}

void loop() {
  Serial.println("\r\nscan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.print((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "  " : "* ");
      Serial.println(WiFi.SSID(i));
      delay(10);
    }
  }

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  // Wait a bit before scanning again
  delay(5000);
}

void printHex(int num, int precision, bool NewLine) {
  char tmp[16];
  char format[128];
  sprintf(format, "0x%%.%dX", precision);
  sprintf(tmp, format, num);
  if (NewLine) {
    Serial.println(tmp);
  } else {
    Serial.print(tmp);
  }
}
