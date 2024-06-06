// this is cursed!
public class MapTest {
    // does not segfault
//    public static void main(String[] args) {
//        System.loadLibrary("test-natives");
//
//        NativeMap<String, String> test = new NativeMap<>();
//
//        String key = "Hello!";
//        String value = "42";
//
//        System.out.println(test.size());
//        test.clear();
//        Object o = test.put(key, value);
//        System.out.println(o);
//        System.out.println(test.size());
//        o = test.put(key, value);
//        System.out.println(o);
//        System.out.println(test.size());
//        o = test.get(key);
//        System.out.println(o);
//
//        System.out.println(value);
//    }

    // segfaults
    public static void main(String[] args) {
        System.loadLibrary("test-natives");

        NativeMap<String, String> test = new NativeMap<>();

        String key = "Hello!";
        String value = "42";

        System.out.println(test.size());
        test.clear();
        System.out.println(test.put(key, value));
        System.out.println(test.size());
        Object o = test.put(key, value);
        System.out.println(o);
        System.out.println(test.size());
        o = test.get(key);
        System.out.println(o);

        System.out.println(value);
    }
}
