package heap;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;

/**
 * It represents a minimum heap. Elements in the heap are ordered according
 * to a criterion specified by a comparator at creation time.
 * @param <T>: type of the minimum heap elements
 */

class Heap<T> {

  private ArrayList<T> heap = null;
  private Comparator<? super T> compare = null;
  private HashMap<T, Integer> mapOfIndex;

  /**
   * It creates an empty minimum heap
   * @param compare : a comparator implementing the precedence relation among heap elements.
   */
  public Heap(Comparator<? super T> compare) {
    this.heap = new ArrayList<T>();
    this.compare = compare;
    this.mapOfIndex = new HashMap<T, Integer>();
  }

  /**
   * 
   * @param elem : the element whose left child is desired
   * @return the left child of elem if it exists, elem otherwise, by getting elem's index,
   * then calculatig the child's index and (if it's not out of bounds) returning the child. 
   * @throws IllegalArgumentException
   */
  public T leftElem(T elem) throws IllegalArgumentException {
    if (!mapOfIndex.containsKey(elem))
      throw new IllegalArgumentException("Heap leftElem: element not found");

    int ind = mapOfIndex.get(elem);

    if ((2 * ind) + 1< this.getSize())
      return this.heap.get((2 * ind) + 1);
    else
      return this.heap.get(ind);
  }

  /**
   * 
   * @param elem : the element whose right child is desired
   * @return the right child of elem if it exists, elem otherwise, by getting elem's index,
   * then calculatig the child's index and (if it's not out of bounds) returning the child. 
   * @throws IllegalArgumentException
   */
  public T rightElem(T elem) throws IllegalArgumentException {
    if (!mapOfIndex.containsKey(elem))
      throw new IllegalArgumentException("Heap rightElem: element not found");

    int ind = mapOfIndex.get(elem);

    if ((2 * ind) + 2 < this.getSize())
      return this.heap.get((2 * ind) + 2);
    else
      return this.heap.get(ind);
  }

  /**
   * 
   * @param elem : the element whose parent is desired
   * @return elem's parent, by getting elem's index, then calculatig the parent's index 
   * and returning it. 
   * @throws IllegalArgumentException
   */
  public T parentElem(T elem) throws IllegalArgumentException {
    if (!mapOfIndex.containsKey(elem))
      throw new IllegalArgumentException("Heap parentElem: element not found");

    int parentInd = (this.mapOfIndex.get(elem) - 1) / 2;
    return this.heap.get(parentInd);
  }

  /**
   * 
   * It inserts x into the heap. It does so by inserting it into the last position
   * then swapping it into its correct position.
   * @param x: the element to be inserted
   */
  public int heapInsert(T x) {
    this.heap.add(x);
    int p = this.heap.size() - 1;
    this.mapOfIndex.put(x, p);
    T elem = this.heap.get(p);
    while (p > 0 && (this.compare).compare(elem, parentElem(heap.get(p))) < 0) {
      swap(p, (p - 1)/ 2);
      p = ((p -1)/ 2);
      elem = this.heap.get(p);
    }
    return 0;
  }

  /**
   * 
   * It swaps two elements in the heap and updates their indexes.
   * @param a : the element to be swapped with b
   * @param b : the element to be swapped with a
   */
  private void swap(int a, int b) {
    T tmp1 = this.heap.get(a);
    T tmp2 = this.heap.get(b);
    this.heap.set(a, tmp2);
    this.heap.set(b, tmp1);
    this.mapOfIndex.replace(tmp2, a);
    this.mapOfIndex.replace(tmp1, b);
  }

  /**
   * 
   * @return the number of elements in the Heap
   */
  public int getSize() {
    return this.heap.size();
  }

  /**
   * 
   * @return the element in the root position, as it is a MinHeap
   */
  public T getMinElement() {
    return this.heap.get(0);
  }

  /**
   * 
   * It extracts the root by replacing it with the last element,
   * Size and the indexes are updated.
   * Then heapify is called on the (new) root to restore the order.
   * @return the minimum element in the Heap
   */
  public T extractMin() {
    T min = this.getElem(0);
    this.mapOfIndex.remove(this.getElem(0));
    this.mapOfIndex.replace(this.getElem(this.getSize() - 1), 0);
    this.heap.set(0, this.getElem(this.getSize() - 1));
    this.heap.remove(this.getSize() - 1);
    heapify(0);
    return min;
  }

  /**
   * 
   * Heapify restores the order into the heap by comparing and swapping the elements.
   * @param index
   */
  private void heapify(int index) {
    if (this.getSize() == 0)
      return;
    int m;
    T elem = this.getElem(index);
    T leftElem = leftElem(elem);
    T rightElem = rightElem(elem);
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

  /**
   * 
   * @param i : index of the element that should be returned
   * @return the element at i index 
   * @throws NullPointerException
   */
  private T getElem(int i) throws NullPointerException {
    if (i < 0 || i > this.getSize() - 1)
      throw new NullPointerException("Heap getElem: Index ouf of bound");
   
    return this.heap.get(i);
  }

  /**
   * 
   * @param valueToDecrease : element to be decreased
   * @param newValue : new value to be assigned to the element to decrease
   * @throws Exception
   */
  public void decreaseElement(T valueToDecrease, T newValue) throws Exception {
    if (!mapOfIndex.containsKey(valueToDecrease))
      throw new Exception("Heap decreaseElement: Element not found");

    int ind = this.mapOfIndex.get(valueToDecrease);
    this.mapOfIndex.remove(valueToDecrease);
    this.mapOfIndex.put(newValue, ind);
    this.heap.set(ind, newValue);
    T elem = this.heap.get(ind);

    while (ind > 0 && (this.compare).compare(elem, parentElem(this.heap.get(ind))) < 0) {
      swap(ind, (ind -1)/ 2);
      ind = (ind -1)/ 2;
      elem = this.heap.get(ind);
    }
  }

  /**
   * 
   * @param elem : element to be checked if it exists
   * @return true if the Heap contains the element
   */
  public boolean containsElem(T elem) {
    return this.mapOfIndex.containsKey(elem);
  }
}
