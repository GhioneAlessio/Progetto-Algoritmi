package src;

import java.util.Comparator;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import org.junit.Before;
import org.junit.Test;

/*
 * Test suite for the Heap library
 */

public class HeapTests {

  class IntegerComparator implements Comparator<Integer>{
    @Override  
    public int compare(Integer i1, Integer i2) {
      return (i1.compareTo(i2));
    }
  }

  class StringComparator implements Comparator<String>{
    @Override  
    public int compare(String s1, String s2) {
      return (s1.compareTo(s2));
    }
  }

  private Integer i1, i2, i3, i4, i5, i6;
  private String s1, s2, s3;
  private Heap<Integer> intHeap;
  private Heap<String> strHeap;

  @Before
  public void createHeap() throws Exception{
    i1 = -12;
    i2 = 0;
    i3 = 4;
    i4 = 7;
    i5 = 10;
    i6 = 13;
    s1 = "alpha";
    s2 = "beta";
    s3 = "gamma";
    intHeap = new Heap<>(new IntegerComparator());
    strHeap = new Heap<>(new StringComparator());
  }

  @Test
  public void testSize_zeroEl(){
    assertEquals(0,intHeap.getSize());
  }

  @Test
  public void testSizeInsertInt_oneEl(){
    intHeap.heapInsert(i1);
    assertEquals(1,intHeap.getSize());
  }
  
  @Test
  public void testSizeInsertInt_threeEl(){
    intHeap.heapInsert(i1);
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    assertEquals(3,intHeap.getSize());
  }

  @Test
  public void testGetMinElementInt(){
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.heapInsert(i1);
    assertTrue(i1==intHeap.getMinElement());
  }

  @Test
  public void testLeftElemInt() throws Exception{
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.heapInsert(i1);
    assertTrue(i3==intHeap.leftElem(i1));
  }

  @Test
  public void testRightElemInt() throws Exception{
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.heapInsert(i1);
    assertTrue(i2==intHeap.rightElem(i1));
  }

  @Test
  public void testParentElemInt() throws Exception{ 
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.heapInsert(i1);
    assertTrue(i1==intHeap.parentElem(i2));
  }

  @Test
  public void testExtractGetMinInt() throws Exception{
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.heapInsert(i1);
    intHeap.extractMin();
    assertFalse(i1==intHeap.getMinElement());
  }

  @Test
  public void testDecreaseElemInt() throws Exception{
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.decreaseElement(i2, i1);
    assertTrue(i1==intHeap.getMinElement());
  }

  @Test
  public void testGetMinElementInt_moreEl(){
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.heapInsert(i6);
    intHeap.heapInsert(i4);
    intHeap.heapInsert(i1);
    intHeap.heapInsert(i5);
    assertTrue(i1==intHeap.getMinElement());
  }

  @Test
  public void testLeftElemInt_moreEl() throws Exception{
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.heapInsert(i6);
    intHeap.heapInsert(i4);
    intHeap.heapInsert(i1);
    intHeap.heapInsert(i5);
    assertTrue(i6==intHeap.leftElem(i5));
  }

  @Test
  public void testRightElemInt_moreEl() throws Exception{
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.heapInsert(i6);
    intHeap.heapInsert(i4);
    intHeap.heapInsert(i1);
    intHeap.heapInsert(i5);
    assertTrue(i3==intHeap.rightElem(i2));
  }

  @Test
  public void testParentElemInt_moreEl() throws Exception{
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.heapInsert(i6);
    intHeap.heapInsert(i4);
    intHeap.heapInsert(i1);
    intHeap.heapInsert(i5);
    assertTrue(i2==intHeap.parentElem(i4));
  }

  @Test
  public void testExtractGetMinInt_moreEl() throws Exception{
    intHeap.heapInsert(i2);
    intHeap.heapInsert(i3);
    intHeap.heapInsert(i6);
    intHeap.heapInsert(i4);
    intHeap.heapInsert(i1);
    intHeap.heapInsert(i5);
    intHeap.extractMin();
    assertTrue(i2==intHeap.getMinElement());
  }

  @Test
  public void testSizeInsertStr_oneEl(){
    strHeap.heapInsert(s1);
    assertEquals(1,strHeap.getSize());
  }
  
  @Test
  public void testSizeInsertStr_threeEl(){
    strHeap.heapInsert(s1);
    strHeap.heapInsert(s2);
    strHeap.heapInsert(s3);
    assertEquals(3,strHeap.getSize());
  }

  @Test
  public void testGetMinElementStr(){
    strHeap.heapInsert(s2);
    strHeap.heapInsert(s3);
    strHeap.heapInsert(s1);
    assertTrue(s1.equals(strHeap.getMinElement()));
  }

  @Test
  public void testLeftElemStr() throws Exception{
    strHeap.heapInsert(s2);
    strHeap.heapInsert(s3);
    strHeap.heapInsert(s1);
    assertTrue(s3.equals(strHeap.leftElem(s1)));
  }

  @Test
  public void testRightElemStr() throws Exception{
    strHeap.heapInsert(s2);
    strHeap.heapInsert(s3);
    strHeap.heapInsert(s1);
    assertTrue(s2.equals(strHeap.rightElem(s1)));
  }

  @Test
  public void testParentElemStr() throws Exception{
    strHeap.heapInsert(s2);
    strHeap.heapInsert(s3);
    strHeap.heapInsert(s1);
    assertTrue(s1.equals(strHeap.parentElem(s2)));
  }

  @Test
  public void testExtractGetMinStr() throws Exception{
    strHeap.heapInsert(s2);
    strHeap.heapInsert(s3);
    strHeap.heapInsert(s1);
    strHeap.extractMin();
    assertFalse(s1.equals(strHeap.getMinElement()));
  }

  @Test
  public void testDecreaseElemStr() throws Exception{
    strHeap.heapInsert(s2);
    strHeap.heapInsert(s3);
    strHeap.decreaseElement(s2, s1);
    assertTrue(s1.equals(strHeap.getMinElement()));
  } 
}
