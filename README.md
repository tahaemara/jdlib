# Jdlib
Java Wrapper For dlib for Linux and MacOSX. Till now the wrapper contains stubs for face HOG detector, facial landmarks, face embedding models. 


## Demo
### Face Clustering Example
<img src="https://media.giphy.com/media/FD9AfNUw3VX8CqYaph/giphy.gif" width="700" height="400" />

## Using Jdlib
JAR files contains binaries of Jdlib on current supprted platforms (Linux and Mac OS X) inside [releases](https://github.com/tahaemara/jdlib/releases).

Also you can have everything downloaded and installed automatically with Maven after including the next dependency inside the pom.xml.

```
<dependency>
  <groupId>com.emaraic</groupId>
  <artifactId>jdlib</artifactId>
  <version>1.0.1</version>
</dependency>
```

## Compiling Jdlib

### Requirments:
- Dlib installation requirments [Using dlib from C++](http://dlib.net/compile.html)
- JDK 8 or latter
- Maven

### Clone project:
```
$ git clone https://github.com/tahaemara/jdlib.git
```

### Compile JNI/C++ code:
```
$ cd jdlib/jni
$ mkdir build
$ cd build
$ cmake ..
$ make 
```
### Compile Java Package:

```
$ cd ../../Jdlib
$ mvn package
```

After that you will have the JAR file including the binaries for your platform inside Jdlib/target. Then you can use it inside your project as an external jar or install it manually in [local maven](https://maven.apache.org/guides/mini/guide-3rd-party-jars-local.html). 

## Compiling and running examples

- Download needed models to example folder
```
$ cd examples
$ wget http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2
$ wget http://dlib.net/files/dlib_face_recognition_resnet_model_v1.dat.bz2
```
- Unzip model
```
$ bzip2 -dk shape_predictor_68_face_landmarks.dat.bz2
$ bzip2 -dk dlib_face_recognition_resnet_model_v1.dat.bz2
```
- Change Diectory to an example folder such as faces_clustering:
```
cd examples/faces_clustering/
```
- Build package via maven
```
mvn package
```
- Run example
```
java -jar target/JdlibExamples-1.0.0-jar-with-dependencies.jar
```
