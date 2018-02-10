#include <powerexp.h>

double PowerExp::calculate1RM(double speed,int weight){
	return (weight*100)/(((11,4196*(speed*speed))-(81,904*speed))+114,03);
}
