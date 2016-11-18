# minimum rc file for sh-compatible shells

# default architecture is not necessary
#export PIPS_ARCH=LINUX_x86_64_LL

# subversion repositories
export NEWGEN_SVN=https://scm.cri.ensmp.fr/svn/newgen
export LINEAR_SVN=https://scm.cri.ensmp.fr/svn/linear
export PIPS_SVN=https://scm.cri.ensmp.fr/svn/pips

# production directory
prod=/home/dounia/MYPIPS/prod

# software roots are not needed
#export EXTERN_ROOT=$prod/extern
#export NEWGEN_ROOT=$prod/newgen
#export LINEAR_ROOT=$prod/linear
#export PIPS_ROOT=$prod/pips

# fix path
PATH=$prod/pips/bin:$prod/pips/utils:$prod/newgen/bin:$PATH

# The Fortran compiler to use:
export PIPS_F77=gfortran
