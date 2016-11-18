/* Bug reported by Corinne
 *
 * Issue with struct t of type timeval
 */

#include <sys/time.h>
#include <time.h>

unsigned long long int time01() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (t.tv_sec * 1e6 + t.tv_usec);
}

