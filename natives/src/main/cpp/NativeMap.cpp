#include <pch.h>
#include <NativeMap.h>

#define JNI_MAP std::map<JKey,jobject>
#define byte uint8_t

class JKey {
public:
    JNIEnv* env;
    jobject obj;
    jmethodID hashCodeMID;
    jmethodID equalsMID;

    JKey(JNIEnv* env, jobject obj) : env(env), obj(obj) {
        jclass clz = env->GetObjectClass(obj);
        hashCodeMID = env->GetMethodID(clz, "hashCode", "()I");
        equalsMID = env->GetMethodID(clz, "equals", "(Ljava/lang/Object;)Z");
    }

    int hashCode() const {
        return env->CallIntMethod(obj, hashCodeMID);
    }

    bool operator<(const JKey& other) const {
        return hashCode() < other.hashCode();
    }
    bool operator<=(const JKey& other) const {
        return hashCode() <= other.hashCode();
    }
    bool operator>=(const JKey& other) const {
        return hashCode() >= other.hashCode();
    }
    bool operator>(const JKey& other) const {
        return hashCode() > other.hashCode();
    }

    bool operator!=(const JKey& other) const {
        return !(env->CallBooleanMethod(obj, equalsMID, other.obj));
    }
    bool operator==(const JKey& other) const {
        return env->CallBooleanMethod(obj, equalsMID, other.obj);
    }
};

JNIEXPORT jlong JNICALL Java_NativeMap_nCreate
  (JNIEnv *, jclass) {
    void* rawMemory = std::calloc(1, sizeof(JNI_MAP));
//    JNI_MAP* myMapPtr = new (rawMemory) JNI_MAP();
    new (rawMemory) JNI_MAP();
    return (jlong) rawMemory;
}

JNIEXPORT void JNICALL Java_NativeMap_nFree
  (JNIEnv *, jclass, jlong handle) {
  JNI_MAP* ptr = (JNI_MAP*) handle;
  free(ptr);
}

JNIEXPORT jboolean JNICALL Java_NativeMap_nContainsKey
  (JNIEnv *env, jclass, jlong handle, jobject key) {
    JNI_MAP* ptr = (JNI_MAP*) handle;

    JKey jKey = JKey(env, key);
    return ptr->count(jKey) != 0;
}

JNIEXPORT jboolean JNICALL Java_NativeMap_nContainsValue
  (JNIEnv *, jclass, jlong handle, jobject value) {
    JNI_MAP* ptr = (JNI_MAP*) handle;
    for (std::pair<JKey,jobject> pair : *ptr) {
        if (pair.second == value) {
            return true;
        }
    }
    return false;
}

JNIEXPORT jobject JNICALL Java_NativeMap_nGet
  (JNIEnv *env, jclass, jlong handle, jobject key) {
    JNI_MAP* ptr = (JNI_MAP*) handle;

    JKey jKey = JKey(env, key);
    auto it = ptr->find(jKey);

    bool isNewEntry = (it == ptr->end());

    if (isNewEntry) {
        return nullptr;
    } else {
        return (jobject) it->second;
    }
}

JNIEXPORT jobject JNICALL Java_NativeMap_nPut
  (JNIEnv *env, jclass, jlong handle, jobject key, jobject value, jobject incrementTracker) {
    byte* buf = (byte*) ((env)->GetDirectBufferAddress(incrementTracker));

    JNI_MAP* ptr = (JNI_MAP*) handle;

    JKey jKey = JKey(env, key);
    auto it = ptr->find(jKey);

    bool isNewEntry = (it == ptr->end());

    jobject old = nullptr;
    if (isNewEntry) {
        buf[0] = 1;
    } else {
        old = it->second;
        buf[0] = 0;
        ptr->erase(it); // Efficiently erase using iterator
    }

    ptr->insert(std::make_pair(jKey, value));

    return (jobject) old;
}

JNIEXPORT jobject JNICALL Java_NativeMap_nRemove
  (JNIEnv *env, jclass, jlong handle, jobject key, jobject incrementTracker) {
    byte* buf = (byte*) ((env)->GetDirectBufferAddress(incrementTracker));

    JNI_MAP* ptr = (JNI_MAP*) handle;

    JKey jKey = JKey(env, key);
    auto it = ptr->find(jKey);

    bool isNewEntry = (it == ptr->end());

    jobject old = nullptr;
    if (isNewEntry) {
        buf[0] = 0;
    } else {
        old = it->second;
        buf[0] = 1;
        ptr->erase(it); // Efficiently erase using iterator
    }

    return (jobject) old;
}

JNIEXPORT void JNICALL Java_NativeMap_nPutAll
  (JNIEnv *, jclass, jlong handle, jobject, jobject) {
  JNI_MAP* ptr = (JNI_MAP*) handle;
  // !TODO: implement
}

JNIEXPORT void JNICALL Java_NativeMap_nClear
  (JNIEnv *, jclass, jlong handle) {
  JNI_MAP* ptr = (JNI_MAP*) handle;
  ptr->clear();
}
