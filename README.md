# Arduino Toy Server

Demonstrate sending a api packet to the Arduino from Android [Toy Controller](https://github.com/birdming22/ToyController).

## API Format
Any Byte except API ID should not be larger than 0x7F.

### API Frame Figure

    ----------------------
    | Id | Len | Payload |
    ----------------------
    
### API ID 

API ID length is one byte.

    0x81: RGB LED Function
    
### Payload Length

Payload length is one byte and max value is 127.
    
### Payload

Payload length is N bytes. N is payload length.

## Reference


[DataReceiver](https://github.com/markfickett/DataReceiver)