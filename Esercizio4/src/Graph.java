package src;
import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;

public class Graph<T extends Comparable<T>, S> {

  private HashMap<T, ArrayList<Vector<T, S>>> nodeMap;
  private boolean directed_graph;

  public Graph(boolean direct) {
    this.nodeMap = new HashMap<T, ArrayList<Vector<T,S>>>();
    this.directed_graph = direct;
  }

  public void addNode(T elem) {
    nodeMap.put(elem, new ArrayList<Vector<T, S>>());
  }

  public void add_edge(T node1, T node2, S label) {

    (nodeMap.get(node1)).add(new Vector<T, S>(node2, label));

    if (!is_directed()) {
      nodeMap.get(node2).add(new Vector<T, S>(node1, label));
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
    ArrayList<Vector<T, S>> tmp = nodeMap.get(node1);
    if(tmp == null)
      return false;
    for (int i = 0; i < tmp.size(); i++) {
      if (tmp.get(i).getVertex().compareTo(node2) == 0)
        return true;
    }
    return false;
  }

  public void remove_node(T node){
    nodeMap.remove(node); 
    for (Map.Entry<T, ArrayList<Vector<T, S>>> listOfNode : nodeMap.entrySet()){
       for(int i = 0; i < listOfNode.getValue().size(); i++){
          if(node.compareTo(listOfNode.getValue().get(i).getVertex()) == 0)
          listOfNode.getValue().remove(i);
        }
    }
  }

  public void remove_edge(T node1, T node2) {
    for(int i = 0; i < nodeMap.get(node1).size(); i++){
      if((nodeMap.get(node1)).get(i).getVertex().compareTo(node2) == 0)
        nodeMap.get(node1).remove(i);
    }

    if (!is_directed()) {
      for(int i = 0; i < nodeMap.get(node2).size(); i++){
        if((nodeMap.get(node2)).get(i).getVertex().compareTo(node1) == 0)
          nodeMap.get(node2).remove(i);  
      }
    }
  }

  public int get_nodes_num() {
    return nodeMap.size();
  }

  public int get_edges_num() {
    int edges_num = 0;
    for (Map.Entry<T, ArrayList<Vector<T, S>>> listOfNode : nodeMap.entrySet()){
      edges_num += listOfNode.getValue().size();
    }
    if(is_directed()){
      return edges_num;
    }
    else{
      return edges_num/2;
    }
  }

  public ArrayList<T> getNodes(){
    ArrayList<T> listOfNodes = new ArrayList<T>();
    for(Map.Entry<T, ArrayList<Vector<T, S>>> nodesTmp : nodeMap.entrySet()){
      listOfNodes.add(nodesTmp.getKey());
    }
    System.out.println("list of nodes sizze = " + listOfNodes.size());
    return listOfNodes;
  }

  public ArrayList<T> getAdjNodes(T node){
    ArrayList<T> adjList = new ArrayList<>();
    ArrayList<Vector<T,S>> tmpList = nodeMap.get(node);
    for(int i = 0; i < tmpList.size(); i++){
      adjList.add(tmpList.get(i).getVertex());
    }
    return adjList;
  }
//TODO
  // public HashSet getEdges(){
  //   HashSet<T> edgeSet = new HashSet<T>();
  // }


  public S getLabel(T Node1, T Node2) throws Exception{
    ArrayList<Vector<T, S>> lisOfadj = nodeMap.get(Node1);
    for(int i = 0; i < lisOfadj.size(); i++){
      if(lisOfadj.get(i).getVertex() == Node2)
        return lisOfadj.get(i).getLabel();
    }
    throw new Exception("edge not existent");
  }

  public S Dijkstra(T startNode, T destinationNode) throws Exception{
    if(!is_directed())
      throw new Exception();

    
  }

  /*
  pi_greco = padre
  v = nodo generico
  s = nodo di partenza
  d = profondità,  
  u = nodo boh, non agg capit
  W(u,v) = peso arco tra u e v  
  se la somma della profondità di u + il peso tra u e v è minore della profondità di v, aggiorno v(porto su kinda), nuoa profondità la somma(u.d + W(u,v)) e come padre u
  */

  // void dijkstra(int graph[V][V], int src)
  // {
  //     int dist[V]; // The output array.  dist[i] will hold the shortest
  //     // distance from src to i
  //     bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
  //     // path tree or shortest distance from src to i is finalized
  //     // Initialize all distances as INFINITE and stpSet[] as false
  //     for (int i = 0; i < V; i++)
  //         dist[i] = INT_MAX, sptSet[i] = false;
  //     // Distance of source vertex from itself is always 0
  //     dist[src] = 0;
  //     // Find shortest path for all vertices
  //     for (int count = 0; count < V - 1; count++) {
  //         // Pick the minimum distance vertex from the set of vertices not
  //         // yet processed. u is always equal to src in the first iteration.
  //         int u = minDistance(dist, sptSet);
  //         // Mark the picked vertex as processed
  //         sptSet[u] = true;
  //         // Update dist value of the adjacent vertices of the picked vertex.
  //         for (int v = 0; v < V; v++)
  //             // Update dist[v] only if is not in sptSet, there is an edge from
  //             // u to v, and total weight of path from src to  v through u is
  //             // smaller than current value of dist[v]
  //             if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
  //                 && dist[u] + graph[u][v] < dist[v])
  //                 dist[v] = dist[u] + graph[u][v];
  //     }
  // }

//   Dijkstra(G, s)
// Q ← V
// for ∀v ∈ V do v .d← ∞, v .π ← nil
// s.d← 0
// s.π← nil
// while Q 6 = ∅ do
// u ← togli nodo con d minimo da Q
// for ∀v ∈ adj[u] do
// if v ∈ Q e u.d + W (u, v ) < v .d then
// v .d ← u.d + W (u, v )
// v .π ← u

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