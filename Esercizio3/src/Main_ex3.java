package src;

public class Main_ex3 {
  public static void main(String[] args) throws Exception{
    Heap<Integer> heap = new Heap<>(new ComparatorIntField());
    heap.heap_insert(3);
    heap.heap_insert(9);
    heap.heap_insert(13);
    heap.heap_insert(5);
    heap.heap_insert(4);
    heap.heap_insert(7);

    for(int i = 0; i < heap.get_size(); i++){
      System.out.print(heap.get_elem(i) + " ");
    }
    System.out.println("min elem = " + heap.get_min_element());
    heap.remove_min();

    for(int i = 0; i < heap.get_size(); i++){
      System.out.print(heap.get_elem(i) + " ");
    }
    System.out.println("min elem = " + heap.get_min_element());
    System.out.println("13, parent elem = " + heap.parent_elem(13));
  }
}
