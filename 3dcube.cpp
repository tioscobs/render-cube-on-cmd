#include <iostream>
#include <conmanip.h>
#include <windows.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;
using namespace conmanip;

// TO CHANGE = Not send manually rows and columns of the matrices as arguments.
void matrix_multiply(auto matrix1, auto matrix2, auto matrix_result, int a_rows, int b_columns, int b_rows){
   for(int r = 0; r < a_rows; r++){
      for(int c = 0; c < b_columns; c++){
         for(int br = 0; br < b_rows; br++){
               matrix_result[br] = matrix_result[br] + (matrix1[r][br] * matrix2[r]);
            }
         }
   }
}
 
// NOTE: The quadrants are created based on the first point vector2. So, consider point1 X and Y the middle.
//  ______________________________
// |              |              |
// |   X2-, Y2-   |   X2+, Y2-   |
// |              |              |
// |-----------(X, Y)------------|
// |              |              |
// |   X2-, Y2+   |   X2+, Y2+   |              
// |______________|______________|

// TESTING: NEED TO FIX ALL QUADRANTS ( :C )
void draw_line(auto point1, auto point2, auto console){
   float distance = sqrt(pow(point1[0] - point2[0], 2) + pow(point1[1] - point2[1], 2));
   float co = abs(point1[0] - point2[0]), ca = abs(point1[1] - point2[1]);
   float tang = co/ca;
   int X, Y, fY;
   for(int i = 0; i < round(distance); i++){
      X = point1[0], Y = point1[1];

      if(point2[0] != point1[0]){
         X = ((point1[1] - point2[1]) < 0) ? X + i : X - i;

         if((point2[0] < point1[0] && point2[1] < point1[1])){ // X2 < 0 && Y2 < 0
            fY = point1[1] - ca;
            Y = fY + ((X - point2[0])/tang);
         }else if((point2[0] > point1[0] && point2[1] > point1[1])){ // X2 > 0 && Y2 > 0
            fY = point1[1] + ca;
            Y = fY + ((X - point2[0])/tang);
         }else{ // Using to test quadrants (X2 > 0 && Y2 < 0) and (X2 < 0 && Y2 > 0)
            Y = fY - ((X - point2[0])/tang);
         }
      }else{ // X1 == X2
         if(point1[1] < point2[1])
            Y += i;
         else
            Y -= i;
      }
      

      console.setpos(50 + X, 5 + Y);
      cout << "#";
      //cout << X << " " << Y << endl << endl;
   }
}

int main(){
   console_out_context context_out;
   console_out console(context_out);

   const int projection_matrix[2][3] = {
      {1, 0, 0},
      {0, 1, 0},
   };

   const int cube_dots[8][3] = {
      {-5, 5, 5},
      {5, 5, 5},
      {5, -5, 5},
      {-5, -5, 5},
      {-5, 5, -5},
      {5, 5, -5},
      {5, -5, -5},
      {-5, -5, -5},
   };
   
   float angle = 0;

   // RENDER
   while (true){
      system("cls");

      int dots[2][2] = {
         {0, 0},
         {5, 5}
      };
      
      for(auto dot: dots){
         console.setpos(50 + dot[0], 5 + dot[1]);
         cout << "&";
      }

      draw_line(dots[0], dots[1], console);

      /*
      int i = 0;
      int dots[4][2] = {};
      for(auto dot : cube_dots){
         int rot_dot[3] = {0, 0, 0};
         int rot2_dot[3] = {0, 0, 0};
         int proj_dot[3] = {0, 0, 0};

         float rotationX_matrix[3][3]{
            {1, 0, 0},
            {0, cos(angle), -sin(angle)},
            {0, sin(angle), cos(angle)},
         };

         float rotationY_matrix[3][3]{
            {cos(angle), 0, sin(angle)},
            {0, 1, 0},
            {-sin(angle), 0, cos(angle)},
         };

         float rotationZ_matrix[3][3]{
            {cos(angle), -sin(angle), 0},
            {sin(angle), cos(angle), 0},
            {0, 0, 1},
         };

         matrix_multiply(rotationY_matrix, dot, rot_dot, 3, 1, 3);
         matrix_multiply(rotationX_matrix, rot_dot, rot2_dot, 3, 1, 3);

         matrix_multiply(projection_matrix, rot2_dot, proj_dot, 2, 1, 3);

         //cout << proj_dot[0] << endl << proj_dot[1] << endl << endl;
         console.setpos(50 + proj_dot[0], 15 + proj_dot[1]);
         cout << "&";

         angle += 0.05;
         dots[i][0] = proj_dot[0], dots[i][1] = proj_dot[1];
         i++;
      }*/


      Sleep(500);
   }
   return 0;
}