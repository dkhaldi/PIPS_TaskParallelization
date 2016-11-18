# $Id: region_trans_stat_common_dim.awk 23065 2016-03-02 09:05:50Z coelho $
#
# Copyright 1989-2016 MINES ParisTech
#
# This file is part of PIPS.
#
# PIPS is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# PIPS is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.
#
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with PIPS.  If not, see <http://www.gnu.org/licenses/>.
#

BEGIN{  
  n_modules=0;
  base=75;
  n_calls=0;
  n_success=0;
  n_part_failure=0;
  n_non_lin=0;
}
NF!=0	{
	
  n_modules++;
  
  n_calls += $(base+0);
  n_success += $(base+1);
  n_part_failure += $(base+2);
  n_non_lin += $(base+3);  

  tot_tmp = $(base+0);
  if (tot_tmp !=0)
    print $1,"&",tot_tmp,"&",$(base+1),"&",int($(base+1)*100/tot_tmp),"&",$(base+2),"&",int($(base+2)*100/tot_tmp),"&",$(base+3),"&",int($(base+3)*100/tot_tmp),"\\\\";
  else
    print $1,"&",0,"&",0,"&",0,"&",0,"&",0,"&",0,"&",0,"\\\\";


}
END {	
  print "\\hline";
  
  if (n_calls !=0)
    print WORKSPACE, "&",n_calls,"&", n_success, "&", int(n_success*100/n_calls), "&", n_part_failure, "&",int(n_part_failure*100/n_calls),"&",n_non_lin, "&", int(n_non_lin*100/n_calls),"\\\\";
  else
   print WORKSPACE,"&",0,"&",0,"&",0,"&",0,"&",0,"&",0,"&",0,"\\\\"; 
}
