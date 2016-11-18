/*

  $Id: Watcher.java 23065 2016-03-02 09:05:50Z coelho $

  Copyright 1989-2016 MINES ParisTech

  This file is part of PIPS.

  PIPS is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  PIPS is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.

  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with PIPS.  If not, see <http://www.gnu.org/licenses/>.

*/

package fr.ensmp.cri.jpips;

import java.lang.*;
import java.util.*;
import java.io.*;

/** A class that checks for the tpips output stream.
 * @author Francois Didry
 */  
public class Watcher 
  implements Runnable
{
  public Process tpips;  //tpips instance
  
  public Watcher(Process tpips)
  {
    this.tpips = tpips;
  }
  
  public void run()
  {
    try
    {
      System.out.println("Tpips watcher running");
      tpips.waitFor();
      System.out.println("tpips down");
    }
    catch(InterruptedException e)
    {
      System.out.println(e);
    }
  }
}