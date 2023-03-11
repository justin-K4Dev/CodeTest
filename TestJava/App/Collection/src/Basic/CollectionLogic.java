/**
 * Created by justin on 2015-06-09.
 */

package Basic;

import java.util.*;


public class CollectionLogic {

    public static void TestQueue() {

    }

    public static void TestMap() {

        // Algorism Example 1
        {
            // Hashtable 생성
            Hashtable<String, Double> ht = new Hashtable<String, Double>();
            Enumeration<String> names;
            String str;

            ht.put( "영국", new Double( 1240.34 ) );
            ht.put( "베트남", new Double( 223.39 ) );
            ht.put( "중국", new Double( 1378.00 ) );
            ht.put( "일본", new Double( 9999.55 ) );
            ht.put( "대만", new Double( -122.08 ) );
            ht.put( "홍콩",  new Double( 55.77 ) );

            names = ht.keys();
            while ( names.hasMoreElements() ) {
                str = (String) names.nextElement();
                System.out.println(str + ": " + ht.get(str));
            }

            double bonus = ((Double) ht.get("중국")).doubleValue();
            ht.put( "중국", new Double(bonus + 1000) );
            System.out.println( "중국's new deposit: " + ht.get("중국") );
        }

        // Hashtable Example 1
        {
            // Hashtable 생성
            Hashtable<String, Double> ht = new Hashtable<String, Double>();
            Enumeration<String> names;
            String str;

            ht.put( "영국", new Double( 1240.34 ) );
            ht.put( "베트남", new Double( 223.39 ) );
            ht.put( "중국", new Double( 1378.00 ) );
            ht.put( "일본", new Double( 9999.55 ) );
            ht.put( "대만", new Double( -122.08 ) );
            ht.put( "홍콩",  new Double( 55.77 ) );

            names = ht.keys();
            while ( names.hasMoreElements() ) {
                str = (String) names.nextElement();
                System.out.println(str + ": " + ht.get(str));
            }

            double bonus = ((Double) ht.get("중국")).doubleValue();
            ht.put( "중국", new Double(bonus + 1000) );
            System.out.println( "중국's new deposit: " + ht.get("중국") );
        }

        // TreeMap Example 1
        {
            // HashMap 생성
            Map<String, Double> hm = new TreeMap<String, Double>();

            // HashMap 요소 추가
            hm.put("한국", new Double(200.34));
            hm.put("핀란드", new Double(1400.39));
            hm.put("미국", new Double(2300.00));
            hm.put("스웨덴", new Double(5400.55));
            hm.put("abc", new Double(-540.08));
            hm.put("호호", null);

            // HashMap 목록 Set<?> 반환
            Set<?> set = hm.entrySet();

            // Set<?> 반복자 반환
            Iterator<?> i = set.iterator();

            // 반복자 활용 Key-Value 출력
            while( i.hasNext() ) {
                Map.Entry me = ( Map.Entry )i.next();
                System.out.print( me.getKey() + ": " );
                System.out.println( me.getValue() );
            }

            // 특정 Key의 Value 변경
            double bonus = hm.get("스웨덴").doubleValue();
            hm.put( "스웨덴", new Double(bonus + 1000) );
            System.out.println( "스웨덴's new deposit: " + hm.get("스웨덴") );
        }

        // HashMap Example 2
        {
            // HashMap 생성
            Map<String, Double> hm = new HashMap<String, Double>();

            // HashMap 요소 추가
            hm.put("태국", new Double(1240.34));
            hm.put("슬로바키아", new Double(223.39));
            hm.put("벨기에", new Double(1378.00));
            hm.put("네덜란드", new Double(9999.55));
            hm.put("abc", new Double(-122.08));
            hm.put("호호", null);

            // HashMap 목록 Set<?> 반환
            Set<?> set = hm.entrySet();

            // Set<?> 반복자 반환
            Iterator<?> i = set.iterator();

            // 반복자 활용 Key-Value 출력
            while( i.hasNext() ) {
                Map.Entry me = ( Map.Entry )i.next();
                System.out.print( me.getKey() + ": " );
                System.out.println( me.getValue() );
            }

            // 특정 Key의 Value 변경
            double bonus = hm.get("네덜란드").doubleValue();
            hm.put( "네덜란드", new Double(bonus + 1000) );
            System.out.println( "네덜란드's new deposit: " + hm.get("네덜란드") );
        }

        // HashMap Example 1
        {
            Map<Integer, String> map = new HashMap<Integer, String>();

            // Key : no, Value : name - HashMap 요소 추가
            map.put( 1, "Quick" );
            map.put( 2, "Yion" );
            map.put( 3, "GLiDER" );
            map.put( 100, "Wiki" );

            System.out.println( map );
            System.out.println( map.get(100) );

            // 특정 Key-Value 출력
            System.out.println( map.containsKey( 3 ) );
            System.out.println( map.containsValue( "Yion" ) );

            // Key 목록 Set 반환 후 출력
            Set<Integer> keys = map.keySet();
            System.out.println( keys );

            // Value 목록 Collection 반환 후 출력
            Collection<String> values = map.values();
            System.out.println( values );
        }
    }

    public static void TestSet() {

        // TreeSet Example 1
        {
            // TreeSet 생성
            Set<String> ts = new TreeSet<String>();

            // TreeSet 요소 추가
            ts.add( "C" );
            ts.add( "A" );
            ts.add( "B" );
            ts.add( "E" );
            ts.add( "F" );
            ts.add( "D" );

            System.out.println( ts );
        }

        // LinkedHashSet Example 1
        {
            // LinkedHashSet 생성
            Set<String> linkHashSet = new LinkedHashSet<String>();

            // LinkedHashSet 요소 추가
            linkHashSet.add( "B" );
            linkHashSet.add( "A" );
            linkHashSet.add( "D" );
            linkHashSet.add( "E" );
            linkHashSet.add( "C" );
            linkHashSet.add( "F" );

            System.out.println( linkHashSet );
        }

        // HashSet Example 1
        {
            // HashSet 생성
            Set<String> hs = new HashSet<String>();

            // HashSet 요소 추가
            hs.add( "B" );
            hs.add( "A" );
            hs.add( "D" );
            hs.add( "E" );
            hs.add( "C" );
            hs.add( "F" );

            System.out.println( hs );
        }
    }

    public static void TestList() {

        // LinkedList 응용 Example 1
        {
            // LinkedList 생성
            LinkedList<Integer> ll = new LinkedList<Integer>();
            ll.add(new Integer(-8));
            ll.add(new Integer(20));
            ll.add(new Integer(-20));
            ll.add(new Integer(8));

            // 역순의 비교자를 생성.
            Comparator<Integer> r = Collections.reverseOrder();

            // 비교자를 사용해서 리스트 정렬
            Collections.sort(ll, r);

            // 반복자 반환
            Iterator<Integer> li = ll.iterator();

            System.out.print("List sorted in reverse: ");
            while (li.hasNext()) {
                System.out.print(li.next() + " ");
            }
            System.out.println();

            // LinkedList 임의로 섞음
            Collections.shuffle(ll);

            // 임의의 리스트 출력
            li = ll.iterator();
            System.out.print("List shuffled: ");

            while (li.hasNext()) {
                System.out.print(li.next() + " ");
            }

            System.out.println("Minimum: " + Collections.min(ll));
            System.out.println("Maximum: " + Collections.max(ll));
        }

        // LinkedList Example 1
        {
            // LinkedList 생성
            LinkedList<String> ll = new LinkedList<String>();

            // LinkedList 요소 추가
            ll.add( "F" );
            ll.add( "B" );
            ll.add( "D" );
            ll.add( "E" );
            ll.add( "C" );
            ll.addLast( "Z" );
            ll.addFirst( "A" );

            ll.add( 1, "A2" );

            System.out.println( "Original contents of ll: " + ll );

            // LinkedList 특정 요소 제거
            ll.remove( "F" );
            ll.remove( 2 ); // index 기반 제거

            System.out.println( "Contents of ll after deletion: " + ll );

            // LinkedList 특정 위치 제거
            ll.removeFirst();
            ll.removeLast();
            System.out.println( "ll after deleting first and last: " + ll );

            // LinkedList 특정 위치 반환 & Value 변경
            Object val = ll.get(2);
            ll.set( 2, (String) val + " Changed" );

            // LinkedList 출력
            System.out.println( "ll after change: " + ll );
        }

        // ArrayList Example 2
        {
            // ArrayList 생성
            List<Integer> al = new ArrayList<Integer>();

            // ArrayList 요소 추가
            al.add( new Integer(1) );
            al.add( new Integer(2) );
            al.add( new Integer(3) );
            al.add( new Integer(4) );

            // ArrayList 요소 출력
            System.out.println( "Contents of al: " + al );

            // ArrayList => Array 변환
            Object ia[] = al.toArray();
            int sum = 0;

            // 배열 Value 연산 & 출력
            for( int i = 0; i < ia.length; i++ ) {
                sum += ((Integer) ia[i]).intValue();
            }
            System.out.println( "Sum is: " + sum );
        }

        // ArrayList Example 1
        {
            // ArrayList 생성
            List<String> al = new ArrayList<String>();
            System.out.println( "Initial size of ArrayList: " + al.size() );

            // ArrayList 요소 추가
            al.add( "C" );
            al.add( "A" );
            al.add( "E" );
            al.add( "B" );
            al.add( "D" );
            al.add( "F" );
            al.add( 1, "A2" );  // 배열 index 에 요소 추가
            System.out.println( "Size of al after additions: " + al.size() );

            // ArrayList 요소 출력
            System.out.println( "Contents of al: " + al );

            // ArrayList 특정 요소 제거
            al.remove("F");
            al.remove(2); // index 기반 제거

            System.out.println( "Size of al after deletions: " + al.size() );
            System.out.println( "Contents of al: " + al );
        }
    }

    public static void TestArray() {

        // int 배열 생성 & 할당
        int[] idxList = new int[5];

        // string 배열 생성 & 할당
        String[] userInfoList = new String[10];

        // string 배열 생성 & 할당 & 출력
        String[] userInfoPool = new String[] { "one", "two" };
        for( int i = 0; i < userInfoPool.length; i++ ) {
            String value = userInfoPool[i];
            System.out.println( "Pool Value : " + value );
        }
    }
}
