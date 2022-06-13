package graph;

import java.util.HashMap;

import java.util.ArrayList;

/**
 * It represents a graph.
 * @param <T> : type of the nodes 
 * @param <S> : type of the edge's weight
 * 
 */
public class Graph<T, S> {

  private HashMap<T, HashMap<T, S>> nodeMap;
  private boolean directed_graph;

  /**
   * 
   * It creates an empty graph.
   * @param direct : boolean variable that establishes if the edges are directed or not 
   */
  public Graph(boolean direct) {
    this.nodeMap = new HashMap<T, HashMap<T, S>>();
    this.directed_graph = direct;
  }

  /**
   * 
   * It adds a node to the graph.
   * @param elem : element to be added
   * @throws Exception
   */
  public void addNode(T elem) throws Exception {
    if (this.containsNode(elem))
      throw new Exception("Graph addNode: Node already exists");
    else
      this.nodeMap.put(elem, new HashMap<T, S>());
  }

  /**
   * 
   * It adds an edge between two nodes.
   * @param node1 : first node
   * @param node2 : second node
   * @param label : weight of the edge between the nodes
   * @throws Exception
   */
  public void addEdge(T node1, T node2, S label) throws Exception {
    if (this.containsEdge(node1, node2))
      throw new Exception("Graph addEdge: Edge already exists");
    else {
      (this.nodeMap.get(node1)).put(node2, label);
      if (!isDirected())
        this.nodeMap.get(node2).put(node1, label);
    }
  }

  /**
   * 
   * @return true if the edges are directed
   */
  public boolean isDirected() {
    return this.directed_graph;
  }

  /**
   * 
   * It checkes if the graph contains the specified node.
   * @param node : node to be checked if it exists
   * @return true if the Graph contains the node
   */
  public boolean containsNode(T node) {
    if (this.nodeMap.containsKey(node))
      return true;
    return false;
  }

  /**
   * 
   * It checkes if the graph contains an edge between the specified nodes.
   * @param node1 : first node
   * @param node2 : second node
   * @return true if the Graph contains the edge between node1 and node2
   */
  public boolean containsEdge(T node1, T node2) {
    if (this.containsNode(node1) && this.containsNode(node2)) {
      if (this.nodeMap.get(node1).containsKey(node2))
        return true;
    }
    return false;
  }

  /**
   * 
   * It removes a node if it exists.
   * @param node to be removed
   * @throws Exception
   */
  public void removeNode(T node) throws Exception {

    if (!this.containsNode(node))
      throw new Exception("Graph removeNode; Graph doesn't contain the specified node");

    this.nodeMap.remove(node);
    for (HashMap<T, S> adjNodes : this.nodeMap.values()) {
      adjNodes.remove(node);
    }
  }

  /**
   * It removes the edge between the specified nodes if it exists.
   * @param node1 : first node
   * @param node2 : second node
   * @throws Exception
   */
  public void removeEdge(T node1, T node2) throws Exception {

    if (this.containsNode(node1) && this.containsNode(node2)) {
      if (this.nodeMap.get(node1).containsKey(node2)) {
        this.nodeMap.get(node1).remove(node2);
        if (!isDirected())
          this.nodeMap.get(node2).remove(node1);
      } else
          throw new Exception("Graph removeEdge: Edge does not exist");
    } else
        throw new Exception("Graph removeEdge: Graph does not contains the specified node/s");
  }

  /**
   * 
   * @return the number of nodes in the graph
   */
  public int getNodesNum() {
    return nodeMap.size();
  }

  /**
   * 
   * @return the number of edges in the graph (if the edges aren't directed it 
   * halves the obtained quantity, because every edge is counted twice)
   */
  public int getEdgesNum() {
    int edges_num = 0;
    for (HashMap<T, S> adjNodes : this.nodeMap.values()) {
      edges_num += adjNodes.size();
    }
    if (isDirected()) {
      return edges_num;
    } else {
      return edges_num / 2;
    }
  }

  /**
   * 
   * @return the list of the nodes
   */
  public ArrayList<T> getNodes() {
    ArrayList<T> listOfNodes = new ArrayList<>();
    for (T nodesTmp : this.nodeMap.keySet()) {
      listOfNodes.add(nodesTmp);
    }
    return listOfNodes;
  }

  /**
   * 
   * @param node : node whose adjacents are desired
   * @return the list of the adjacents of the specified node
   * @throws Exception
   */
  public ArrayList<T> getAdjNodes(T node) throws Exception {
    if (!this.containsNode(node))
      throw new Exception("Graph getAdjNodes: Graph doesn't contain the specified node");
    
      ArrayList<T> adjList = new ArrayList<>();
    for (T nodesTmp : this.nodeMap.get(node).keySet()) {
      adjList.add(nodesTmp);
    }
    return adjList;
  }

  /**
   * 
   * @return the list of the edges
   */
  public ArrayList<Edge<T, S>> getEdges() {
    ArrayList<Edge<T, S>> edgeList = new ArrayList<Edge<T, S>>();
    for (T nodeTmp : this.nodeMap.keySet()) {
      for (T edgeTmp : this.nodeMap.get(nodeTmp).keySet()) {
        edgeList.add(new Edge<T, S>(nodeTmp, edgeTmp, this.nodeMap.get(nodeTmp).get(edgeTmp)));
      }
    }
    return edgeList;
  }

  /**
   * 
   * @param node1 : first node
   * @param node2 : second node
   * @return the weight of the edge between the specified nodes
   * @throws Exception
   */
  public S getLabel(T node1, T node2) throws Exception {
    if(!this.containsEdge(node1, node2))
      throw new Exception("Graph getLabel: Edge does not exist");
    
    return this.nodeMap.get(node1).get(node2);
  }

  @Override
  public String toString() {
    String res = "";
    for (T vertex : this.getNodes()) {
      try {
        res = res + vertex.toString() + ": " + this.getAdjNodes(vertex).toString() + "\n";
      } catch (Exception e) {
        e.printStackTrace();
      }
    }
    return res;
  }

}