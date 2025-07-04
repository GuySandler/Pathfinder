// wackamole
const int Buttons[] = {3, 1, 4, 2}; // right, top, bottom, left

const int Leds[] = {29, 28, 27, 26}; // right to left

double OnTime = .6;
int score = 0;
int order[50];

void setup() {
	for (int i = 0; i < 4; i++) {
		pinMode(Buttons[i], INPUT_PULLUP);
		pinMode(Leds[i], OUTPUT);
		digitalWrite(Leds[i], LOW);
	}

	randomSeed(analogRead(A0)); // internet claims this will help randomness, this or millis()
	resetGame();
}

void loop() {
	startAnimation();
	gameLoop();
}

void blink(int Led, double OnTime) {
	digitalWrite(Led, HIGH);
	delay(OnTime * 1000);
	digitalWrite(Led, LOW);
}

void resetGame() {
	score = 0;
	for (int i = 0; i < 50; i++) {
		order[i] = random(0, 4);
	}
}

int updateTimer(int timer) {
	return millis() - timer;
}

bool isTimeUp(int timer) {
	return updateTimer(timer) >= 1000*120;
}

void startAnimation() {
	for (int i = 0; i < 4; i++) {
		digitalWrite(Leds[i], HIGH);
		delay(750);
	}
	for (int i = 0; i < 4; i++) {
		digitalWrite(Leds[i], LOW);
	}
	delay(500);
}

void gameLoop() {
	int startTime = millis();
	for (int i = 0; i < 50; i++) {
		if (isTimeUp(startTime)) {
			break;
		}

		digitalWrite(Leds[order[i]], HIGH);
		unsigned long appearTime = millis();
		bool hit = false;
		while (millis() - appearTime < OnTime * 1000) {
			if (digitalRead(Buttons[moleIndex]) == LOW) {
				delay(50);
				while (digitalRead(Buttons[moleIndex]) == LOW) {
					delay(10);
				}
				score++;
				hit = true;
				break;
			}
		}
		digitalWrite(Leds[order[i]], LOW);
		delay(random(300, 700));
	}
}

void showScore() {
	for (int i = 0; i < z; i++) {
		for (int z = 0; z < 4; z++) {
			blink(Leds[z], OnTime * 1000);
		}
	}
	if (score >= 12) {
		digitalWrite(Leds[3], HIGH);
		delay(400);
	}
	if (score >= 25) {
		digitalWrite(Leds[2], HIGH);
		delay(400);
	}
	if (score >= 37) {
		digitalWrite(Leds[1], HIGH);
		delay(400);
	}
	if (score >= 50) {
		digitalWrite(Leds[0], HIGH);
		delay(400);
	}
}

void winAnimation() {
	for (int i = 0; i < 4; i++) {
		digitalWrite(Leds[2], LOW);
		digitalWrite(Leds[0], LOW);
		digitalWrite(Leds[3], HIGH);
		digitalWrite(Leds[1], HIGH);
		delay(300);
		digitalWrite(Leds[3], LOW);
		digitalWrite(Leds[1], LOW);
		digitalWrite(Leds[2], HIGH);
		digitalWrite(Leds[0], HIGH);
		delay(300);
	}
	for (int i = 0; i < 4; i++) {
		digitalWrite(Leds[i], HIGH);
	}
	delay(500);
	for (int i = 0; i < 4; i++) {
		digitalWrite(Leds[i], LOW);
	}
}