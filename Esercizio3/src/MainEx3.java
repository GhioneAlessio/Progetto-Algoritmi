package src;

public class MainEx3 {
  public static void main(String[] args) throws Exception{
    Heap<Integer> heap = new Heap<>(new ComparatorIntField());
    heap.heapInsert(3);
    heap.heapInsert(9);
    heap.heapInsert(13);
    heap.heapInsert(5);
    heap.heapInsert(4);
    heap.heapInsert(7);
    for(int i = 0; i < heap.getSize(); i++){
      System.out.print(heap.getElem(i) + " ");
    }
    System.out.println("min elem = " + heap.getMinElement());
    heap.extractMin();
    for(int i = 0; i < heap.getSize(); i++){
      System.out.print(heap.getElem(i) + " ");
    }
    System.out.println("min elem = " + heap.getMinElement());
    System.out.println("13, parent elem = " + heap.parentElem(13));
  }
}
