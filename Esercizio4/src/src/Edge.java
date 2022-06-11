package src;

public class Edge<T, S> {

  private T node1;
  private T node2;
  private S label;

  public Edge(T node1, T node2, S lab){
    this.node1 = node1;
    this.node2 = node2;
    this.label = lab;
  }

  public T getNode1(){
    return node1;
  }

  public T getNode2(){
    return node2;
  }

  public S getLabel(){
    return label;
  }

  public String toString(){
    return "node 1 = " + this.node1 + ", node 2 = " + this.node2 + ", label = " + this.label;
  }
}