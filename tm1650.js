function i2c_start() {
	GPIO.write(scl, 1);
	Sys.usleep(10);
	GPIO.write(sda, 1);
	Sys.usleep(10);
	GPIO.write(sda, 0);
	Sys.usleep(10);
	GPIO.write(scl, 0);
	Sys.usleep(10);
}
function i2c_stop() {
	GPIO.write(scl, 0);
	Sys.usleep(10);
	GPIO.write(sda, 0);
	Sys.usleep(10);
	GPIO.write(scl, 1);
	Sys.usleep(10);
	GPIO.write(sda, 1);
	Sys.usleep(10);
}
function i2c_ack() {
	let v = GPIO.read(sda);
	while (v === 1) {
		Sys.usleep(10);
		print('wite the call back');
	}
	GPIO.set_mode(sda, GPIO.MODE_OUTPUT);
	GPIO.write(scl, 0);
	Sys.usleep(10);
	GPIO.write(sda, 1);
	Sys.usleep(10);
	GPIO.write(scl, 1);
	Sys.usleep(10);
	GPIO.write(scl, 0);
	Sys.usleep(10);
}
function i2c_write1() {		//write bite 1
	GPIO.set_mode(sda, GPIO.MODE_OUTPUT);
	GPIO.write(sda, 1);
	Sys.usleep(1);
	GPIO.write(scl, 0);
	Sys.usleep(1);
	GPIO.write(scl, 1);
	Sys.usleep(1);
	GPIO.write(scl, 0);
	Sys.usleep(1);
	GPIO.write(sda, 0);
	Sys.usleep(1);
	GPIO.set_mode(sda, GPIO.MODE_INPUT);
}
function i2c_write0() {		//write bite 0
	GPIO.set_mode(sda, GPIO.MODE_OUTPUT);
	GPIO.write(sda, 0);
	Sys.usleep(1);
	GPIO.write(scl, 0);
	Sys.usleep(1);
	GPIO.write(scl, 1);
	Sys.usleep(1);
	GPIO.write(scl, 0);
	Sys.usleep(1);
	GPIO.write(sda, 0);
	Sys.usleep(1);
	GPIO.set_mode(sda, GPIO.MODE_INPUT);
}
//2loops
function i2c_48() { //start setting
	i2c_write0();
	i2c_write1();
	i2c_write0();
	i2c_write0();
	i2c_write1();
	i2c_write0();
	i2c_write0();
	i2c_write0();
}
function i2c_49() { //brightness setting
	i2c_write0();
	i2c_write0();
	i2c_write0();
	i2c_write1();
	i2c_write0();
	i2c_write0();
	i2c_write0();
	i2c_write1();
}
function i2c_68() { //Dig 1
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write1();
	i2c_write0();
	i2c_write0();
	i2c_write0();
}
function i2c_6a() { //Dig 2
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write1();
	i2c_write0();
	i2c_write1();
	i2c_write0();
}
function i2c_6c() { //Dig 3
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write0();
}
function i2c_6e() { //Dig 4
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write0();
}
function num0() { //num 0	3f	bf
	i2c_write1();
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
}
function num1() { //num 1	06	86
	i2c_write1();
	i2c_write0();
	i2c_write0();
	i2c_write0();
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write0();
}
function num2() { //num 2	5b	db
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write1();
	i2c_write1();
}
function num3() { //num 3	4f	cf
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
}
function num4() { //num 4	66	e6
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write0();
}
function num5() { //num 5	6d ed
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write1();
}
function num6() { //num 6	7d	fd
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write1();
}
function num7() { //num 7	07 87
	i2c_write1();
	i2c_write0();
	i2c_write0();
	i2c_write0();
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write1();
}
function num8() { //num 8	7f	ff
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
}
function num9() { //num 9	6f	df
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write0();
	i2c_write1();
	i2c_write1();
	i2c_write1();
	i2c_write1();
}
//3loops
function i2c_set(dig,numer) {
	i2c_start(); //start
	i2c_48(); //commend1
	i2c_ack();
	i2c_49(); //commend2
	i2c_ack();
	i2c_stop();
	i2c_start();
	if(dig === 1){		 //address
		i2c_68()
	}
	else if (dig === 2){
		i2c_6a()
	}
	else if (dig === 3){
		i2c_6c()
	}
	else if (dig === 4){
		i2c_6e()
	}
	i2c_ack();
	if(numer === 0){			 //date
		num0();
	}
	else if (numer === 1){
		num1();
	}
	else if (numer === 2){
		num2();
	}
	else if (numer === 3){
		num3();
	}
	else if (numer === 4){
		num4();
	}
	else if (numer === 5){
		num5();
	}
	else if (numer === 6){
		num6();
	}
	else if (numer === 7){
		num7();
	}
	else if (numer === 8){
		num8();
	}
	else if (numer === 9){
		num9();
	}
	i2c_ack();
	i2c_stop();
	Sys.usleep(1); //stop
}
