    Wire_beginTransmission(0x68);
    Wire_write(0x00);
    int valll = 55;                   //ss
    int dd = (valll/10*16) + (valll%10);
    Wire_write(dd);
    Wire_endTransmission();
    Wire_beginTransmission(0x68);
    Wire_write(0x01);
    int vallll = 04;                   //mm
    int ddd = (vallll/10*16) + (vallll%10);
    Wire_write(ddd);
    Wire_endTransmission();
    Wire_beginTransmission(0x68);
    Wire_write(0x02);
    int vall = 01;                   //hh
    int d = (vall/10*16) + (vall%10);
    Wire_write(d);
    Wire_endTransmission();
