// Memory Game

// other idea: making a just 4 buttons, score
const int Buttons[] = {3, 1, 4, 2}; // right, top, bottom, left

const int Leds[] = {29, 28, 27, 26}; // right to left

double OnTime = 1;
double OffTime = 1;
int score = 0;
int order[50];
int currentStep = 1;

void setup() {
	for (int i = 0; i < 4; i++) {
		pinMode(Buttons[i], INPUT_PULLUP);
		pinMode(Leds[i], OUTPUT);
		digitalWrite(Leds[i], LOW);
	}

	randomSeed(analogRead(A0)); // internet claims this will help randomness
	resetGame();
}

void loop() {
	startAnimation();
	displayPattern(order, currentStep);
	if (checkInput()) {
		score++;
		currentStep++;
		if (currentStep >= 50) {
			winAnimation();
			currentStep = 50; // cap at 50
		}
	}
	else {
		loseAnimation();
		resetGame();
	}
	delay(2000);
}

void blink(int Led, double OnTime, double OffTime) {
	digitalWrite(Led, HIGH);
	delay(OnTime * 1000);
	digitalWrite(Led, LOW);
	delay(OffTime * 1000);
}

void displayPattern(int order[], int currentStep) {
	for (int i = 0; i < currentStep; i++) {
		blink(Leds[order[i]], OnTime, OffTime);
		delay(500);
	}
}

bool checkInput() {
	for (int i = 0; i < currentStep; i++) {
		int pressedButton = awaitButton();
		if (pressedButton != order[i]) {
			return false;
		}
		blink(Leds[pressedButton], OnTime, OffTime);
	}
	return true;
}

int awaitButton() {
	while (true) {
		for (int i = 0; i < 4; i++) {
			if (digitalRead(Buttons[i]) == LOW) {
				delay(50);
				while (digitalRead(Buttons[i]) == LOW) {
					delay(10);
				}
				return i;
			}
		}
		delay(50);
	}
}

void resetGame() {
	score = 0;
	currentStep = 1;
	for (int i = 0; i < 50; i++) {
		order[i] = random(0, 4);
	}
}

void startAnimation() {
	for (int z = 0; z < 3; z++) {
		for (int i = 0; i < 4; i++) {
			digitalWrite(Leds[i], HIGH);
		}
		delay(OnTime * 600);
		for (int i = 0; i < 4; i++) {
			digitalWrite(Leds[i], LOW);
		}
		delay(OffTime * 600);
	}
	delay(1000);
}

void winAnimation() {
	for (int i = 0; i < 4; i++) {
		digitalWrite(Leds[i], HIGH);
		delay(500);
	}
	delay(600);
	for (int i = 0; i < 4; i++) {
		digitalWrite(Leds[i], LOW);
		delay(500);
	}
	delay(600);
	for (int i = 0; i < 4; i++) {
		digitalWrite(Leds[i], HIGH);
	}
	delay(600);
	for (int i = 0; i < 4; i++) {
		digitalWrite(Leds[i], LOW);
	}
	delay(600);
}

void loseAnimation() {
	for (int i = 0; i < 2; i++) {
		digitalWrite(Leds[i], HIGH);
	}
	delay(1500);
	for (int i = 0; i < 2; i++) {
		digitalWrite(Leds[i], LOW);
	}
}