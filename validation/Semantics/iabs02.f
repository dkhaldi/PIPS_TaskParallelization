      program iabs02

C     Non trivial and non-linear expressions
C
C     FI: it is not practical for maintenance to test several
C     expressions in one file because differences are spread all
C     over. Unless the same variable is used again and again.

C      read *, n
      if(m.lt.0) stop

      i = iabs(n+m/2)

      print *, i

      read *, j

      j = iabs(i*(i+1))

      print *, j

      if(j.ne.3) stop

      k = iabs(j*(i+1))

      print *, k

      end
