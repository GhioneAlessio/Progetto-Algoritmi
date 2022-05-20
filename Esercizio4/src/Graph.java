package src;

import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;

public class Graph<T extends Comparable<T>> {

  private HashMap<T, ArrayList<T>> nodeMap;
  private boolean directed_graph;

  public Graph(boolean direct) {
    this.nodeMap = new HashMap<T, ArrayList<T>>();
    this.directed_graph = direct;
  }
// arraylist contiene etichetta per identificare archi kinda
  public void add_node(T elem) {
    nodeMap.put(elem, new ArrayList<T>());
  }

  public void add_edge(T node1, T node2) {

    (nodeMap.get(node1)).add(node2);

    if (!is_directed()) {
      nodeMap.get(node2).add(node1);
    }

  }

  public boolean is_directed() {
    return directed_graph;
  }

  public boolean contains_node(T node) {
    if(nodeMap.containsKey(node))
        return true;
    return false; 
  }

  public boolean contains_edge(T node1, T node2) {
    ArrayList<T> tmp = nodeMap.get(node1);
    if(tmp == null)
      return false;
    for (int i = 0; i < tmp.size(); i++) {
      if (tmp.get(i).compareTo(node2) == 0)
        return true;
    }
    return false;
  }

  public void remove_node(T node){
    nodeMap.remove(node); 
    for (Map.Entry<T, ArrayList<T>> set : nodeMap.entrySet()){
       for(int i = 0; i < set.getValue().size(); i++){
          if(node.compareTo(set.getValue().get(i)) == 0)
            set.getValue().remove(node);
        }
    }
  }

  

  public void remove_edge(T node1, T node2) {
    nodeMap.get(node1).remove(node2);

    if (!is_directed()) {
      nodeMap.get(node2).remove(node1);
    }
  }

  public int get_nodes_num() {
    return nodeMap.size();
  }
//TODO
  public int get_edges_num() {
    int edges_num = 0;
    if(is_directed()){
      for (Map.Entry<T, ArrayList<T>> set : nodeMap.entrySet()){
        edges_num += set.getValue().size();
      }
      return edges_num;
    }
    else{
      return -1;
    }
  }

}

// - Creazione di un grafo vuoto – O(1)
// - Aggiunta di un nodo – O(1)
// - Aggiunta di un arco – O(1)
// - Verifica se il grafo è diretto – O(1)
// - Verifica se il grafo contiene un dato nodo – O(1)
// - Verifica se il grafo contiene un dato arco – O(1) (*)
// - Cancellazione di un nodo – O(n)
// - Cancellazione di un arco – O(1) (*)
// - Determinazione del numero di nodi – O(1)
// - Determinazione del numero di archi – O(n) yet to do

// - Recupero dei nodi del grafo – O(n) 
// - Recupero degli archi del grafo – O(n) 
// - Recupero nodi adiacenti di un dato nodo – O(1) (*)
// - Recupero etichetta associata a una coppia di nodi – O(1) (*) 