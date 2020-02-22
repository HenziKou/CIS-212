#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GetPixelIndex(int width, int height, int row, int column);

typedef struct
{
     /* data members go here */
     unsigned char R;
     unsigned char G;
     unsigned char B;
} Pixel;

typedef struct
{
     /* data members go here */
     int width;
     int height;
     Pixel *colors;
} Image;

/*
 * Arguments:
 *   filename: the name of the file to read
 *   img:      a pointer to an Image struct.  You put the data from the
 *             file in this struct
 */

void ReadImage(char *filename, Image *img)
{
     fprintf(stderr, "Reading image \"%s\"\n", filename);

     /* Initialize variables */
     FILE *f_in = fopen(filename, "rb");
     char magicNum[128];
     int width, height, maxval;
     fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);  
     
     /* where f_in is the name of the input FILE.
     * NOTE: maxval is not needed, but we need to parse it.
     * NOTE: after the fscanf above, the file position indicator will
     * be pointing directly at the pixel data.
     */

     img->width = width;
     img->height = height;
     img->colors = malloc(sizeof(Pixel) * img->width * img->height);

     fread(img->colors, sizeof(Pixel), img->width * img->height, f_in);
     
     /* Close input file */
     fclose(f_in);

     fprintf(stderr, "Done reading image \"%s\"\n", filename);
}


/*
 * Arguments:
 *   filename: the name of the file to write
 *   img:      a pointer to an Image struct.  You put the data from the
 *             file in this struct
 */

void WriteImage(char *filename, Image *img)
{
    fprintf(stderr, "Writing image \"%s\"\n", filename);

    /* HINT:
     *  use fprintf to print out the first 4 lines of the file
     *  then use fwrite to print binary data.
     */

     FILE *f_out = fopen(filename, "wb");

     fprintf(f_out, "P6\n%d %d\n%d\n", img->width, img->height, 255);
     fwrite(img->colors, sizeof(Pixel), img->width * img->height, f_out);

     /* Close output file */ 
     fclose(f_out);

     fprintf(stderr, "Done writing image \"%s\"\n", filename);
}

/* 
 * Arguments:
 *    width:  the width of the image
 *    height: the height of the image
 *    row:    the row of the pixel
 *    column: the column of the pixel
 *
 * Returns: the index of the pixel in the image for (column, row)
 */

int GetPixelIndex(int width, int height, int row, int column)
{
    if (column < 0 || column >= width)
    {
        fprintf(stderr, "You asked for a pixel index for column %d, but the only valid values are between 0 and %d\n", column, width-1);
        exit(EXIT_FAILURE);
    }
    if (row < 0 || row >= height)
    {
        fprintf(stderr, "You asked for a pixel index for row %d, but the only valid values are between 0 and %d\n", row, height-1);
        exit(EXIT_FAILURE);
    }
    return row*width + column;
}

/* 
 * Arguments:
 *   input:    an image.  Take this image and replace the diagonal with
 *             a yellow line.
 *   output:   an image.  This should be the image with the yellow line
 *             diagonal.
 */
void YellowDiagonal(Image *input, Image *output)
{
    fprintf(stderr, "Executing YellowDiagonal\n");

    /* HINTS: 
     *   You will need to assign values to every data member of the output.
     *   For the output's Pixel array you will need to do a malloc to get
     *   a new array.
     *   Yellow in R/G/B is 255/255/0.
     */

     /* Assign output image values of Image struct */
     output->width = input->width;
     output->height = input->height;
     output->colors = malloc(sizeof(Pixel) * input->width * input->height);

     int size = input->width * input->height;

     /* Copy all pixels from input image to output image */
     for (int i = 0; i < size; i++)
     {
          output->colors[i] = input->colors[i];
     }

     /* If pixel is on diagonal change color to yellow */
     for (int j = 0; j < output->width; j++)
     {
	  for (int k = 0; k < output->height; k++)
	  {
	       int index = GetPixelIndex(output->width, output->height, k, j);

	       if (j == k)
	       {
	            output->colors[index].R = 255;
	            output->colors[index].G = 255;
	            output->colors[index].B = 0;
	       }
	  }
     }

    fprintf(stderr, "Done executing YellowDiagonal\n");
}

/* 
 * Arguments:
 *   input1:    an image.  This is the "left image".
 *   input2:    an image.  This is the "right image".
 *   output:    an image.  This is the horizontal combination of input1 and 2.
 */
void LeftRightCombine(Image *input1, Image *input2, Image *output)
{
     fprintf(stderr, "Executing LeftRightCombine\n");

     /* HINTS: 
     *   You will need to assign values to every data member of the output.
     *   For the output's Pixel array you will need to do a malloc to get
     *   a new array.
     *   The output's Pixel array will be larger than either of the inputs.
     *   IMPORTANT: the pixel index for an output pixel will be different
     *     than the pixel index for either of the inputs ... you will need
     *     to call GetPixelIndex multiple times.
     */

     /* Assign output image values of Image stuct */
     output->width = input1->width + input2->width;
     output->height = (input1->height + input2->height) / 2;
     output->colors = malloc(sizeof(Pixel) * output->width * output->height);

     for (int i = 0; i < output->width; i++)
     {
	  for (int j = 0; j < output->height; j++)
	  {
	       int out_index = GetPixelIndex(output->width, output->height, j, i);

	       /* Add first image to the left */
	       if (i < input1->width)
	       {
	            int in1_index = GetPixelIndex(input1->width, input1->height, j, i);
		    output->colors[out_index] = input1->colors[in1_index];
	       }

	       /* Add second image to the right */
	       else
	       {
		    int reindex = i - 500;
		    int in2_index = GetPixelIndex(input2->width, input2->height, j, reindex);
		    output->colors[out_index] = input2->colors[in2_index];
	       }
	  }
     }

          fprintf(stderr, "Done executing LeftRightCombine\n");
}

void VerifyInput()
{
    FILE *f_in = fopen("2G_input.pnm", "r");
    if (f_in == NULL)
    {
        fprintf(stderr, "Cannot open 2G_input.pnm for reading.\n");
        exit(EXIT_FAILURE);
    }
    fclose(f_in);

    FILE *f_out = fopen("2G_output.pnm", "w");
    if (f_out == NULL)
    {
        fprintf(stderr, "Cannot open 2G_output.pnm for writing.\n");
        exit(EXIT_FAILURE);
    }
    fclose(f_out);
}

int main(int argc, char *argv[])
{
    VerifyInput();

    Image source_image;
    Image yellow_diagonal;
    Image left_right;

    ReadImage("2G_input.pnm", &source_image);
    WriteImage("output_of_read.pnm", &source_image);

    YellowDiagonal(&source_image, &yellow_diagonal);
    WriteImage("yellow_diagonal.pnm", &yellow_diagonal);

    LeftRightCombine(&source_image, &yellow_diagonal, &left_right);
    WriteImage("2G_output.pnm", &left_right);

    /* Freeing images */
    free(source_image.colors);
    free(yellow_diagonal.colors);
    free(left_right.colors);

    return 0;
}
