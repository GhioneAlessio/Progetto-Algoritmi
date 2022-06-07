package src;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;

class Heap<T> {

  private ArrayList<T> heap = null;
  private Comparator<? super T> compare = null;
  private HashMap<T, Integer> mapOfIndex;

  public Heap(Comparator<? super T> compare) {
    this.heap = new ArrayList<T>();
    this.compare = compare;
    this.mapOfIndex = new HashMap<T, Integer>();
  }

  public T leftElem(T elem) throws IllegalArgumentException {
    if (!mapOfIndex.containsKey(elem))
      throw new IllegalArgumentException("Heap leftElem: element not found");

    int ind = mapOfIndex.get(elem);

    if (2 * ind < this.getSize())
      return this.heap.get(2 * ind);
    else
      return this.heap.get(ind);
  }

  public T rigthElem(T elem) throws IllegalArgumentException {
    if (!mapOfIndex.containsKey(elem))
      throw new IllegalArgumentException("Heap rightElem: element not found");

    int ind = mapOfIndex.get(elem);

    if ((2 * ind) + 1 < this.getSize())
      return this.heap.get((2 * ind) + 1);
    else
      return this.heap.get(ind);
  }

  public T parentElem(T elem) throws IllegalArgumentException {
    if (!mapOfIndex.containsKey(elem))
      throw new IllegalArgumentException("Heap parentElem: element not found");

    int parentInd = this.mapOfIndex.get(elem) / 2;
    return this.heap.get(parentInd);
  }

  public int heapInsert(T x) {
    this.heap.add(x);
    int p = this.heap.size() - 1;
    this.mapOfIndex.put(x, p);
    T elem = this.heap.get(p);
    while (p > 0 && (this.compare).compare(elem, parentElem(heap.get(p))) < 0) {
      swap(p, p / 2);
      p = p / 2;
      elem = this.heap.get(p);
    }
    return 0;
  }

  private void swap(int a, int b) {
    T tmp1 = this.heap.get(a);
    T tmp2 = this.heap.get(b);
    this.heap.set(a, tmp2);
    this.heap.set(b, tmp1);
    this.mapOfIndex.replace(tmp2, a);
    this.mapOfIndex.replace(tmp1, b);
  }

  public int getSize() {
    return this.heap.size();
  }

  public T getMinElement() {
    return this.heap.get(0);
  }

  public T extractMin() {

    T min = this.getElem(0);
    this.mapOfIndex.remove(this.getElem(0));
    this.mapOfIndex.replace(this.getElem(this.getSize() - 1), 0);
    this.heap.set(0, this.getElem(this.getSize() - 1));
    this.heap.remove(this.getSize() - 1);
    heapify(0);
    return min;
  }

  private void heapify(int index) {
    if (this.getSize() == 0)
      return;
    int m;
    T elem = this.getElem(index);
    T leftElem = leftElem(elem);
    T rightElem = rigthElem(elem);
    if ((this.compare).compare(elem, leftElem) < 0 && (this.compare).compare(elem, rightElem) < 0) {
      m = index;
    } else if ((this.compare).compare(leftElem, elem) < 0 && (this.compare).compare(leftElem, rightElem) < 0)
      m = this.mapOfIndex.get(leftElem);
    else
      m = this.mapOfIndex.get(rightElem);
    if (m != index) {
      swap(m, index);
      heapify(m);
    }
  }

  private T getElem(int i) throws NullPointerException {
    if (i < 0 || i > this.getSize() - 1)
      throw new NullPointerException("Heap getElem: Index ouf of bound");
   
    return this.heap.get(i);
  }

  public void decreaseElement(T valueToDecrease, T newValue) throws Exception {
    if (!mapOfIndex.containsKey(valueToDecrease))
      throw new Exception("Heap decreaseElement: Element not found");

    int ind = this.mapOfIndex.get(valueToDecrease);
    this.mapOfIndex.remove(valueToDecrease);
    this.mapOfIndex.put(newValue, ind);
    this.heap.set(ind, newValue);
    T elem = this.heap.get(ind);

    while (ind > 0 && (this.compare).compare(elem, parentElem(this.heap.get(ind))) < 0) {
      swap(ind, ind / 2);
      ind = ind / 2;
      elem = this.heap.get(ind);
    }
  }

  public boolean containsElem(T elem) {
    return this.mapOfIndex.containsKey(elem);
  }
}
