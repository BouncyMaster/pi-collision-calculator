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

#endif // DATA_H
