/****************************************************************************/
/*                                                                          */
/*                     Example of NRLIB32 library use                       */
/*                                                                          */
/*  This program make a net population live ; each net has same input ,     */
/*  but it  correct her behaviour by imitating another net random selected. */
/*  Only first <ua> nets don't choose model ; they have correct trainer     */
/*  value from a file .                                                     */
/*                                                                          */
/*  We can see that knoledge diffuse on entire population.                  */
/*                                                                          */
/*  On command line we can choose a different value for any parameeter  or  */
/*  let defaults (see help routine).                                        */
/*                                                                          */
/*  You must compile this program and link it with NRLIB32.OBJ file.        */
/*  Memory model is large.                                                  */
/*                                                                          */
/****************************************************************************/

# include "nrlib.h"       /* Library include                             */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>








main(int argc, char *argv[])
{
	NRLib nrlib;
	return nrlib.example1_main(argc, argv);
}















