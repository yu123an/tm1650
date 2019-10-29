load('api_gpio.js');
load('api_dataview.js');
load('api_sys.js');
load('api_timer.js');
load('api_math.js');
let scl = 5;
let sda = 4;
GPIO.set_mode(scl, GPIO.MODE_OUTPUT);
GPIO.set_mode(sda, GPIO.MODE_OUTPUT);

Timer.set(20000 , Timer.REPEAT, function() {
   function seting(a,b) {
	i2c_set(a,b);
 }
  let now = Timer.now();
  let s = Timer.fmt("%R", now);
  let hour = JSON.parse(s.slice(0,2));
  let n3 = s.slice(3,4);
  let n4 = s.slice(4,5);
  let nn3 = JSON.parse(n3);
  let nn4 = JSON.parse(n4);
  seting(4,nn4);
  seting(3,nn3);
  let realhour = (hour + 8)%24;
  if (realhour < 10){
    let pp = 0;
    let qq = realhour;
    seting(2,qq);
    seting(1,pp); 
  }
  else{
    let pp = realhour%10;
    let qq = Math.floor(realhour/10);
    seting(2,pp);
    seting(1,qq);
   }
 print('i am so good------------------------------');
}, null);
