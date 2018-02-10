#include "Arduino.h"
#include "hcsr04.h"
#include <LiquidCrystal.h>
#include <CMMC_LED.h>
#include <ArduinoSTL.h>
#include <encoder.h>
#include <Button.h>

bool Encoder::startPressed(){
	
	return this->startButton.pressed();
}

double Encoder::calculateWeightSpeed(int time){
	std::vector<Measure> rawMeasures = this->takeMeasures(time);
	std::vector<Measure> measures = this->filterInvalid(rawMeasures);
	Measure max = this->maxDistance(measures);
	Measure min = this->minDistance(measures);
	double speed = (max.distance - min.distance) / (max.time - min.time);
	return speed;
}

void Encoder::show1RMValue(double value){
	this->lcd.clear();
	this->lcd.setCursor(0,0);
	this->lcd.print("Tu 1RM es ");
	this->lcd.print(value);
	this->lcd.print(".");
}

std::vector<Measure> Encoder::takeMeasures(int seconds){
	std::vector<Measure> result(2,Measure(-1,-1));
	int t0 = micros();
	int i = 0;
	Serial.print("T0 = ");
	Serial.println(t0);
	int t1 = micros(); 
	while( t1 - t0 < seconds * 1000000 || i < 5000){
		Serial.print("i = ");
		Serial.println(i);
		Serial.print("T1 = ");
		Serial.println(t1);
		Serial.print("T1 - T0 = ");
		Serial.println(t1 - t0);
		result.at(i).time = millis()/1000.0; //t in seconds
		result.at(i).distance = this->sonic.distanceInMillimeters() / 1000.0; //d in metres
		t1 = micros();
		i++;
	}
	return result;
}

bool Encoder::upPressed(){
	this->upButton.pressed();
}

bool Encoder::downPressed(){
	this->downButton.pressed();
}

void Encoder::increaseWeight(){
	weight += 5;
	this->showWeight(weight);
}

void Encoder::reduceWeight(){
	if(weight > 0)
		weight -= 5;
	this->showWeight(weight);
}

int Encoder::getWeight(){
	return this->weight;
}

void Encoder::showWeight(int _weight){
	this->lcd.clear();
	this->lcd.print("Peso = ");
	this->lcd.print(_weight);
	
}

Measure Encoder::maxDistance(std::vector<Measure> measures){
	int max = 0;
	for(int i = 0;i < measures.size();i++){
		if(measures.at(i).distance > measures.at(max).distance){
			max = i;		
		}
	}
	return measures.at(max);
}

Measure Encoder::minDistance(std::vector<Measure> measures){
	int min = 0;
	for(int i = 0;i < measures.size();i++){
		if(measures.at(i).distance < measures.at(min).distance){
			min = i;		
		}
	}
	return measures.at(min);
}

std::vector<Measure> Encoder::filterInvalid(std::vector<Measure> measures){
	for(int i=0;i< measures.size();i++){
		Measure actual = measures.at(i);
		if(!actual.isValid()){
			measures.erase(measures.begin() + i);
		}
	}
}
