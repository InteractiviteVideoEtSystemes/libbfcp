#!/bin/bash

#Nom du paquetage 
PROJET=libbfcp


#Preparation du fichier spec de packaging rpm
function prepare_spec
{
    #Architecture
    SRVARCH=`uname -i`
    #Check Fedora
    rpm -q fedora-release > /dev/null
    fcres=$?
    #Check CentOS
    rpm -q centos-release > /dev/null
    cosres=$?
    #Fedora Core Version
    if [ ${fcres} -eq 0 ]
       then
       FCV=`rpm -q fedora-release | sed s/fedora-release-// | sed s/-.*//`
       sed s/ives_distrib/ives.fc${FCV}/g ${PROJET}.spec.ives > ${PROJET}.spec.tmp
       sed s/ives_archi/${SRVARCH}/g ${PROJET}.spec.tmp > ${PROJET}.spec
        rm ${PROJET}.spec.tmp
    #CentOS Version
    elif [ ${cosres} -eq 0 ]
       then
       COSV=`rpm -q centos-release | sed s/centos-release-// | sed s/-.*//`
       sed s/ives_distrib/ives.el${COSV}/g ${PROJET}.spec.ives > ${PROJET}.spec.tmp
       sed s/ives_archi/${SRVARCH}/g ${PROJET}.spec.tmp > ${PROJET}.spec
	rm ${PROJET}.spec.tmp
    else
       echo "Erreur: On n'a pas trouve de distribution Fedora, ou CentOS !"
       exit
    fi
}


#Creation de l'environnement de packaging rpm
function create_rpm
{
    #Cree l'environnement de creation de package
    #Creation des macros rpmbuild
    rm ~/.rpmmacros
    touch ~/.rpmmacros
    echo "%_topdir" $PWD"/rpmbuild" >> ~/.rpmmacros
    echo "%_tmppath %{_topdir}/TMP" >> ~/.rpmmacros
    echo "%_signature gpg" >> ~/.rpmmacros
    echo "%_gpg_name IVeSkey" >> ~/.rpmmacros
    echo "%_gpg_path" $PWD"/gnupg" >> ~/.rpmmacros
    echo "%vendor IVeS" >> ~/.rpmmacros
    #Import de la clef gpg IVeS
    if [[ -z $1 || $1 -ne nosign ]]
    then
    	svn export https://svn.ives.fr/svn-libs-dev/gnupg
    fi
    mkdir -p rpmbuild
    mkdir -p rpmbuild/SOURCES
    mkdir -p rpmbuild/SPECS
    mkdir -p rpmbuild/BUILD
    mkdir -p rpmbuild/SRPMS
    mkdir -p rpmbuild/TMP
    mkdir -p rpmbuild/RPMS
    mkdir -p rpmbuild/RPMS/noarch
    mkdir -p rpmbuild/RPMS/i386
    mkdir -p rpmbuild/RPMS/x86_64
    #Recuperation de la description du package 
    cd ./rpmbuild/SPECS/
    cp ../../${PROJET}.spec ${PROJET}.spec
    cd ../../
    #Cree le package
   if [[ -z $1 || $1 -ne nosign ]]
    then
                rpmbuild -bb --sign $PWD/rpmbuild/SPECS/${PROJET}.spec
   else
             rpmbuild -bb $PWD/rpmbuild/SPECS/${PROJET}.spec
    fi
    if [ $? == 0 ]
    then
        echo "************************* fin du rpmbuild ****************************"
        #Recuperation du rpm
        mv -f $PWD/rpmbuild/RPMS/i386/*.rpm $PWD/.
        mv -f $PWD/rpmbuild/RPMS/x86_64/*.rpm $PWD/.
    fi
    clean
}

function clean
{
  	# On efface les liens ainsi que le package precedemment cr��
  	echo Effacement des fichiers et liens gnupg rpmbuild ${PROJET}.rpm ${TEMPDIR}/${PROJET}
  	rm -rf gnupg rpmbuild ${PROJET}.rpm ${TEMPDIR}/${PROJET}
}

case $1 in
  	"clean")
  		echo "Nettoyage des liens et du package crees par la cible dev"
  		clean ;;
  	"rpmInstall")
  		#rpmInstall est appele automatiquement par le script de creation de rpm
  		echo "Copie des fichiers du rpm dans la localisation temporaire"
  		copy_rpmInstall $2;;
  	"rpm")
  		echo "Creation du rpm"
                prepare_spec
  		create_rpm $2 ;;
  	*)
  		echo "usage: install.ksh [options]" 
  		echo "options :"
  		echo "  rpm		Generation d'un package rpm"
  		echo "  clean		Nettoie tous les fichiers cree par le present script, liens, tar.gz et rpm";;
esac
