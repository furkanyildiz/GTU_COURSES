#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14
double reflection(double angle);

int kickDisc(double wallWidth, double wallHeight, double ballCenterX, double kickAngle, double ballRadius, double goalWidth);

double randNumber(double angle);

int isitGoal(int Merkez, double wallWidth, double wallHeight, double ballCenterX, double
kickAngle, double ballRadius, double goalWidth);


int main(){

	printf("it returns: %d\n",kickDisc(10, 26, 2, 45, 1, 2));
	return 0;
}
double randNumber(double angle){
	srand(angle);
	return rand();
}


double reflection(double angle){
	double radius;
	double tanjant;
	double RandomAngle;
	if(angle>175)
		angle=175;
	else if(angle<5)
		angle=5;
	RandomAngle=angle+(int)randNumber(angle)%11-5;
	radius=RandomAngle*PI/180.0;
	tanjant=tan(radius);
	return tanjant;


}

int kickDisc(double wallWidth, double wallHeight, double ballCenterX, double
kickAngle, double ballRadius, double goalWidth){

 	int Merkez;
	Merkez=ballCenterX;

return isitGoal(Merkez,wallWidth,wallHeight,ballCenterX,kickAngle,ballRadius,goalWidth);

}

int isitGoal(int Merkez, double wallWidth, double wallHeight, double ballCenterX, double
kickAngle, double ballRadius, double goalWidth){
	int ans=1;
	double x=23;/*İlkinde girmesin diye base case ye uydurma değer verdik.*/
	double y=23;/*İlkinde girmesin diye base case ye uydurma değer verdik.*/
	double RandAngle;
	Merkez=ballCenterX;
	if(wallHeight<=0)
		if((x<=wallWidth-goalWidth)/2 && x>=((wallWidth-goalWidth)/2)+goalWidth)
			ans= 1;
		else
			ans= 0;
	else if(wallWidth==0 || goalWidth==0 || wallHeight==0 || ballRadius==0)
		ans= 0;
	else if(x==0)
			ans*=isitGoal(0,wallWidth,wallHeight-y,ballRadius,kickAngle,ballRadius,goalWidth);
		RandAngle=randNumber(kickAngle);
	x=wallWidth-Merkez-ballRadius;
	printf("kickAngle=%f\n",reflection(kickAngle+RandAngle));
	y=x*reflection(kickAngle+RandAngle);
	x=0;
	printf("x=%f\n",x);
	printf("y=%f\n",y);
	return ans;
}
