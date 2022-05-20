package src;
public class Dist implements Comparable<Dist>{
  String city1;
  String city2;
  float  distance;

  public Dist(String c1, String c2, float d){
    this.city1 = c1;
    this.city2 = c2;
    this.distance = d;
  }

  @Override
  public int compareTo(Dist o) {
    if(this.city1 == o.city1 && this.city2 == o.city2 && this.distance == o.distance)
      return 0;
    else 
      return -1;
  }


}
