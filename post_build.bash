#!/bin/bash
sudo yum -y remove libbfcp
sudo yum localinstall --nogpgcheck -y libbfcp*.rpm
ENVOYER_VISIO2=$1
if [ "$ENVOYER_VISIO2" != "" ] 
then
    echo "On envoie sur visio2"
    scp -oPort=2222 *.rpm jenkins@visio2.visioassistance.net:/home/jenkins/$NODE_NAME
else
    echo "On n'envoie rien sur visio2"
fi

