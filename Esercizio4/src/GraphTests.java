import graph.*;

import java.util.ArrayList;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import org.junit.Before;
import org.junit.Test;

/*
 * Test suite for Graph
 */

public class GraphTests {

  private Integer n1, n2, n3, e1, e2, e3;
  private Graph<Integer, Integer> intGraph;

  @Before
  public void createGraph() throws Exception{
    n1 = 1;
    n2 = 3;
    n3 = 5;
    e1 = 2;
    e2 = 4;
    e3 = 6;
    intGraph = new Graph<>(true);
  }
 
  @Test
  public void testIsDirected(){
    assertTrue(intGraph.isDirected());
  }

  @Test
  public void testAddContainsNode() throws Exception{
    intGraph.addNode(n1);
    assertTrue(intGraph.containsNode(n1));
  }
  
  @Test
  public void testAddContainsEdge() throws Exception{
    intGraph.addNode(n1);
    intGraph.addNode(n2);
    intGraph.addEdge(n1, n2, e1);
    assertTrue(intGraph.containsEdge(n1, n2));
  }

  @Test
  public void testRemoveNode() throws Exception{
    intGraph.addNode(n1);
    intGraph.removeNode(n1);
    assertFalse(intGraph.containsNode(n1));
  }

  @Test
  public void testRemoveEdge() throws Exception{
    intGraph.addNode(n1);
    intGraph.addNode(n2);
    intGraph.addEdge(n1, n2, e1);
    intGraph.removeEdge(n1, n2);
    assertFalse(intGraph.containsEdge(n1, n2));
  }

  @Test
  public void testGetNodesNum_zeroNodes(){
    assertEquals(0, intGraph.getNodesNum());
  }

  @Test 
  public void testGetNodesNum_threeNodes() throws Exception{
    intGraph.addNode(n1);
    intGraph.addNode(n2);
    intGraph.addNode(n3);
    assertEquals(3, intGraph.getNodesNum());
  }

  @Test 
  public void testGetEdgesNum_zeroEdges(){
    assertEquals(0, intGraph.getEdgesNum());
  }

  @Test 
  public void testGetEdgesNum_twoEdges() throws Exception{
    intGraph.addNode(n1);
    intGraph.addNode(n2);
    intGraph.addNode(n3);
    intGraph.addEdge(n1, n2, e1);
    intGraph.addEdge(n2, n3, e2);
    assertEquals(2, intGraph.getEdgesNum());
  }

  @Test 
  public void testGetLabel() throws Exception{
    intGraph.addNode(n1);
    intGraph.addNode(n2);
    intGraph.addEdge(n1, n2, e1);
    assertEquals(e1, intGraph.getLabel(n1, n2));
  }

  @Test 
  public void testGetNodes() throws Exception{
    ArrayList<Integer> listExpected = new ArrayList<Integer>();
    listExpected.add(n1);
    listExpected.add(n2);
    listExpected.add(n3);
    intGraph.addNode(n1);
    intGraph.addNode(n2);
    intGraph.addNode(n3);
    assertEquals(listExpected, intGraph.getNodes());
  }

  @Test 
  public void testGetEdges() throws Exception{
    ArrayList<Edge<Integer, Integer>> listExpected = new ArrayList<Edge<Integer, Integer>>();
    listExpected.add(new Edge<Integer, Integer>(n1, n2, e1));
    listExpected.add(new Edge<Integer, Integer>(n2, n3, e2));
    intGraph.addNode(n1);
    intGraph.addNode(n2);
    intGraph.addNode(n3);
    intGraph.addEdge(n1, n2, e1);
    intGraph.addEdge(n2, n3, e2);
    assertEquals(listExpected, intGraph.getEdges());
  }

  @Test 
  public void testGetAdjNodes() throws Exception{
    ArrayList<Integer> listExpected = new ArrayList<Integer>();
    listExpected.add(n2);
    listExpected.add(n3);
    intGraph.addNode(n1);
    intGraph.addNode(n2);
    intGraph.addNode(n3);
    intGraph.addEdge(n1, n2, e1);
    intGraph.addEdge(n1, n3, e2);
    assertEquals(listExpected, intGraph.getAdjNodes(n1));
  }

}
