package src;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Set;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

public class Main_ex4 implements Comparator<Float> {
  public static void main(String[] args) throws Exception {
    Graph<String, Double> graph = new Graph<String, Double>(false);
    load_file(args[0], graph);

    Graph<String, Double> shortestPath = dijkstra(graph, "torino");

    ArrayList<String> path = bfs(shortestPath, "torino", "catania");
    System.out.println("path = size " + path.size());
    System.out.print(path);
    System.out.println();
    int dist = 0;
    String tmp = path.get(0);
    for (int i = 1; i < path.size(); i++) {
      dist += shortestPath.getLabel(tmp, path.get(i));
      tmp = path.get(i);
    }
    System.out.println("distanza torino - catania = " + (double) dist / 1000 + " km");
  }

  public static void load_file(String file_name, Graph<String, Double> graph) throws Exception {
    File file;
    Scanner scanner = null;
    try {
      file = new File(file_name);
      scanner = new Scanner(file);
    } catch (FileNotFoundException e) {
      System.out.println("load_file: error detected.");
    }

    while (scanner.hasNextLine()) {
      String tmp = scanner.nextLine();
      String[] split = tmp.split(",");
      String city1 = split[0];
      String city2 = split[1];
      Double dist = Double.parseDouble(split[2]);
      if (!graph.containsNode(city1))
        graph.addNode(city1);
      if (!graph.containsNode(city2))
        graph.addNode(city2);
      if (!graph.containsEdge(city1, city2))
        graph.addEdge(city1, city2, dist);
    }
    scanner.close();
  }

  public static Graph<String, Double> dijkstra(Graph<String, Double> graph, String sourceCity) throws Exception {

    Graph<String, Double> shortestPath = new Graph<String, Double>(true);

    Heap<WeightedNode<String, Double>> priorityQueue = new Heap<>(
        Comparator.comparing((WeightedNode<String, Double> n) -> n.getWeight())); 

    HashMap<String, WeightedNode<String, Double>> weightedNodeMap = new HashMap<>();
    ArrayList<String> nodesList = graph.getNodes();

    for (int i = 0; i < nodesList.size(); i++) {
      WeightedNode<String, Double> tmp = new WeightedNode<String, Double>(nodesList.get(i),
          Double.POSITIVE_INFINITY, "");
      priorityQueue.heapInsert(tmp);
      weightedNodeMap.put(tmp.getNode(), tmp);
    }
    priorityQueue.decreaseElement(weightedNodeMap.get(sourceCity), new WeightedNode<String, Double>(sourceCity, 0.0, null));

    while (priorityQueue.getSize() != 0) {
      WeightedNode<String, Double> u = priorityQueue.extractMin();
      
      shortestPath.addNode(u.getNode());
      String uName = u.getNode();
      if (graph.containsEdge(weightedNodeMap.get(uName).getPrevious(), uName))
        shortestPath.addEdge(weightedNodeMap.get(uName).getPrevious(), uName, graph.getLabel(weightedNodeMap.get(uName).getPrevious(), uName));

      ArrayList<String> adjList = graph.getAdjNodes(uName);

      for (int i = 0; i < adjList.size(); i++) {
        String vAdj = adjList.get(i);
        Double newDistance = u.getWeight() + graph.getLabel(u.getNode(), vAdj);

        if (weightedNodeMap.containsKey(vAdj) && weightedNodeMap.get(vAdj).getWeight() > newDistance  ) {
          weightedNodeMap.get(vAdj).setWeight(newDistance);
          weightedNodeMap.get(vAdj).setPrevious(u.getNode());
          priorityQueue.decreaseElement(weightedNodeMap.get(vAdj),
          new WeightedNode<String, Double>(vAdj, newDistance, u.getNode()));
        }
      }
      weightedNodeMap.remove(u.getNode());
    }
    return shortestPath;
  }

  @Override
  public int compare(Float weight1, Float weight2) {
    if (weight1 < weight2)
      return -1;
    return 0;
  }

  public static ArrayList<String> bfs(Graph<String, Double> graph, String source, String destination) throws Exception {
    Queue<String> queue = new LinkedList<>();
    Set<String> visited = new HashSet<>();
    HashMap<String, String> previous = new HashMap<>();

    queue.add(source);
    visited.add(source);
    previous.put(source, null);

    while (!queue.isEmpty()) {
      String node = queue.poll();
      if (node.equals(destination)) {
        break;
      }
      ArrayList<String> adjList = graph.getAdjNodes(node);
      for (int i = 0; i < adjList.size(); i++) {
        String nodeTmp = adjList.get(i);
        if (!visited.contains(nodeTmp)) {
          queue.add(nodeTmp);
          visited.add(nodeTmp);
          previous.put(nodeTmp, node);
        }
      }
    }

    ArrayList<String> path = new ArrayList<>();
    String node = destination;

    while (previous.get(node) != null) {
      path.add(0, node);
      node = previous.get(node);
    }

    path.add(0, node);
    return path;
  }
}