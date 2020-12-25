# Jdlib
Java Wrapper For dlib


## Using Jdlib
JAR files contains binaries of Jdlib on current supprted platforms (Linux and Mac OS X).

Also you can have everything downloaded and installed automatically with Maven after including the next dependency inside the pom.xml.

```
<dependency>
  <groupId>com.emaraic</groupId>
  <artifactId>jdlib</artifactId>
  <version>1.0.0</version>
</dependency>
```

## Compiling Jdlib
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

After that you will have the JAR file including the binaries for your platform inside Jdlib/target. 

