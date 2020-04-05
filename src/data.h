#ifndef DATA_H
#define DATA_H

const float mass_difference = 100;

const float first_square[] = {
	 .1, -.7,  1, 0, 0,
	 .1, -.9,  1, 0, 0,
	-.1, -.7,  1, 0, 0,
	-.1, -.9,  1, 0, 0
};
const float second_square[] = {
	 .1, -.7,  0, 1, 0,
	 .1, -.9,  0, 1, 0,
	-.1, -.7,  0, 1, 0,
	-.1, -.9,  0, 1, 0
}; 

const float wall_floor[] = {
	 -1,  -1,  .1, .1, .1,
	  1,  -1,  .1, .1, .1,
	  1, -.9,  .1, .1, .1,
	-.9, -.9,  .1, .1, .1,
	-.9,   1,  .1, .1, .1,
	 -1,   1,  .1, .1, .1,
};

#endif // DATA_H
