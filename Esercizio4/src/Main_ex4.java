package src;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;


public class Main_ex4 {
  public static void main(String[] args) throws Exception {
    ArrayList<Dist> record = new ArrayList<Dist>();
    load_file(args[0], record);
    Graph<Dist, Integer> graph = new Graph<Dist, Integer>(true);
    for(int i = 0; i<record.size(); i++){
      Dist tmp = record.get(i);
      graph.addNode(tmp); 
    }
    graph.add_edge(record.get(1), record.get(2), 3);
    graph.add_edge(record.get(1), record.get(5), 5);
    System.out.println("nodes num = " + graph.get_nodes_num());
    System.out.println("edges num = " + graph.get_edges_num());
    System.out.println("contains edge = " + graph.contains_edge(record.get(1), record.get(2)));
    System.out.println("contains node = " + graph.contains_node(record.get(1)));
    // graph.remove_node(record.get(1));
    System.out.println("nodes num = " + graph.get_nodes_num());
    System.out.println("edges num = " + graph.get_edges_num());
    System.out.println("contains node = " + graph.contains_node(record.get(1)));
    System.out.println("contains edge = " + graph.contains_edge(record.get(1), record.get(2)));
  }

  public static void load_file(String file_name, ArrayList<Dist> record){
    
    try{
      File file = new File(file_name);
      Scanner scanner = new Scanner(file);
      while(scanner.hasNextLine()){
        String tmp = scanner.nextLine();
        String[] split = tmp.split(",");
        String part1 = split[0]; 
        String part2 = split[1]; 
        float part3 = Float.parseFloat(split[2]);
        record.add(new Dist(part1, part2, part3));
      }
      scanner.close();    
    }catch(FileNotFoundException e){
      System.out.println("load_file: error detected.");
      e.printStackTrace();
    }
    }
}
  