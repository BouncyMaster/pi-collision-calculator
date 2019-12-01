#ifndef DATA_H
#define DATA_H

const float mass_difference = 100;

float first_square[] = {
   .2, -.7,  1, 0, 0,
   .2, -.9,  1, 0, 0,
    0, -.7,  1, 0, 0,
    0, -.9,  1, 0, 0
};
float second_square[] = {
  -.4, -.7,  0, 1, 0,
  -.4, -.9,  0, 1, 0,
  -.6, -.7,  0, 1, 0,
  -.6, -.9,  0, 1, 0
}; 

const float wall_floor[30] = {
   -1,  -1,  .1, .1, .1,
    1,  -1,  .1, .1, .1,
    1, -.9,  .1, .1, .1,
  -.9, -.9,  .1, .1, .1,
  -.9,   1,  .1, .1, .1,
   -1,   1,  .1, .1, .1,
};

const unsigned char digit_i[10][7] = {
  {3, 5, 2, 0, 3},
  {3, 5},
  {0, 3, 4, 1, 2, 5},
  {0, 3, 4, 1, 4, 5, 2},
  {0, 1, 4, 3, 5},
  {3, 0, 1, 4, 5, 2},
  {3, 0, 2, 5, 4, 1},
  {0, 3, 5},
  {1, 4, 5, 2, 0, 3, 4},
  {4, 1, 0, 3, 5, 2}
};

const unsigned char digit_i_len[10] = {
  5, 2, 6, 7, 5, 6, 6, 3, 7, 6
};

float digit_vertices[30] = {
  -.8,  .9,  1, 1, 1, // top left
  -.8,  .8,  1, 1, 1, // middle left
  -.8,  .7,  1, 1, 1, // bottom left
  -.7,  .9,  1, 1, 1, // top right
  -.7,  .8,  1, 1, 1, // middle right
  -.7,  .7,  1, 1, 1, // bottom right
};

#endif // DATA_H
