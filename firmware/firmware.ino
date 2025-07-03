// Memory Game
int Buttons[] = {D1, D2, D3, D4}; // right, top, bottom, left}

int Leds[] = {D26, D27, D28, D29}; // left to right

double OnTime = 1;
double OffTime = 1;
int score = 0;
int order[50];
int currentStep = 1;

void setup() {
	// pinMode(Button1, INPUT);
	// pinMode(Button2, INPUT);
	// pinMode(Button3, INPUT);
	// pinMode(Button4, INPUT);
	// pinMode(Led1, OUTPUT);
	// pinMode(Led2, OUTPUT);
	// pinMode(Led3, OUTPUT);
	// pinMode(Led4, OUTPUT);
	for (int i = 0; i < 4; i++) {
		pinMode(Buttons[i], INPUT);
		pinMode(Leds[i], OUTPUT);
		digitalWrite(Leds[i], LOW)
	}

	// turn all leds off
	digitalWrite(Led1, LOW);
	digitalWrite(Led2, LOW);
	digitalWrite(Led3, LOW);
	digitalWrite(Led4, LOW);

	for (int i = 0; i < 50; i++) {
		order[i] = random(1, 5);
	}
}

void loop() {
	displayPattern(order, currentStep);
	checkInput(order, currentStep, score);
	if (currentStep >= 50) {
		// TODO: win animation
	}
}

void blink(int Led, double OnTime, double OffTime) {
	digitalWrite(Led, HIGH);
	delay(OnTime * 1000);
	digitalWrite(Led, LOW);
	delay(OffTime * 1000);
}

void displayPattern(int order[], int currentStep) {
	for (int i = 0; i < currentStep; i++) {
		switch (order[i]) {
			case 1:
				blink(Led1, OnTime, OffTime);
				break;
			case 2:
				blink(Led2, OnTime, OffTime);
				break;
			case 3:
				blink(Led3, OnTime, OffTime);
				break;
			case 4:
				blink(Led4, OnTime, OffTime);
				break;
		}
		delay(500);
	}
}

void checkInput(int order[], int &currentStep, int &score) {
	for (int i = 0; i < currentStep; i++) {
		bool buttonpressed = false;
		// can probably optimize with an array
		int Button1State = digitalRead(Button1);
		int Button2State = digitalRead(Button2);
		int Button3State = digitalRead(Button3);
		int Button4State = digitalRead(Button4);
		switch (order[i]) {
			case 1:
				while (!buttonpressed) {
					Button1State = digitalRead(Button1);
					Button2State = digitalRead(Button2);
					Button3State = digitalRead(Button3);
					Button4State = digitalRead(Button4);
					if (Button1State == LOW && Button2State == LOW && Button3State == LOW && Button4State == LOW) {
						continue;
					} else if (Button1State == HIGH) {
						buttonpressed = true;
						score++;
						currentStep++;
						blink(Led1, OnTime, OffTime);
					} else {
						buttonpressed = true;
						// TODO: lose animation
						score = 0;
						currentStep = 1;
					}
					delay(50);
				}
				break;
			case 2:
				while (!buttonpressed) {
					Button1State = digitalRead(Button1);
					Button2State = digitalRead(Button2);
					Button3State = digitalRead(Button3);
					Button4State = digitalRead(Button4);
					if (Button1State == LOW && Button2State == LOW && Button3State == LOW && Button4State == LOW) {
						continue;
					} else if (Button2State == HIGH) {
						buttonpressed = true;
						score++;
						currentStep++;
						blink(Led2, OnTime, OffTime);
					} else {
						buttonpressed = true;
						score = 0;
						currentStep = 1;
					}
					delay(50);
				}
				break;
			case 3:
				while (!buttonpressed) {
					Button1State = digitalRead(Button1);
					Button2State = digitalRead(Button2);
					Button3State = digitalRead(Button3);
					Button4State = digitalRead(Button4);
					if (Button1State == LOW && Button2State == LOW && Button3State == LOW && Button4State == LOW) {
						continue;
					} else if (Button3State == HIGH) {
						buttonpressed = true;
						score++;
						currentStep++;
						blink(Led3, OnTime, OffTime);
					} else {
						buttonpressed = true;
						score = 0;
						currentStep = 1;
					}
					delay(50);
				}
				break;
			case 4:
				while (!buttonpressed) {
					Button1State = digitalRead(Button1);
					Button2State = digitalRead(Button2);
					Button3State = digitalRead(Button3);
					Button4State = digitalRead(Button4);
					if (Button1State == LOW && Button2State == LOW && Button3State == LOW && Button4State == LOW) {
						continue;
					} else if (Button4State == HIGH) {
						buttonpressed = true;
						score++;
						currentStep++;
						blink(Led4, OnTime, OffTime);
					} else {
						buttonpressed = true;
						score = 0;
						currentStep = 1;
					}
					delay(50);
				}
				break;
		}
	}
}