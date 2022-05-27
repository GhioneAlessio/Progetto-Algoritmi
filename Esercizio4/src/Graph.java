package src;
import java.util.HashMap;

import java.util.ArrayList;

public class Graph<T extends Comparable<T>, S> {

  private HashMap<T, HashMap<T, S>> nodeMap;
  private boolean directed_graph;

  public Graph(boolean direct) {
    this.nodeMap = new HashMap<T, HashMap<T,S>>();
    this.directed_graph = direct;
  }

  public void addNode(T elem) {
    nodeMap.put(elem, new HashMap<T, S>());
  }

  public void addEdge(T node1, T node2, S label) {

    (nodeMap.get(node1)).put(node2, label);

    if (!isDirected()) {
      nodeMap.get(node2).put(node1, label);
    }

  }

  public boolean isDirected() {
    return directed_graph;
  }

  public boolean containsNode(T node) {
    if(nodeMap.containsKey(node))
        return true;
    return false; 
  }

  public boolean containsEdge(T node1, T node2) {
    if(nodeMap.get(node1).containsKey(node2) == true)
      return true;
    return false;
  }

  public void removeNode(T node){
    nodeMap.remove(node);
    for (HashMap<T, S> adjNodes : nodeMap.values()){
      adjNodes.remove(node);
    }
  }

  public void removeEdge(T node1, T node2) {
    nodeMap.get(node1).remove(node2);
    if (!isDirected()) {
      nodeMap.get(node2).remove(node1);
    }
  }

  public int getNodesNum() {
    return nodeMap.size();
  }

  public int getEdgesNum() {
    int edges_num = 0;
    for (HashMap<T, S> adjNodes : nodeMap.values()){
      edges_num += adjNodes.size();
    }
    if(isDirected()){
      return edges_num;
    }
    else{
      return edges_num/2;
    }
  }

  public ArrayList<T> getNodes(){
    ArrayList<T> listOfNodes = new ArrayList<>();
    for(T nodesTmp : nodeMap.keySet()){
      listOfNodes.add(nodesTmp);
    }
    return listOfNodes;
  }

  public ArrayList<T> getAdjNodes(T node){
    ArrayList<T> adjList = new ArrayList<>();
    for(T nodesTmp : nodeMap.get(node).keySet()){
      adjList.add(nodesTmp);
    }
    return adjList;
  }
//TODO
  // public HashSet getEdges(){
  //   HashSet<T> edgeSet = new HashSet<T>();
  // }


  public S getLabel(T node1, T node2) throws Exception{
    return this.nodeMap.get(node1).get(node2);
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
// - Determinazione del numero di archi – O(n) 
// - Recupero nodi adiacenti di un dato nodo – O(1) (*)
// - Recupero dei nodi del grafo – O(n) 
// - Recupero etichetta associata a una coppia di nodi – O(1) (*) 

// - Recupero degli archi del grafo – O(n)  yet to do