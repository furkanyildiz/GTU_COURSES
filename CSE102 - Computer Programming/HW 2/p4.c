#include <stdio.h>
#define PI 3
int areaofRectangle(int Rwidth, int Rheight);
int perimeterofRectangle(int Rwidth2, int Rheight2);
int areaofSquare(int Swidth);
int perimeterofSquare(int Swidth2);
int areaofCircle(int radius);
int perimeterofCircle(int radius);

int main(void){
	int Rwidth,Rheight,Swidth,radius;
	
	printf("Please enter the width of the rectagle:");
	scanf("%d",&Rwidth);
	printf("Please enter the height of the rectagle:");
	scanf("%d",&Rheight);
	areaofRectangle(Rwidth,Rheight);
	perimeterofRectangle(Rwidth,Rheight);
	printf("Please enter the width of the square");
	scanf("%d",&Swidth);
	printf("The area of the square is:");
	areaofSquare(Swidth);
	perimeterofSquare(Swidth);
	printf("Please enter the radius of the circle:");
	scanf("%d",&radius);
	areaofCircle(radius);
	perimeterofCircle(radius);
	return (0);

}

int areaofRectangle(int Rwidth, int Rheight)
{
	int area;


	area=Rwidth*Rheight;
	printf("The area of the rectagle is: %d\n",area);
	
}

int perimeterofRectangle(int Rwidth2, int Rheight2)
{
	int perimeterRectangle;

	perimeterRectangle=(Rwidth2*2)+(Rheight2*2);
	printf("The perimeter of the rectangle is: %d\n",perimeterRectangle);

}

int areaofSquare(int Swidth)
{
	int areaSquare;

	
	areaSquare=Swidth*Swidth;
	printf("The area of the square is:\n",areaSquare);
}

int perimeterofSquare(int Swidth2)
{
	int perimeterSquare;
	perimeterSquare=(4*Swidth2);
	printf("The perimeter of the square is: %d\n",perimeterSquare);
	
	
}

int areaofCircle(int radius)
{
	int areaCircle;
	areaCircle=PI*radius*radius;
	printf("The area of the circle is: %d\n",areaCircle);
}

int perimeterofCircle(int radius)
{
	int perimeterCircle;
	perimeterCircle=2*PI*radius;
	printf("The perimeter of the circle is: %d\n",perimeterCircle);

}
