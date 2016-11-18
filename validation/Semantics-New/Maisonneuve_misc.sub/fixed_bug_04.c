// Poor analysis of multiplication in deprecated versions of PIPS.

// $Id: fixed_bug_04.c 5188 2011-12-31 09:49:52Z coelho $

void run(void) {
	int i, n, m;
	i = rand();
	n = rand();
	m = rand();
	
	if (m >= 0 && n >= 1 && i <= m) {
		if (i > n * m) "unreachable";
	}
	
}

int main(void) {
	run();
	return 0;
}

