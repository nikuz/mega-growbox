

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);     // start serial1 communication at 9600bps
  Serial1.flush();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial1.write("Test message\n"); //Send the Quotient or "how many times" value
  delay(2000);
}
