load('api_config.js');
load('api_events.js');
load('api_gpio.js');
load('api_mqtt.js');
load('api_i2c.js');
load('api_sys.js');
load('api_timer.js');

Timer.set(1000 /* 1 sec */, Timer.REPEAT, function() {
  let bus = I2C.get();
  I2C.writeRegB(bus,36,0,17);
   I2C.writeRegB(bus,52,0,255);
   I2C.write(bus, 36, "17", 1, 0);
   I2C.write(bus, 52, "66", 1, true);
}, null);
