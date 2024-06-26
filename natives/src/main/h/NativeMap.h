/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class NativeMap */

#ifndef _Included_NativeMap
#define _Included_NativeMap
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     NativeMap
 * Method:    nCreate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_NativeMap_nCreate
  (JNIEnv *, jclass);

/*
 * Class:     NativeMap
 * Method:    nFree
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_NativeMap_nFree
  (JNIEnv *, jclass, jlong);

/*
 * Class:     NativeMap
 * Method:    nContainsKey
 * Signature: (JLjava/lang/Object;)Z
 */
JNIEXPORT jboolean JNICALL Java_NativeMap_nContainsKey
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     NativeMap
 * Method:    nContainsValue
 * Signature: (JLjava/lang/Object;)Z
 */
JNIEXPORT jboolean JNICALL Java_NativeMap_nContainsValue
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     NativeMap
 * Method:    nGet
 * Signature: (JLjava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_NativeMap_nGet
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     NativeMap
 * Method:    nPut
 * Signature: (JLjava/lang/Object;Ljava/lang/Object;Ljava/nio/ByteBuffer;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_NativeMap_nPut
  (JNIEnv *, jclass, jlong, jobject, jobject, jobject);

/*
 * Class:     NativeMap
 * Method:    nRemove
 * Signature: (JLjava/lang/Object;Ljava/nio/ByteBuffer;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_NativeMap_nRemove
  (JNIEnv *, jclass, jlong, jobject, jobject);

/*
 * Class:     NativeMap
 * Method:    nPutAll
 * Signature: (JLjava/util/Set;Ljava/nio/IntBuffer;)V
 */
JNIEXPORT void JNICALL Java_NativeMap_nPutAll
  (JNIEnv *, jclass, jlong, jobject, jobject);

/*
 * Class:     NativeMap
 * Method:    nClear
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_NativeMap_nClear
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
