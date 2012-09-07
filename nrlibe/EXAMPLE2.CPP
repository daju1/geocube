/****************************************************************************/
/*                                                                          */
/*                     Example 2 of NRLIB32 library use                     */
/*                                                                          */
/*  This program is an example of genetic algoritm for xor net training.    */
/*  A population of nets are tested for xor behavior. Net fitness correspond*/
/*  to inverse of mean quadratic error.                                     */
/*  After all nets are tested , they are ordered according to their fitness */
/*  (first the best or the minimum mean quadratic error).                   */
/*                                                                          */
/*  This is the first generation ; best 1/5 of population procreate and     */
/*  replace other nets (total nets is constant) .                           */
/*  On new population we apply a little random mutations to weights.        */
/*                                                                          */
/*  In this example, application of genetic algoritm is not a classical     */
/*  version, because we don't use binary alphabet for genetic string and    */
/*  we don't apply  crossover operator (sexual procreation).                */
/*                                                                          */
/*  This algoritm is repeated for more generations , and you can see that   */
/*  the net behavior improve.                                               */
/*                                                                          */
/*  This algoritm is slower than EBP , but is useful in tasks that need more*/
/*  complicated fitness evaluation than exactly answers , like ecological   */
/*  tasks.                                                                  */
/*                                                                          */
/*  You must compile this program and link it with NRLIB32.OBJ file.        */
/*  Memory model is large.                                                  */
/*                                                                          */
/****************************************************************************/



# include "nrlib.h"                 /* Library include                    */
# include <stdio.h>
# include <stdlib.h>
# include <math.h>



main(int argc, char *argv[])
{
	NRLib nrlib;
	return nrlib.example2_main(argc, argv);
}














