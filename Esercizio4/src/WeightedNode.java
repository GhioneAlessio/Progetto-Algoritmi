package src;

import java.util.Objects;

public class WeightedNode<T, S>{
  
  private T node;
  private S weight;

  public WeightedNode(T node, S weight) {
    this.node = node;
    this.weight = weight;
  }

  public T getNode() {
    return this.node;
  }

  public S getWeight() {
    return this.weight;
  }

  public void setWeight(S weight) {
    this.weight = weight;
  }

  @Override 
  public boolean equals(Object obj) {
    if (obj == null) {
      return false;
    }
    if (!(obj instanceof WeightedNode)) {
      return false;
    }
    if (this == obj) {
      return true;
    }
     @SuppressWarnings({"unchecked"})
    WeightedNode<T,S> tmp = (WeightedNode<T,S>)obj;
    if(this.node.equals(tmp.getNode()))
      return true;
    else 
      return false;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.node);
  }
}