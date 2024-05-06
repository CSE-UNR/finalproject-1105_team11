//read.c


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_HEIGHT 1025
#define MAX_WIDTH 1025


#define MAX_PIXELS_PER_LINE 70


#define MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )


int theImageArray[1025][MAX_WIDTH];
int theImageArrayDup[1025][MAX_WIDTH];


FILE* read_pgm_file_info
(
   int* height,
   int* width,
   int* maxPixel,
   char* pgmFname
)
{
   static FILE* fp = 0L ;
   char pgmFormatFlag[3] =  { '\0' } ;


   char trash[80] = { '\0' } ;
   memset ( ( void * ) trash, '\0', 80 ) ;


   fp = fopen ( pgmFname, "r" ) ;


   if ( fp )
   {
    
       fscanf ( fp, "%2c\n", pgmFormatFlag ) ;
    
       if ( ! strcmp ( pgmFormatFlag, "P2" ) )
       {


           fgets (  trash, 70, fp ) ;


           fscanf ( fp, "%i", width ) ;
            fscanf ( fp, "%i", height ) ;


           fscanf ( fp, "%i", maxPixel ) ;
       }
      
   }


   return fp ;
}


void write_pgm_file_from_array
(
   char* pgmOutFileName,
   int imageArray[][MAX_WIDTH],
   char* commentLine,
   int height,
   int width,
   int maxPixel
)
{
   int row = 0 ;
   int col = 0 ;
   FILE* fp = fopen ( pgmOutFileName, "w" ) ;
   if ( fp )
   {
      
       fprintf ( fp, "P2\n" ) ;
       fprintf ( fp, "%s\n", commentLine ) ;
       fprintf ( fp, "%u %u\n", width, height ) ;
       fprintf ( fp, "%u\n", maxPixel ) ;


       for ( row = 0 ; row < height ; row ++ )
       {
           for ( col = 0 ; col < width ; col ++ )
           {
               fprintf ( fp, "%u", imageArray[row][col] ) ;
              
               if ( MAX_PIXELS_PER_LINE > 1 )
               {
                   fprintf ( fp, " " ) ;
               }
               if ( ( col % MAX_PIXELS_PER_LINE ) == 0 )
               {
                   fprintf ( fp, "\n" ) ;
               }
           }
         
           if ( col % MAX_PIXELS_PER_LINE )
           {
               fprintf ( fp, "\n" ) ;
           }
       }
       fclose ( fp ) ;
   }
   return ;
}


void read_pgm_file_into_array
(
   int imageArray[][MAX_WIDTH],
   int* height,
   int* width,
   int* maxPixel,
   char* pgmInFileName
)
{
   int row = 0 ;
   int col = 0 ;
   FILE* fp = read_pgm_file_info ( height, width, maxPixel, pgmInFileName ) ;
   char trash = ' ';
   char yesThreshold = ' ';


   if ( fp )
   {
       printf ( "reading height=%d, width=%d\n", *height, *width ) ;
       for ( row = 0 ; row < MIN( MAX_HEIGHT - 1, *height ) ; row ++ )
       {
           for ( col = 0 ; col < MIN( MAX_WIDTH -1, *width ) ; col ++ )
           {
               fscanf ( fp, "%i", &imageArray[row][col]) ;
           }
       }
       fclose ( fp ) ;
   }


   return ;
}


int main( void )
{
   int height  = 0 ;
   int width = 0 ;
   int maxPixel = 0 ;


   char* pgmInFileName = "irv.pgm" ;
   char* pgmOutFileName = "irv_out.pgm" ;


   read_pgm_file_into_array (theImageArray, &height, &width, &maxPixel, pgmInFileName ) ;


   for(int i = 0; i < 1025; i++){
       for(int j = 0; j < MAX_WIDTH; j++){
           theImageArrayDup[i][j] = theImageArray[i][j];
       }
   }
   imageProcessing(theImageArray, theImageArrayDup,height,width);


   write_pgm_file_from_array ( pgmOutFileName, theImageArray, "# JR test file", height, width,
                               maxPixel ) ;


   printf ( "Copying %s to %s, height=%u, width=%u, maxPixel=%d\n", pgmInFileName,
            pgmOutFileName,
            height, width, maxPixel ) ;


   return 0 ;
}
