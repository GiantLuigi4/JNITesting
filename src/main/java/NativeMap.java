import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.util.Collection;
import java.util.Map;
import java.util.Set;

public class NativeMap<K, V> implements Map<K, V> {
    private int size;
    private final long handle;
    private final ByteBuffer incrementTracker = ByteBuffer.allocateDirect(1);

    public NativeMap() {
        this.size = 0;
        this.handle = nCreate();
    }

    boolean freed = false;

    public void free() {
        if (!freed) {
            nFree(handle);
            freed = true;
        }
    }

    @Override
    protected void finalize() throws Throwable {
        free();
    }

    public static native long nCreate();

    public static native long nFree(long handle);

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public boolean containsKey(Object key) {
        return nContainsKey(handle, key);
    }

    public static native boolean nContainsKey(long handle, Object key);

    @Override
    public boolean containsValue(Object value) {
        return nContainsValue(handle, value);
    }

    public static native boolean nContainsValue(long handle, Object key);

    @Override
    public V get(Object key) {
        return (V) nGet(handle, key);
    }

    public static native Object nGet(long handle, Object key);

    @Override
    public V put(K key, V value) {
        Object res = nPut(handle, key, value, incrementTracker);
        size += incrementTracker.get(0);
        return (V) res;
    }

    public static native Object nPut(long handle, Object key, Object value, ByteBuffer tracker);

    @Override
    public V remove(Object key) {
        Object res = nRemove(handle, key, incrementTracker);
        size -= incrementTracker.get(0);
        return (V) res;
    }

    public static native Object nRemove(long handle, Object key, ByteBuffer tracker);

    @Override
    public void putAll(Map<? extends K, ? extends V> m) {
        IntBuffer incrementTracker = ByteBuffer.allocateDirect(4).asIntBuffer();
        // generics are a meme in java
        //noinspection unchecked
        nPutAll(handle, (Set<? extends Entry<Object, Object>>) (Object) m.entrySet(), incrementTracker);
        size += incrementTracker.get(0);
    }

    public static native void nPutAll(long handle, Set<? extends Entry<Object, Object>> entries, IntBuffer incrementTracker);

    @Override
    public void clear() {
        nClear(handle);
        size = 0;
    }

    public static native void nClear(long handle);

    @Override
    public Set<K> keySet() {
        return null;
    }

    @Override
    public Collection<V> values() {
        return null;
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        return null;
    }
}
