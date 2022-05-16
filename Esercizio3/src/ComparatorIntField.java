package src;

import java.util.Comparator;

public class ComparatorIntField implements Comparator<Integer>{
  
  @Override  
  public int compare(Integer v1, Integer v2) {
    return (v1.compareTo(v2));
   }
}

