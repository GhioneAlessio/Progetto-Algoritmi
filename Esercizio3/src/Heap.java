package src;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;

class Heap<T> {

  public ArrayList<T> array = null;
  private Comparator<? super T> compare = null;
  private HashMap<T, Integer> list_index;

  public Heap(Comparator<? super T> compare) {
    this.array = new ArrayList<T>();
    this.compare = compare;
    this.list_index = new HashMap<T, Integer>();
  }

  public T left_elem(T elem) throws IllegalArgumentException{
    if (!list_index.containsKey(elem))
      throw new IllegalArgumentException("Heap does not contain the specified element");
  
    int ind = list_index.get(elem);

    if (2 * ind <= this.get_size())
      return this.array.get(2 * ind);
    else
      return this.array.get(ind);
  }

  public T right_elem(T elem) throws IllegalArgumentException{
    if (!list_index.containsKey(elem))
      throw new IllegalArgumentException("Heap does not contain the specified element");
  
    int ind = list_index.get(elem);
   
    if ((2 * ind) + 1 <= this.get_size())
      return this.array.get((2 * ind) + 1);
    else
      return this.array.get(ind);
  }

  public T parent_elem(T elem) throws IllegalArgumentException{
    if (!list_index.containsKey(elem))
      throw new IllegalArgumentException("Heap does not contain the specified element");
  
    int parent_ind = this.list_index.get(elem)/2;
    return this.array.get(parent_ind);
  }

  public int heap_insert(T x){
    this.array.add(x);
    int p = this.array.size()-1;
    this.list_index.put(x, p);
    T elem = this.array.get(p);
    while(p > 0 && (this.compare).compare(elem , parent_elem(array.get(p))) < 0){
      swap(p, p/2);
      p = p/2;
      elem = this.array.get(p);
    }
    return 0;
  }

  private void swap(int a, int b) {
    T tmp1 = this.array.get(a);
    T tmp2 = this.array.get(b);
    this.array.set(a, tmp2);
    this.array.set(b, tmp1);
    this.list_index.replace(tmp2, a);
    this.list_index.replace(tmp1, b);
  }

  public int get_size() {
    return this.array.size();
  }

  public T get_min_element(){
    return this.array.get(0);
  }

  public void remove_min(){
    this.list_index.remove(get_min_element());
    for(int i = 0; i < this.get_size()-1; i++){
      this.array.set(i, this.get_elem(i+1));
      this.list_index.replace(this.array.get(i), i);
    }
    this.array.remove(this.get_size()-1);
  }

  public T get_elem(int i) throws NullPointerException{
    if(i < 0 || i > this.get_size())
      throw new NullPointerException("Index ouf od bound");
    return this.array.get(i);
  }

  public void decrease_element(int ind, T x) throws HeapException{
    if((this.compare).compare(this.array.get(ind), x) < 0){
      throw new HeapException("The new value has to be lower");
    }
    this.list_index.remove(this.get_elem(ind));
    this.list_index.put(x, ind);
    this.array.set(ind,x);
    T elem = this.array.get(ind);

    while(ind > 0 && (this.compare).compare(elem , parent_elem(this.array.get(ind))) < 0){
      swap(ind, ind/2);
      ind = ind/2;
      elem = this.array.get(ind);
    }
  }
  
}
