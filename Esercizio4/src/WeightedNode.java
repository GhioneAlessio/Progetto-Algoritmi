import java.util.Objects;

/**
 * 
 * It represents an object that contains the node, the sum of the edges' weights
 * from the source to the node and his previous.
 * @param <T> : type of the node and his previous 
 * @param <S> : type of the weight
 */
public class WeightedNode<T, S>{
  
  private T node;
  private S weight;
  private T previous;

  public WeightedNode(T node, S weight, T previous) {
    this.node = node;
    this.weight = weight;
    this.previous = previous;
  }

  public T getNode() {
    return this.node;
  }

  
  public S getWeight() {
    return this.weight;
  }
  
  public T getPrevious() {
    return this.previous;
  }

  public void setWeight(S weight) {
    this.weight = weight;
  }

  public void setPrevious(T previous) {
    this.previous = previous;
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