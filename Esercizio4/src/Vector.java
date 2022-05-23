package src;

public class Vector<T, S> {

  private T vertex;
  private S label;

  public Vector(T ver, S lab){
    this.vertex = ver;
    this.label = lab;
  }

  public T getVertex(){
    return vertex;
  }

  public S getLabel(){
    return label;
  }
}