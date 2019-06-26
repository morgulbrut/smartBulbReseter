# smartBulbReseter

## setup

in Arduino make a new tab, name it `arduino_secrets.h` containing the following

```C
#define SECRET_PINNUMBER     "1234"
```

with the correct PIN of your used SIM.


## code
it's basically just copy pasted from different library examples, mainly Adafuits Neopixel library and the MKRGSM SMS recieve example. But that's how Arduino coding works these days, right?