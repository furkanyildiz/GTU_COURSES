#include <stdio.h>
int areaofRectangle(int width, int height);
int main(void){
	int height,width;
	
	printf("Please enter the width of the rectagle:");
	scanf("%d",&width);
	printf("Please enter the height of the rectagle:");
	scanf("%d",&height);
	printf("The area of the rectagle is: %d",areaofRectangle(width,height));
	
	return (0);

}

int areaofRectangle(int width, int height)
{
	
	return(width*height);
	
}
