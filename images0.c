//images.c


#include <read.c>
#include <call.c>
#include <stdio.h>
#include <stdlib.h>


void imageProcessing(int theImageArray[1025][1025], int theImageArrayDup[1025][1025], int height, int width) {
   char inputFunc[30];


   printf("Enter the function you wish to apply to your image. (Threshold, Luminosity,\nFraming, Transform, Convolve, Invert) \n");
   scanf("%s", inputFunc);
   lowerletter(inputFunc);


   if(strcmp(inputFunc,"invert") == 0) {
       invert(theImageArray);
   }


   if(strcmp(inputFunc,"convolve") == 0) {
       convolve(theImageArray, height, width);
   }


   if(strcmp(inputFunc, "threshold") == 0){
       threshold(theImageArray);
   }


   if(strcmp(inputFunc, "luminosity") == 0){
       luminosity(theImageArray);
   }


   if(strcmp(inputFunc, "framing") == 0){
       frame(theImageArray, height, width);
   }


   if(strcmp(inputFunc,"transform") == 0) {
       transformation(theImageArray, theImageArrayDup, height, width);
   }




   printf("\nDone\n");
}




void lowerletter(char myString[30]){
   for(int i = 0; i < strlen(myString); i++){
       myString[i] = tolower(myString[i]);
   }


}
