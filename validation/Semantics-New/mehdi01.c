/* FI: I do not remember why Mehdi submitted this case...  He did not
 * want to use the best available options to compute the preconditions
 * as indicated in the tpips script.
 *
 * w is positive, but this is not detected in the first pass as could
 * be expected because no information about z is available yet.
 *
 * Since i==z-1 when w is computed, w==i+3 after w's update and w==i+2
 * on loop exit, but this is not found precisely by transformer
 * refinement... in the postconditions, while the information is
 * avalable in the transformer of "w=z+2;".
 */

int SIZE=10;

void mehdi01()
{
  int i,z=0,w=0;
  for(i=0 ; i < SIZE ; i++) {
    z=z+1;
    w=z+2;
  }
  return;
}
