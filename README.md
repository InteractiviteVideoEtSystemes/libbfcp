# libbfcp
Lib BFCP (fork from libbfcp)

An open source BFCP (Binary Floor Control Protocol, RFC4582) library written in C
and C++. Repackaged and modified for IVeS solutions. Fork from the libbfcp written
by Lorenzo Miniero (see Confiance open source project)


## Build instructions

The instructions below were tested on CentOS 6 64 bits.

1- Install prerequistes

  # yum install gcc-c++, make, rpm-build


2- Produce the RPM package

Do not compile as root but use a normal linux user

   $ git clone http://github.com/neutrino38/libbfcp  
   $ cd libbfcp
   $ ./install.ksh rpm nosign

3- Install the RPM package

  $ su
  Password: xxxxx
  # rpm -ivh libbfcp-x.y.z-t.ives.el6.x86_64.rpm

Libraries are compiled in both debug and release mode. They are located in

/opt/ives/lib64

Header files are located in 

/opt/ives/include
