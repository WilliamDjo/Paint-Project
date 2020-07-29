// Assignment 1 19T3 COMP1511: CS Paint
// paint.c
//
// This program was written by William (z5268184)
// on 15th October
//
// Version 1.0.0 (2019-10-08): Assignment released.

#include <stdio.h>
#define EXIT_PROGRAM 0

// Note: you may find the square root function (sqrt) from the math
// library useful for drawing ellipses in Stage 3 and Stage 4.
#include <math.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define WHITE 4
#define DARK 1
#define GREY 2
#define LIGHT 3

// IF YOU NEED MORE #defines ADD THEM HERE


// Provided helper functions:
// Display the canvas.
void displayCanvas(int canvas[N_ROWS][N_COLS]);

// Clear the canvas by setting every pixel to be white.
void clearCanvas(int canvas[N_ROWS][N_COLS]);

// Calculate the distance between two points.
// Note: you will only need this function for the Draw Ellipse command
// in Stages 3 and 4.
double distance(int row1, int col1, int row2, int col2);

//drawing a line function
void drawLine(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int currentShade);

//drawing a square function
void fillSquare(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int currentShade);

//a function to process what happens when the length of the drawing goes out of bound
int outOfbound(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS]);

//a function to calculate if a negative line is inputted
void negativeLine(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int currentShade);

//a function to calculate if a negative length of a square is inputted
void negativeSquare(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int currentShade);

//a function to change the shade that gives access to both an eraser and
//different shades of grey
int changeShade(int currentShade, int new_shade);

//this function will allow to copy a certain section of the canvas
void copyCanvas(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int currentShade, int temp[N_ROWS][N_COLS], int target_row, int target_col);

//this function will allow to take the copied section of the canvas and paste it elsewhere
void pasteCanvas(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int temp[N_ROWS][N_COLS], int target_row, int target_col);

//this function will draw an ellipse
void drawEllipse(int focus_1_row, int focus_1_col, int focus_2_row, int focus_2_col, double lengthOfellipse, int fill, int canvas[N_ROWS][N_COLS], int currentShade);

int main(void) {
    int canvas[N_ROWS][N_COLS];
    int temp[N_ROWS][N_COLS] = {0};
    clearCanvas(temp);
    clearCanvas(canvas);

    int cmd;
    int start_row;
    int start_col;
    int length;
    int direction;
    int currentShade = BLACK;
    int new_shade;
    int target_row;
    int target_col;
    int focus_1_row;
    int focus_1_col;
    int focus_2_row;
    int focus_2_col;
    int fill;
    double lengthOfellipse;
    
    while(scanf("%d", &cmd) == 1){
    //scanf("%d %d %d %d\n", &start_row, &start_col, &length, &direction);
     if (cmd == 0){
        scanf("%d %d %d %d %lf %d", &focus_1_row, &focus_1_col, &focus_2_row, &focus_2_col, &lengthOfellipse, &fill);
        drawEllipse(focus_1_row, focus_1_col, focus_2_row, focus_2_col, lengthOfellipse, fill, canvas, currentShade);
     }    
     if (cmd == 1){
        scanf("%d %d %d %d\n", &start_row, &start_col, &length, &direction);
        if(length < 0){
            negativeLine(start_row, start_col, length, direction, canvas, currentShade);
        }else if (length >= 0){
            drawLine(start_row, start_col, length, direction, canvas, currentShade);
        }
     }  
     if (cmd == 2){
        scanf("%d %d %d %d\n", &start_row, &start_col, &length, &direction);
        if (length < 0) {
            negativeSquare(start_row, start_col, length, direction, canvas, currentShade);
        }else if (length >= 0){
            fillSquare(start_row, start_col, length, direction, canvas, currentShade);
        }
    }
    if (cmd == 3){
        scanf("%d\n", &new_shade);
        currentShade = changeShade(currentShade, new_shade);
        }
       
    if (cmd == 4){
        scanf("%d %d %d %d %d %d\n", &start_row, &start_col, &length, &direction, &target_row, &target_col);
        copyCanvas(start_row, start_col, length, direction, canvas, currentShade, temp, target_row, target_col);
        //printf("Got here\n");
        //pasteCanvas(start_row, start_col, length, direction, canvas, temp, target_row, target_col);
    }  
    
    }
    displayCanvas(canvas);
    

    return EXIT_PROGRAM;
}

//out of bound function
//if the length goes out of the canvas's bound, the program will just print a clear canvas
int outOfbound(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS]){
    if ( start_row < -1) {
        return 0;
    }else if (start_col < -1){
        return 0;
    }else if (start_row > N_ROWS){
        return 0;
    }else if (start_col > N_COLS){
        return 0;
    }
    //out of bound for 135 degrees
    int rowBoundOne = start_row + length; // sets rowBoundOne as the endpoint of the row
    int colBoundOne = start_col + length; // sets colBoundOne as the endpoint of the column
    //out of bound for 315 degrees
    int rowBoundTwo = start_row - length;
    int colBoundTwo = start_col - length;
    //out of bound for 225 degrees
    int rowBoundThree = start_row + length;
    int colBoundThree = start_col - length;
    //out of bound for 45 degrees
    int rowBoundFour = start_row - length;
    int colBoundFour = start_col + length;
    //out of bound for 180 degrees
    int rowBoundFive = start_row + length;
    //out of bound for 90 degrees
    int colBoundSix = start_col + length;
    //out of bound for 0 and 360 degrees
    int rowBoundSeven = start_row - length;
    //out of bound for 270 degrees
    int rowBoundEigth = start_col - length;
    
    if (direction == 135 && (rowBoundOne > N_ROWS || colBoundOne > N_COLS)){
        return 0;
    }else if (direction == 315 && (rowBoundTwo < -1 || colBoundTwo < -1)){
        return 0;
    }else if (direction == 225 && (rowBoundThree > N_ROWS || colBoundThree < -1)){
        return 0;
    }else if (direction == 45 && (rowBoundFour < -1 || colBoundFour > N_COLS)){
        return 0;
    }else if (direction == 180 && rowBoundFive > N_ROWS){
        return 0;
    }else if (direction == 90 && colBoundSix > N_COLS){
        return 0;
    }else if ((direction == 0 || direction % 360 == 0) && rowBoundSeven < -1){ 
        return 0;
    }else if (direction == 270 && rowBoundEigth < -1){
        return 0;
    }
    
    return 1;
}

int changeShade(int currentShade, int new_shade){
    //int temp;
    
    //if the current colour is black then this if will run
    if(currentShade == BLACK){
        if (new_shade + currentShade == 1){
            currentShade = DARK;
        }else if(new_shade + currentShade == 2){
            currentShade = GREY;
        }else if (new_shade + currentShade == 3){
            currentShade = LIGHT;
        }else if (new_shade + currentShade == 4){
            currentShade = WHITE;
        }
    } else if(currentShade == DARK){ //if the current colour is dark then this if will run
        //printf("%d\n", currentShade);
        if (new_shade + currentShade == 0){
            currentShade = BLACK;
        }else if(new_shade + currentShade == 2){
            currentShade = GREY;
        }else if (new_shade + currentShade == 3){
            currentShade = LIGHT;
        }else if (new_shade + currentShade == 4){
            currentShade = WHITE;
        }
        //printf("%d\n", currentShade);
    } else if(currentShade == GREY){ //if the current colour is grey then this if will run
        if (new_shade + currentShade == 1){
            currentShade = DARK;
        }else if(new_shade + currentShade == 0){
            currentShade = BLACK;
        }else if (new_shade + currentShade == 3){
            currentShade = LIGHT;
        }else if (new_shade + currentShade == 4){
            currentShade = WHITE;
        }
    } else if(currentShade == LIGHT){ //if the current colour is light then this if will run
        if (new_shade + currentShade == 1){
            currentShade = DARK;
        }else if(new_shade + currentShade == 2){
            currentShade = GREY;
        }else if (new_shade + currentShade == 0){
            currentShade = BLACK;
        }else if (new_shade + currentShade == 4){
            currentShade = WHITE;
        }
    } else if(currentShade == WHITE){ //if the current colour is white then this if will run
         if (new_shade + currentShade == 1){
            currentShade = DARK;
        }else if(new_shade + currentShade == 2){
            currentShade = GREY;
        }else if (new_shade + currentShade == 3){
            currentShade = LIGHT;
        }else if (new_shade + currentShade == 0){
            currentShade = BLACK;
        }
    }
    return currentShade;
}

//drawing a line function
void drawLine(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int currentShade){
    int i = 0;
    outOfbound(start_row, start_col, length, direction, canvas);
    if (outOfbound(start_row, start_col, length, direction, canvas) == 0){
    //this if statement is just to show what will happen if outofbound is true, it will do nothing!!!
    
    }else if (outOfbound(start_row, start_col, length, direction, canvas) == 1){
    while (i < length){
        if (direction == 90) {
            canvas[start_row][start_col] = currentShade;
            start_col++;
        }else if (direction == 270) {
            canvas[start_row][start_col] = currentShade;
            start_col--;
        }else if (direction == 180) {
            canvas[start_row][start_col] = currentShade;
            start_row++;
        }else if (direction == 0 || direction == 360) {
            canvas[start_row][start_col] = currentShade;
            start_row--;
        //if direction is greater than 360 it will take modulo 360
        }else if (direction > 360 && direction % 360 == 90) {
            canvas[start_row][start_col] = currentShade;
            start_col++;
        }else if (direction > 360 && direction % 360 == 270) {
            canvas[start_row][start_col] = currentShade;
            start_col--;
        }else if (direction > 360 && direction % 360 == 180) {
            canvas[start_row][start_col] = currentShade;
            start_row++;
        }else if (direction == 45 || direction % 360 == 45) {
            canvas[start_row][start_col] = currentShade;
            start_col++;
            start_row--;
        }else if (direction == 135 || direction % 360 == 135){
            canvas[start_row][start_col] = currentShade;
            start_row++;
            start_col++;
        }else if (direction == 315 || direction % 360 == 315){
            canvas[start_row][start_col] = currentShade;
            start_row--;
            start_col--;
        }else if (direction == 225 || direction % 360 == 225){
            canvas[start_row][start_col] = currentShade;
            start_row++;
            start_col--;
        }else{
        
        }
        i++;
    }   
    }
}

//drawing a square function
//the square drawn will be filled with a colour
void fillSquare(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int currentShade){
    int j = 0; //counter 1 to loop through row
    int n = 0; //counter 2 to loop through column
    outOfbound(start_row, start_col, length, direction, canvas);
    
    if (outOfbound(start_row, start_col, length, direction, canvas) == 0){
    ////this if statement is just to show what will happen if outofbound is true, it will do nothing!!!
    }else if (outOfbound(start_row, start_col, length, direction, canvas) == 1){                  
    while (j < length) { 
        //printf("%d\n", j);
        if (direction % 360 == 45 || direction == 45) {             
            while (n < length) { 
                canvas[start_row][start_col] = currentShade;  
                start_col++;                                  
                n++;
           }
           n = 0;
            while(n < length) {
                //canvas[start_row][start_col] = 0; 
                start_col--;
                n++;
            }
            start_row--;
            j++;
            n = 0;      
        }
        if (direction % 360 == 135 || direction == 135) {             
            while (n < length) { 
                canvas[start_row][start_col] = currentShade;  
                start_col++;                                  
                n++;
            }
           n = 0;
            while(n < length) {
                //canvas[start_row][start_col] = 0; 
                start_col--;
                n++;
            }
            start_row++;
            j++;
            n = 0;   
        }
        if (direction % 360 == 225 || direction == 225) {             
            while (n < length) { 
                canvas[start_row][start_col] = currentShade;  
                start_col--;                                  
                n++;
            }
           n = 0;
            while(n < length) {
                //canvas[start_row][start_col] = 0; 
                start_col++;
                n++;
            }
            start_row++;
            j++;
            n = 0;   
        }
        if (direction % 360 == 315 || direction == 315) {             
            while (n < length) { 
                canvas[start_row][start_col] = currentShade;  
                start_col--;                                  
                n++;
            }
           n = 0;
            while(n < length) {
                //canvas[start_row][start_col] = 0; 
                start_col++;
                n++;
            }
            start_row--;
            j++;
            n = 0;   
        }
        if (direction == 90) {
            canvas[start_row][start_col] = currentShade;
            start_col++;
            j++;
        }else if (direction == 270) {
            canvas[start_row][start_col] = currentShade;
            start_col--;
            j++;
        }else if (direction == 180) {
            canvas[start_row][start_col] = currentShade;
            start_row++;
            j++;
        }else if (direction == 0 || direction == 360) {
            canvas[start_row][start_col] = currentShade;
            start_row--;
            j++;
        }else if (direction > 360 && direction % 360 == 90) {
            canvas[start_row][start_col] = currentShade;
            start_col++;
            j++;
        }else if (direction > 360 && direction % 360 == 270) {
            canvas[start_row][start_col] = currentShade;
            start_col--;
            j++;
        }else if (direction > 360 && direction % 360 == 180) {
            canvas[start_row][start_col] = currentShade;
            start_row++;
            j++;
        }
        
        }
    }
}

//negative line function
//this function will convert a negative length into a positive length
//but will be aimed at the opposite direction
void negativeLine(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int currentShade){
    length = length * -1;
        if (direction < 180){
            //if direction is greater than 180, the direction will be added
            //with 180 so that the direction changes to its opposite side
            direction = direction + 180;
        }else if (direction > 180){
            //if direction is lesser than 180, the direction will be decreased
            //by 180 so that the direction changes to its opposite side
            direction = direction - 180;
        }
    drawLine(start_row, start_col, length, direction, canvas, currentShade);
  }

//negative square function
//this function will convert a negative length into a positive length
//but will be aimed at the opposite direction for squares
void negativeSquare(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int currentShade){
    length = length * -1;
        if (direction < 180){
            //if direction is greater than 180, the direction will be added
            //with 180 so that the direction changes to its opposite side
            direction = direction + 180;
        }else if (direction >= 180){
            //if direction is lesser than 180, the direction will be decreased
            //by 180 so that the direction changes to its opposite side
            direction = direction - 180;
        }
    fillSquare(start_row, start_col, length, direction, canvas, currentShade);
}

/*
this function will take the coordinates from the starting point, create a square or line in a 
given direction but instead of filling the square
copy the square into a temp canvas
*/
void copyCanvas(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int currentShade, int temp[N_ROWS][N_COLS], int target_row, int target_col){
    int j = 0; //counter 1 to loop through row
    int n = 0; //counter 2 to loop through column
    //int temp[N_ROWS][N_COLS];
    outOfbound(start_row, start_col, length, direction, canvas);
    //clearCanvas(temp);
    if (outOfbound(start_row, start_col, length, direction, canvas) == 0){
    //this if statement is just to show what will happen if outofbound is true, it will do nothing!!!
    }else if (outOfbound(start_row, start_col, length, direction, canvas) == 1 && outOfbound(target_row, target_col, length, direction, canvas) == 1){                  
        int start_val_col = start_col;
        int start_val_row = start_row;
        while (j < length) { 
            if (direction % 360 == 45 || direction == 45) {             
                while (n < length) {
                    //canvas[start_row][start_col] = currentShade;
                    temp[start_row][start_col] = canvas[start_row][start_col];
                    //canvas[start_row][start_col] = temp[start_row][start_col];
                    start_col++;                                  
                    n++;
               }
               n = 0;
                while(n < length) {
                    //canvas[start_row][start_col] = 0; 
                    start_col--;
                    n++;
                }
                //start_col = start_val;
                start_row--;
                j++;
                n = 0;      
            }
            if (direction % 360 == 135 || direction == 135) {             
                while (n < length) { 
                    //canvas[start_row][start_col] = currentShade;
                    temp[start_row][start_col] = canvas[start_row][start_col];
                    //canvas[start_row][start_col] = currentShade;  
                    start_col++;                                  
                    n++;
                }
               n = 0;
                while(n < length) {
                    //canvas[start_row][start_col] = 0; 
                    start_col--;
                    n++;
                }
                start_row++;
                j++;
                n = 0;   
            }
            if (direction % 360 == 225 || direction == 225) {             
                while (n < length) {
                    //canvas[start_row][start_col] = currentShade;
                    temp[start_row][start_col] = canvas[start_row][start_col];
                    //canvas[start_row][start_col] = currentShade;  
                    start_col--;                                  
                    n++;
                }
               n = 0;
                while(n < length) {
                    //canvas[start_row][start_col] = 0; 
                    start_col++;
                    n++;
                }
                start_row++;
                j++;
                n = 0;   
            }
            if (direction % 360 == 315 || direction == 315) {             
                while (n < length) { 
                    //canvas[start_row][start_col] = currentShade;
                    temp[start_row][start_col] = canvas[start_row][start_col];
                    //canvas[start_row][start_col] = currentShade;  
                    start_col--;                                  
                    n++;
                }
               n = 0;
                while(n < length) {
                    //canvas[start_row][start_col] = 0; 
                    start_col++;
                    n++;
                }
                start_row--;
                j++;
                n = 0;   
            }
            if (direction == 90) {
                //canvas[start_row][start_col] = currentShade;
                temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                start_col++;
                j++;
            }else if (direction == 270) {
                //canvas[start_row][start_col] = currentShade;
                temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                start_col--;
                j++;
            }else if (direction == 180) {
                //canvas[start_row][start_col] = currentShade;
                temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                start_row++;
                j++;
            }else if (direction == 0 || direction == 360) {
                //canvas[start_row][start_col] = currentShade;
                temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                start_row--;
                j++;
            }else if (direction > 360 && direction % 360 == 90) {
                //canvas[start_row][start_col] = currentShade;
                temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                start_col++;
                j++;
            }else if (direction > 360 && direction % 360 == 270) {
                //canvas[start_row][start_col] = currentShade;
                temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                start_col--;
                j++;
            }else if (direction > 360 && direction % 360 == 180) {
                //canvas[start_row][start_col] = currentShade;
                temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                start_row++;
                j++;
            }
        }
        start_col = start_val_col;
        start_row = start_val_row;
        pasteCanvas(start_row, start_col, length, direction, canvas, temp, target_row, target_col);   
        //displayCanvas(temp);
        //printf("\n \n \n");
    }   
//pasteCanvas(start_row, start_col, length, direction, canvas, temp, target_row, target_col);   
}

//this function will paste the line or square that is in the temp canvas to the 
//target row and column
void pasteCanvas(int start_row, int start_col, int length, int direction, int canvas[N_ROWS][N_COLS], int temp[N_ROWS][N_COLS], int target_row, int target_col){
    int j = 0; //counter 1 to loop through row
    int n = 0; //counter 2 to loop through column
    //int temp[N_ROWS][N_COLS];
    outOfbound(start_row, start_col, length, direction, canvas);
    //clearCanvas(temp);
    if (outOfbound(start_row, start_col, length, direction, canvas) == 0){
    //this if statement is just to show what will happen if outofbound is true, it will do nothing!!!
    }else if (outOfbound(start_row, start_col, length, direction, canvas) == 1){                  
        while (j < length) { 
            if (direction % 360 == 45 || direction == 45) {             
                while (n < length) { 
                    //temp[start_row][start_col] = canvas[start_row][start_col];
                    canvas[target_row][target_col] = temp[start_row][start_col];
                    start_col++;
                    target_col++;                                  
                    n++;
               }
               n = 0;
                while(n < length) {
                    //canvas[start_row][start_col] = 0; 
                    start_col--;
                    target_col--;
                    n++;
                }
                start_row--;
                target_row--;
                j++;
                n = 0;      
            }
            if (direction % 360 == 135 || direction == 135) {             
                while (n < length) { 
                    //temp[start_row][start_col] = canvas[start_row][start_col];
                    //canvas[start_row][start_col] = currentShade;
                    canvas[target_row][target_col] = temp[start_row][start_col];  
                    start_col++;
                    target_col++;                                  
                    n++;
                }
               n = 0;
                while(n < length) {
                    //canvas[start_row][start_col] = 0; 
                    start_col--;
                    target_col--;
                    n++;
                }
                start_row++;
                target_row++;
                j++;
                n = 0;   
            }
            if (direction % 360 == 225 || direction == 225) {             
                while (n < length) {
                    //temp[start_row][start_col] = canvas[start_row][start_col];
                    //canvas[start_row][start_col] = currentShade;
                    canvas[target_row][target_col] = temp[start_row][start_col];  
                    start_col--;
                    target_col--;                                  
                    n++;
                }
               n = 0;
                while(n < length) {
                    //canvas[start_row][start_col] = 0; 
                    start_col++;
                    target_col++;
                    n++;
                }
                start_row++;
                target_col++;
                j++;
                n = 0;   
            }
            if (direction % 360 == 315 || direction == 315) {             
                while (n < length) { 
                    //temp[start_row][start_col] = canvas[start_row][start_col];
                    //canvas[start_row][start_col] = currentShade; 
                    canvas[target_row][target_col] = temp[start_row][start_col]; 
                    start_col--;
                    target_col--;                                  
                    n++;
                }
               n = 0;
                while(n < length) {
                    //canvas[start_row][start_col] = 0; 
                    start_col++;
                    target_col++;
                    n++;
                }
                start_row--;
                target_row--;
                j++;
                n = 0;   
            }
            if (direction == 90) {
                //temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                canvas[target_row][target_col] = temp[start_row][start_col];
                start_col++;
                target_col++;
                j++;
            }else if (direction == 270) {
                //temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                canvas[target_row][target_col] = temp[start_row][start_col];
                start_col--;
                target_col--;
                j++;
            }else if (direction == 180) {
                //temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                canvas[target_row][target_col] = temp[start_row][start_col];
                start_row++;
                target_row++;
                j++;
            }else if (direction == 0 || direction == 360) {
                //temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                canvas[target_row][target_col] = temp[start_row][start_col];
                start_row--;
                target_row--;
                j++;
            }else if (direction > 360 && direction % 360 == 90) {
                //temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                canvas[target_row][target_col] = temp[start_row][start_col];
                start_col++;
                target_col++;
                j++;
            }else if (direction > 360 && direction % 360 == 270) {
                //temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                canvas[target_row][target_col] = temp[start_row][start_col];
                start_col--;
                target_col--;
                j++;
            }else if (direction > 360 && direction % 360 == 180) {
                //temp[start_row][start_col] = canvas[start_row][start_col];
                //canvas[start_row][start_col] = currentShade;
                canvas[target_row][target_col] = temp[start_row][start_col];
                start_row++;
                target_row++;
                j++;
            }
        }
    }   
}

//this function is given six inputs, which which describes two focus pixels, 
//a length and an additional integer in order to draw the ellipse
void drawEllipse(int focus_1_row, int focus_1_col, int focus_2_row, int focus_2_col, double lengthOfellipse, int fill, int canvas[N_ROWS][N_COLS], int currentShade){
    int start_row = 0;

    if (fill != 0){
        while(start_row < N_ROWS){
            int start_col = 0;
            while(start_col < N_COLS){
                if (distance(focus_1_row, focus_1_col, start_row, start_col) + distance(start_row, start_col, focus_2_row, focus_2_col) <= 2 * lengthOfellipse){
                    canvas[start_row][start_col] = currentShade;
                }
                start_col++;
            }
            start_row++;
        }    
    }
} 


// Displays the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.
//
// You should not need to change the displayCanvas function.
void displayCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}


// Sets the entire canvas to be blank, by setting each element in the
// 2-dimensional canvas array to be WHITE (which is #defined at the top
// of the file).
//
// You should not need to change the clearCanvas function.
void clearCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}

// Calculate the distance between two points (row1, col1) and (row2, col2).
// Note: you will only need this function for the Draw Ellipse command
// in Stages 3 and 4.
double distance(int row1, int col1, int row2, int col2) {
    int row_dist = row2 - row1;
    int col_dist = col2 - col1;
    return sqrt((row_dist * row_dist) + (col_dist * col_dist));
}
