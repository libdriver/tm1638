[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1638

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1638/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

TM1638 ist ein IC zur LED-Antriebssteuerung (Leuchtdiodenanzeige) und mit einer Tastatur-Scan-Schnittstelle ausgestattet. Es integriert eine MCU-Digitalschnittstelle, einen Datenspeicher, einen LED-Antrieb und eine Tastatur-Scan-Schaltung. Dieses Produkt zeichnet sich durch zuverlässige Qualität, stabile Leistung und hohe Störfestigkeit aus. Es wird hauptsächlich für elektrische Haushaltsgeräte (intelligente Warmwasserbereiter, Mikrowellenherde, Waschmaschinen, Klimaanlagen, Elektroherde), Set-Top-Boxen, elektronische Waagen, intelligente Messgeräte und andere digitale Röhren- oder LED-Anzeigegeräte verwendet.

LibDriver TM1638 ist der von LibDriver gestartete Vollfunktionstreiber von TM1638. LibDriver TM1638 bietet digitale Röhrenanzeige, Tastatur-Scanning und andere Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver TM1638-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver TM1638 SPI.

/test enthält den Testcode des LibDriver TM1638-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver TM1638-Beispielcode.

/doc enthält das LibDriver TM1638-Offlinedokument.

/Datenblatt enthält TM1638-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_tm1638_basic.h"

uint8_t res;
uint8_t segk[4];
uint16_t number[] = {TM1638_NUMBER_0, TM1638_NUMBER_1, TM1638_NUMBER_2,
                     TM1638_NUMBER_3, TM1638_NUMBER_4, TM1638_NUMBER_5,
                     TM1638_NUMBER_6, TM1638_NUMBER_7, TM1638_NUMBER_8, TM1638_NUMBER_9};

/* init */
res = tm1638_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* write */
res = tm1638_basic_write(0x00, number, 8);
if (res != 0)
{
    (void)tm1638_basic_deinit();
    
    return 1;
}

...
    
/* read */
res = tm1638_basic_read(segk);
if (res != 0)
{
    (void)tm1638_basic_deinit();
    
    return 1;
}

/* output */
tm1638_interface_debug_print("tm1638: segk[0]: 0x%02X.\n", segk[0]);
tm1638_interface_debug_print("tm1638: segk[1]: 0x%02X.\n", segk[1]);
tm1638_interface_debug_print("tm1638: segk[2]: 0x%02X.\n", segk[2]);
tm1638_interface_debug_print("tm1638: segk[3]: 0x%02X.\n", segk[3]);

...
    
/* on */
res = tm1638_basic_display_on();
if (res != 0)
{
    (void)tm1638_basic_deinit();
    
    return 1;
}

...
    
/* off */
res = tm1638_basic_display_off();
if (res != 0)
{
    (void)tm1638_basic_deinit();
    
    return 1;
}

...
    
/* deinit */
res = tm1638_basic_deinit();
if (res != 0)
{
    return 1;
}

return 0;
```
### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/tm1638/index.html](https://www.libdriver.com/docs/tm1638/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.