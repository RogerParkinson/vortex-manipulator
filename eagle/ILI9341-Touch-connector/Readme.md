ILI9341 connector for 14 pads + 4 pads for touch, broken out to 14 connector pins using a touch controller.

It is a clone of the PCB for [this screen](https://www.aliexpress.com/item/J34-F85-Free-Shipping-240x320-2-8-SPI-TFT-LCD-Touch-Panel-Serial-Port-Module-with/32599693865.html)
but without the SD card and the PCB is much smaller making it useful when you have very little room to mount it. The screen itself is available separately [here](https://www.aliexpress.com/item/J34-Free-Shipping-240x320-2-8-SPI-Serial-ILI9341-TFT-Color-LCD-Screen-Display-with-Touch/32435870215.html)

To build this you need a couple of resistors and ceramic capacitors as well as an [RT9169](https://www.aliexpress.com/item/Free-shipping-10pcs-lot-RT9169-30GV-RT9169-BK-SOT-23-new-original/32510597351.html)
and a [XPT2046 touch controller](https://www.aliexpress.com/item/Free-shipping-20pcs-lot-XPT2046-2046-TSSOP16-new-original/32639677099.html).

Aliexpress links come and go so if the links don't work then you can search for RT9169, and also for an ILI9341 screen. You want the screen _without_ the PCB because the already mounted on a PCB are too big (though they are easier to solder). Also make sure you order one with a touch capability. There are lots around that just display but are not touch screens. You also need the XPT2046 touch controller.

I used solder paste etc for the smd parts but I hand soldered the screen. It is fiddly work but I don't think it is a good idea to put the screen through an oven or hot plate.

Be careful when soldering the screen to the board. Those connections are very fine and, when soldered, rather fragile. Make sure you stick the board and screen together somehow, such as double sided tape, to prevent strain on the connection. It is important to get the screen connection around the right way. Check carefully before you solder.

For details on connecting the resulting board to your processor see [PJRC's instructions](https://www.pjrc.com/store/display_ili9341_touch.html).

<a href="https://oshpark.com/shared_projects/iFrrmh3h"><img src="https://oshpark.com/assets/badge-5b7ec47045b78aef6eb9d83b3bac6b1920de805e9a0c227658eac6e19a045b9c.png" alt="Order from OSH Park"></img></a>