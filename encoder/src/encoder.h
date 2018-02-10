#ifndef encoder_h
#define encoder_h

#include "Arduino.h"
#include "hcsr04.h"
#include <LiquidCrystal.h>
#include <CMMC_LED.h>
#include <ArduinoSTL.h>
#include <Button.h>

struct Measure{
	public:
		double time;
		double distance;
		bool isValid(){
			return distance > 0;		
		};
		Measure(double t,double d){
			time = t;
			distance = d;
		}
};

class Encoder
{
  public:
	Encoder(LiquidCrystal lcd,
		HCSR04 sonic,
		Button startB,
		Button upB,
		Button downB,
		CMMC_LED led) :startButton(startB),upButton(upB),downButton(downB),sonic(sonic),lcd(lcd),led(led) {
		Serial.begin(9600);
		startB.begin();
		upB.begin();
		downB.begin();
		Serial.println("Encoder started");
	};

	bool startPressed();
	double calculateWeightSpeed(int time);
	void show1RMValue(double value);
	bool upPressed();
	bool downPressed();
	void increaseWeight();
	void reduceWeight();
	int getWeight();
  private:
	std::vector<Measure> filterInvalid(std::vector<Measure>);
	void showWeight(int);
	std::vector<Measure> takeMeasures(int);
	Measure maxDistance(std::vector<Measure>);
	Measure minDistance(std::vector<Measure>);

	Button startButton;
	Button upButton;
	Button downButton;
	
	HCSR04 sonic;
	LiquidCrystal lcd;
	CMMC_LED led;

	int weight;
};

#endif
