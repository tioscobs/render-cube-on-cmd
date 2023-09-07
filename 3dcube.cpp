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
         cout << "#";

         angle += 0.05;
      }
      Sleep(100);
   }
   return 0;
}