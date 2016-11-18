# $Id: counts.mk 1201 2009-09-27 11:27:38Z coelho $

optimality.count:
	grep 'freia_status .*_helper_' *.result/test | \
	cut -d: -f1 | \
	uniq -c | sort -n > $@

clean: counts-clean
counts-clean:
	$(RM) optimality.count
