#!/bin/bash
rm -f *.rpm
sudo yum -y remove "libbfcp*"
./install.ksh rpm nosign

