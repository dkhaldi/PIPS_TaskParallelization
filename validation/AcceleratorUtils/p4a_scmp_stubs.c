#include <stdlib.h>
#include <string.h>

typedef struct dtable{
  int ** buffers;
  int size;
}dtable;

dtable * buffertable=NULL;


/*VERY QUICK AND VERY DIRTY!!*/

void P4A_scmp_read(size_t element_size,
		   const void *host_address,
		   void *accel_address) {
  /* We can use memcpy() since we are sure there is no overlap */
  memcpy(accel_address, host_address, element_size);
}

void P4A_scmp_write(size_t element_size,
		    void *host_address,
		    const void *accel_address) {
  /* We can use memcpy() since we are sure there is no overlap */
  memcpy(host_address, accel_address, element_size);
}

void P4A_scmp_malloc(void **dest,  size_t n) {

  if(*dest==(void*)0)
      *dest = malloc(n);
}


void P4A_scmp_dealloc(void *dest) {
  /* free(dest);	 */
}

void * P4A_scmp_flow(void** flow) {
}

void P4A_copy_from_accel_1d(size_t element_size,
			    size_t d1_size,
			    size_t d1_block_size,
			    size_t d1_offset,
			    void *host_address,
			    const void *accel_address) {
  size_t i;
  char * cdest = d1_offset*element_size + (char *)host_address;
  const char * csrc = accel_address;
  for(i = 0; i < d1_block_size*element_size; i++)
    cdest[i] = csrc[i];
}

void P4A_copy_to_accel_1d(size_t element_size,
			  size_t d1_size,
			  size_t d1_block_size,
			  size_t d1_offset,
			  const void *host_address,
			  void *accel_address) {
  size_t i;
  char * cdest = accel_address;
  const char * csrc = d1_offset*element_size + (char *)host_address;
  for(i = 0; i < d1_block_size*element_size; i++)
    cdest[i] = csrc[i];
}

void P4A_copy_from_accel_2d(size_t element_size,
			    size_t d1_size, size_t d2_size,
			    size_t d1_block_size, size_t d2_block_size,
			    size_t d1_offset, size_t d2_offset,
			    void *host_address,
			    const void *accel_address) {
  size_t i, j;
  char * cdest = d2_offset*element_size + (char*)host_address;
  const char * csrc = (char*)accel_address;
  for(i = 0; i < d1_block_size; i++)
    for(j = 0; j < d2_block_size*element_size; j++)
      cdest[(i + d1_offset)*element_size*d2_size + j] =
        csrc[i*element_size*d2_block_size + j];
}


void P4A_copy_to_accel_2d(size_t element_size,
			  size_t d1_size, size_t d2_size,
			  size_t d1_block_size, size_t d2_block_size,
			  size_t d1_offset,   size_t d2_offset,
			  const void *host_address,
			  void *accel_address) {
  size_t i, j;
  char * cdest = (char *)accel_address;
  const char * csrc = d2_offset*element_size + (char *)host_address;
  for(i = 0; i < d1_block_size; i++)
    for(j = 0; j < d2_block_size*element_size; j++)
      cdest[i*element_size*d2_block_size + j] =
        csrc[(i + d1_offset)*element_size*d2_size + j];
}
