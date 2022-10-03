# CUrlPractice

* Environment
  
  Unix OS (my environment: MSYS2 in Windows)

* Prerequisite of Module/Package

  autoconf automake libtool openssl libcurl

* libcurl installation (refer to https://curl.se/ and https://github.com/curl/curl instructions)
  1. Clone the source code from https://github.com/curl/curl
  2. Open terminal at the root of the git repository (i.e. [User path]/curl/)
  3. Input command "autoreconf -fi"
  4. Input command "./config --with-ssl" or "./config --with-openssl" (can be replaced with any supported ssl pacakge you have)
  5. Input command "make"
  6. Input command "make install"
  7. Input command "curl -V" to check if the curl is installed success and get details (supported protocols)

* Execution
  1. Open terminal at this project folder
  2. Input command "gcc main.c -lcurl"
  3. Input command "./a [URL:PORT]" (ex: ./a www.example.com:1234)
  4. Check the "data.txt" file  
